package com.ensim.TP3.controller;

import com.ensim.TP3.Tp3Application;
import com.ensim.TP3.model.Weather;
import com.fasterxml.jackson.databind.JsonNode;
import com.fasterxml.jackson.databind.ObjectMapper;
import org.json.JSONException;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.*;
import org.springframework.web.client.RestTemplate;
import org.json.JSONArray;
import org.json.JSONObject;

import java.io.IOException;


@Controller
public class MeteoController {


    private static final Logger log = LoggerFactory.getLogger(Tp3Application.class);

    @Autowired
    RestTemplate restTemplate;

    @Autowired
    ObjectMapper objectMapper;

    double latitude,longitude;


    @PostMapping("/meteo")
    public String post(@RequestParam("address") String address, Model model) throws IOException, JSONException {

        model.addAttribute("address",address);

        String url = "https://api-adresse.data.gouv.fr/search/?q=" + address + "&limit=1";
        JsonNode result = restTemplate.getForObject(url, JsonNode.class);
        model.addAttribute("result", result.toString());

//        Fetching coordinates from JSON
        JSONObject json = new JSONObject(result.toString());
        JSONArray features = json.getJSONArray("features");
        for (int i = 0; i < features.length(); i++) {
            JSONObject feature = features.getJSONObject(i);
            String featureType = feature.getString("type");
            System.out.println("Feature " + (i + 1) + " type : " + featureType);
            JSONObject geometry = feature.getJSONObject("geometry");
            JSONArray coordinates = geometry.getJSONArray("coordinates");
            log.info("coordinates : " + coordinates);

            longitude = coordinates.getDouble(0);
            latitude = coordinates.getDouble(1);

            model.addAttribute("longitude", coordinates.get(0).toString());
            model.addAttribute("latitude", coordinates.get(1).toString());
        }

//        Calling meteo-concept API to fetch weather forecast for input address
        url = "https://api.meteo-concept.com/api/forecast/daily/0?" +
                "token=dacfffe93c5426aa642025036d0013dbd137c6d381440bfc2cff811794e2adac&latlng="
                + latitude + ',' + longitude + "&world=false";

        // Using Jackson to deserialize data from JSON file
        result = restTemplate.getForObject(url, JsonNode.class);
        Weather forecast = objectMapper.readValue(result.toString(), Weather.class);

        
        model.addAttribute("forecast",forecast);
        return "meteo";
    }

}
