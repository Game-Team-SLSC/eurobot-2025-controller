#include <Arduino.h>
#include <ezButton.h>
#include <RF24.h>
#include <JoystickData.h>
#include <RemoteData.h>
#include "Button.h"
#include "Joystick.h"
#include "Slider.h"
#include "ThreePosButton.h"
#include "LCDDisplay.h"
#include "Remote.h"
#include <LiquidCrystal_I2C.h>

// Définitions des broches
#define BUTTON1_PIN 22
#define BUTTON2_PIN 23
#define BUTTON3_PIN 24
#define BUTTON4_PIN 25
#define BUTTON5_PIN 26
#define BUTTON6_PIN 27
#define BUTTON7_PIN 28
#define BUTTON8_PIN 29
#define BUTTON9_PIN 30
#define BUTTON10_PIN 31

#define JOYSTICK_RIGHT_VERT A1
#define JOYSTICK_RIGHT_HORIZ A0
#define JOYSTICK_RIGHT_SW 34
#define JOYSTICK_LEFT_VERT A11
#define JOYSTICK_LEFT_HORIZ A12
#define JOYSTICK_LEFT_SW 33

#define ENCODER_A 14 // Broche A de l'encodeur (PCINT10)
#define ENCODER_B 15 // Broche B de l'encodeur (PCINT9)
#define ENCODER_SW 32 // Broche du bouton de l'encodeur

#define RF24_CE 48
#define RF24_CSN 49
#define RF24_SCK 52
#define RF24_MISO 50
#define RF24_MOSI 51
#define RF24_IRQ 11

#define THREEPOS_UP 12
#define THREEPOS_DOWN 13

#define SLIDER_PIN A8

// Adresse RF24
const byte RF_ADDRESS[6] = "00001";

// Variables globales
volatile byte score = 130; // Score initial
volatile byte lastScore = 130 ;
volatile uint8_t lastState = 0; // État précédent des broches de l'encodeur
bool encoderButtonState = false; // État du bouton de l'encodeur

// Initialisation des objets
Button buttons[10] = {
  Button(BUTTON1_PIN), Button(BUTTON2_PIN), Button(BUTTON3_PIN),
  Button(BUTTON4_PIN), Button(BUTTON5_PIN), Button(BUTTON6_PIN),
  Button(BUTTON7_PIN), Button(BUTTON8_PIN), Button(BUTTON9_PIN),
  Button(BUTTON10_PIN)
};

Joystick joystickRight(JOYSTICK_RIGHT_VERT, JOYSTICK_RIGHT_HORIZ, JOYSTICK_RIGHT_SW);
Joystick joystickLeft(JOYSTICK_LEFT_VERT, JOYSTICK_LEFT_HORIZ, JOYSTICK_LEFT_SW);
Slider slider(SLIDER_PIN);
ThreePosButton threePosButton(THREEPOS_UP, THREEPOS_DOWN);

LCDDisplay lcd;
Remote remote;

// Fonction d'interruption pour mettre à jour la position de l'encodeur
void updateEncoder() {
  uint8_t state = (digitalRead(ENCODER_A) << 1) | digitalRead(ENCODER_B); // Combiner les états des broches A et B
  if (state != lastState) {
    if (lastState == 0b10 && state == 0b00) {
      score++; // Rotation dans le sens horaire
    } else if (lastState == 0b01 && state == 0b00) {
      score--; // Rotation dans le sens anti-horaire
    }
    score = constrain(score, 0, 255); // Limiter la position entre 0 et 255
    lastState = state; // Mettre à jour l'état précédent
  }
}

// Configuration des interruptions PCINT
void setupPCINT() {
  // Activer les interruptions PCINT pour les broches 14 (PCINT10) et 15 (PCINT9)
  PCMSK1 |= (1 << PCINT10) | (1 << PCINT9); // Activer les interruptions pour les broches 14 et 15
  PCICR |= (1 << PCIE1); // Activer le groupe PCINT1 (broches 8 à 15)
}

// Fonction d'interruption PCINT1 (broches 8 à 15)
ISR(PCINT1_vect) {
  updateEncoder(); // Appeler la fonction de mise à jour de l'encodeur
}

void setup() {
  Serial.begin(9600);
  remote.setup();

  // Configuration des broches des boutons
  for (int i = 0; i < 10; i++) {
    pinMode(buttons[i].getPin(), INPUT_PULLUP);
  }

  // Configuration des broches des joysticks
  pinMode(JOYSTICK_LEFT_VERT, INPUT);
  pinMode(JOYSTICK_LEFT_HORIZ, INPUT);
  pinMode(JOYSTICK_LEFT_SW, INPUT);

  pinMode(JOYSTICK_RIGHT_VERT, INPUT);
  pinMode(JOYSTICK_RIGHT_HORIZ, INPUT);
  pinMode(JOYSTICK_RIGHT_SW, INPUT);

  // Configuration des broches de l'encodeur
  pinMode(ENCODER_A, INPUT_PULLUP);
  pinMode(ENCODER_B, INPUT_PULLUP);
  pinMode(ENCODER_SW, INPUT_PULLUP); // Broche du bouton de l'encodeur

  // Configuration des broches du bouton à 3 positions
  pinMode(THREEPOS_UP, INPUT);
  pinMode(THREEPOS_DOWN, INPUT);

  // Configuration des broches du slider
  pinMode(SLIDER_PIN, INPUT);

  // Initialisation de la communication RF24
  remote.setup();

  // Initialisation de l'écran LCD
  lcd.init();
  lcd.print("Initialisation"); // Message de démarrage
  lcd.displayScore(score);

  // Configuration des interruptions PCINT pour l'encodeur
  setupPCINT();
}

void loop() {

  // Mise à jour des capteurs
  for (int i = 0; i < 10; i++) {
    buttons[i].update();
  }
  joystickRight.update();
  joystickLeft.update();
  threePosButton.update();

  // Lire l'état du bouton de l'encodeur
  bool currentButtonState = digitalRead(ENCODER_SW); // LOW signifie appuyé (pull-up)

  // Si le bouton est pressé, ajouter 10 au score
  if (currentButtonState) {
    Serial.print("Bouton de l'encodeur relaché. Nouveau score : ");
    Serial.println(score);
  }
  else {
    score += 5;
    score = constrain(score, 0, 255);
    //Serial.println("Bouton de l'encodeur relâché.");
  }

  // Mettre à jour l'état du bouton
  encoderButtonState = currentButtonState;
  

  // Mettre à jour l'affichage LCD
  if ( lastScore != score) {
  lcd.displayScore(score);
  }
  
  // Préparation des autres données
  RemoteData remoteData;

  // Boutons
  for (int i = 0; i < 10; i++) {
    remoteData.buttons[i] = buttons[i].isPressed();
  }


  // Slider
  remoteData.slider = map(slider.readValue(), 0, 1023, 0, 255);
  remoteData.joystickRight = joystickRight.getData();
  remoteData.joystickLeft = joystickLeft.getData();

  // Score
  lastScore = score; // Utiliser la position de l'encodeur mise à jour par les interruptions

  // Envoi des autres données via RF24
  
  bool remoteDataSent = remote.sendRemoteData(remoteData);
  if (remoteDataSent) {
    //Serial.println("Autres données envoyées avec succès !");
  } else {
    //Serial.println("Échec de l'envoi des autres données.");
  }

  // Délai pour stabiliser
  delay(20);
}