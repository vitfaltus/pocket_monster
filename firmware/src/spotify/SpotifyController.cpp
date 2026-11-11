#include "spotify/SpotifyController.hpp"

#include "secrets.hpp"

SpotifyController::SpotifyController(SpotifyCommandQueue* sQueue) : sp(secrets::SpotifySecrets::CLIENT_ID,
                                                                       secrets::SpotifySecrets::CLIENT_SECRET,
                                                                       secrets::SpotifySecrets::REFRESH_TOKEN)
{
  queue = sQueue;
  sp.begin();
  while (!sp.is_auth())
  {
    sp.handle_client();
  }
}

void SpotifyController::threadLoop()
{
  if (!queue) return;

  while (true)
  {
    switch (queue->getCommand())
    {
    case Empty:
      break;
    case Stop:
      sendPlay(false);
      break;
    case Play:
      sendPlay(true);
      break;
    case NextSong:
      sendPlayNext();
      break;
    case PreviousSong:
      sendPlayPrevious();
      break;
    case IncrementVolume:
      volume = volume + volumeIncrement >= maxVolume ? maxVolume : volume + volumeIncrement;
      sendVolume();
      break;
    case DecrementVolume:
      volume =  volumeIncrement > volume ? 0 : volume - volumeIncrement;
      sendVolume();
      break;
    default:
      ;
    }
  }

}

void SpotifyController::sendPlay(const bool play)
{
  if (play) sp.start_a_users_playback();
  else  sp.pause_playback();
}

void SpotifyController::sendPlayNext()
{
  sp.skip_to_next();
}

void SpotifyController::sendPlayPrevious()
{
  sp.skip_to_previous();
}

void SpotifyController::sendVolume()
{
  sp.set_volume(volume);
}

uint8_t SpotifyController::getVolume() const
{
  return volume;
}

uint8_t SpotifyController::getVolumeIncrement() const
{
  return volumeIncrement;
}

void SpotifyController::setVolumeIncrement(const uint8_t increment)
{
  if (increment > maxVolume) volumeIncrement = maxVolume;
  volumeIncrement = increment;
}
