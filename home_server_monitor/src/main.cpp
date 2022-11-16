#include "WiFi.h"
#include "DHT.h"
#include "CO2Sensor.h"
#include "weblib/ESPAsyncWebServer.h"
#include <mDNS.h>


#define HOSTNAME      "monitor"

#define DHTPIN      15
#define DHTTYPE     DHT22

const unsigned RX_PIN = 17;
const unsigned TX_PIN = 18;

// Set your access point network credentials
const char* ssid = "gandalf2";
const char* password = "hodorhodorhodor";


DHT dht(DHTPIN, DHTTYPE);
CO2Sensor co2sensor(RX_PIN,TX_PIN, &Serial1);
AsyncWebServer server(80);


String read_temp() {
    static float old_value;
    // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
    float h = dht.readTemperature();
    if (isnan(h)) {
        Serial.println("Failed to read temperature from DHT sensor!");
        return String(old_value);
    }
    else {
        old_value = h;
        Serial.print("Temperature reading: ");
        Serial.println(h);
        return String(h);
    }
};

String read_humidity() {
    static float old_value;
    // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
    float h = dht.readHumidity();
    if (isnan(h)) {
        Serial.println("Failed to read humidity from DHT sensor!");
        return String(old_value);
    }
    else {
        old_value = h;
        Serial.print("Humidity reading: ");
        Serial.println(h);
        return String(h);
    }
};

String read_co2() {
    int h = co2sensor.digital_read();
    Serial.print("CO2 reading: ");
    Serial.println(h);
    return String(h);
};

void setup(){

    // connect to wifi here... then:
    Serial.begin(115200);

    Serial1.begin(9600,SERIAL_8N1,RX_PIN,TX_PIN);
    dht.begin();

    // Setting the ESP as an access point
    Serial.print("Setting up WiFi");
    WiFi.setHostname("wrover_module_2");
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting to WiFi..");
    }
    Serial.print("Connected at: ");
    Serial.println(WiFi.localIP());

    // this advertises the device locally at "coolname.local"
    mdns_init();
    mdns_hostname_set(HOSTNAME);
    mdns_instance_name_set(HOSTNAME);
    Serial.printf("MDNS responder started at http://%s.local\n", HOSTNAME);


    server.on("/temperature", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send_P(200, "text/plain", read_temp().c_str());
    });
    server.on("/humidity", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send_P(200, "text/plain", read_humidity().c_str());
    });
    server.on("/co2", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send_P(200, "text/plain", read_co2().c_str());
    });

    server.begin();
};


unsigned long interval = 30000;

void loop() {
    delay(interval);

    // if WiFi is down, try reconnecting
    if ((WiFi.status() != WL_CONNECTED)) {
        Serial.println("Reconnecting to WiFi...");
        WiFi.disconnect();
        WiFi.begin(ssid, password);
        while (WiFi.status() != WL_CONNECTED) {
            delay(1000);
            Serial.println("Connecting to WiFi..");
        }
    }
}
//    delay(1000);
//    float humid = dht.readHumidity();
//   delay(2000);
//    float temp = dht.readTemperature();
//   delay(2000);
//    int co2 = co2sensor.digital_read();
//    delay(500);
//    Serial.print("Temp:");
//    Serial.println(temp);
//    Serial.print("Humid:");
//    Serial.println(humid);
//    Serial.print("CO2:");
//    Serial.println(co2);
//    delay(500);
//};



