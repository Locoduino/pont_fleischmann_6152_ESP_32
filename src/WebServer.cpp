/*
   WebSockets.cpp

*/


#include "WebServer.h"

/****************************** Constructeur ******************************/

WebServer::WebServer(uint16_t port) {
  mPort = port;
}

/******************************** begin ********************************/

void WebServer::start() { // Start WebSocket server

  ESP32WebServer WebServer(mPort);

  WebServer::on("/" , [&]() {
    WebServer::send(200, "text/plain", "this works as well");
  });

  WebServer::onNotFound([&]() {
    !Files::handleFileRead(this);
  });

  WebServer::begin();                             // start the HTTP server


#ifdef DEBUG
  Serial.printf("WebServer started on port %d.\n", mPort);
#endif
}
