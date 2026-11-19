#include <Arduino.h>

#include "config.hpp"
#include "secrets.hpp"
#include "StateMachine.hpp"
#include "input/InputHandler.hpp"
#include "spotify/SpotifyCommandQueue.hpp"
#include "spotify/SpotifyController.hpp"
#include "spotify/status/SpotifySongInfo.hpp"
#include "view/ViewManager.hpp"

static InputHandler* inputHandler = nullptr;
static SpotifyCommandQueue* spotifyQueue = new SpotifyCommandQueue();
static SpotifySongInfo* spotifySongInfo = new SpotifySongInfo();
static ViewManager* viewManager;
static SpotifyController* spotifyController = nullptr;

static StateMachine* stateMachine = nullptr;



 void runSpotify(void* _)
{
  spotifyController = new SpotifyController(spotifyQueue, spotifySongInfo);
  spotifyController->threadLoop();
}

void runStateMachine(void* _)
 {
   inputHandler = new InputHandler();
   stateMachine = new StateMachine(spotifyQueue);
   viewManager = new ViewManager(spotifySongInfo);
   while (true)
   {
     stateMachine->tick(inputHandler->getInput());
     viewManager->updateView();
     vTaskDelay(10/portTICK_PERIOD_MS);
   }
 }

static void connect_to_wifi(){
  WiFi.begin(secrets::WiFiSecrets::SSID, secrets::WiFiSecrets::PASSWORD);
  Serial.print("Connecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.printf("\nConnected to WiFi\n");
}

void setup() {
  Serial.begin(9600);


   spotifyQueue = new SpotifyCommandQueue();

  connect_to_wifi();

  xTaskCreatePinnedToCore(&runSpotify, "spotify", 16384, nullptr, 5, nullptr,1);

 xTaskCreatePinnedToCore(&runStateMachine, "stateMachine", 16384, nullptr, 5, nullptr,0);
 }

void loop() {


}