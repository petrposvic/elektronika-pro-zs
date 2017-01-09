void setup() {
  pinMode(9, OUTPUT);
  Serial.begin(19200);
}

void loop() {
  while (Serial.available()) {
    int ch = Serial.read();
    if (ch < 96 || ch > 110) {
      continue;
    }

    if (ch == 97) {
      analogWrite(9, 250);
    } else if (ch == 100) {
      analogWrite(9, 50);
    }
    delay(100);
  }

  delay(1000);
}
