#include<ESP8266WiFi.h>
#include<WiFiClient.h>
#include<ESP8266WebServer.h>
#include <ArduinoJson.h>

const char* ssid = "Prahalad Nothing 2";//Replace with your network SSID
const char* password = "prasid123";//Replace with your network password
ESP8266WebServer server(80);
String page = "";
float data1, data2;
int data3;
void setup()
{
  Serial.begin(9600);
  WiFi.begin(ssid, password);
while (WiFi.status() != WL_CONNECTED)
  {
  delay(500);
  Serial.print(".");
  }
  Serial.println(WiFi.localIP());
  delay(500);
  server.on("/", []()
  {
    page = "<html><head><title>IoT Design</title></head><style type=\"text/css\">";
    page += "table{border-collapse: collapse;}th {background-color:  green ;color: white;}table,td {border: 4px solid black;font-size: x-large;";
    page += "text-align:center;border-style: groove;border-color: rgb(255,0,0);}</style><body><center>";
    page += "<h1>Smart Aquaponics Monitoring using IoT</h1><br><br><table style=\"width: 1200px;height: 450px;\"><tr>";
    page += "<th>Parameters</th><th>Value</th><th>Units</th></tr><tr><td>PH Value</td><td>"+String(data1)+"</td><td>N/A</td></tr>";
    page += "<tr><td>Temperature</td><td>"+String(data2)+"</td><td>Centigrade</td></tr><tr><td>Moisture</td><td>"+String(data3)+"</td><td>%</td>";
    page += "<meta http-equiv=\"refresh\" content=\"3\">";
    server.send(200, "text/html", page);
  });
  server.begin();
}
void loop() {
  if (Serial.available()) {
    String jsonData = Serial.readStringUntil('\n'); // Read the serial data until newline
    DynamicJsonBuffer jsonBuffer; // Use DynamicJsonBuffer instead of StaticJsonBuffer
    JsonObject& root = jsonBuffer.parseObject(jsonData); // Parse the JSON data

    if (!root.success()) {
      Serial.println("JSON parsing failed!");
      return;
    }

    // Use as<int>() to parse integer values
    data1 = root["a1"].as<float>(); // pH value as float
    data2 = root["a2"].as<float>(); // Temperature value as float
    data3 = root["a3"].as<int>();   // Moisture value as int

    Serial.println(data1);
    Serial.println(data2);
    Serial.println(data3);
  }
  server.handleClient();
}