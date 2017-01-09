void setup() {
  pinMode(2, INPUT);
  pinMode(3, OUTPUT); // PWM
  pinMode(9, OUTPUT); // PWM
  Serial.begin(9600);
}

void loop() {
  /*int a = digitalRead(2);
  Serial.println(a);

  if (a == HIGH) {
    analogWrite(3, 255);
  } else {
    analogWrite(3, 50);
  }*/
  for (int i = 0; i < 255; i++) {
    analogWrite(9, i);
    delay(10);
  }
  for (int i = 254; i > 0; i--) {
    analogWrite(9, i);
    delay(10);
  }

  delay(1000);
}
