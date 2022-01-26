#include <Arduino.h>
#include "./buttonHandler.h"

#include <MozziGuts.h>
#include <Oscil.h>                // oscillator template
#include <tables/sin2048_int8.h>  // sine table for oscillator

// Serial port: /dev/ttyACM0

#define AUDIO_OUTPUT_PIN 9
#define MOZZI_CONTROL_RATE 64

#define C4 3
#define D4 4
#define E4 5
#define F4 6
#define G4 7

ButtonHandler buttonHandler;
Oscil <SIN2048_NUM_CELLS, AUDIO_RATE> aSin(SIN2048_DATA);

int gain = 0;

void handlePress(int pin) { }

void handleRelease(int pin) { }

void setup() {
  // pinMode(AUDIO_OUTPUT_PIN, OUTPUT);
  Serial.begin(9600);

  buttonHandler.registerButton( { C4, D4, E4, F4, G4 } );
  buttonHandler.registerHandlers(&handlePress, &handleRelease);
  startMozzi(MOZZI_CONTROL_RATE);
  aSin.setFreq(2000);
}

void loop() {
  audioHook();
}

void updateControl() {
  buttonHandler.update();
  gain = buttonHandler.getState(C4) == 1 ? 255 : 0;
  Serial.println(buttonHandler.getState(C4));
}

int updateAudio() {
  return (aSin.next() * gain) >> 8;
}
