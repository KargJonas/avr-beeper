#include <Arduino.h>
#include "./buttonHandler.h"

#define AUDIO_OUTPUT_PIN 9

ButtonHandler buttonHandler;

// Serial port: /dev/ttyACM0

void setup() {
  pinMode(AUDIO_OUTPUT_PIN, OUTPUT);
  Serial.begin(9600);

  buttonHandler.registerButtonN( { 3, 4, 5, 6, 7 } );

  // buttonHandler.registerButton(3,
  //   []() { analogWrite(AUDIO_OUTPUT_PIN, 100); },
  //   []() { analogWrite(AUDIO_OUTPUT_PIN, 0); }
  // );

  buttonHandler.registerHandlers(
    [](int pin) { analogWrite(AUDIO_OUTPUT_PIN, 100); },
    [](int pin) { analogWrite(AUDIO_OUTPUT_PIN, 0); }
  );
}

void loop() {
  buttonHandler.update();
}