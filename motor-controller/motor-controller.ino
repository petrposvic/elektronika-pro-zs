#include <SoftwareSerial.h>

#define PIN_RX0   2
#define PIN_TX0   3
#define PIN_IN1   4
#define PIN_IN2   5
#define PIN_IN3   6
#define PIN_IN4   7
#define PIN_ENA   10 // PWM
#define PIN_ENB   11 // PWM

SoftwareSerial mySerial(PIN_RX0, PIN_TX0);
char ch;

void setup() {
  pinMode(PIN_ENA, OUTPUT);
  pinMode(PIN_ENB, OUTPUT);
  pinMode(PIN_IN1, OUTPUT);
  pinMode(PIN_IN2, OUTPUT);
  pinMode(PIN_IN3, OUTPUT);
  pinMode(PIN_IN4, OUTPUT);

  digitalWrite(PIN_ENA, LOW);
  digitalWrite(PIN_ENB, LOW);
  digitalWrite(PIN_IN1, HIGH); 
  digitalWrite(PIN_IN2, LOW);
  digitalWrite(PIN_IN3, HIGH);
  digitalWrite(PIN_IN4, LOW);

  Serial.begin(57600);
  mySerial.begin(9600);
}

void loop() {
  int motor = 0;
  int spd = 0;

  while (true) {
    delay(1);

    if (mySerial.available()) {
      ch = mySerial.read();
      if (ch == '\n') {
        break;
      }
    }

    if (ch == 'L') {
      motor = 10;
    } else if (ch == 'R') {
      motor = 11;
    }

    if (ch >= 48 && ch <= 57) {
      spd *= 10;
      spd += ((int) ch - 48);
    }
  }

  set_speed(motor, spd);
  delay(10);
}

void set_speed(int motor, int spd) {
  Serial.print("Motor: ");
  Serial.print(motor);
  Serial.print(" Speed: ");
  Serial.println(spd);

  if (motor != 10 && motor != 11) {
    return;
  }

  if (spd < 0 || spd > 255) {
    return;
  }

  analogWrite(motor, spd);
  Serial.print(motor);
  Serial.print(" ");
  Serial.println(spd);
}

