#include "../include/StateMachine.hpp"

#include <HardwareSerial.h>

void StateMachine::handleDisconnected(InputHandler::InputAction input)
{
}

void StateMachine::handleSpotifyControl(const InputHandler::InputAction input)
{

  switch (input)
  {
  case InputHandler::None:
    break;
  case InputHandler::BtnLeftButtonPress:
    queue->pushCommand(DecrementVolume);
    break;
  case InputHandler::BtnMiddleButtonPress:
    if (playing) queue->pushCommand(Stop);
    else queue->pushCommand(Play);
    playing = not playing;
    break;
  case InputHandler::BtnRightButtonPress:
    queue->pushCommand(IncrementVolume);
    break;
  case InputHandler::BtnLeftButtonLongPress:
    queue->pushCommand(PreviousSong);
    break;
  case InputHandler::BtnMiddleButtonLongPress:
    state = Settings;
    break;
  case InputHandler::BtnRightButtonLongPress:
    queue->pushCommand(NextSong);
    break;
  case InputHandler::PositiveScroll:
    queue->pushCommand(IncrementVolume);
    break;
  case InputHandler::NegativeScroll:
    queue->pushCommand(DecrementVolume);
    break;
  }
}

void StateMachine::handleLocalPlayer(const InputHandler::InputAction input)
{
  switch (input) {
  case InputHandler::None:
    break;
  case InputHandler::BtnLeftButtonPress:
    break;
  case InputHandler::BtnMiddleButtonPress:
    break;
  case InputHandler::BtnRightButtonPress:
    break;
  case InputHandler::BtnLeftButtonLongPress:
    break;
  case InputHandler::BtnMiddleButtonLongPress:
    break;
  case InputHandler::BtnRightButtonLongPress:
    break;
  case InputHandler::PositiveScroll:
    break;
  case InputHandler::NegativeScroll:
    break;
  }

}

void StateMachine::handleSettings(const InputHandler::InputAction input)
{
  switch (input) {
  case InputHandler::None:
    break;
  case InputHandler::BtnLeftButtonPress:
    break;
  case InputHandler::BtnMiddleButtonPress:
    break;
  case InputHandler::BtnRightButtonPress:
    break;
  case InputHandler::BtnLeftButtonLongPress:
    break;
  case InputHandler::BtnMiddleButtonLongPress:
    state = SpotifyControl;
    break;
  case InputHandler::BtnRightButtonLongPress:
    break;
  case InputHandler::PositiveScroll:
    break;
  case InputHandler::NegativeScroll:
    break;
  }

}

StateMachine::StateMachine(SpotifyCommandQueue* sQueue)
{
  if (!sQueue)
  {
    Serial.println("StateMachine: sQueue is nullptr");
    return;
  }
  queue = sQueue;
}


void StateMachine::tick(const InputHandler::InputAction inputAction)
{
  switch (state)
  {
  case Disconnected:
    handleDisconnected(inputAction);
    break;
  case SpotifyControl:
    handleSpotifyControl(inputAction);
    break;
  case LocalPlayer:
    handleLocalPlayer(inputAction);
    break;
  case Settings:
    handleSettings(inputAction);
    break;
  }


}
