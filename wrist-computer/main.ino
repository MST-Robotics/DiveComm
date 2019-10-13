/*
  Wrist Computer Display Unit

 Pases data input through serial and either executes sent commands or pages
 the diver through use of an alert circuit and displaying text to the screen.

  Pin Connections:
 * BUZZER ground pin to ground
 * BUZZER positive pin to 100ohm resistor
 * BUZZER resistor pin to arduino pin 9
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)
 */

#include <LiquidCrystal.h>
#include 'wrist_computer.h'

// CONSRANTS
#define BAUD_RATE 9600;
#define BUZZER 9
#define ALERT_LENGTH 500
#define ALERT_PAUSE 1000

// initialize the LCD library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  pinMode(BUZZER, OUTPUT);

  lcd.print("    <READY>     ");
  Serial.begin(BAUD_RATE);
}

void loop() {
  // not needed, waiting on serialEvent
}

void serialEvent () {
    input = ""
    while(Serial.available()) {
        data_char = (char)Serial.read();
        input += data_char;
    }
    if (data[0] == '>') {
        parseCommand(input);
    } else {
        sendPage(input);
    }
}

void parseCommand(string data) {
    lcd.setCursor(0, 0);
    lcd.print("CMD NOT IMPL!"); // command parsing not yet implemented
}

void sendPage(string data) {
    for (int i = 0; i < ALERT_BEEPS; i++) {
        tone(BUZZER, 1000);
        delay(ALERT_LENGTH);
        noTone(BUZZER);
        delay(ALERT_PAUSE);
    }
    lcd.setCursor(0, 0);
    lcd.print(CLEAR);
    lcd.setCursor(0, 0);
    lcd.print(data);
}