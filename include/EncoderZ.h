#ifndef ENCODERZ_H
#define ENCODERZ_H

#include <Arduino.h>
#include <ezButton.h>
#include <Encoder.h>

class EncoderZ {
  private:
    Encoder encoder;       // Utilisation de la classe Encoder
    ezButton buttonSW;     // Bouton SW avec debounce
    int position;          // Position actuelle de l'encodeur
    int minPosition;       // Position minimale
    int maxPosition;       // Position maximale

  public:
    EncoderZ(int pA, int pB, int pSW, int minPos = 0, int maxPos = 200);
    void update();         // Mettre à jour la position de l'encodeur
    int getScore();     // Retourner la position actuelle
    bool isSWPressed();    // Retourne true si le bouton SW a été pressé
};

#endif