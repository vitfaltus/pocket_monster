#ifndef FIRMWARE_SPOTIFYSONGINFO_HPP
#define FIRMWARE_SPOTIFYSONGINFO_HPP
#include <cstdint>
#include <mutex>

#include "config.hpp"

class SpotifySongInfo
{
  char songName[config::BufferSize::stringBufferSize] = {};
  char artistName[config::BufferSize::stringBufferSize] = {};
  std::mutex mtx;

  public:
  SpotifySongInfo();

  bool changed = false;

  void setSongName(const char* songName);
  void setArtistName(const char* artistName);

  const char* getSongName();
  const char* getArtistName();
};



#endif //FIRMWARE_SPOTIFYSONGINFO_HPP
