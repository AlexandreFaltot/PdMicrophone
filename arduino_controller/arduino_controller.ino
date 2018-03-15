#include <Keypad.h>

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns

char hexaKeys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3, 2};

int intKeys[ROWS][COLS] = {
  {1, 2, 3, 10},
  {4, 5, 6, 12},
  {7, 8, 9, 13},
  {15, 0, 16, 14}
};

const int pitchInterrupterPin = 53;
const int reverbInterrupterPin = 52;
const int pitchLevelPin = A0;
const int reverbLevelPin = A1;
int pitchValue;
int  reverbValue;
char key;

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

void setup() {
  Serial.begin(9600);
  pinMode(pitchInterrupterPin, INPUT);
  pinMode(reverbInterrupterPin, INPUT);
  pinMode(pitchLevelPin, INPUT);
  pinMode(reverbLevelPin, INPUT);
}

void loop() {
  key = customKeypad.getKey();
  if (key) {
    Serial.write(keyToInt(key));
    Serial.flush();
  }

  if (digitalRead(pitchInterrupterPin) == HIGH) {
    pitchValue = analogRead(pitchLevelPin);
    pitchValue = map(pitchValue, 0, 1020, 251, 151);
    Serial.write(pitchValue);
    Serial.flush();
  } else {
    Serial.write(201);
    Serial.flush();
  }

  if (digitalRead(reverbInterrupterPin) == HIGH) {
    reverbValue = analogRead(reverbLevelPin);
    reverbValue = map(reverbValue, 0, 1020, 150, 50);
    Serial.write(reverbValue);
    Serial.flush();
  } else {
    Serial.write(50);
    Serial.flush();
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
