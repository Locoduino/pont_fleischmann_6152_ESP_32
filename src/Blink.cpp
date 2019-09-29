/*
   Concerne les fonctions liees aux eclairages, feux rouge en bout de pont et
   simulation de vielle ampoule pour la cabine.
*/

#include "Blink.h"

int                       Blink::feuxState {LOW};
unsigned long             Blink::previousMillisFeux {0};
const unsigned int        Blink::intervalFeux {1000};
int                       Blink::cabineState {LOW};
unsigned long             Blink::previousMillisCabine {0};
unsigned int              Blink::intervalCabine {1000};
unsigned long             Blink::eclCabineDuree {0};
int                       Blink::eclCabineRepetition{0};


void Blink::feux() {
  if (calculMillis (previousMillisFeux, intervalFeux)) {
    previousMillisFeux = millis();
    feuxState = !feuxState;
    feuxState ? FEUX_H : FEUX_L;
  }
}

void Blink::cabine() {
  if (cabineState) {
    if (calculMillis (previousMillisCabine, intervalCabine)) {
      previousMillisCabine = millis();
      eclCabineRepetition  = random (2, 5);   // Repetition
      for ( int i = 1; i <= eclCabineRepetition; i++) {
        eclCabineDuree = random (10, 100);    // Duree de 0,01 à 0,1 secondes
        CABINE_L;
        delay(eclCabineDuree);
        eclCabineDuree = random (10, 100);    // Duree de 0,01 à 0,1 secondes
        CABINE_H;
        delay(eclCabineDuree);
      }
      intervalCabine  = random (2000, 10000);   // Frequence de 2 à 10 secondes
    }
  }
}
