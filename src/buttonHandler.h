#pragma once
#include <Arduino.h>
#include <ArduinoSTL.h>
#include <functional>

#define AUDIO_OUTPUT_PIN 9

// void pressHandler() {
//   Serial.println("pressed");
//   // analogWrite(AUDIO_OUTPUT_PIN, 100);
// }

// void releaseHandler() {
//   Serial.println("released");
//   // analogWrite(AUDIO_OUTPUT_PIN, 0);
// }

class Button {
public:
  byte pin;
  bool state;
  void (*pressHandler)();
  void (*releaseHandler)();

  Button(
    byte _pin,
    void (*_pressHandler)(),
    void (*_releaseHandler)()
  )
  : pin(_pin),
    pressHandler(_pressHandler),
    releaseHandler(_releaseHandler),
    state(false) { }
};

class ButtonHandler {
private:
  std::vector<Button> buttons;

public:
  ButtonHandler() { }

  void registerButton(byte _pin, void (*_pressHandler)() = [](){}, void (*_releaseHandler)() = [](){}) {
    Button registeredButton = Button(_pin, _pressHandler, _releaseHandler);
    buttons.push_back(registeredButton);
  }

  void update() {
    std::for_each(buttons.begin(), buttons.end(), [](Button &button) {
      bool newState = (digitalRead(button.pin) == HIGH);
      if (newState != button.state) {
        button.state = newState;
        if (newState) button.pressHandler();
        else button.releaseHandler();
      }
    });
  }
};