#include <SoftwareSerial.h>

// Abychom nemuseli v programu pouzivat cisla PINu, vytvorime si nekolik
// slovnich definic. Bude se nam tak lepe pracovat s PINy a z nazvu definice
// rychle zjistime, co je k PINu pripojene.
#define PIN_BT_RX   2
#define PIN_BT_TX   3
#define PIN_IN1     4
#define PIN_IN2     5
#define PIN_IN3     6
#define PIN_IN4     7
#define PIN_MOTOR_A 10 // PWM
#define PIN_MOTOR_B 11 // PWM

// Na PIN 2 a 3 je pripojeny bluetooth modul. Tyto dva PINy budou slouzit
// pro seriovou komunikaci
SoftwareSerial Bluetooth = SoftwareSerial(PIN_BT_RX, PIN_BT_TX);

bool zpet = false;
long last = 0;

void setup() {
  // Zahajime seriovou komunikaci s pocitacem (USB) rychlosti 9600
  Serial.begin(9600);

  // Zahajime seriovou komunikaci s bluetooth modulem rychlosti 19200. Je potreba
  // vedet, jakou rychlosti komunikuje bluetooth modul. Vetsinou lze bluetooth
  // modul nastavit tak, aby komunikoval ruznou rychlosti. Jakou rychlost ma modul
  // od vyroby, jake rychlosti podporuje a jak je nastavit lze zjistit u
  // vyrobce modulu.
  Bluetooth.begin(19200);

  // Vsechny PINy nastavime do rezimu zapisovani. Nebudeme z nich nic cist,
  // ale naopak my jim budeme rikat, jaka hodnota na nich ma byt nastavena.
  pinMode(PIN_MOTOR_A, OUTPUT);
  pinMode(PIN_MOTOR_B, OUTPUT);
  pinMode(PIN_IN1, OUTPUT);
  pinMode(PIN_IN2, OUTPUT);
  pinMode(PIN_IN3, OUTPUT);
  pinMode(PIN_IN4, OUTPUT);

  // Vypneme oba motory
  digitalWrite(PIN_MOTOR_A, LOW);
  digitalWrite(PIN_MOTOR_B, LOW);

  // Motor A se bude tocit proti smeru hodinovych rucicek
  digitalWrite(PIN_IN1, LOW); 
  digitalWrite(PIN_IN2, HIGH);
  // Motor B se bude tocit proti smeru hodinovych rucicek
  digitalWrite(PIN_IN3, LOW);
  digitalWrite(PIN_IN4, HIGH);
}

void loop() {

  // Vice jak vterinu neprisla data z bluetooth. Asi doslo ke ztrate spojeni.
  // Pro jistotu vypnout oba motory.
  if ((millis() - last) > 1000) {
    analogWrite(PIN_MOTOR_A, 0);
    analogWrite(PIN_MOTOR_B, 0);
  }

  // Bluetooth.available() vraci pocet znaku, ktere cekaji na seriove lince. Pokud
  // je pocet vetsi nez 0, podminka je splnena.
  if (Bluetooth.available()) {

    // Do promenne "ch" nacti nasledujici znak, ktery prisel po seriove lince.
    char znak = Bluetooth.read();

    // To, co prislo z bluetooth, vypiseme na serial monitor
    // Serial.print(znak);

    // Ulozime si cas precteni dat z bluetooth
    last = millis();

    // Ted vime, ze v promenne "znak" je nejaky znak, ktery prisel po seriove
    // lince (priradil nam ho tam prikaz Bluetooth.read()). Dokud do promenne "znak"
    // nepriradime jinou hodnotu, nezmeni se. V nasledujich nekolika radcich
    // testujeme, jaka hodnota je v promenne "znak". Pouziva se konstrukce "if",
    // dvojite == (jednoduche = prirazuje, dvojite == testuje) a jednoduche
    // uvozovky '.

    if (znak == 'F') {
      Serial.println("Vpred");
      analogWrite(PIN_MOTOR_A, 80);
      analogWrite(PIN_MOTOR_B, 80);
    } else

    if (znak == 'G') {
      Serial.println("Vlevo");
      analogWrite(PIN_MOTOR_A, 0);
      analogWrite(PIN_MOTOR_B, 150);
    } else

    if (znak == 'I') {
      Serial.println("Vpravo");
      analogWrite(PIN_MOTOR_A, 150);
      analogWrite(PIN_MOTOR_B, 0);
    } else

    if (znak == 'B') {
      Serial.println("Zpet");
      if (!zpet) {
        zpet = true;
        digitalWrite(PIN_IN1, HIGH);
        digitalWrite(PIN_IN2, LOW); 
        digitalWrite(PIN_IN3, HIGH);
        digitalWrite(PIN_IN4, LOW);
      }

      analogWrite(PIN_MOTOR_A, 50);
      analogWrite(PIN_MOTOR_B, 50);
    } else

    if (znak == 'S') {
      Serial.println("Stop");
      if (zpet) {
        zpet = false;
        digitalWrite(PIN_IN1, LOW); 
        digitalWrite(PIN_IN2, HIGH);
        digitalWrite(PIN_IN3, LOW);
        digitalWrite(PIN_IN4, HIGH);
      }

      analogWrite(PIN_MOTOR_A, 0);
      analogWrite(PIN_MOTOR_B, 0);
    }
  }

  delay(5);
}
