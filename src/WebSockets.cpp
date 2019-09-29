/*
   WebSockets.cpp

*/


#include "WebSockets.h"

/****************************** Constructeur ******************************/

Fl_WebSockets::Fl_WebSockets(uint16_t port) {
  mPort = port;
  mInputMsg = NULL;
  ptWss = NULL;
  mState = 0;
}

/******************************** begin ********************************/

void Fl_WebSockets::begin() { // Start WebSocket server
  ptWss = new WebSocketsServer(mPort);
  ptWss->begin();
  ptWss->onEvent([&](uint8_t num, WStype_t type, uint8_t * payload, size_t length) {
    switch (type) {
      case WStype_DISCONNECTED:
      delete ptWss;
#ifdef DEBUG
        Serial.printf("Wifi [%u] Disconnected!\n", num);
#endif
        break;
      case WStype_CONNECTED: {
          IPAddress ip = ptWss->remoteIP(num);
#ifdef DEBUG
          Serial.printf("Wifi [%u] Connected from %d.%d.%d.%d url: %s\n", num, ip[0], ip[1], ip[2], ip[3], payload);
#endif
          ptWss->sendTXT(num, "Connected");
        }
        break;
      case WStype_TEXT:
#ifdef DEBUG
        Serial.printf("Wifi [%u] get Text: %s\n", num, payload);
#endif

        mInputMsg = (char*)payload;
        mState = 1;
        break;
    }
  });
  Serial.printf("WebSocket started on port %d.\n", mPort);
}

/******************************** loop ********************************/

void Fl_WebSockets::handle() {
  ptWss->loop();
}

/******************************** getInputMsg ********************************/

const char* Fl_WebSockets::getInputMsg() {
  return mInputMsg;
}

/******************************** msgRx ********************************/

int Fl_WebSockets::msgRx() {
  return mState;
}

/******************************** broadcastTXT ********************************/

bool Fl_WebSockets::broadcastTXT(const char * text) {
  ptWss->broadcastTXT(text);
}

void Fl_WebSockets::setState(bool state) {
  mState = state;
}
