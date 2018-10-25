#include <WiFi.h>
#include <HTTPClient.h>

//const char* ssid = "DESKTOP-DELL";
//const char* password = "@0147969#Wifi";
const char* ssid = "iPhone de Andres";
const char* password = "pascocasa42";
//const String appUrl = "https://us-central1-iot-sensor-movimento.cloudfunctions.net";
const String appUrl = "http://7def700d.ngrok.io/iot-sensor-movimento/us-central1";
int pir = 13;
int pirLed = 27;
int acionamento;
bool isPresence = false;
String eventId = "0";

void setup() {
  pinMode(pir, INPUT);
  pinMode(pirLed, OUTPUT);
  Serial.begin(9600);
  // Serial.begin(115200);
  delay(4000);
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
 
  Serial.println("Connected to the WiFi network");
}

void loop() {
  if ((WiFi.status() == WL_CONNECTED)) {

    acionamento = digitalRead(pir);

    if (acionamento == HIGH) {
      if (!isPresence) {
        Serial.println("START");
        digitalWrite(pirLed, HIGH);
        isPresence = true;
        long timeStart = millis();
        request(0, "start", timeStart);
      }
    } else {
      if (isPresence) {
        Serial.println("STOP");
        digitalWrite(pirLed, LOW);
        isPresence = false;
        long timeEnd = millis();
        request(0, "stop", timeEnd);
      }
    }
    
  }else{
    Serial.println("Error in WiFi connection");
  }
}

void request(int count, char* action, long timestamp) {
  HTTPClient http;
  String address = appUrl + "/iot?id=" + eventId + "&action=" + action + "&timestamp=" + timestamp;
  Serial.println("Sending request to " + address);
  http.begin(address);

  int httpResponseCode = http.GET();
  String response = http.getString();
  Serial.println(httpResponseCode);
  Serial.println("Response: " + response);

  if(count < 3) {
    if(httpResponseCode != 200){
      Serial.println("Error. Trying again...");
      request(count + 1, action, timestamp);
    } else {
      eventId = response;
      Serial.println("Returned");
    }
  } else {
    Serial.println("Error on send request.");
  }
  
  http.end();
}

