#ifndef LCDDISPLAY_H
#define LCDDISPLAY_H

//#include <DFRobot_RGBLCD1602.h>
#include <LiquidCrystal_I2C.h>

class LCDDisplay {
  private:
  LiquidCrystal_I2C lcd;

  public:
    LCDDisplay();
    void init(); // Initialisation de l'écran LCD
    void setRGB(uint8_t r, uint8_t g, uint8_t b); // Configuration du rétroéclairage
    void print(const char* text); // Affichage d'un texte sur l'écran
    void displayScore(int score); // Affiche le score sur l'écran LCD
};

#endif