#ifndef THREEPOSBUTTON_H
#define THREEPOSBUTTON_H

#include <Arduino.h>
#include <ezButton.h>
#include <RemoteData.h> // Inclusion de la structure RemoteData

class ThreePosButton {
  private:
    ezButton buttonUp;   // Bouton Up avec debounce
    ezButton buttonDown; // Bouton Down avec debounce
    SWITCH_3_POS state;  // État du bouton à 3 positions

  public:
    ThreePosButton(int pU, int pD);
    void update();
    SWITCH_3_POS getState(); // Retourne l'état du bouton à 3 positions
};

#endif