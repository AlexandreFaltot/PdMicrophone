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

const int pitchButtonPin = 3;
const int pitchLevelPin = A0;
const int reverbButtonPin = 2;
const int indicatorReverbPin = 4;
const int indicatorPitchPin = 13;
bool activateReverb = false;
bool activatePitch = false;
int pitchValue;

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

void setup() {
  Serial.begin(9600);
  pinMode(pitchButtonPin, INPUT_PULLUP);
  pinMode(reverbButtonPin, INPUT_PULLUP);
  pinMode(indicatorReverbPin, OUTPUT);
  pinMode(indicatorPitchPin, OUTPUT);
  pinMode(pitchLevelPin, INPUT);
}

void loop() {

  if (activatePitch) {
    pitchValue = analogRead(pitchLevelPin);
    pitchValue = map(pitchValue, 0, 1023, 250, 150);
    Serial.write(pitchValue);
    Serial.flush();
  }
  
  char key = customKeypad.getKey();
  if (key) {
    Serial.write(keyToInt(key));
    Serial.flush();
  }

  if (digitalRead(pitchButtonPin) == LOW) {
    activatePitch = !activatePitch;
    Serial.write(200);
    Serial.flush();
    if (activatePitch) {
      digitalWrite(indicatorPitchPin, HIGH);
    } else {
      digitalWrite(indicatorPitchPin, LOW);
    }
    delay(250);
  }

  if (digitalRead(reverbButtonPin) == LOW) {
    activateReverb = !activateReverb;
    if (activateReverb) {
      digitalWrite(indicatorReverbPin, HIGH);
      Serial.write(101);
    } else {
      digitalWrite(indicatorReverbPin, LOW);
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
