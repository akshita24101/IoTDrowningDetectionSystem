#include <LiquidCrystal.h>
#include <SoftwareSerial.h>

// LCD pins: RS, EN, D4, D5, D6, D7
LiquidCrystal lcd(7, A3, A1, A2, A0, 11);

// ESP8266 SoftwareSerial on D12 (RX), D13 (TX)
SoftwareSerial espSerial(12, 13); // Arduino RX, TX

// Sensor pins
const int trigPin = 5;
const int echoPin = 6;
const int pirPin = 4;

// Wi-Fi credentials and ThingSpeak
String ssid = "YOUR_SSID"; // Replace with your Wi-Fi SSID
String password = "YOUR_PASSWORD"; // Replace with your Wi-Fi password
String apiKey = "YOUR_WRITE_API_KEY"; // Replace with ThingSpeak Write API key
const char* server = "api.thingspeak.com";

// Threshold for demonstration
const int demoDistance = 10; // cm (for hand detection)

void setup() {
  Serial.begin(9600);
  espSerial.begin(115200); // Use 9600 if 115200 doesn’t work
  lcd.begin(16, 2);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(pirPin, INPUT);

  lcd.print("Connecting WiFi");
  connectWiFi();
  lcd.clear();
}

void loop() {
  // Measure distance
  digitalWrite(trigPin, LOW); delayMicroseconds(2);
  digitalWrite(trigPin, HIGH); delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH);
  int distance = duration * 0.034 / 2;

  // PIR reading
  int pirValue = digitalRead(pirPin);
  bool drowning = (distance <= demoDistance && pirValue == HIGH);

  // Display on LCD
  lcd.setCursor(0, 0);
  lcd.print("Dist: ");
  lcd.print(distance);
  lcd.print(" cm   ");

  lcd.setCursor(0, 1);
  if (drowning) {
    lcd.print(">>> DROWNING <<<");
  } else {
    lcd.print("All OK          ");
  }

  // Send to ThingSpeak
  sendToThingSpeak(distance, pirValue, drowning);

  delay(15000); // ThingSpeak requires minimum 15s delay between posts
}

void connectWiFi() {
  sendCommand("AT+RST", 2000);
  sendCommand("AT+CWMODE=1", 1000);
  sendCommand("AT+CWJAP=\"" + ssid + "\",\"" + password + "\"", 6000);
}

void sendToThingSpeak(int distance, int pirValue, bool drowning) {
  String data = "GET /update?api_key=" + apiKey;
  data += "&field1=" + String(distance);
  data += "&field2=" + String(pirValue);
  data += "&field3=" + String(drowning ? 1 : 0);

  Serial.println("=== ThingSpeak Request ===");
  Serial.println(data);

  sendCommand("AT+CIPSTART=\"TCP\",\"" + String(server) + "\",80", 2000);
  sendCommand("AT+CIPSEND=" + String(data.length() + 2), 1000);
  espSerial.print(data + "\r\n");

  Serial.println("✅ Sent to ESP8266. Awaiting response:");
  long timeout = millis();
  while ((millis() - timeout) < 5000) {
    while (espSerial.available()) {
      char c = espSerial.read();
      Serial.write(c);
    }
  }
  Serial.println("==========================");
}

void sendCommand(String cmd, const int timeout) {
  espSerial.println(cmd);
  long int time = millis();
  while ((millis() - time) < timeout) {
    while (espSerial.available()) {
      char c = espSerial.read();
      Serial.write(c);
    }
  }
}
