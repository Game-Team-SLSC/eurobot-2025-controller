#include "Slider.h"

Slider::Slider(int p) : pin(p) {}

int Slider::readValue() {
  return analogRead(pin); // Lecture de la valeur du slider
}