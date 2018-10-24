#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "DESKTOP-DELL";
const char* password = "@0147969#Wifi";
const String appUrl = "https://us-central1-iot-sensor-movimento.cloudfunctions.net";

void setup() {
  Serial.begin(115200);
  delay(4000);
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
 
  Serial.println("Connected to the WiFi network");
}

void loop() {
  if ((WiFi.status() == WL_CONNECTED)) { //Check the current connection status
    
    HTTPClient http;

    String getURL = appUrl + "/iot?id=123&action=start&timestamp=134556789";
    
    http.begin(getURL);  //Specify destination for HTTP request
    int httpResponseCode = http.GET();
    
    //para o post 
    //http.addHeader("Content-Type", "text/plain");
    //int httpResponseCode = http.POST("POSTING from ESP32");   //Send the actual POST request
 
    if (httpResponseCode > 0) { //Check for the returning code

      Serial.println(httpResponseCode);   //Print return code
//      if(httpResponseCode != 200){
        
//      }else{
        String response = http.getString(); //Get the response to the request
        Serial.println(response);           //Print request answer
//      }
      
    } else {
      Serial.println("Error on HTTP request");
    }
    
    http.end(); //Free the resources
  }else{
    Serial.println("Error in WiFi connection");
  }
  delay(10000);
}
