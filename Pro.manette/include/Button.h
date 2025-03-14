#ifndef BUTTON_H
#define BUTTON_H

#include <ezButton.h>

class Button {
  private:
    ezButton button;
    int pin;

  public:
    Button(int p);
    void update();
    bool isPressed(); // Retourne true si le bouton a été pressé
    int getPin();     // Retourne le numéro de broche
};

#endif