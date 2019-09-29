/*
   Motor.h

*/


#ifndef __MOTOR_H__
#define __MOTOR_H__

#include <Arduino.h>

class Motor {
  public:
    Motor(uint8_t const, uint8_t const, uint8_t const);  // Constructeur
    void drive(bool);
    void brake();

  private:
    uint8_t PinA_In1, PinA_In2, PinB_In1;
    void fwd();
    void rev();
};


#endif /* defined(__MOTOR_H__) */
