#include "../../include/input/PotentiometerHandler.hpp"
#include "../../include/config.hpp"
#include <esp32-hal-gpio.h>

PotentiometerHandler::PotentiometerHandler()
{
  pinMode(config::PinConfig::POTENTIOMETER, INPUT);
  updatePosition();
}

PotentiometerHandler::Movement PotentiometerHandler::getMovement()
{
  const long unsigned now = millis();
  if ( now - lastCheck < delayTimeMs){return None;}
  lastCheck = now;

  const uint16_t previousPosition = position;
  updatePosition();
  if (previousPosition / stepSize == position/stepSize) return None;
  if (position - previousPosition > 0 ) return Positive;
  return Negative;
}

uint16_t PotentiometerHandler::getPosition() const
{
  return position;
}

void PotentiometerHandler::updatePosition()
{
  int tmpPosition = 0;
  for (uint8_t i = 0; i < samplesPerRead; i++)
  {
    tmpPosition += analogRead(config::PinConfig::POTENTIOMETER);
  }
  position = analogRead(config::PinConfig::POTENTIOMETER)/ samplesPerRead;
}
