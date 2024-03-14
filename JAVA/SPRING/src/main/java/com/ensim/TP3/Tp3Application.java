package com.ensim.TP3;

import com.ensim.TP3.model.Quote;
import com.fasterxml.jackson.databind.JsonNode;
import com.fasterxml.jackson.databind.ObjectMapper;
import org.json.JSONObject;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.boot.CommandLineRunner;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.boot.web.client.RestTemplateBuilder;
import org.springframework.context.annotation.Bean;
import org.springframework.web.client.RestTemplate;

@SpringBootApplication
public class Tp3Application {

	private static final Logger log = LoggerFactory.getLogger(Tp3Application.class);
	public static void main(String[] args) {
		SpringApplication.run(Tp3Application.class, args);
	}

	@Bean
	public RestTemplate restTemplate(RestTemplateBuilder builder) {
		return builder.build();
	}

	@Bean
	public ObjectMapper objectMapper(){
		ObjectMapper obj = new ObjectMapper();
		return obj;
	}

/*	@Bean
	public CommandLineRunner run(RestTemplate restTemplate) throws Exception {
		return args -> {
			Quote quote = restTemplate.getForObject(
					"https://api-adresse.data.gouv.fr/search/?q=8+bd+du+port", Quote.class);
			log.info(quote.toString());
		};
	}*/
}
