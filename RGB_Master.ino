#include <ArduinoJson.h>
#include <Wire.h>
#include <Adafruit_TCS34725.h>

  String input = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete
JsonObject obj;

void setup() {
  // initialize serial:
  Serial.begin(9600);
  // reserve 200 bytes for the inputString:
  randomSeed(analogRead(0));
  DynamicJsonDocument doc(1024);
  int randNumber = random(300);
  int randNumber2 = random(255);
  input ="{\"1\":{\"R\": 55,\"G\":155,\"B\":255,\"W\":"+ String(randNumber)+",\"Bat\":59},\"2\":{\"R\": 50,\"G\":150,\"B\":250,\"W\":"+ String(randNumber2)+",\"Bat\":99}}";
  deserializeJson(doc, input);
  obj = doc.as<JsonObject>();
}

void loop() {
  Serial.println("!"+input+"¡");
  //int test = obj["1"]["R"];
  //Serial.println(test);
  delay(100);
}
