



#include "Motor.h"

// Constructeur
Motor::Motor(uint8_t const PinA_In1, uint8_t const PinA_In2, uint8_t const PinB_In1) {
  this->PinA_In1 = PinA_In1;
  this->PinA_In2 = PinA_In2;
  this->PinB_In1 = PinB_In1;

  pinMode(PinA_In1, OUTPUT);
  pinMode(PinA_In2, OUTPUT);
  pinMode(PinB_In1, OUTPUT);

  //digitalWrite(PinA_Pwm, LOW);
  digitalWrite(PinA_In1, LOW);
  digitalWrite(PinA_In2, HIGH);
  digitalWrite(PinB_In1, HIGH);
}

void Motor::drive(bool dir) {
  if (dir == 0)
    rev();
  else
    fwd();
}

void Motor::brake() {
  digitalWrite(PinB_In1, HIGH);
}

void Motor::fwd() {
  digitalWrite(PinA_In1, HIGH);
  digitalWrite(PinA_In2, HIGH);
  digitalWrite(PinB_In1, LOW);
}

void Motor::rev() {
  digitalWrite(PinA_In1, LOW);
  digitalWrite(PinA_In2, LOW);
  digitalWrite(PinB_In1, LOW);
}
