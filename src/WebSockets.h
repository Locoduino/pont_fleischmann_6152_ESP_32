
/*
   WebSockets.h

*/

#ifndef _webSockets_H_
#define _webSockets_H_

#include <Arduino.h>
#include <WebSocketsServer.h> 
#include "Config.h"
 


class Fl_WebSockets {

  private:
    uint16_t mPort;
    char*    mInputMsg;
    int      mState;

  public:
    Fl_WebSockets(uint16_t port);
    WebSocketsServer* ptWss;

    void begin();
    const char* getInputMsg();
    int msgRx();
    void handle();
    bool broadcastTXT(const char *);
    void onWsEvent(uint8_t, WStype_t, uint8_t *, size_t);
    void setState(bool);
};


#endif /* defined(_webSockets_H_) */
