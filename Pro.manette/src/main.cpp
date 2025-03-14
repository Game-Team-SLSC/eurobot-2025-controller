#include <Arduino.h>
#include <ezButton.h>
#include <RF24.h>
//#include <DFRobot_RGBLCD1602.h>
#include <JoystickData.h> // Inclusion de la structure JoystickData
#include <RemoteData.h>  // Inclusion de la structure RemoteData
#include "Button.h"
#include "Joystick.h"
#include "EncoderZ.h"    // Utilisation de la nouvelle classe EncoderB
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

#define JOYSTICK_RIGHT_VERT A11
#define JOYSTICK_RIGHT_HORIZ A12
#define JOYSTICK_RIGHT_SW 34
#define JOYSTICK_LEFT_VERT A1
#define JOYSTICK_LEFT_HORIZ A0
#define JOYSTICK_LEFT_SW 33

#define ENCODER_A 14
#define ENCODER_B 15
#define ENCODER_SW 32

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

byte score = 70;
byte currentStateA;
byte lastStateA;

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

void setup() {
  Serial.begin(9600);
  remote.setup();

  for (int i = 0; i < 10; i++) {
    pinMode(buttons[i].getPin(), INPUT_PULLUP);
  }

  lastStateA = digitalRead(ENCODER_A);

  // Configuration des broches des joysticks
  pinMode(JOYSTICK_LEFT_VERT, INPUT);
  pinMode(JOYSTICK_LEFT_HORIZ, INPUT);
  pinMode(JOYSTICK_LEFT_SW, INPUT_PULLUP);

  pinMode(JOYSTICK_RIGHT_VERT, INPUT);
  pinMode(JOYSTICK_RIGHT_HORIZ, INPUT);
  pinMode(JOYSTICK_RIGHT_SW, INPUT_PULLUP);

  // Configuration des broches de l'encodeur
  pinMode(ENCODER_A, INPUT);
  pinMode(ENCODER_B, INPUT);
  pinMode(ENCODER_SW, INPUT_PULLUP);

  // Configuration des broches du bouton à 3 positions
  pinMode(THREEPOS_UP, INPUT_PULLUP);
  pinMode(THREEPOS_DOWN, INPUT_PULLUP);

  // Configuration des broches du slider
  pinMode(SLIDER_PIN, INPUT);

  // Initialisation de la communication RF24
  remote.setup();

  // Initialisation de l'écran LCD
  lcd.init();
  //lcd.setRGB(0, 255, 255); // Rétroéclairage blanc // Luminosité maximale
  lcd.print("Initialisation"); // Message de démarrage
}

void loop() {
  // Mise à jour des capteurs
  for (int i = 0; i < 10; i++) {
    buttons[i].update();
  }
  joystickRight.update();
  joystickLeft.update();
  threePosButton.update();

  // Read the current state of outputA
  currentStateA = digitalRead(ENCODER_A);


  // If last and current state of outputA are different, then pulse occurred
  // React to only 1 state change to avoid double count
  if (currentStateA != lastStateA  && currentStateA == 1){

    // If the outputB state is different than the outputA state then
    // the encoder is rotating CCW so decrement
    if (digitalRead(ENCODER_B) != currentStateA) {
      score --;
    } else {
      // Encoder is rotating CW so increment
      score ++;
    }
    Serial.println(score);
    lcd.displayScore(score);
  }

  score = constrain(score, 1, 256);
  // Remember last outputA state
  lastStateA = currentStateA; // Récupération de la position de l'encodeur


  // Préparation des données des joysticks
  JoystickData joystickLeftData = joystickLeft.getData();
  JoystickData joystickRightData = joystickRight.getData();


  // Envoi des données des joysticks via RF24
  //bool joystickDataSent = remote.sendJoystickData(joystickLeftData) && remote.sendJoystickData(joystickRightData);
  //if (joystickDataSent) {
    //Serial.println("Données des joysticks envoyées avec succès !");
  //} else {
    //Serial.println("Échec de l'envoi des données des joysticks.");
  //}

  // Préparation des autres données
  RemoteData remoteData;

  // Boutons
  for (int i = 0; i < 10; i++) {
    remoteData.buttons[i] = buttons[i].isPressed();
  }

  // Slider
  remoteData.slider = map(slider.readValue(), 0, 1023, 0, 255);
  //Serial.println(remoteData.slider);

  // Bouton à 3 positions
  remoteData.sw = threePosButton.getState();

  // Envoi des autres données via RF24
  //bool remoteDataSent = remote.sendRemoteData(remoteData);
  //if (remoteDataSent) {
    //Serial.println("Autres données envoyées avec succès !");
  //} else {
    //Serial.println("Échec de l'envoi des autres données.");
  //}

  // Délai pour stabiliser
  delay(1);
}