//
//void setup(){
//    // Serial port for debugging purposes
//    Serial.begin(115200);
//    Serial.println();
//
//    // Setting the ESP as an access point
//    Serial.print("Setting AP (Access Point)…");
//    // Remove the password parameter, if you want the AP (Access Point) to be open
//    WiFi.softAP(ssid, password);
//
//    IPAddress IP = WiFi.softAPIP();
//    Serial.print("AP IP address: ");
//    Serial.println(IP);
//
//    server.on("/temperature", HTTP_GET, [](AsyncWebServerRequest *request){
//        request->send_P(200, "text/plain", readTemp().c_str());
//    });
//    server.on("/humidity", HTTP_GET, [](AsyncWebServerRequest *request){
//        request->send_P(200, "text/plain", readHumi().c_str());
//    });
//    server.on("/pressure", HTTP_GET, [](AsyncWebServerRequest *request){
//        request->send_P(200, "text/plain", readPres().c_str());
//    });
//
//    bool status;
//
//    // default settings
//    // (you can also pass in a Wire library object like &Wire2)
//    status = bme.begin(0x76);
//    if (!status) {
//        Serial.println("Could not find a valid BME280 sensor, check wiring!");
//        while (1);
//    }
//
//    // Start server
//    server.begin();
//}
//
//void loop(){
//
//}
//#include <Arduino.h>
//#include <ESPmDNS.h>
///*********
//  Rui Santos
//  Complete project details at https://randomnerdtutorials.com
//*********/
//
//// Import required libraries
//#include "WiFi.h"
//#include "weblib/ESPAsyncWebServer.h"
//#include "DHT.h"
//#include "CO2Sensor.h"
//
//// Replace with your network credentials
//const char* ssid = "gandalf2";
//const char* password = "hodorhodorhodor";
//
//#define DHTPIN      17
//#define DHTTYPE     DHT22
//#define CO2SENSOR_RX_PIN 27
//#define CO2SENSOR_TX_PIN 26
//
//
//DHT dht(DHTPIN, DHTTYPE);
//CO2Sensor co2sensor(CO2SENSOR_RX_PIN,CO2SENSOR_TX_PIN);
//
//// Create AsyncWebServer object on port 80
//AsyncWebServer server(80);
//
//String readDHTTemperature() {
//    delay(500);
//    static float old_value;
//    // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
//    // Read temperature as Celsius (the default)
//    float t = dht.readTemperature();
//
//    // Read temperature as Fahrenheit (isFahrenheit = true)
//    //float t = dht.readTemperature(true);
//    // Check if any reads failed and exit early (to try again).
//    if (isnan(t)) {
//        Serial.println("Failed to read from DHT sensor!");
//        return String(old_value);
//    }
//    else {
//        old_value = t;
//        Serial.print("Temperature reading: ");
//        Serial.println(t);
//        return String(t);
//    }
//}
//
//String readCO2(){
//    int co2 = co2sensor.digital_read();
//    Serial.print("CO2 reading: ");
//    Serial.println(co2);
//    return String(co2);
//}
//
//String readDHTHumidity() {
//    delay(500);
//    static float old_value;
//    // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
//    float h = dht.readHumidity();
//    if (isnan(h)) {
//        Serial.println("Failed to read from DHT sensor!");
//        return String(old_value);
//    }
//    else {
//        old_value = h;
//        Serial.print("Humidity reading: ");
//        Serial.println(h);
//        return String(h);
//    }
//
//}
//
//const char index_html[] PROGMEM = R"rawliteral(
//<!DOCTYPE HTML><html>
//<head>
//  <meta name="viewport" content="width=device-width, initial-scale=1">
//  <link rel="stylesheet" href="https://use.fontawesome.com/releases/v5.7.2/css/all.css" integrity="sha384-fnmOCqbTlWIlj8LyTjo7mOUStjsKC4pOpQbqyi7RrhN7udi9RwhKkMHpvLbHG9Sr" crossorigin="anonymous">
//  <style>
//    html {
//     font-family: Arial;
//     display: inline-block;
//     margin: 0px auto;
//     text-align: center;
//    }
//    h2 { font-size: 3.0rem; }
//    p { font-size: 3.0rem; }
//    .units { font-size: 1.2rem; }
//    .dht-labels{
//      font-size: 1.5rem;
//      vertical-align:middle;
//      padding-bottom: 15px;
//    }
//  </style>
//</head>
//<body>
//  <h2>Home Monitor by CemBa</h2>
//  <p>
//    <i class="fas fa-thermometer-half" style="color:#059e8a;"></i>
//    <span class="dht-labels">Temperature</span>
//    <span id="temperature">%TEMPERATURE%</span>
//    <sup class="units">&deg;C</sup>
//  </p>
//  <p>
//    <i class="fas fa-tint" style="color:#00add6;"></i>
//    <span class="dht-labels">Humidity</span>
//    <span id="humidity">%HUMIDITY%</span>
//    <sup class="units">&percnt;</sup>
//  </p>
//  <p>
//    <i class="fas fa-air-freshener" style="color:#00add6;"></i>
//    <span class="dht-labels">CO2</span>
//    <span id="co2">%CO2%</span>
//    <sup class="units">ppm</sup>
//  </p>
//</body>
//<script>
//setInterval(function ( ) {
//  var xhttp = new XMLHttpRequest();
//  xhttp.onreadystatechange = function() {
//    if (this.readyState == 4 && this.status == 200) {
//      document.getElementById("temperature").innerHTML = this.responseText;
//    }
//  };
//  xhttp.open("GET", "/temperature", true);
//  xhttp.send();
//}, 10000 ) ;
//
//setInterval(function ( ) {
//  var xhttp = new XMLHttpRequest();
//  xhttp.onreadystatechange = function() {
//    if (this.readyState == 4 && this.status == 200) {
//      document.getElementById("humidity").innerHTML = this.responseText;
//    }
//  };
//  xhttp.open("GET", "/humidity", true);
//  xhttp.send();
//}, 10000 ) ;
//
//setInterval(function ( ) {
//  var xhttp = new XMLHttpRequest();
//  xhttp.onreadystatechange = function() {
//    if (this.readyState == 4 && this.status == 200) {
//      document.getElementById("co2").innerHTML = this.responseText;
//    }
//  };
//  xhttp.open("GET", "/CO2", true);
//  xhttp.send();
//}, 10000 ) ;
//
//</script>
//</html>)rawliteral";
//
//// Replaces placeholder with DHT values
//String processor(const String& var){
//    //Serial.println(var);
//    if(var == "TEMPERATURE"){
//
//        return readDHTTemperature();
//
//    } else if(var == "HUMIDITY"){
//
//        return readDHTHumidity();
//
//    } else if(var == "CO2"){
//
//        return readCO2();
//
//    }
//    return String();
//}
//
//void setup(){
//    // Serial port for debugging purposes
//    Serial.begin(115200);
//
//    dht.begin();
//    co2sensor.set_auto_calibration(false);
//
//    // Connect to Wi-Fi
//    WiFi.setHostname("wrover_module_1");
//    WiFi.begin(ssid, password);
//    while (WiFi.status() != WL_CONNECTED) {
//        delay(1000);
//        Serial.println("Connecting to WiFi..");
//    }
//
//    if(!MDNS.begin("measurement_node_1")) {
//        Serial.println("Error starting mDNS");
//        return;
//    }
//    // Print ESP32 Local IP Address
//    Serial.println(WiFi.localIP());
//
//    // Route for root / web page
//    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
//        request->send_P(200, "text/html", index_html, processor);
//    });
//    server.on("/temperature", HTTP_GET, [](AsyncWebServerRequest *request){
//        request->send_P(200, "text/plain", readDHTTemperature().c_str());
//    });
//    server.on("/humidity", HTTP_GET, [](AsyncWebServerRequest *request){
//        request->send_P(200, "text/plain", readDHTHumidity().c_str());
//    });
//    server.on("/CO2", HTTP_GET, [](AsyncWebServerRequest *request){
//        request->send_P(200, "text/plain", readCO2().c_str());
//    });
//
//    // Start server
//    server.begin();
//}
//
//void loop(){
//    delay(5000);
//    Serial.print("RSSI");
//    Serial.println(WiFi.RSSI());
//}
