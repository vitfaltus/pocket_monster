#include <Arduino.h>

#include "config.hpp"
#include "input/InputHandler.hpp"

static InputHandler* inputHandler;
void setup() {
  Serial.begin(9600);
  auto* buttonHandler =  new ButtonHandler(config::ButtonInputVals::NoPressValue, config::ButtonInputVals::LeftAnalogValue,
        config::ButtonInputVals::MiddleAnalogValue, config::ButtonInputVals::RightAnalogValue,
        config::ButtonInputVals::ShortPressThreshold, config::ButtonInputVals::LongPressThreshold);

  inputHandler = new InputHandler(buttonHandler);
}

void loop() {
  auto x = inputHandler->getInput();
  if (x != InputHandler::None)
  {
    Serial.println(x);
  }

}