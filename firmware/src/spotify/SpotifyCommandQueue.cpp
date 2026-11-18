#include "spotify/SpotifyCommandQueue.hpp"

#include <HardwareSerial.h>

SpotifyCommandQueue::SpotifyCommandQueue()
{
  for (auto& it : commandQueue)
  {
    it = Empty;
  }
  queueReadIndex= 0;
  queueWriteIndex= 0;
}

uint8_t SpotifyCommandQueue::getQueueSize()
{
  return queueSize;
}

SpotifyCommand SpotifyCommandQueue::getCommand()
{
  std::lock_guard lock(queueMutex);

  const SpotifyCommand ret = commandQueue[queueReadIndex];
  if (ret == Empty) return ret;

  commandQueue[queueReadIndex] = Empty;
  if (queueReadIndex == queueSize-1)
    queueReadIndex = 0;
  else
    queueReadIndex++;

  return ret;
}

void SpotifyCommandQueue::pushCommand(const SpotifyCommand command)
{
  if (command == Empty) return;

  std::lock_guard lock(queueMutex);
  commandQueue[queueWriteIndex] = command;
  queueWriteIndex = queueWriteIndex + 1 >= queueSize ? 0 : queueWriteIndex + 1;
}