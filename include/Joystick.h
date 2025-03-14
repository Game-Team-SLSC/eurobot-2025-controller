#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <Arduino.h>
#include <ezButton.h>
#include <JoystickData.h> // Inclusion de la structure JoystickData

class Joystick {
  private:
    int pinVert;    // Broche pour l'axe vertical
    int pinHoriz;   // Broche pour l'axe horizontal
    ezButton buttonSW; // Bouton SW avec debounce

  public:
    Joystick(int pV, int pH, int pSW); // Constructeur
    void update(); // Mise à jour de l'état du joystick
    JoystickData getData(); // Retourne les données du joystick
};

#endif