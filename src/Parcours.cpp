

#include "Parcours.h"


// Constructeur
Parcours::Parcours()
  : m_trackIn(0)
  , m_trackOut(0)
  , m_currentTrack(0)
  , m_dir(0)
  , m_temp(0)
  , m_sens('F')
  , m_motor()
{}

void Parcours::addMotor(Motor *motor) {
  m_motor = motor;
}

int8_t Parcours::setParam(const uint8_t *n, const uint8_t *s) {

  if (*n > 0 && *n <= 48) {

    m_dir = 0;
    char sens = 'F';
    // F, la loco va sortir en marche avant
    // R, la loco va sortir en marche arriere (cas general par defaut)

    if (*s != 'F')  // Si s n'est pas 'F' cad 'R' ou rien -> valeur par defaut = 'R'
      sens = 'R';

    if (*n == m_currentTrack && sens == m_sens)
      return -2;  // Position actuelle du pont

    switch (sens) {
      case 'R' :
        m_temp = abs(m_currentTrack - *n);
        m_trackOut = *n;
        break;
      case 'F' :
        m_temp = abs((m_currentTrack - *n) + 24);
        if (*n > 24)
          m_trackOut = *n - 24;
        else
          m_trackOut = *n + 24;
        break;
    }

    if (*n < m_currentTrack)
      m_dir = !m_dir;

    if (m_temp >= 24) {
      m_temp = 48 - m_temp;
      m_dir = !m_dir;
    }

    if (m_trackOut < m_currentTrack && sens == 'F')
      m_dir = !m_dir;

    m_sens = sens;

    if (m_temp == 0)
      return -2;  // Position actuelle du pont



#ifdef DEBUG
    Serial.print("currentTrack : "); Serial.println(m_currentTrack);
    Serial.print("temp : "); Serial.println(m_temp);
    Serial.print("sens : "); Serial.println(m_sens);
    Serial.print("dir : "); Serial.println(m_dir);
    Serial.print("trackOut : "); Serial.println(m_trackOut);
    Serial.println("");
#endif

    Parcours::run(m_temp, m_dir);
    return m_temp;
  }
  return 1; // $error
}

/******************** init **************************/
void Parcours::init() {
  m_trackOut = 1;
  m_currentTrack = m_trackOut;
  m_motor->drive(0);
}

/******************** run **************************/
void Parcours::run(uint8_t temp, uint8_t dir) {
  // Polarite
  if (dir == 1)
    digitalWrite(REL_POLARITE_DCC, LOW);
  else
    digitalWrite(REL_POLARITE_DCC, HIGH);
  m_motor->drive(dir);
}

/******************** stop **************************/
void Parcours::stop() {
  m_motor->brake();
  m_currentTrack = m_trackOut;
}

/******************** getTrackOut ********************/
//int8_t Parcours::getTrackOut() {
//  return m_trackOut;
//}
