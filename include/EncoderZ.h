#ifndef ENCODERZ_H
#define ENCODERZ_H

#include <Arduino.h>
#include <ezButton.h>
#include <RotaryEncoder.h>

class EncoderZ {
  private:
    bool pin1;
    bool pin2;
    byte position;

  public:
    EncoderZ(int pA, int pB, int pSW, int minPos = 0, int maxPos = 200);
    void update();         // Mettre à jour la position de l'encodeur
    int getScore();     // Retourner la position actuelle
    bool isSWPressed();    // Retourne true si le bouton SW a été pressé
};

#endif