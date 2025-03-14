#include "LCDDisplay.h"

LCDDisplay::LCDDisplay() : lcd(0x6B, 16, 2) {}

void LCDDisplay::init() {
  lcd.init(); // Initialisation de l'écran LCD
  lcd.setPWM(BLUE, 254);
}

void LCDDisplay::print(const char* text) {
  lcd.print(text); // Affichage d'un texte sur l'écran
}

void LCDDisplay::displayScore(int score) {
  lcd.setCursor(0, 1); // Positionne le curseur sur la deuxième ligne
  lcd.print("Score: ");
  lcd.setCursor(8, 1);
  lcd.print("    ");
  lcd.setCursor(7, 1);
  lcd.print(score); // Affiche le score
}