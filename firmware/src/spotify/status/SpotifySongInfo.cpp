#include "spotify/status/SpotifySongInfo.hpp"

#include <algorithm>
#include <cstring>

#include "config.hpp"

SpotifySongInfo::SpotifySongInfo()
{
}

void SpotifySongInfo::setSongName(const char* _songName)
{
  std::lock_guard lock(mtx);
  memcpy(songName, _songName,std::min(static_cast<size_t>(config::BufferSize::stringBufferSize), strlen(_songName)));
  songName[config::BufferSize::stringBufferSize - 1] = '\0';
  changed = true;
}

void SpotifySongInfo::setArtistName(const char* _artistName)
{
  std::lock_guard lock(mtx);
  memcpy(artistName, _artistName,std::min(static_cast<size_t>(config::BufferSize::stringBufferSize), strlen(_artistName)));
  artistName[config::BufferSize::stringBufferSize - 1] = '\0';
  changed = true;
}


const char* SpotifySongInfo::getSongName()
{
  changed = false;
  return songName;
}

const char* SpotifySongInfo::getArtistName()
{
  changed = false;
  return artistName;
}






