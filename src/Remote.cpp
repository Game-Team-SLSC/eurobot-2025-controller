#include "Remote.h"
#include <RF24.h>

#define RF_ADDRESS "CR912"

Remote::Remote() : radio(48, 49) {}

void Remote::setup() {
  radio.begin();

  radio.openWritingPipe((const byte*)RF_ADDRESS);
  radio.setPALevel(RF24_PA_LOW);
  radio.setDataRate(RF24_250KBPS);
  radio.setChannel(110);

  radio.stopListening();
}

bool Remote::sendRemoteData(const RemoteData& data) {
  return radio.write(&data, sizeof(data)); // Retourne true si la transmission réussit
}