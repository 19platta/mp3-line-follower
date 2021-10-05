String incomingString = "";
const String MODE1 = "blink\n";

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600); // opens serial port, sets data rate to 9600 bps
}

void loop() {
  // check if data is available
  if (Serial.available() > 0) {
    // read the incoming string:
    incomingString = Serial.readString();

    // prints the received data
    Serial.print("I received: ");
    Serial.println(incomingString);
  }
  Serial.println(incomingString);
  if (incomingString.equals(MODE1)) {
      Serial.println("string is blink");
      digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
      delay(1000);                       // wait for a second
      digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
      delay(1000); 
  }

  else {
      digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
      delay(1000); 
  }
}
