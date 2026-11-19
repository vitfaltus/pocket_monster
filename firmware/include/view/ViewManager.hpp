#ifndef FIRMWARE_VIEWMANAGER_HPP
#define FIRMWARE_VIEWMANAGER_HPP
#include "spotify/status/SpotifySongInfo.hpp"


class ViewManager
{
  SpotifySongInfo* spotifySongInfo;


  public:
  ViewManager(SpotifySongInfo* songInfo);
  void updateView() const;

};


#endif //FIRMWARE_VIEWMANAGER_HPP
