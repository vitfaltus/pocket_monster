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

    constexpr uint16_t LongPressThreshold = 600;
    constexpr uint16_t ShortPressThreshold = 100;
  }


  namespace PinConfig
  {
    constexpr int BUTTON_PANEL = GPIO_NUM_4;
    constexpr int POTENTIOMETER = GPIO_NUM_2;
  }

}


#endif //FIRMWARE_CONFIG_HPP
