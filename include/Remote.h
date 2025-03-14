#ifndef REMOTE_H
#define REMOTE_H

#include <RF24.h>
#include <JoystickData.h> // Inclusion de la structure JoystickData
#include <RemoteData.h>  // Inclusion de la structure RemoteData

class Remote {
  private:
    RF24 radio;

  public:
    Remote();
    void setup();
    bool sendJoystickData(const JoystickData& data); // Envoie les données du joystick
    bool sendRemoteData(const RemoteData& data);     // Envoie les autres données
};

#endif