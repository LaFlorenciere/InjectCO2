#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <RotaryEncoder.h>

// Initialisation de l'écran LCD I2C

LiquidCrystal_I2C lcd(0x27, 20, 4); // au lieu de LiquidCrystal_I2C lcd(0x27, 16, 2);


// Pins de l'encodeur rotatif
const int encoderPinA = 2;
const int encoderPinB = 3;
const int encoderButtonPin = 4;

// Initialisation de l'encodeur rotatif
RotaryEncoder encoder(encoderPinA, encoderPinB);

// Pins des interrupteurs et électrovannes
const int interrupteurPin1 = A3;
const int interrupteurPin2 = A4;
const int electrovannePin1 = 9;
const int electrovannePin2 = 10;

// Durées d'ouverture et de fermeture des électrovannes (en millisecondes)
const unsigned long electrovanneOuverture = 10000;
const unsigned long electrovanneFermeture = 10000;

// Modes de fonctionnement
enum Mode {
  MODE_EV1_PARTIELLE,
  MODE_EV2_PARTIELLE,
  MODE_EV1_EV2_PARTIELLE,
  MODE_EV1_CONTINU,
  MODE_EV2_CONTINU,
  MODE_EV1_EV2_CONTINU,
  MODE_TOTAL
};

Mode currentMode = MODE_EV1_PARTIELLE;

// Variables pour la gestion des électrovannes
bool electrovanne1Ouverte = false;
bool electrovanne2Ouverte = false;

// Variables pour la gestion des temporisations
unsigned long previousMillisMenu = 0;
unsigned long previousMillisEV1 = 0;
unsigned long previousMillisEV2 = 0;
unsigned long intervalEV1 = 0;
unsigned long intervalEV2 = 0;
 
// Compteurs
int ev1Compteur = 0;
int ev2Compteur = 0;
unsigned long ev1Temps = 0;
unsigned long ev2Temps = 0;

void updateMenuDisplay();

void setup() {
  // Configuration de l'écran LCD
  lcd.init();
  lcd.backlight();

  // Configuration des interrupteurs et électrovannes
  pinMode(interrupteurPin1, INPUT_PULLUP);
  pinMode(interrupteurPin2, INPUT_PULLUP);
  pinMode(electrovannePin1, OUTPUT);
  pinMode(electrovannePin2, OUTPUT);
  digitalWrite(electrovannePin1, HIGH);
  digitalWrite(electrovannePin2, HIGH);

  // Configuration de l'encodeur rotatif
  pinMode(encoderPinA, INPUT_PULLUP);
  pinMode(encoderPinB, INPUT_PULLUP);
  

  updateMenuDisplay();
}

