#ifndef FIRMWARE_CONFIG_HPP
#define FIRMWARE_CONFIG_HPP
#include <cstdint>
#include <esp32-hal-gpio.h>

namespace config
{
  namespace ButtonInputVals
  {
    constexpr uint16_t NoPressValue = 785;

    constexpr uint16_t LeftAnalogValue = 905;
    constexpr uint16_t MiddleAnalogValue = 1050;
    constexpr uint16_t RightAnalogValue = 1515;

    constexpr uint16_t LongPressThreshold = 50;
    constexpr uint16_t ShortPressThreshold = 10;
  }


  namespace PinConfig
  {
    constexpr int BUTTON_PANEL = GPIO_NUM_33;
    constexpr int POTENTIOMETER = GPIO_NUM_32;
  }

}


#endif //FIRMWARE_CONFIG_HPP
