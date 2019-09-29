/*
   Blink.h

*/



#ifndef __Blink_H__
#define __Blink_H__

#include "Arduino.h"
#include "Config.h"

struct Blink {
  static int feuxState;
  static unsigned long previousMillisFeux;
  static const unsigned int intervalFeux;
  static int cabineState;
  static unsigned long previousMillisCabine;
  static unsigned int intervalCabine;
  static unsigned long eclCabineDuree;
  static int eclCabineRepetition;
  static void feux();
  static void cabine();
};

#endif  /* defined(__Blink_H__) */
