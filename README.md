# Elektřina
- dva póly
    - plus, kladný, červený
    - mínus, záporný, černý

## Vodič
- cokoliv, co vodí (elektřinu, teplo, …)
- v našem případě to většinou bude drátek

## Obvod
- zapojení vodičů a součástek
- aby obvodem protékal proud, musí být
    - připojený ke zdroji napětí
    - uzavřený

## Zdroj napětí
- baterie
- “velikost udávána ve Voltech [V]”

## LED
- delší nožička je +
- kratší nožička je -
- pracovní napětí 2V
- pracovní proud 0.02A

## Rezistor
- zvyšuje elektrický odpor v obvodu
- snižuje proud
- čím vyšší odpor, tím menší proud

## Napětí
- je v baterii mezi + a -
- značí se U a udává se ve Voltech [V]

## Proud
- začne protékat uzavřeným obvodem
- značí se I a udává se v Ampérech [A]

## Odpor
- brání protékání proudu obvodem
- značí se R a udává se v Ohmech [Ω]

## Ohmův zákon
- I = U / R
- R = U / I
- U = I * R

Velký zdroj napětí může LEDku (spotřebič) nenávratně poškodit. Vždy je třeba vědět, jaký má LEDka (spotřebič) pracovní napětí a pracovní proud a v případě potřeby do obvodu zapojit rezistor! Velikost rezistoru spočítáme pomocí Ohmova zákonu R = U / I.

# Nepájivé pole
- dírky ve sloupcích a, b, c, d, e, ... NEJSOU propojeny
- dírky v řádcích 1, 2, 3, 4, ... JSOU propojeny
- dírky ve speciálních sloupcích + a - jsou propojeny

# Arduino
- každý program se skládá ze dvou funkcí
    - void setup() {}
        - spustí se pouze jednou, ihned po připojení k baterii
        - měla by obsahovat příkazy, které něco nastavují
    - void loop() {}
        - spouští se opakovaně
- za každý přikaz je nutné psát ; (ta klávesa pod ESC)
- PIN
    - nožička
    - digitální jsou značené D0, D1, D2, ...
    - analogové jsou značené A0, A1, A2, ...
- digitální stavy
    - 0 (LOW) nebo 1 (HIGH)
    - LOW
        - elektřina neprochází
        - připojený spotřebič (LEDka) nepracuje (nesvítí)
    - HIGH
        - elektřina prochází
        - připojený spotřebič (LEDka) pracuje (svítí)

## Příkazy
- Serial.begin(9600);
    - připraví sériovou komunikaci
- Serial.println("Ahoj");
    - pošle slovo Ahoj po sériové lince
- Serial.read();
    - přečte, co přišlo po sériové lince
- Serial.available();
    - zjistí, jestli ze sériové linky přišla nějaká data
- delay(pocetMilisekund);
    - pozastaví program (čeká)
- pinMode(cisloPinu, typ);
    - nastavuje, jestli z PINu budeme číst (typ INPUT), nebo ho budeme nastavovat (typ OUTPUT)
    - cisloPinu je buď
        - digitální 0, 1, 2, ...
        - analogové A0, A1, A2, ...
- digitalWrite(cisloPinu, stav);
    - nastavuje, jestli na PINu bude napětí (stav HIGH) nebo ne (stav LOW)
    - pokud na PIN nastavíme HIGH, chová se jako + na baterii
    - pokud na PIN nastavíme LOW, chová se jako - na baterii
- digitalRead(cisloPinu);
    - přečte, jestli je na PINu LOW nebo HIGH
- analogWrite(cisloPinu, hodnota);
    - nastaví na PIN napětí mezi 0V a 5V
    - hodnota je od 0 do 255
        - 0 odpovídá 0V
        - 128 odpovídá 2.5V
        - 255 odpovídá 5V
- analogRead(cisloPinu);
    - přečte, jaké je na PINu napětí
    - hodnoty od 0 do 255

# Sériová komunikace
- používáme 2 vodiče
    - TX pro odesílání dat
    - RX pro přijímání dat
- přenášíme čísla dvojkové soustavy
- každý znak (např. písmeno) má svůj číselný kód
- pokud posíláme slovo "ahoj", ve skutečnosti se posílají čísla 97, 104, 111 a 106 (01100001, 01101000, 01101111 a 01101010 ve dvojkové soustavě)

# Matematika

## Jednotky
- MV (mega volt, milion Voltů), do jednoho MV se vejde 1.000kV nebo 1.000.000V nebo 1.000.000.000mV.
- kV (kilo volt, tisíc Voltů), do jednoho kV se vejde 1.000V nebo 1.000.000mV nebo 0.001MV.
- V (volt), do jednoho V se vejde 1.000mV nebo 0.001kV nebo 0.000001MV.
- mV (mili volt, tisícina jednoho Voltu), do jednoho mV se vejde 0.001V nebo 0.000001kV.

## Dvojková soustava
- můžeme použít pouze dvě cifry, 0 nebo 1
- skládáním těchto dvou cifer za sebe vznikají větší čísla, podobně jako v desítkové soustavě např. složením 1 a 5 vznikne číslo 15

| Desítková | Dvojková |
|-----------|----------|
|         0 |        0 |
|         1 |        1 |
|         2 |       10 |
|         3 |       11 |
|         4 |      100 |
|         5 |      101 |

# Odkazy
![QR kód](http://chart.apis.google.com/chart?cht=qr&chs=350x350&choe=UTF-8&chld=H%7C0&chl=http://bit.do/tahak)
- [circuits.io - Návrh obvodů v internetovém prohlížeči](https://circuits.io)
- [arduino.cc - Vývojová platforma Arduino](https://www.arduino.cc/)

