#include "EncoderZ.h"

// Constructeur
EncoderZ::EncoderZ(int pA, int pB, int pSW, int minPos, int maxPos)
  : encoder(pA, pB), buttonSW(pSW), position(0), minPosition(minPos), maxPosition(maxPos) {
  buttonSW.setDebounceTime(50); // Débounce de 50 ms
  
  int score = 70;
  int currentStateA;
  int lastStateA;
}

// Mettre à jour la position de l'encodeur
void EncoderZ::update() {
  buttonSW.loop(); // Mise à jour de l'état du bouton SW avec debounce

  // Put in a slight delay to help debounce the reading
  delay(1);

}

// Retourne true si le bouton SW a été pressé
bool EncoderZ::isSWPressed() {
  return buttonSW.isPressed();
}