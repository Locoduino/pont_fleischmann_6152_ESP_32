
/*
   WebServ.h

*/

#ifndef _WebServ_H_
#define _WebServ_H_

#include <Arduino.h>
#include <ESP32WebServer.h>
#include "Config.h"
#include "Files.h"


class WebServer : public ESP32WebServer {

  private:
    uint16_t mPort;

  public:
    WebServer (uint16_t);
    void start();
    void handleNotFound();
    bool handleFileRead(String);
    void handleFileUpload();
};


#endif /* defined(_WebServ_H_) */
