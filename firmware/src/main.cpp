#include <Arduino.h>

#include "config.hpp"
#include "secrets.hpp"
#include "input/InputHandler.hpp"
#include "spotify/SpotifyCommandQueue.hpp"
#include "spotify/SpotifyController.hpp"

static InputHandler* inputHandler;
static SpotifyCommandQueue* spotifyQueue = new SpotifyCommandQueue();
static SpotifyController* spotifyController = nullptr;

static void runSpotify(void* _)
{
  spotifyController = new SpotifyController(spotifyQueue);
  spotifyController->threadLoop();
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


  auto* buttonHandler =  new ButtonHandler(config::ButtonInputVals::NoPressValue, config::ButtonInputVals::LeftAnalogValue,
        config::ButtonInputVals::MiddleAnalogValue, config::ButtonInputVals::RightAnalogValue,
        config::ButtonInputVals::ShortPressThreshold, config::ButtonInputVals::LongPressThreshold);

  inputHandler = new InputHandler(buttonHandler);

  connect_to_wifi();

  xTaskCreatePinnedToCore(runSpotify, "spotify", 1000, nullptr, 5, nullptr,1);
}

void loop() {
  if (auto x = inputHandler->getInput(); x != InputHandler::None)
  {
    Serial.println(x);
  }

}