int dataPin  = 2;
int latchPin = 3;
int clockPin = 4;
 
byte data[] = {
  B10000000,
  B01000000,
  B00100000,
  B00010000,
  B00001000,
  B00000100,
  B00000010,
  B00000001,
  B00000010,
  B00000100,
  B00001000,
  B00010000,
  B00100000,
  B01000000,
  B10000000,
  B11000000,
  B10100000,
  B10010000,
  B10001000,
  B10000100,
  B10000010,
  B10000001,
  B01000010,
  B00100100,
  B00011000,
  B00100100,
  B01000010,
  B10000001,
  B10000010,
  B10000100,
  B10001000,
  B10010000,
  B10100000,
  B11000000,
};

void setup() {
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
}
 
void loop() {
  for (int index = 0; index < sizeof(data); index++) {
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, data[index]);  
    digitalWrite(latchPin, HIGH);
    delay(100);
  }
}
