#ifndef FIRMWARE_STATEMACHINE_HPP
#define FIRMWARE_STATEMACHINE_HPP
#include "input/InputHandler.hpp"
#include "spotify/SpotifyCommandQueue.hpp"

enum MachineState
{
  Disconnected,
  SpotifyControl,
  LocalPlayer,
  Settings
};

class StateMachine
{
  MachineState state = SpotifyControl;
  SpotifyCommandQueue* queue = nullptr;
  bool playing = false;

  void handleDisconnected(InputHandler::InputAction input);
  void handleSpotifyControl(InputHandler::InputAction input);
  void handleLocalPlayer(InputHandler::InputAction input);
  void handleSettings(InputHandler::InputAction input);


  public:
  StateMachine(SpotifyCommandQueue* queue);
  void tick(InputHandler::InputAction inputAction);


};


#endif //FIRMWARE_STATEMACHINE_HPP
