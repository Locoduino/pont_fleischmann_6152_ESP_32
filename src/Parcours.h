//
//  Parcours.h
//
//
//  Created by Christophe on 12/09/2017.
//

#ifndef ___Parcours_H__
#define ___Parcours_H__

#include <Arduino.h>
#include <WiFiClient.h>
#include "Config.h"
#include "Motor.h"


static int currentTrack;

class Parcours {

  private:
    uint8_t m_dir;
    uint8_t m_temp;
    char    m_sens;
    uint8_t m_trackOut;
    uint8_t m_trackIn;
    uint8_t m_currentTrack;
    Motor * m_motor;

  public:
    Parcours(); // Constructeur
    int8_t setParam(const uint8_t *, const uint8_t *);
    void init();
    void run(uint8_t, uint8_t);
    void stop();
    //int8_t getTrackOut();
    void addMotor(Motor *);
};

#endif /* defined(___Parcours_H__) */
