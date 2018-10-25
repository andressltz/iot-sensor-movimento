#include <WiFi.h>
#include <HTTPClient.h>

//const char* ssid = "DESKTOP-DELL";
//const char* password = "@0147969#Wifi";
const char* ssid = "iPhone de Andres";
const char* password = "pascocasa42";
//const String appUrl = "https://us-central1-iot-sensor-movimento.cloudfunctions.net";
const String appUrl = "http://4e07ecdf.ngrok.io/iot-sensor-movimento/us-central1";
int pir = 13;
int acionamento;
bool isPresence = false;
int eventId = NULL;

void setup() {
  pinMode(pir, INPUT);
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
        isPresence = true;
        long timeStart = millis();
        eventId = timeStart;
        request(eventId, "start", timeStart);
      }
    } else {
      if (isPresence) {
        Serial.println("STOP");
        isPresence = false;
        long timeEnd = millis();
        request(eventId, "stop", timeEnd);
      }
    }
    
  }else{
    Serial.println("Error in WiFi connection");
  }
}

void request(int eventId, char* action, long timestamp) {
  HTTPClient http;
  String address = appUrl + "/iot?id=" + eventId + "&action=" + action + "&timestamp=" + timestamp;
  Serial.println("Sending request to " + address);
  http.begin(address);

  int httpResponseCode = http.GET();
  String response = http.getString();
  Serial.println("ResponseCode: " + httpResponseCode);
  Serial.println("Response: " + response);

  if(httpResponseCode != 200){
//    request(eventId, action, timestamp);
  } else {
    eventId = response.toInt();
  }

  Serial.println("Returned");
  http.end();
}
