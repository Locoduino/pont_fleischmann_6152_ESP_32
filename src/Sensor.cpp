


#include "Sensor.h"


Sensor::Sensor(const uint8_t inPin) {   //Constructeur
  m_inPin = inPin;
  m_counter = 0;
  m_state;
}

uint8_t Sensor::read() {
  m_state = digitalRead(m_inPin);
  return m_state;
}

void Sensor::reset() {
  m_counter = 0;
}

void Sensor::addCount() {
  m_counter++;
#ifdef DEBUG
  Serial.println(m_counter);
#endif
}

uint8_t Sensor::getCount() {
  return m_counter;
}
