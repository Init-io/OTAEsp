#ifndef OTAESP_H
#define OTAESP_H

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

class OTAEsp {
public:
    OTAEsp();
    void start(const char *ssid, const char *password);
    void end();
    void host(const String &html);
    String get(const String &fieldName);
    bool connect(const char *ssid, const char *password);

    ESP8266WebServer server; // Expose the server to allow debugging in `loop`
};

#endif
