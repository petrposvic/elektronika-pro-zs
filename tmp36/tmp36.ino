#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

void setup() {
  Serial.begin(9600);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.display();
  delay(2000);
}

void loop() {
  float tmp = ((analogRead(A0) * 5.0) / 1024.0 - 0.5) * 100;

  Serial.println(tmp);
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.print(tmp);
  display.println(" C");
  display.display();

  delay(1000);
}
