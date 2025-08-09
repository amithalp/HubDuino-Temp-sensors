// -------User setup
//--Update IPAddress for device
//--Update IPAddress for gateway (Router)
//--Update IPAddress for hubIP (hubitat hub)
//--Optional
//------Update TEMP_SEND_INTERVAL = 60000;     // 60 seconds
//------Update CONNECTION_TIMEOUT = 180000;     // 180 seconds

#include <SPI.h>
#include <Ethernet.h>
#include <SmartThings.h>
#include <SmartThingsEthernetW5x00.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// ---------- Ethernet Setup ----------
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x01 };
IPAddress ip(10, 21, 1, 160);
IPAddress gateway(10, 21, 1, 1);
IPAddress subnet(255, 255, 255, 0);
IPAddress dns(8, 8, 8, 8);

// Hubitat setup
IPAddress hubIP(10, 21, 1, 74);
const unsigned int hubPort = 39501;

// ---------- DS18B20 Setup ----------
#define ONE_WIRE_BUS 32
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

// ---------- OLED Setup (SSD1315) ----------
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// ---------- HubDuino ----------
st::SmartThingsEthernetW5x00* smartthing;

// ---------- Status Tracking ----------
unsigned long lastSend = 0;
unsigned long lastSuccessfulSend = 0;
const unsigned long TEMP_SEND_INTERVAL = 60000;     // 60 seconds
const unsigned long CONNECTION_TIMEOUT = 180000;     // 180 seconds

void setup() {
  Serial.begin(115200);
  delay(1000);

  // Start Ethernet
  Ethernet.init(5); // CS pin for W5500
  smartthing = new st::SmartThingsEthernetW5x00(
    mac, ip, gateway, subnet, dns,
    8090,
    hubIP, hubPort,
    nullptr,
    "EthernetShield",
    true,
    500
  );
  smartthing->init();

  // Start DS18B20
  sensors.begin();

  // Start OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1315 OLED not found"));
    for (;;);
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Pool Monitor Ready");
  display.display();
  delay(1000);
}

void loop() {
  if (millis() - lastSend >= TEMP_SEND_INTERVAL) {
    sensors.requestTemperatures();
    float tempPool = sensors.getTempCByIndex(0);
    float tempRoom = sensors.getTempCByIndex(1);

    Serial.print("Pool Temp: "); Serial.println(tempPool);
    Serial.print("Room Temp: "); Serial.println(tempRoom);

    // Send to Hubitat
    smartthing->send("temperature1 " + String(tempPool, 1));
    smartthing->send("temperature2 " + String(tempRoom, 1));
    lastSuccessfulSend = millis();  // assume success

    // Display
    display.clearDisplay();

    // Pool Temp
    display.setTextSize(2);
    display.setCursor(0, 0);
    display.print("Pool:");
    display.print(tempPool, 1);
    display.println("C");

    // Room Temp
    display.setCursor(0, 20);
    display.print("Room:");
    display.print(tempRoom, 1);
    display.println("C");

    // IP and status
    display.setTextSize(1);
    display.setCursor(0, 45);
    display.print("IP: ");
    display.println(ip);

    display.print("Status: ");
      if (Ethernet.linkStatus() == LinkON && millis() - lastSuccessfulSend <= CONNECTION_TIMEOUT) {
           display.println("OK");
      } else {
      display.println("FAIL");
          }


    display.display();
    lastSend = millis();
  }
}
