#include "OTAEsp.h"

// Constructor
OTAEsp::OTAEsp() : server(80) {}

// Start AP mode
void OTAEsp::start(const char *ssid, const char *password) {
    Serial.println("[OTAEsp] Starting AP...");
    WiFi.softAP(ssid, password);

    // Configure static IP (optional but improves reliability)
    WiFi.softAPConfig(IPAddress(192, 168, 4, 1), IPAddress(192, 168, 4, 1), IPAddress(255, 255, 255, 0));

    Serial.println("[OTAEsp] AP Started!");
    Serial.print("[OTAEsp] IP Address: ");
    Serial.println(WiFi.softAPIP());
}

// Stop AP mode
void OTAEsp::end() {
    Serial.println("[OTAEsp] Stopping AP...");
    server.stop();
    WiFi.softAPdisconnect(true);
    Serial.println("[OTAEsp] AP Stopped!");
}

// Host the provided HTML page
void OTAEsp::host(const String &html) {
    Serial.println("[OTAEsp] Setting up HTML page...");
    server.on("/", [this, html]() {
        Serial.println("[OTAEsp] Client requested the HTML page.");
        digitalWrite(LED_BUILTIN, LOW); // Turn on LED when the page is accessed
        server.send(200, "text/html", html);
        digitalWrite(LED_BUILTIN, HIGH); // Turn off LED after serving
    });

    server.onNotFound([]() {
        Serial.println("[OTAEsp] Client requested an unknown route.");
    });

    server.begin();
    Serial.println("[OTAEsp] HTML page is now hosted!");
}

// Get the value of a specific form field
String OTAEsp::get(const String &fieldName) {
    if (server.hasArg(fieldName)) {
        Serial.print("[OTAEsp] Received field: ");
        Serial.print(fieldName);
        Serial.print(" = ");
        Serial.println(server.arg(fieldName));
        return server.arg(fieldName);
    }
    Serial.print("[OTAEsp] Field not found: ");
    Serial.println(fieldName);
    return "";
}

// Connect to a Wi-Fi network
bool OTAEsp::connect(const char *ssid, const char *password) {
    Serial.println("[OTAEsp] Connecting to Wi-Fi...");
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);

    int attempts = 0;
    while (WiFi.status() != WL_CONNECTED && attempts < 20) {
        delay(500);
        Serial.print(".");
        attempts++;
    }

    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("\n[OTAEsp] Connected to Wi-Fi!");
        Serial.print("[OTAEsp] IP Address: ");
        Serial.println(WiFi.localIP());
        return true;
    } else {
        Serial.println("\n[OTAEsp] Failed to connect to Wi-Fi.");
        return false;
    }
}

// Check if the ESP is connected to a Wi-Fi network
bool OTAEsp::isConnected() {
    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("[OTAEsp] ESP is connected to Wi-Fi.");
        return true;
    } else {
        Serial.println("[OTAEsp] ESP is NOT connected to Wi-Fi.");
        return false;
    }
}
