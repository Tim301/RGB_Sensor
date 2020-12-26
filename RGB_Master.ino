String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete

void setup() {
  // initialize serial:
  Serial.begin(9600);
  // reserve 200 bytes for the inputString:
  randomSeed(analogRead(0));
}

void loop() {
  int randNumber = random(300);
  Serial.println("!{\"1\":{\"boolean\": true,\"color\":\"gold\",\"null\":\"null\",\"number\": 123},\"2\":{\"boolean\":\"true\",\"color\":\"gold\",\"null\":\"null\",\"number\":"+ String(randNumber)+"}}¡");
  delay(100);
}
