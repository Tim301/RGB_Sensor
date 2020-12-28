
#include <ESP8266WiFi.h>
#include <espnow.h> // <esp_now.h> is for esp32
#include <ArduinoJson.h>
#include <Wire.h>
#include <Adafruit_TCS34725.h>

// F4:CF:A2:D0:56:2C

boolean stringComplete = false;  // whether the string is complete

// Worst case:  "{\"1\":{\"R\":65536,\"G\":65536,\"B\":65536,\"W\":665536,\"Bat\":100},\"2\":{\"R\":65536,\"G\":65536,\"B\":65536,\"W\":65536,\"Bat\":100},\"3\":{\"R\":65536,\"G\":65536,\"B\":65536,\"W\":65536,\"Bat\":100},\"4\":{\"R\":65536,\"G\":65536,\"B\":65536,\"W\":65536,\"Bat\":100},\"5\":{\"R\":65536,\"G\":65536,\"B\":65536,\"W\":65536,\"Bat\":100},\"6\":{\"R\":65536,\"G\":65536,\"B\":65536,\"W\":65536,\"Bat\":100},\"7\":{\"R\":65536,\"G\":65536,\"B\":65536,\"W\":65536,\"Bat\":100}}";
// Json Document size = 768 - calulated with https://arduinojson.org/v6/assistant/
DynamicJsonDocument Data(1024);
DynamicJsonDocument Default(1024);

// Esp Now message Struct
typedef struct struct_message {
  String id;
  int r;
  int g;
  int b;
  int w;
  int bat;
} struct_message;

struct_message myData;

// Callback function that will be executed when data is received
void OnDataRecv(uint8_t * mac, uint8_t *incomingData, uint8_t len) {
  memcpy(&myData, incomingData, sizeof(myData));
  Data[myData.id]["R"] =  myData.r;
  Data[myData.id]["G"] =  myData.g;
  Data[myData.id]["B"] =  myData.b;
  Data[myData.id]["W"] =  myData.w;
  Data[myData.id]["Bat"] =  myData.bat;
}

void setup() {
  // initialize serial:
  Serial.begin(9600);
  randomSeed(analogRead(0));
  create_default();
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Once ESPNow is successfully Init, we will register for recv CB to
  // get recv packer info
  esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);
  esp_now_register_recv_cb(OnDataRecv);
}

void loop() {
  String input = "";         // a string to hold outgoing data
  serializeJson(Data, input);
  Serial.println("!" + input + "¡");
  Data = Default;
  delay(1000);
}

void create_default() {
  for (int i = 1; i < 9; i++) {
    Default[String(i)]["R"] =  0;
    Default[String(i)]["G"] =  0;
    Default[String(i)]["B"] =  0;
    Default[String(i)]["W"] =  0;
    Default[String(i)]["Bat"] =  0;
  }
}
