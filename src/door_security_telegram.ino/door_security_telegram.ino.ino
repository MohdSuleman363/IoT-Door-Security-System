#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>

// ================== WiFi Credentials ==================
const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";

// ================== Telegram Credentials ==================
const String BOT_TOKEN = "YOUR_BOT_TOKEN";   // without "bot"
const String CHAT_ID  = "YOUR_CHAT_ID";

// ================== Hardware ==================
#define BUTTON_PIN D2   // GPIO4

// ================== Telegram Server ==================
const char* HOST = "api.telegram.org";
const int HTTPS_PORT = 443;

// ================== State ==================
bool lastButtonState = HIGH;

void setup() {
  Serial.begin(115200);
  pinMode(BUTTON_PIN, INPUT_PULLUP);  // internal pull-up

  Serial.println();
  Serial.print("Connecting to WiFi");

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  bool currentState = digitalRead(BUTTON_PIN);

  // Trigger only once per press
  if (lastButtonState == HIGH && currentState == LOW) {
    Serial.println("Button pressed! Sending Telegram alert...");
    sendTelegramMessage("Alert! Door opened.");
  }

  lastButtonState = currentState;
  delay(50); // debounce
}

void sendTelegramMessage(String message) {
  WiFiClientSecure client;
  client.setInsecure(); // skip SSL certificate check

  if (!client.connect(HOST, HTTPS_PORT)) {
    Serial.println("Telegram connection failed");
    return;
  }

  String url = "/bot" + BOT_TOKEN +
               "/sendMessage?chat_id=" + CHAT_ID +
               "&text=" + urlencode(message);

  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + HOST + "\r\n" +
               "Connection: close\r\n\r\n");

  while (client.connected()) {
    String line = client.readStringUntil('\n');
    if (line == "\r") break;
  }

  Serial.println("Telegram alert sent");
}

// ================== URL Encode Function ==================
String urlencode(String str) {
  String encoded = "";
  char c;
  char code[4];

  for (int i = 0; i < str.length(); i++) {
    c = str.charAt(i);
    if (isalnum(c)) {
      encoded += c;
    } else {
      sprintf(code, "%%%02X", c);
      encoded += code;
    }
  }
  return encoded;
}
