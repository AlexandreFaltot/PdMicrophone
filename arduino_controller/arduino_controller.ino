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

int intKeys[ROWS][COLS] = {
  {1, 2, 3, 10},
  {4, 5, 6, 20},
  {7, 8, 9, 30},
  {50, 0, 60, 40}
};
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
    Serial.write(keyToInt(key));
    Serial.flush();
  }

  if (digitalRead(buttonPin) == LOW) {
    activateReverb = !activateReverb;
    if (activateReverb) {
      digitalWrite(indicatorPin, HIGH);
      Serial.write(101);
    } else {
      digitalWrite(indicatorPin, LOW);
      Serial.write(100);
    }
    Serial.flush();
    delay(250);
  }

}

int keyToInt(char key) {
  for (int i = 0 ; i < ROWS ; i++) {
    for (int j = 0 ; j < COLS ; j++) {
      if (hexaKeys[i][j] == key) {
        return intKeys[i][j];
      }
    }
  }
}
