#ifndef FIRMWARE_POTENTIOMETERHANDLER_HPP
#define FIRMWARE_POTENTIOMETERHANDLER_HPP
#include <cstdint>


class PotentiometerHandler
{
  public:
  PotentiometerHandler();
  enum Movement
  {
    None,
    Positive,
    Negative
  };

  Movement getMovement();

  uint16_t getPosition() const;

  private:
  static constexpr uint8_t samplesPerRead = 3;
  static constexpr uint16_t  stepSize = 100;
  static constexpr uint8_t delayTimeMs = 10;
  unsigned long lastCheck = 0;
  uint16_t position = 0;

  void updatePosition();
};


#endif //FIRMWARE_POTENTIOMETERHANDLER_HPP
