#include "input/InputHandler.hpp"

#include "config.hpp"

InputHandler::InputAction InputHandler::getInput()
{
  const auto buttonInput = buttonHandler.checkButtons();
  const auto scrollInput = potentiometerHandler.getMovement();

  if (scrollInput == PotentiometerHandler::None && buttonInput == ButtonHandler::None)
  {
    return None;
  }

  switch (scrollInput)
  {
  case PotentiometerHandler::Positive:
    return PositiveScroll;
  case PotentiometerHandler::Negative:
    return NegativeScroll;
  case PotentiometerHandler::None:
    break;
  }

  switch (buttonInput)
  {
  case ButtonHandler::None:
    return None;
  case ButtonHandler::LeftButtonPress:
    return BtnLeftButtonPress;
  case ButtonHandler::MiddleButtonPress:
    return BtnMiddleButtonPress;
  case ButtonHandler::RightButtonPress:
    return BtnRightButtonPress;
  case ButtonHandler::LeftButtonLongPress:
    return BtnLeftButtonLongPress;
  case ButtonHandler::MiddleButtonLongPress:
    return BtnMiddleButtonLongPress;
  case ButtonHandler::RightButtonLongPress:
    return BtnRightButtonLongPress;
  }
  return None;
}

uint16_t InputHandler::getScrollWheelPosition() const
{
  return potentiometerHandler.getPosition();
}
