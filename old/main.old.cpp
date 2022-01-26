#include <Arduino.h>

const int buzzer = 2;

const int aPin = 3;
const int bPin = 4;
const int cPin = 5;
const int dPin = 6;
const int ePin = 7;

bool a, b, c, d, e;

#define C4 261
#define D4 293
#define E4 329
#define F4 349
#define G4 392

#define DELAY 3

void setup() {
  pinMode(buzzer, OUTPUT);
  pinMode(aPin, INPUT);
  pinMode(bPin, INPUT);
  pinMode(cPin, INPUT);
  pinMode(dPin, INPUT);
  pinMode(ePin, INPUT);
}

void playNote(int note, int duration) {}

void loop() {
  a = digitalRead(aPin) == HIGH;
  b = digitalRead(bPin) == HIGH;
  c = digitalRead(cPin) == HIGH;
  d = digitalRead(dPin) == HIGH;
  e = digitalRead(ePin) == HIGH;

  if (!(a || b || c || d || e)) {
    noTone(buzzer);
    noTone(buzzer2);
  }

  if (a) {
    tone(buzzer, C4);
  }

  if (b) {
    tone(buzzer, D4);
  }

  if (c) {
    tone(buzzer, E4);
  }

  if (d) {
    tone(buzzer, F4);
  }

  if (e) {
    tone(buzzer, G4);
  }
}