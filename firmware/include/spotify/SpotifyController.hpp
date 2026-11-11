#ifndef FIRMWARE_SPOTIFYCONTROLLER_HPP
#define FIRMWARE_SPOTIFYCONTROLLER_HPP
#include "SpotifyCommandQueue.hpp"
#include "SpotifyEsp32.h"


class SpotifyController
{

  Spotify sp;
  SpotifyCommandQueue* queue = nullptr;

  uint8_t volumeIncrement = 5;
  uint8_t volume = 30;
  static constexpr uint8_t maxVolume = 100;


  void sendPlay(bool play);
  void sendPlayNext();
  void sendPlayPrevious();
  void sendVolume();
  uint8_t getVolume() const;
  uint8_t getVolumeIncrement() const;
  void setVolumeIncrement(uint8_t increment);

  public:
  SpotifyController(SpotifyCommandQueue* queue);

  void threadLoop();

};


#endif //FIRMWARE_SPOTIFYCONTROLLER_HPP
