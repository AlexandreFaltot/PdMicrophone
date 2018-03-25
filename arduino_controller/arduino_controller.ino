#include <LiquidCrystal.h>
#include <Keypad.h>

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
const int reverbDesactivated = 20;
const int reverbActivated = 21;
const int pitchDesactivated = 30;
const int pitchActivated = 31;

char hexaKeys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3, 2};

int intKeys[ROWS][COLS] = {
  {1, 2, 3, 11},
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
LiquidCrystal lcd(32, 30, 28, 26, 24, 22);

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.print(" PureData Micro ");
  lcd.setCursor(0, 1);
  lcd.print("   Controller   ");
  pinMode(pitchInterrupterPin, INPUT);
  pinMode(reverbInterrupterPin, INPUT);
  pinMode(pitchLevelPin, INPUT);
  pinMode(reverbLevelPin, INPUT);
  delay(5000);
}

void loop() {
  key = customKeypad.getKey();
  if (key) {
    Serial.write(keyToInt(key));
    Serial.flush();
  }

  lcd.setCursor(0, 0);
  if (digitalRead(pitchInterrupterPin) == HIGH) {
    pitchValue = analogRead(pitchLevelPin);
    pitchValue = map(pitchValue, 0, 1020, 251, 151);
    Serial.write(pitchActivated);
    Serial.flush();
    Serial.write(pitchValue);
    Serial.flush();
    float pitch = ((float) pitchValue - 201) / 10;
    if (pitch < 0) {
      lcd.print("Pitch:      " + String(pitch, 2));
    } else {
      lcd.print("Pitch:      +" + String(pitch, 2));
    }
  } else {
    Serial.write(pitchDesactivated);
    Serial.flush();
    Serial.write(201);
    Serial.flush();
    lcd.print("Pitch:       OFF");
  }

  lcd.setCursor(0, 1);
  if (digitalRead(reverbInterrupterPin) == HIGH) {
    reverbValue = analogRead(reverbLevelPin);
    reverbValue = map(reverbValue, 0, 1020, 150, 50);
    Serial.write(reverbActivated);
    Serial.flush();
    Serial.write(reverbValue);
    Serial.flush();
    float reverb = ((float) reverbValue - 50) / 100;
    if (reverb < 0) {
      lcd.print("Reverb:    " + String(reverb, 2));
    } else {
      lcd.print("Reverb:     " + String(reverb, 2));
    }
  } else {
    lcd.print("Reverb:      OFF");
    Serial.write(reverbDesactivated);
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
