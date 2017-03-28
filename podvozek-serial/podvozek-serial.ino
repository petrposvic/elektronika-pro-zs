// Abychom nemuseli v programu pouzivat cisla PINu, vytvorime si nekolik
// sovnich definic. Bude se nam tak lepe pracovat s PINy a z nazvu definice
// rychle zjistime, co je k PINu pripojene.
#define PIN_IN1     4
#define PIN_IN2     5
#define PIN_IN3     6
#define PIN_IN4     7
#define PIN_MOTOR_A 10 // PWM
#define PIN_MOTOR_B 11 // PWM

// Tato promenna bude obsah smer otaceni motoru. Pokud bude 0, budou se
// motory otacet po smeru hodinovych rucicek. Pokud bude 1, budou se otacet
// proti smeru hodinovych rucicek. Hodnota teto promenne smer nezmeni, ale
// pokud ji nastavime na odpovidajici hodnotu vzdy, kdyz zmenime smer motoru,
// budeme vzdy vedet, jakym smerem se motory otaceji.
int smer;

void setup() {
  // Zahajime seriovou komunikaci rychlosti 9600
  Serial.begin(9600);

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

  // Motor A se bude tocit po smeru hodinovych rucicek
  digitalWrite(PIN_IN1, HIGH); 
  digitalWrite(PIN_IN2, LOW);
  // Motor B se bude tocit po smeru hodinovych rucicek
  digitalWrite(PIN_IN3, HIGH);
  digitalWrite(PIN_IN4, LOW);
  // Protoze jsme v predchozich 4 prikazech nastavili, aby se oba motory
  // tocily po smeru hodinovych rucicek, nastavime promennou "smer" na 0.
  // Kdyz pak budeme nekdy chtit zjistit, jakym smerem se motory toci,
  // zjistime to podle hodnoty ulozene v promenne "smer".
  smer = 0;
}

