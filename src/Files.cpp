/*
   Files.cpp

*/


#include "Files.h"

void Files::begin() {
  SPIFFS.begin();
  listDir(SPIFFS, "/", 0);
}

bool Files::handleFileRead(ESP32WebServer* webServer) { // send the right file to the client (if it exists)
  String path = webServer->uri();
  Serial.println("handleFileRead: " + path);
  if (path.endsWith("/")) path += "index.html";          // If a folder is requested, send the index file
  String contentType = getContentType(path);             // Get the MIME type
  String pathWithGz = path + ".gz";
  if (SPIFFS.exists(pathWithGz) || SPIFFS.exists(path)) { // If the file exists, either as a compressed archive, or normal
    if (SPIFFS.exists(pathWithGz))                          // If there's a compressed version available
      path = pathWithGz;                                      // Use the compressed verion
    File file = SPIFFS.open(path, "r");                    // Open the file
    size_t sent = webServer->streamFile(file, contentType);    // Send it to the client
    file.close();                                          // Close the file again
    Serial.println(String("\tSent file: ") + path);
    return true;
  }
  Serial.println(String("\tFile Not Found: ") + path);   // If the file doesn't exist, return false
  return false;
}


void Files::listDir(fs::FS &fs, const char * dirname, uint8_t levels) {
  Serial.printf("Listing directory: %s\r\n", dirname);

  File root = fs.open(dirname);
  if (!root) {
    Serial.print("- failed to open directory\n");
    return;
  }
  if (!root.isDirectory()) {
    Serial.print(" - not a directory\n");
    return;
  }

  File file = root.openNextFile();
  while (file) {
    if (file.isDirectory()) {
      Serial.print("  DIR : ");
      Serial.print(file.name());
      Serial.print("\n");
      if (levels)
        listDir(fs, file.name(), levels - 1);

    } else {
      Serial.print("  FILE: ");
      Serial.print(file.name());
      Serial.print("\t\tSIZE: ");
      Serial.print(formatBytes(file.size()));
      Serial.print("\n");
    }
    file = root.openNextFile();
  }
  Serial.print("\n\n");
}

/*__________________________________________________________HELPER_FUNCTIONS__________________________________________________________*/

String Files::formatBytes(size_t bytes) { // convert sizes in bytes to KB and MB
  if (bytes < 1024) {
    return String(bytes) + " B";
  } else if (bytes < (1024 * 1024)) {
    return String(bytes / 1024.0) + " KB";
  } else if (bytes < (1024 * 1024 * 1024)) {
    return String(bytes / 1024.0 / 1024.0) + " MB";
  }
}

String Files::getContentType(String filename) { // determine the filetype of a given filename, based on the extension
  if (filename.endsWith(".html")) return "text/html";
  else if (filename.endsWith(".css")) return "text/css";
  else if (filename.endsWith(".js")) return "application/javascript";
  else if (filename.endsWith(".ico")) return "image/x-icon";
  else if (filename.endsWith(".gz")) return "application/x-gzip";
  return "text/plain";
}
