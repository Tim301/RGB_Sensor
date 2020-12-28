#include <ESP8266WiFi.h>
#include <espnow.h>

#define ID "1"

// REPLACE WITH RECEIVER MAC Address
uint8_t broadcastAddress[] = {0xF4, 0xCF, 0xA2, 0xD0, 0x56, 0x2C};

// Structure example to send data
// Must match the receiver structure
typedef struct struct_message {
  String id;
  int r;
  int g;
  int b;
  int w;
  int bat;
} struct_message;

// Create a struct_message called myData
struct_message Data;

unsigned long lastTime = 0;  
unsigned long timerDelay = 50;  // send readings timer
 
void setup() {
  // Init Serial Monitor
  Serial.begin(9600);
 
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Once ESPNow is successfully Init, we will register for Send CB to
  // get the status of Trasnmitted packet
  esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
  
  // Register peer
  esp_now_add_peer(broadcastAddress, ESP_NOW_ROLE_SLAVE, 1, NULL, 0);
}
 
void loop() {
  if ((millis() - lastTime) > timerDelay) {
    // Set values to send
    //Data.id =  ID;
    Data.id =  String(random(1,9));
    Data.r = 55;
    Data.g = 155;
    Data.b = 255;
    Data.w = random(1,300);
    Data.bat = random(1,100);

    // Send message via ESP-NOW
    esp_now_send(broadcastAddress, (uint8_t *) &Data, sizeof(Data));

    lastTime = millis();
  }
}
