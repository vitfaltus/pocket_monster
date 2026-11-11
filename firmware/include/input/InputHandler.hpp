#ifndef FIRMWARE_INPUTHANDLER_HPP
#define FIRMWARE_INPUTHANDLER_HPP
#include "ButtonHandler.hpp"
#include "PotentiometerHandler.hpp"


class InputHandler
{
  ButtonHandler* buttonHandler;
  PotentiometerHandler potentiometerHandler;
  public:
  InputHandler(ButtonHandler* buttonHandler);

  enum InputAction
  {
    None,
    BtnLeftButtonPress,
    BtnMiddleButtonPress,
    BtnRightButtonPress,
    BtnLeftButtonLongPress,
    BtnMiddleButtonLongPress,
    BtnRightButtonLongPress,
    PositiveScroll,
    NegativeScroll
  };

  InputAction getInput();

  uint16_t getScrollWheelPosition() const;

};


#endif //FIRMWARE_INPUTHANDLER_HPP
