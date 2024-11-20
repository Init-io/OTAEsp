#include <OTAEsp.h>

OTAEsp otaesp;

void setup() {
    Serial.begin(9600);
    pinMode(LED_BUILTIN, OUTPUT); // Configure the onboard LED
    digitalWrite(LED_BUILTIN, HIGH); // Turn off the LED initially

    Serial.println("[Setup] Starting OTAEsp...");

    // Start AP mode
    otaesp.start("OTAEsp", "12345678");

    // Host an HTML form
    String html = R"rawliteral(
        <!DOCTYPE html>
        <html>
        <head><title>ESP8266 Form</title></head>
        <body>
            <h1>ESP8266 Form</h1>
            <form action="/submit" method="POST">
                SSID: <input type="text" name="ssid"><br>
                Password: <input type="text" name="spass"><br>
                <button type="submit">Submit</button>
            </form>
        </body>
        </html>
    )rawliteral";
    otaesp.host(html);

    Serial.println("[Setup] OTAEsp is ready!");
}

void loop() {
    // Handle server requests
    otaesp.server.handleClient();

    // Debug: Print the form values
    Serial.println(otaesp.get("ssid"));  // Correct field name: "ssid"
    Serial.println(otaesp.get("spass")); // Correct field name: "spass"

    // Connect to Wi-Fi using submitted credentials
    String ssid = otaesp.get("ssid");
    String pass = otaesp.get("spass");

    if (!ssid.isEmpty() && !pass.isEmpty()) { // Ensure values are not empty
        if (otaesp.connect(ssid.c_str(), pass.c_str())) {
            Serial.println("[Loop] Successfully connected to Wi-Fi!");
            otaesp.end();
        } else {
            Serial.println("[Loop] Failed to connect to Wi-Fi.");
        }
    } else {
        Serial.println("[Loop] SSID or Password is empty. Waiting for input...");
    }

    delay(6000);
}
