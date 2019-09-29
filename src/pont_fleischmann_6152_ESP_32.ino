/*
   Automatisation d'un pont tournant FLEISCHMANN 6152 (HO)
   avec un ESP32.

   Christophe Bobille 2017-2019
   chrisophe.bobille@gmail.com

   Voir https://randomnerdtutorials.com/esp32-pinout-reference-gpios/
*/

#define VERSION  "v 1.5"
#define PROJECT  "Pont tournant FLEISCHMANN 6152"


#include "Blink.h"
#include "Config.h"
#include "Parcours.h"
#include "OTA.h"
#include "Sensor.h"
#include "Wifi.h"
#include "WebSockets.h"
#include "WebServer.h"



/******************** Fonction generique calculMillis() ********************/

bool calculMillis (unsigned long previous, unsigned long interval) {
  bool state = false;
  if (interval < millis() - previous)
    state = !state;
  return state;
}


/******************** Instance de Sensor *******************/

// creation des objets capteur hall
Sensor* hall1 = new Sensor(HALL_1);                 // instance de Sensor pour l'initialisation du pont
Sensor* hall2 = new Sensor(HALL_2);                 // instance de Sensor pour le capteur de la roue dentée

/******************** Interruption pour capteurs a effet Hall *******************/

// routines d'interruption pour les capteurs
void IRAM_ATTR isr1() {
  hall1->addCount();                                // incrementation du compteur
}
void IRAM_ATTR isr2() {
  hall2->addCount();                                // incrementation du compteur
}

/******************** Instance de Wifi *******************/

Wifi wifi;

/******************** Instance de Parcours *******************/

Parcours* parcours = new Parcours();

/******************** Instance de Motor **********************/

Motor* motor = new Motor(PIN_A_IN1, PIN_A_IN2, PIN_B_IN1);

/******************** Instance de ESP32WebServer, de Fl_WebSockets et de File **********************/

Files files;
WebServer webServer(80);
Fl_WebSockets webSocket(81);




/*__________________________________________________________SETUP__________________________________________________________*/

void setup (void) {

  Serial.begin (BAUD_RATE);

  pinMode(CABINE, OUTPUT);
  pinMode(HALL_1, INPUT);
  pinMode(HALL_2, INPUT);
  pinMode(FEUX, OUTPUT);
  pinMode(REL_POLARITE_DCC, OUTPUT);

  digitalWrite(HALL_1, HIGH);
  digitalWrite(HALL_2, HIGH);
  digitalWrite(REL_POLARITE_DCC, LOW);

#ifdef DEBUG
  Serial.print(".");
  Serial.print("\n");Serial.print("\nProject :      "); Serial.print(PROJECT);
  Serial.print("\nVersion :      "); Serial.print(VERSION);
  Serial.print("\nCompiled :     "); Serial.print(__DATE__);
  Serial.print(" ");                 Serial.print(__TIME__);
  Serial.print("\n");
#endif


  wifi.begin();
  files.begin();
  webServer.start();
  webSocket.begin();

  OTA::begin();

  // eteindre cabine
  CABINE_L;

  // installation des interruptions pour les capteurs a effet Hall
  attachInterrupt(HALL_1, isr1, FALLING);
  attachInterrupt(HALL_2, isr2, FALLING);

  parcours->addMotor(motor);

  /*************** Initialisation du pont face voie 1 ***************/

  parcours->init();
  //while (hall1->getCount() == 0)             // tant que le compteur de hall1 est egal a 0
  Blink::feux();

  // si le compteur de hall1 est egal a 1
  parcours->stop();                          // arret du processus
  FEUX_L;                                    // arret feux rouge clignotant
  delete hall1;
  detachInterrupt(HALL_1);
#ifdef DEBUG
  Serial.print("\nPont face voie 1\n\n");
#endif
}





/*__________________________________________________________LOOP__________________________________________________________*/


void loop() {

  static int16_t temp = 0;

  if (temp > 0)
    Blink::feux();

  Blink::cabine();

  webServer.handleClient();                     // ecoute du port 80
  webSocket.handle();                           // ecoute du port 81
  ArduinoOTA.handle();                          // ecoute pour OTA events

  //******* Gestion de la messagerie **************

  if (webSocket.msgRx()) {                      // nouveau message
    webSocket.setState(0);                      // on reinitialise l'etat pour la reception
   
    long msg = strtol(webSocket.getInputMsg(), NULL, 2);   // lecture du message
    
    if (msg != 0) {                              // le message n'est pas vide
      // parsing du message
      switch (msg >> 7) {                        // lecture du bit 8
        case 0 :                                 // le message concerne la rotation
          if (temp == 0) {
            byte x, y;                           // declaration de 2 variables temporaires pour le sens et la porte choisie
            if (msg >> 6)                        // sens de sortie
              x = 'R';
            else
              x = 'F';
            y = msg & 0x1F;                       // la variable "y" stocke les 5 derniers bits (porte choisie)
#ifdef DEBUG
            Serial.printf("x : %d\n", x);
            Serial.printf("y : %d\n", y);
#endif
            hall2->reset();
            temp = parcours->setParam(&x, &y);    // temp recoit la valeur retournee soit le nombre de porte à parcourir...
            if (temp < 0) {                       // ... ou si temp est negatif, un message d'erreur
#ifdef DEBUG
              switch (temp) {
                case -1 :
                  Serial.print("\nTrajet non valide\n\n");
                  break;
                case -2 :
                  Serial.print("\nTrajet demandé = position actuelle du pont\n\n");
                  break;
              }
#endif
              temp = 0;
            }
            break;
          }
        case 1 :                                     // autres que la rotation
          switch (msg >> 6) {
            case 0 :                                 // lumiere cabine
              switch (msg & 0x1F) {                  // Lecture des 6 derniers bits
                case 0 :                             // eteindre la lumiere
                  CABINE_L;
                  break;
                case 1 :
                  CABINE_H;
                  break;
                case 2 :                             // stoper l'effet clignotant "vielle ampoule"
                  CABINE_H;
                  Blink::cabineState = 0;
                  break;
                case 3 :                             // activer l'effet clignotant "vielle ampoule"
                  CABINE_H;
                  Blink::cabineState = 1;
                  break;
              }
              break;
          }
          break;
      }
    }
  }
  
  if (temp == hall2->getCount()) {
    parcours->stop();
    temp = 0;
    FEUX_L;
  }
}
