#include "Remote.h"
#include <RF24.h>

Remote::Remote() : radio(48, 49) {}

void Remote::setup() {
  while (!radio.begin()) {
    delay(100); // RF_RETRY_DELAY
  }

  radio.openWritingPipe(00001);
  radio.setPALevel(RF24_PA_LOW);
  radio.setDataRate(RF24_250KBPS);
  radio.setChannel(110);

  radio.stopListening();
}

bool Remote::sendJoystickData(const JoystickData& data) {
  return radio.write(&data, sizeof(data)); // Retourne true si la transmission réussit
}

bool Remote::sendRemoteData(const RemoteData& data) {
  return radio.write(&data, sizeof(data)); // Retourne true si la transmission réussit
}