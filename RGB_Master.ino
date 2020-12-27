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
  delay(10);
  int randNumber2 = random(255);
  Serial.println("!{\"1\":{\"R\": 55,\"G\":155,\"B\":255,\"W\":"+ String(randNumber)+",\"Bat\":59},\"2\":{\"R\": 50,\"G\":150,\"B\":250,\"W\":"+ String(randNumber2)+",\"Bat\":99}}¡");
  delay(100);
}
