#define PIN_IN1     4
#define PIN_IN2     5
#define PIN_IN3     6
#define PIN_IN4     7
#define PIN_MOTOR_A 10 // PWM
#define PIN_MOTOR_B 11 // PWM

void setup() {
  pinMode(PIN_MOTOR_A, OUTPUT);
  pinMode(PIN_MOTOR_B, OUTPUT);
  pinMode(PIN_IN1, OUTPUT);
  pinMode(PIN_IN2, OUTPUT);
  pinMode(PIN_IN3, OUTPUT);
  pinMode(PIN_IN4, OUTPUT);

  digitalWrite(PIN_MOTOR_A, LOW);
  digitalWrite(PIN_MOTOR_B, LOW);
  digitalWrite(PIN_IN1, HIGH); 
  digitalWrite(PIN_IN2, LOW);
  digitalWrite(PIN_IN3, HIGH);
  digitalWrite(PIN_IN4, LOW);

  analogWrite(PIN_MOTOR_A, 100);
  analogWrite(PIN_MOTOR_B, 100);
  delay(5000);
  analogWrite(PIN_MOTOR_A, 0);
  delay(2000);
  analogWrite(PIN_MOTOR_A, 100);
  delay(5000);
  analogWrite(PIN_MOTOR_A, 0);
  analogWrite(PIN_MOTOR_B, 0);
}

void loop() {
}
