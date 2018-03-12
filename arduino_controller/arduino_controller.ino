#include <Keypad.h>

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
String key;

char hexaKeys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {5, 6, 7, 8};
byte colPins[COLS] = {9, 10, 11, 12};

const int buttonPin = 2;
const int indicatorPin = 3;
bool activateReverb = false;
Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

void setup() {
  Serial.begin(9600);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(indicatorPin, OUTPUT);
}

void loop() {
  char key = customKeypad.getKey();
  if (key) {
    if (key == '0'){
      Serial.write(0);
    } else if (key == '1') {
      Serial.write(1);
    } else if (key == '2') {
      Serial.write(2);
    } else if (key == '3') {
      Serial.write(3);
    } else if (key == '4') {
      Serial.write(4);
    } else if (key == '5') {
      Serial.write(5);
    } else if (key == '6') {
      Serial.write(6);
    } else if (key == '7') {
      Serial.write(7);
    } else if (key == '8') {
      Serial.write(8);
    } else if (key == '9') {
      Serial.write(9);
    } else if (key == 'A') {
      Serial.write(10);
    } else if (key == 'B') {
      Serial.write(20);
    } else if (key == 'C') {
      Serial.write(30);
    } else if (key == 'D') {
      Serial.write(40);
    }
    Serial.flush();
  }

  if (digitalRead(buttonPin) == LOW) {
    activateReverb = !activateReverb;
    if (activateReverb) {
      digitalWrite(indicatorPin, HIGH);
      Serial.write(51);
    } else {
      digitalWrite(indicatorPin, LOW);
      Serial.write(50);
    }
    Serial.flush();
    delay(250);
  }

}
