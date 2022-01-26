#pragma once
#include <Arduino.h>
#include <ArduinoSTL.h>

#define AUDIO_OUTPUT_PIN 9

class Button {
public:
  byte pin;
  bool state;
  void (*pressHandler)();
  void (*releaseHandler)();
  bool hasHandlers;

  // Constructor without handlers
  Button( byte _pin )
  : pin(_pin),
    state(false),
    hasHandlers(false)
  { }

  // Constructor with handlers
  Button(
    byte _pin,
    void (*_pressHandler)(),
    void (*_releaseHandler)()
  )
  : pin(_pin),
    pressHandler(_pressHandler),
    releaseHandler(_releaseHandler),
    state(false),
    hasHandlers(true)
  { }
};

class ButtonHandler {
private:
  std::vector<Button> buttons;
  void (*pressHandler)(int);
  void (*releaseHandler)(int);
  bool hasHandlers;

public:
  // Constructor without handlers
  ButtonHandler() : hasHandlers(false) { }

  // Constructor with handlers
  ButtonHandler( void (*_pressHandler)(int), void (*_releaseHandler)(int) )
  : pressHandler(_pressHandler), releaseHandler(_releaseHandler), hasHandlers(true) { }

  void registerButton( byte _pin ) {
    Button registeredButton = Button(_pin);
    buttons.push_back(registeredButton);
  }

  void registerButton(
    byte _pin,
    void (*_pressHandler)(),
    void (*_releaseHandler)() )
  {
    Button registeredButton = Button(_pin, _pressHandler, _releaseHandler);
    buttons.push_back(registeredButton);
  }

public:
  void update() {
    for ( Button &button : buttons ) {
      bool newState = (digitalRead(button.pin) == HIGH);

      if ( newState != button.state ) {
        button.state = newState;

        if ( newState ) {
          if ( button.hasHandlers ) button.pressHandler();
          if (hasHandlers) pressHandler(button.pin);
        } else {
          if ( button.hasHandlers ) button.releaseHandler();
          if (hasHandlers) releaseHandler(button.pin);
        }
      }
    }
  }
};
