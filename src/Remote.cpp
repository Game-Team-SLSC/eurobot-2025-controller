#include "Remote.h"
#include <RF24.h>
#include <SecretSettings.h>

#define Motor_Vibr 56

Remote::Remote() : radio(48, 49) {}

void Remote::setup() {
  radio.begin();

  radio.openWritingPipe((const byte*)RF_ADDRESS);
  radio.setPALevel(RF24_PA_LOW);
  radio.setDataRate(RF24_250KBPS);
  radio.setChannel(RADIO_CHANNEL);

  radio.stopListening();
  pinMode(Motor_Vibr, OUTPUT );
}

bool Remote::sendRemoteData(const RemoteData& data) {
  return radio.write(&data, sizeof(data)); // Retourne true si la transmission réussit
}