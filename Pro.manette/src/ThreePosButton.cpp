#include "ThreePosButton.h"

ThreePosButton::ThreePosButton(int pU, int pD) : buttonUp(pU), buttonDown(pD), state(MIDDLE) {
  buttonUp.setDebounceTime(50);   // Débounce de 50 ms
  buttonDown.setDebounceTime(50); // Débounce de 50 ms
}

void ThreePosButton::update() {
  buttonUp.loop();   // Mise à jour de l'état du bouton Up avec debounce
  buttonDown.loop(); // Mise à jour de l'état du bouton Down avec debounce

  if (buttonUp.isPressed()) {
    state = UP;
  } else if (buttonDown.isPressed()) {
    state = DOWN;
  } else {
    state = MIDDLE;
  }
}

SWITCH_3_POS ThreePosButton::getState() {
  return state; // Retourne l'état du bouton à 3 positions
}