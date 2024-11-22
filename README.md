# OTAEsp - ESP8266 OTA Library

**OTAEsp** is a simple library for the ESP8266 platform that allows you to easily set up an access point (AP) to serve an HTML page, retrieve form data, and connect the device to a Wi-Fi network. It is ideal for implementing Over-the-Air (OTA) updates, web interfaces, or simple device configuration over a network.

## Features

- **Start an Access Point (AP)**: Allows the ESP8266 to create a Wi-Fi access point that clients can connect to.
- **Serve an HTML Page**: Hosts an HTML page on the ESP8266, accessible via the AP's IP address.
- **Form Handling**: Retrieves form data submitted by clients in an HTTP request.
- **Wi-Fi Connection**: Connects the ESP8266 to a Wi-Fi network in station mode (STA).

## Installation

1. Download or clone the repository to your Arduino libraries folder or your custom project folder.
2. Include the `OTAEsp` library in your Arduino sketch.

```cpp
#include <OTAEsp.h>
```

## Usage

### 1. Initialize and Start the Access Point (AP)
To start the AP mode, use the `start()` method with the SSID and password for the AP.

```cpp
OTAEsp ota;
ota.start("MyESP8266", "password123");
```

### 2. Serve an HTML Page
Use the `host()` method to serve an HTML page to connected clients.

```cpp
String htmlPage = "<html><body><h1>Hello, World!</h1></body></html>";
ota.host(htmlPage);
```

### 3. Retrieve Form Data
To retrieve the value of a specific form field submitted via the HTML page, use the `get()` method.

```cpp
String fieldValue = ota.get("fieldName");
Serial.println("Received field value: " + fieldValue);
```

### 4. Connect to a Wi-Fi Network
To connect the ESP8266 to a Wi-Fi network, use the `connect()` method.

```cpp
if (ota.connect("yourSSID", "yourPassword")) {
    // Successfully connected to Wi-Fi
} else {
    // Failed to connect to Wi-Fi
}
```

### 5. Stop the Access Point
If you want to check if the wifi is connected, use the `isConnected()` method.

```cpp
ota.isConnected();
```

### 6. Stop the Access Point
If you want to stop the AP mode, use the `end()` method.

```cpp
ota.end();
```

## Example Sketch

Here’s an example of how to use the library in a full sketch:

```cpp
#include <OTAEsp.h>

OTAEsp ota;

void setup() {
    Serial.begin(115200);
    ota.start("ESP8266-AP", "12345678");

    String htmlPage = "<html><body><h1>ESP8266 Web Interface</h1></body></html>";
    ota.host(htmlPage);
}

void loop() {
    ota.server.handleClient();
}
```

## Functions

### `void start(const char *ssid, const char *password)`
- **Description**: Starts the ESP8266 in Access Point (AP) mode with the specified SSID and password.
- **Parameters**:
  - `ssid`: The SSID of the access point.
  - `password`: The password for the access point.

### `void end()`
- **Description**: Stops the AP mode and disconnects the ESP8266 from the network.

### `void host(const String &html)`
- **Description**: Hosts an HTML page at the root endpoint (`/`) of the server.
- **Parameters**:
  - `html`: The HTML content to serve.

### `String get(const String &fieldName)`
- **Description**: Retrieves the value of a specific form field submitted by a client.
- **Parameters**:
  - `fieldName`: The name of the form field to retrieve.
- **Returns**: The value of the form field as a string, or an empty string if not found.

### `bool connect(const char *ssid, const char *password)`
- **Description**: Connects the ESP8266 to a specified Wi-Fi network.
- **Parameters**:
  - `ssid`: The SSID of the Wi-Fi network.
  - `password`: The password for the Wi-Fi network.
- **Returns**: `true` if the connection is successful, `false` if it fails.

## Debugging

The library prints status messages to the Serial Monitor to help with debugging:
- When starting or stopping the AP.
- When the HTML page is served.
- When the device is connecting to a Wi-Fi network.
- When form data is received.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Acknowledgements

- This library is designed for the **ESP8266** platform, which is part of the ESP32/ESP8266 series of Wi-Fi microcontrollers.
- The code makes use of the `ESP8266WiFi` and `ESP8266WebServer` libraries.

## Contributing

Feel free to fork this repository, make improvements, and submit pull requests. Any contributions are welcome!

## Author

[Init]  
[Your GitHub Profile](https://github.com/Init-io)
