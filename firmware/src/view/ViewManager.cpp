#include "../../include/view/ViewManager.hpp"

#include <HardwareSerial.h>

ViewManager::ViewManager(SpotifySongInfo* songInfo)
{
  spotifySongInfo = songInfo;
  Serial.println("ViewManager initialized");
}

void ViewManager::updateView() const
{
  if (!spotifySongInfo->changed) return;
  Serial.println(spotifySongInfo->getSongName());
  Serial.println(spotifySongInfo->getArtistName());

}

