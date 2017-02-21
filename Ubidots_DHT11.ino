#include "DHT.h"
#include "UbidotsMicroESP8266.h"
#include <ESP8266WiFi.h>  


#define TOKEN "EXOncCi9hFnsb8IQ9qEP1UkuzMeY5R"  // Put here your Ubidots TOKEN

#define wifi_ssid "Alert! Virus Found!!!"
#define wifi_password "donotconnectitwifiroutervirus"


Ubidots ubidots(TOKEN);
#define DHTPIN D4     // what pin we're connected to

// Uncomment whatever type you're using!
#define DHTTYPE DHT11    // DHT 11 
//#define DHTTYPE DHT22   // DHT 22 (AM2302)
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

// Connect pin 1 (on the left) of the sensor to +5V
// Connect pin 2 of the sensor to whatever your DHTPIN is
// Connect pin 4 (on the right) of the sensor to GROUND
// Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor

DHT dht(DHTPIN, DHTTYPE);

void setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(wifi_ssid);

  WiFi.begin(wifi_ssid, wifi_password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void setup() {
    Serial.begin(115200);
    setup_wifi();
    dht.begin();
}
void loop() {
    // Reading temperature or humidity takes about 250 milliseconds!
// Sensor readings may also be up to 2 seconds 'old' (its a 
// very slow sensor)
  float h = dht.readHumidity();
// Read temperature as Celsius
  float t = dht.readTemperature();
// Read temperature as Farenheit
  float f = dht.readTemperature(true);
  
// Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

      // Compute heat index in Fahrenheit (the default)
      float hif = dht.computeHeatIndex(f, h);
      // Compute heat index in Celsius (isFahreheit = false)
      float hic = dht.computeHeatIndex(t, h, false);
    

    ubidots.add("5848419a76254204193d48b9", t);  // Change for your variable name
    ubidots.add("584841a1762542031c6fc381", h);
//    ubidots.add("heatindex", hif);
//    ubidots.add("dewpoint", hic);
    ubidots.sendAll();
    delay(1000);
}


