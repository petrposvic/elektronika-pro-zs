// Pouzijeme knihovnu, ktera umi pracovat s displayem
#include <Adafruit_SSD1306.h>

// Promenna "oled" je nas pripojeny display
#define OLED_RESET 4
Adafruit_SSD1306 oled(OLED_RESET);

// Nas pripojeny display ma 64 radku, pokud v knihovne Adafruit_SSD1306.h
// neni nastaveny 64 radkovy, kod nepujde nahrat do Arduina
#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

// float je typ promenne s desetinnou carkou
// obstacle (cesky "prekazka") ma souradnici x, y, zrychleni (v jako velocity) a
// velikost (s jako size)
float obstacle_x, obstacle_y, obstacle_v, obstacle_s;
// player (cesky "hrac") ma souradnici x, y, zrychleni (v jako velocity) a
// velikost (s jako size)
float player_x, player_y, player_v, player_s;

// int je typ promenne pro cele cislo
int score;

void setup() {

  // Tlacitko je pripojeno na digitalni pin 2
  pinMode(2, INPUT);

  Serial.begin(9600);

  // Zahajime praci s displayem
  oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  oled.setTextSize(1);        // Nastavime nejmensi velikost textu
  oled.setTextColor(WHITE);   // Nastavime barvu na bilou (nas jednobarevny display stejne jinou neumi)
  oled.clearDisplay();        // Smazaeme vse, co je na display nakresleno
  oled.display();             // Zobrazime vse, co jsme nakreslili (takze zatim cernou obrazovku)

  // Zavolame funkci restart_game()
  restart_game(true);
}

void loop() {
  obstacle_v += 0.2;          // Zvysime prekazce rychlost o 0.2
  obstacle_x -= obstacle_v;   // Posuneme prekazku doleva o takovou hodnotu, jako je aktualni rychlost
  if (obstacle_x < 0) {       // Kdyz bude prekazka uplne vlevo, tak vytvorime novou (funkce restart_obstacle) a zvysime skore
    restart_obstacle();
    score++;
  }

  if (digitalRead(2)) {
    player_v -= 0.3;          // Pokud je tlacitko na pinu 2 stisknute, snizime hracovu rychlost
  } else {
    player_v += 0.3;          // Pokud neni tlacitko na pinu 2 stisknute, zvysime hracovu rychlost
  }
  player_y += player_v;       // Posuneme hrace dolu o takovou hodnotu, jako je aktualni rychlost
                              // Pokud bude rychlost zaporna,tak se neposouva dolu, ale nahoru

  // Konec hry, kdyz hrac je moc nahore, moc dole nebo prekazka narazi do hrace
  if (
    player_y < 0 ||
    player_y > oled.height() ||
    // Vypocet vzdalenosti dvou bodu: odmocnina((Ax - Bx)^2 + (Ay - By)^2)
    sqrt((player_x - obstacle_x) * (player_x - obstacle_x) + (player_y - obstacle_y) * (player_y - obstacle_y)) < player_s + obstacle_s
  ) {
    Serial.println("Game over");
    restart_game(false);      // Zavolame funkci restart_game()
    return;
  }

  // Kresli score vlevo nahoru (souradnice 0, 0)
  oled.clearDisplay();
  oled.setCursor(0, 0);
  oled.print("Score: ");
  oled.print(score);

  // Kresli hrace
  oled.fillCircle(player_x, player_y, player_s, WHITE);

  // Kresli prekazku
  oled.fillCircle(obstacle_x, obstacle_y, obstacle_s, WHITE);

  // Zobraz vse, co bylo dosud nakresleno
  oled.display();
  delay(10);
}

// Nase vlastni funkce, kde nastavime prostredi tak, jako pri startu hry
void restart_game(bool init) {
  restart_obstacle();
  player_x = oled.width() / 10;
  player_y = oled.height() / 2;
  player_v = 0;
  player_s = 6;
  score = 0;

  // Pokud byla funkce zavolana s parametrem true, dal pokracovat nebude
  if (init) {
    return;
  }

  // Pokud byla funkce zavolana s parametrem false, tak se jeste zobrazi
  // napis "Game over" na 2.5 vteriny
  oled.setTextSize(2);
  oled.setCursor(10, 15);
  oled.print("Game over");
  oled.display();
  delay(2500);
  oled.setTextSize(1);
}

// Nase vlastni funkce, kde nastavime prekazku
void restart_obstacle() {
  obstacle_x = oled.width();
  obstacle_y = random(oled.height()); // Vyska prekazky bude nahodne cislo
  obstacle_v = 0;
  obstacle_s = 2;
}

