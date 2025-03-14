#ifndef SLIDER_H
#define SLIDER_H

#include <Arduino.h>

class Slider {
  private:
    int pin;

  public:
    Slider(int p);
    int readValue();
};

#endif