//
//  Sensor.h
//
//
//  Created by Christophe on 12/09/2017.
//
//

#ifndef ___SENSOR_H__
#define ___SENSOR_H__


#include "Config.h"
#include "Arduino.h"

class Sensor {

  private:
    uint8_t                   m_inPin;
    volatile uint8_t          m_counter;
    bool                      m_state;

  public:
    // Constructeur
    Sensor(const uint8_t);

    void init();
    uint8_t read();
    void reset();
    void addCount();
    uint8_t getCount();

};


#endif /* defined(___SENSOR_H__) */
