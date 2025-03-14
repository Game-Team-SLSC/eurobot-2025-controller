#include "Joystick.h"

Joystick::Joystick(int pV, int pH, int pSW) : pinVert(pV), pinHoriz(pH), buttonSW(pSW) {
  buttonSW.setDebounceTime(50); // Débounce de 50 ms
}

void Joystick::update() {
  buttonSW.loop(); // Mise à jour de l'état du bouton SW avec debounce
}

JoystickData Joystick::getData() {
  JoystickData data;
  data.x = map(analogRead(pinHoriz), 0, 1023, 0, 255); // Conversion en byte (0-255)
  data.y = map(analogRead(pinVert), 0, 1023, 0, 255);  // Conversion en byte (0-255)
  data.sw = buttonSW.isPressed();                      // État du bouton SW
  return data;
}