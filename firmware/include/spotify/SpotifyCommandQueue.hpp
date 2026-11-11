#ifndef FIRMWARE_SPOTIFYCOMMANDQUEUE_HPP
#define FIRMWARE_SPOTIFYCOMMANDQUEUE_HPP
#include <mutex>

#include "SpotifyCommand.hpp"


class SpotifyCommandQueue
{
  std::mutex queueMutex;

  static constexpr uint8_t queueSize = 20;

  SpotifyCommand commandQueue[queueSize]{};
  uint8_t queueStartIndex;

  public:
  SpotifyCommandQueue();
  static uint8_t getQueueSize();
  SpotifyCommand getCommand();
  void pushCommand(SpotifyCommand command);

};


#endif //FIRMWARE_SPOTIFYCOMMANDQUEUE_HPP
