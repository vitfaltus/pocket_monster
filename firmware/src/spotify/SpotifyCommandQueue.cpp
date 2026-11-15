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
  Serial.print("SpotifyCommandQueue::getCommand(), command: ");
  std::lock_guard lock(queueMutex);
  const SpotifyCommand ret = commandQueue[queueReadIndex];
  Serial.println(ret);
  commandQueue[queueReadIndex] = Empty;
  if (queueReadIndex == queueSize-1)
    queueReadIndex = 0;
  else
    queueReadIndex++;
  return ret;
}

void SpotifyCommandQueue::pushCommand(const SpotifyCommand command)
{
  Serial.print("SpotifyCommandQueue::pushCommand(), command: ");
  Serial.println(command);
  std::lock_guard lock(queueMutex);
  commandQueue[queueWriteIndex] = command;
  queueWriteIndex = queueWriteIndex + 1 >= queueSize ? 0 : queueWriteIndex + 1;
}