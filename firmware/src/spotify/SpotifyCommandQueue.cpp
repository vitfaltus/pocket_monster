#include "spotify/SpotifyCommandQueue.hpp"

SpotifyCommandQueue::SpotifyCommandQueue()
{
  for (auto& it : commandQueue)
  {
    it = Empty;
  }
  queueStartIndex = 0;
}

uint8_t SpotifyCommandQueue::getQueueSize()
{
  return queueSize;
}

SpotifyCommand SpotifyCommandQueue::getCommand()
{
  std::lock_guard lock(queueMutex);
  if (queueStartIndex == 0) return commandQueue[queueSize-1];
  return commandQueue[queueStartIndex-1];
}

void SpotifyCommandQueue::pushCommand(const SpotifyCommand command)
{
  std::lock_guard lock(queueMutex);
  commandQueue[queueStartIndex] = command;
  queueStartIndex += 1;
}