void loop() {
  // Gérer les électrovannes
  unsigned long currentMillis = millis(); // Obtenir le temps actuel

switch (currentMode) {
    case MODE_EV1_PARTIELLE:
      if (digitalRead(interrupteurPin1) == LOW && !electrovanne1Ouverte && currentMillis - previousMillisEV1 >= electrovanneFermeture) {
        digitalWrite(electrovannePin1, LOW);
        electrovanne1Ouverte = true;
        previousMillisEV1 = currentMillis;
        ev1Compteur++;
        updateMenuDisplay();
      }
      if (electrovanne1Ouverte && currentMillis - previousMillisEV1 >= electrovanneOuverture) {
        digitalWrite(electrovannePin1, HIGH);
        electrovanne1Ouverte = false;
        previousMillisEV1 = currentMillis;
      }
      break;
    case MODE_EV2_PARTIELLE:
      if (digitalRead(interrupteurPin2) == LOW && !electrovanne2Ouverte && currentMillis - previousMillisEV2 >= electrovanneFermeture) {
        digitalWrite(electrovannePin2, LOW);
        electrovanne2Ouverte = true;
        previousMillisEV2 = currentMillis;
        ev2Compteur++;
        updateMenuDisplay();
      }
      if (electrovanne2Ouverte && currentMillis - previousMillisEV2 >= electrovanneOuverture) {
        digitalWrite(electrovannePin2, HIGH);
        electrovanne2Ouverte = false;
        previousMillisEV2 = currentMillis;
      }
      break;
        case MODE_EV1_EV2_PARTIELLE:
      // EV1
      if (digitalRead(interrupteurPin1) == LOW && !electrovanne1Ouverte && currentMillis - previousMillisEV1 >= electrovanneFermeture) {
        digitalWrite(electrovannePin1, LOW);
        electrovanne1Ouverte = true;
        previousMillisEV1 = currentMillis;
        ev1Compteur++;
        updateMenuDisplay();
      }
      if (electrovanne1Ouverte && currentMillis - previousMillisEV1 >= electrovanneOuverture) {
        digitalWrite(electrovannePin1, HIGH);
        electrovanne1Ouverte = false;
        previousMillisEV1 = currentMillis;
      }
    
      if (digitalRead(interrupteurPin2) == LOW && !electrovanne2Ouverte && currentMillis - previousMillisEV2 >= electrovanneFermeture) {
        digitalWrite(electrovannePin2, LOW);
        electrovanne2Ouverte = true;
        previousMillisEV2 = currentMillis;
        ev2Compteur++;
        updateMenuDisplay();
      }
      if (electrovanne2Ouverte && currentMillis - previousMillisEV2 >= electrovanneOuverture) {
        digitalWrite(electrovannePin2, HIGH);
        electrovanne2Ouverte = false;
        previousMillisEV2 = currentMillis;
      }
      break;
       case MODE_EV1_CONTINU:
    if (digitalRead(interrupteurPin1) == LOW) {
      digitalWrite(electrovannePin1, LOW);
    } else {
      digitalWrite(electrovannePin1, HIGH);
    }
    // Compteur de temps pour EV1
    unsigned long currentMillisEV1 = millis();
    if (digitalRead(interrupteurPin1) == LOW && !electrovanne1Ouverte && currentMillisEV1 - previousMillisEV1 >= electrovanneFermeture) {
      electrovanne1Ouverte = true;
      previousMillisEV1 = currentMillisEV1;
    }
    if (digitalRead(interrupteurPin1) == HIGH && electrovanne1Ouverte && currentMillisEV1 - previousMillisEV1 >= electrovanneOuverture) {
      electrovanne1Ouverte = false;
      previousMillisEV1 = currentMillisEV1;
      ev1Temps += (currentMillisEV1 - previousMillisEV1); // Ajouter le temps d'ouverture de l'électrovanne au compteur de temps EV1
    }
    break;
    case MODE_EV2_CONTINU:
      if (digitalRead(interrupteurPin2) == LOW) {
        digitalWrite(electrovannePin2, LOW);
      } else {
        digitalWrite(electrovannePin2, HIGH);
      }
      break;
    case MODE_EV1_EV2_CONTINU:
      if (digitalRead(interrupteurPin1) == LOW) {
        digitalWrite(electrovannePin1, LOW);
      } else {
        digitalWrite(electrovannePin1, HIGH);
      }
      if (digitalRead(interrupteurPin2) == LOW) {
        digitalWrite(electrovannePin2, LOW);
      } else {
        digitalWrite(electrovannePin2, HIGH);
      }
      break;
    default:
      break;
  }

   // Gérer l'encodeur rotatif
  encoder.tick();
  int newPos = encoder.getPosition();
  static int oldPos = newPos;

  if (currentMillis - previousMillisMenu >= 1) {
    previousMillisMenu = currentMillis;
    if (newPos != oldPos) {
      if (newPos > oldPos) {
        currentMode = (Mode)((currentMode + 1) % MODE_TOTAL);
      } else {
        currentMode = (Mode)((currentMode - 1 + MODE_TOTAL) % MODE_TOTAL);
      }
      updateMenuDisplay();
    }
    oldPos = newPos;
  }

  // Vérifier si l'utilisateur a effectué un double-clic sur le bouton de l'encodeur rotatif
  static bool buttonPressed = false;
  static unsigned long buttonPressTime = 0;

 if (digitalRead(encoderButtonPin) == LOW) {
    if (!buttonPressed) {
      // Le bouton vient d'être enfoncé
      buttonPressed = true;
      buttonPressTime = currentMillis;
    } else {
      // Le bouton est déjà enfoncé
      if (currentMillis - buttonPressTime > 50) {
        // Le bouton est toujours enfoncé après 50 ms, donc c'est un double-clic
        // Redémarrer l'Arduino
        asm volatile ("  jmp 0");
      }
    }
  } else {
    // Le bouton n'est pas enfoncé
    buttonPressed = false;
  }
}


void updateMenuDisplay() {
  lcd.clear();
  lcd.setCursor(0, 0);
  switch (currentMode) {
    case MODE_EV1_PARTIELLE:
      lcd.print("EV1 Partielle ");
      lcd.setCursor(0, 2);
      lcd.print("Ouverture(s): ");
      lcd.print(ev1Compteur); // Afficher le compteur pour EV1
      break;
    case MODE_EV2_PARTIELLE:
      lcd.print("EV2 Partielle ");
      lcd.setCursor(0, 2);
      lcd.print("Ouverture(s): ");
      lcd.print(ev2Compteur); // Afficher le compteur pour EV2
      break;
     case MODE_EV1_EV2_PARTIELLE:
      lcd.print("EV1&2 Partielle");
      lcd.setCursor(0, 1);
      lcd.print("Ouvertures EV1: ");
      lcd.setCursor(15, 1);
      lcd.print(ev1Compteur); // Afficher le compteur pour EV1
      lcd.setCursor(0, 2);
      lcd.print("Ouvertures EV2: ");
      lcd.setCursor(15, 2);
      lcd.print(ev2Compteur); // Afficher le compteur pour EV2
      break;
    case MODE_EV1_CONTINU:
      lcd.print("EV1 Continu ");
      break;
    case MODE_EV2_CONTINU:
      lcd.print("EV2 Continu ");
      break;
    case MODE_EV1_EV2_CONTINU:
      lcd.print("EV1&2 Continu ");
      break;
    default:
      break;
  }
}
