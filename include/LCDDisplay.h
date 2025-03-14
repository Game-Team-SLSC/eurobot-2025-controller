#ifndef LCDDISPLAY_H
#define LCDDISPLAY_H

//#include <DFRobot_RGBLCD1602.h>
#include <DFRobot_RGBLCD1602.h>

class LCDDisplay {
  private:
  DFRobot_RGBLCD1602 lcd;

  public:
    LCDDisplay();
    void init(); // Initialisation de l'écran LCD
    void print(const char* text); // Affichage d'un texte sur l'écran
    void displayScore(int score); // Affiche le score sur l'écran LCD
};

#endif