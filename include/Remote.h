#ifndef REMOTE_H
#define REMOTE_H

#include <RF24.h>
#include "JoystickData.h"
#include "RemoteData.h"
// Inclure la file d'attente personnalisée

class Remote {
  private:
    RF24 radio; // Objet RF24 pour la communication radio
    bool isReady; // Indique si la radio est prête à envoyer des données

  public:
    Remote();
    void setup(); // Initialiser la communication radio
    bool sendRemoteData(const RemoteData& data); // Ajouter d'autres données à la file d'attente
};

#endif