void loop() {

  // Do promenne "pocet" se ulozi pocet znaku, ktere cekaji na seriove lince.
  // Pokud promenna "pocet" bude vetsi nez 0 (tj. na seriove lince ceka alespon
  // jeden znak, provedou se nasledujici prikazy.
  int pocet = Serial.available();
  if (pocet > 0) {

    // Do promenne "ch" nacti nasledujici znak, ktery prisel po seriove lince.
    // Predchozi prikaz Serial.available() ulozil
    char znak = Serial.read();

    // Ted vime, ze v promenne "znak" je nejaky znak, ktery prisel po seriove
    // lince (priradil nam ho tam prikaz Serial.read()). Dokud do promenne "znak"
    // nepriradime jinou hodnotu, nezmeni se. V nasledujich nekolika radcich
    // testujeme, jaka hodnota je v promenne "znak". Pouziva se konstrukce "if",
    // dvojite == (jednoduche = prirazuje, dvojite == testuje) a jednoduche
    // uvozovky '.

    if (znak == 'A') {
      // Nastavit na PIN_MOTOR_A (D10) 255 (tj. 5V) => bude se točit rychle.
      // Stejne tak bychom mohli pouzit prikaz
      //     analogWrite(10, 255);
      // protoze v definici PIN_MOTOR_A je ulozeno cislo 10. Je lepsi pouzivat
      // definice, protoze jeji nazev nam casto napovi, k cemu je dany PIN
      // pripojeny.
      analogWrite(PIN_MOTOR_A, 255);
    }

    if (znak == 'a') {
      // Nastavit na PIN_MOTOR_A (D10) 0 (tj. 0V) => nebude se točit
      analogWrite(PIN_MOTOR_A, 0);
    }

    if (znak == 'B') {
      // Nastavit na PIN_MOTOR_B (D11) 255 (tj. 5V) => bude se točit rychle
      analogWrite(PIN_MOTOR_B, 255);
    }

    if (znak == 'b') {
      // Nastavit na PIN_MOTOR_B (D11) 0 (tj. 0V) => nebude se točit
      analogWrite(PIN_MOTOR_B, 0);
    }

    if (znak == 'C') {
      // Vypneme oba motory
      digitalWrite(PIN_MOTOR_A, LOW);
      digitalWrite(PIN_MOTOR_B, LOW);

      // Motor A se bude tocit po smeru hodinovych rucicek
      digitalWrite(PIN_IN1, HIGH); 
      digitalWrite(PIN_IN2, LOW);

      // Motor B se bude tocit po smeru hodinovych rucicek
      digitalWrite(PIN_IN3, HIGH);
      digitalWrite(PIN_IN4, LOW);

      // Protoze jsme zmenili smer otaceni motoru, zmenime i aktualni hodnotu
      // promenne "smer".
      smer = 0;
    }

    if (znak == 'c') {
      // Vypneme oba motory
      digitalWrite(PIN_MOTOR_A, LOW);
      digitalWrite(PIN_MOTOR_B, LOW);

      // Motor A se bude tocit proti smeru hodinovych rucicek
      digitalWrite(PIN_IN1, LOW); 
      digitalWrite(PIN_IN2, HIGH);

      // Motor B se bude tocit proti smeru hodinovych rucicek
      digitalWrite(PIN_IN3, LOW);
      digitalWrite(PIN_IN4, HIGH);

      // Protoze jsme zmenili smer otaceni motoru, zmenime i aktualni hodnotu
      // promenne "smer".
      smer = 1;
    }

    // V teto podmince testujeme, jaky je aktualni smer otaceni. Pokud bude "po smeru
    // hodin", zmenime ho na "proti smeru hodin". Abychom neprisli o informaci, jakym
    // smerem se motory otaci, musime zmenit i hodnotu promenne "smer".
    if (znak == '@') {
      // Zde muzeme vypnout oba motory, ale neni to potreba
      // digitalWrite(PIN_MOTOR_A, LOW);
      // digitalWrite(PIN_MOTOR_B, LOW);

      // Vsimnete si pouziti "else". Testujeme, jestli je hodnota promenne "smer" rovna
      // 0 a pokud ano, zmenime smer otaceni motoru proti smeru hodin. Pokud je hodnota
      // promenne "smer" cokoliv jineho (my vime, ze to muze byt jen 1), zmenime smer
      // otaceni motoru po smeru hodin.

      // Provede se v pripade, ze hodnota promenne "smer" je 0.
      if (smer == 0) {

        // Nastavime novou hodnotu do promenne "smer".
        smer = 1;

        // Motor A se bude tocit proti smeru hodinovych rucicek
        digitalWrite(PIN_IN1, LOW); 
        digitalWrite(PIN_IN2, HIGH);
  
        // Motor B se bude tocit proti smeru hodinovych rucicek
        digitalWrite(PIN_IN3, LOW);
        digitalWrite(PIN_IN4, HIGH);
      } else {

        // Nastavime novou hodnotu do promenne "smer".
        smer = 0;

        // Motor A se bude tocit po smeru hodinovych rucicek
        digitalWrite(PIN_IN1, HIGH); 
        digitalWrite(PIN_IN2, LOW);
  
        // Motor B se bude tocit po smeru hodinovych rucicek
        digitalWrite(PIN_IN3, HIGH);
        digitalWrite(PIN_IN4, LOW);
      }
    }

    if (znak == '?') {
      if (smer == 0) {
        Serial.println("Motory jsou nastavene na otaceni PO smeru hodin");
      }
      if (smer == 1) {
        Serial.println("Motory jsou nastavene na otaceni PROTI smeru hodin");
      }
    }
  }

  // Zpracovani jednoho znaku trva par milisekund. My dobu zpracovani zvysime
  // o 100 milisekund. Pokud posleme po seriove lince slovo "Aqqqqqqqqqa", tak se
  // levy motor zapne na 1 vterinu (9 znaku q nas program ignoruje, ale po kazdem
  // precteni ceka prave tech 100ms).
  // delay(100);
  delay(10);
}
