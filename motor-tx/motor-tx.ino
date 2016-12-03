int dl, dr;
int al, ar;

void setup() {
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  Serial.begin(9600);
}

void loop() {

  // Digital
  dl = digitalRead(2);
  dr = digitalRead(3);

  if (dl == HIGH) {
    Serial.println("L100");
  } else {
    Serial.println("L0");
  }

  if (dr == HIGH) {
    Serial.println("R100");
  } else {
    Serial.println("R0");
  }
/*
  // Analog
  al = map(analogRead(A0), 0, 1023, 0, 255);
  ar = map(analogRead(A1), 0, 1023, 0, 255);

  Serial.print("L");
  Serial.println(al);
  Serial.print("R");
  Serial.println(ar);
*/
  delay(100);
}
