package com.ensim.TP3.model;

import com.fasterxml.jackson.annotation.JsonProperty;

public class Weather {
    @JsonProperty("city")
    private City city;

    @JsonProperty("update")
    private String update;

    @JsonProperty("forecast")
    private Forecast forecast;

    public City getCity() {
        return city;
    }

    public void setCity(City city) {
        this.city = city;
    }

    public String getUpdate() {
        return update;
    }

    public void setUpdate(String update) {
        this.update = update;
    }

    public Forecast getForecast() {
        return forecast;
    }

    public void setForecast(Forecast forecast) {
        this.forecast = forecast;
    }

static class City {
        @JsonProperty("insee")
        private String insee;

        @JsonProperty("cp")
        private int cp;

        @JsonProperty("name")
        private String name;

        @JsonProperty("latitude")
        private double latitude;

        @JsonProperty("longitude")
        private double longitude;

        @JsonProperty("altitude")
        private int altitude;

        public String getInsee() {
            return insee;
        }

        public void setInsee(String insee) {
            this.insee = insee;
        }

        public int getCp() {
            return cp;
        }

        public void setCp(int cp) {
            this.cp = cp;
        }

        public String getName() {
            return name;
        }

        public void setName(String name) {
            this.name = name;
        }

        public double getLatitude() {
            return latitude;
        }

        public void setLatitude(double latitude) {
            this.latitude = latitude;
        }

        public double getLongitude() {
            return longitude;
        }

        public void setLongitude(double longitude) {
            this.longitude = longitude;
        }

        public int getAltitude() {
            return altitude;
        }

        public void setAltitude(int altitude) {
            this.altitude = altitude;
        }
    }

static class Forecast {
    @JsonProperty("insee")
    private String insee;

    @JsonProperty("cp")
    private int cp;

    @JsonProperty("latitude")
    private double latitude;

    @JsonProperty("longitude")
    private double longitude;

    @JsonProperty("day")
    private int day;

    @JsonProperty("datetime")
    private String datetime;

    @JsonProperty("wind10m")
    private int wind10m;

    @JsonProperty("gust10m")
    private int gust10m;

    @JsonProperty("dirwind10m")
    private int dirwind10m;

    @JsonProperty("rr10")
    private int rr10;

    @JsonProperty("rr1")
    private int rr1;
    @JsonProperty("probarain")
    private int probarain;

    @JsonProperty("weather")
    private int weather;

    @JsonProperty("tmin")
    private int tmin;

    @JsonProperty("tmax")
    private int tmax;

    @JsonProperty("sun_hours")
    private int sun_hours;

    @JsonProperty("etp")
    private int etp;

    @JsonProperty("probafrost")
    private int probafrost;

    @JsonProperty("probafog")
    private int probafog;

    @JsonProperty("probawind70")
    private int probawind70;

    @JsonProperty("probawind100")
    private int probawind100;

    @JsonProperty("gustx")
    private int gustx;

    public String getInsee() {
        return insee;
    }

    public void setInsee(String insee) {
        this.insee = insee;
    }

    public int getCp() {
        return cp;
    }

    public void setCp(int cp) {
        this.cp = cp;
    }

    public double getLatitude() {
        return latitude;
    }

    public void setLatitude(double latitude) {
        this.latitude = latitude;
    }

    public double getLongitude() {
        return longitude;
    }

    public void setLongitude(double longitude) {
        this.longitude = longitude;
    }

    public int getDay() {
        return day;
    }

    public void setDay(int day) {
        this.day = day;
    }

    public String getDatetime() {
        return datetime;
    }

    public void setDatetime(String datetime) {
        this.datetime = datetime;
    }

    public int getWind10m() {
        return wind10m;
    }

    public void setWind10m(int wind10m) {
        this.wind10m = wind10m;
    }

    public int getGust10m() {
        return gust10m;
    }

    public void setGust10m(int gust10m) {
        this.gust10m = gust10m;
    }

    public int getDirwind10m() {
        return dirwind10m;
    }

    public void setDirwind10m(int dirwind10m) {
        this.dirwind10m = dirwind10m;
    }

    public int getRr10() {
        return rr10;
    }

    public void setRr10(int rr10) {
        this.rr10 = rr10;
    }

    public int getRr1() {
        return rr1;
    }

    public void setRr1(int rr1) {
        this.rr1 = rr1;
    }

    public int getProbarain() {
        return probarain;
    }

    public void setProbarain(int probarain) {
        this.probarain = probarain;
    }
    public int getWeather() {
        return weather;
    }

    public void setWeather(int weather) {
        this.weather = weather;
    }

    public int getTmin() {
        return tmin;
    }

    public void setTmin(int tmin) {
        this.tmin = tmin;
    }

    public int getTmax() {
        return tmax;
    }

    public void setTmax(int tmax) {
        this.tmax = tmax;
    }

    public int getSun_hours() {
        return sun_hours;
    }

    public void setSun_hours(int sun_hours) {
        this.sun_hours = sun_hours;
    }

    public int getEtp() {
        return etp;
    }

    public void setEtp(int etp) {
        this.etp = etp;
    }

    public int getProbafrost() {
        return probafrost;
    }

    public void setProbafrost(int probafrost) {
        this.probafrost = probafrost;
    }

    public int getProbafog() {
        return probafog;
    }

    public void setProbafog(int probafog) {
        this.probafog = probafog;
    }

    public int getProbawind70() {
        return probawind70;
    }

    public void setProbawind70(int probawind70) {
        this.probawind70 = probawind70;
    }

    public int getProbawind100() {
        return probawind100;
    }

    public void setProbawind100(int probawind100) {
        this.probawind100 = probawind100;
    }

    public int getGustx() {
        return gustx;
    }

    public void setGustx(int gustx) {
        this.gustx = gustx;
    }
}
}