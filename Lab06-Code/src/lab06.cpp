#include <Arduino.h>
#include <esp.h>
#include <string.h>
#include "Adafruit_Si7021.h"
#include "Adafruit_HTU21DF.h"
#include <LiquidCrystal_I2C.h>

// Globals

// Note:  lcd.init() calls the Wire.h builtin that uses the default
// I2C bus for the ESP32.  Defines below show should show these pin numbers!
// For other boards, there may be a way to pre-initilize the
// Wire object with this data, but seems to be working with defaults.
// For the Adafruit sensors, Sensor.begin() does the same thing, but you
// cannot do both lcd.init() and Sensor.begin()!  However, if we remove
// the lcd, you will need to add back the Sensor.begin() or you will not
// be able to talk to the sensor.
#define SCL 22  // Use default SCL for Huzzah32
#define SDA 23  // Use default SDA for Huzzah32
#define SensorI2CAddress 0x40  // Default address for Si7021 and HTU21DF

// Support for 2 sensor boards: Si7021 (5-pin), HTU21D (4-pin smaller board)
// If you have the HTU21DF part, uncomment the next #define line!
//#define HTU21DF true
#ifndef HTU21DF
Adafruit_Si7021 sensor = Adafruit_Si7021();
#else
Adafruit_HTU21DF sensor = Adafruit_HTU21DF();
#endif

// LCD address (common values: 0x27 or 0x3F - check yours if display blank)
#define LCDI2CAddress 0x27
// Setup for 16 columns and 2 rows.
LiquidCrystal_I2C lcd(LCDI2CAddress, 16, 2);

// Sensor variables
float humidity = 0;
float temp = 0;
// LCD/serial print buffers (16 chars max for LCD)
char tempStr[16];
char humidityStr[16];

// Deep sleep configuration
#define uS_TO_S_FACTOR 1000000ULL  // Microseconds to seconds conversion
#define SLEEP_TIME_SEC 10          // Deep sleep duration in seconds
#define DOT_COUNT      50          // Number of dots to print before sleeping
#define DOT_INTERVAL_MS 100        // Delay between dots (50 * 100ms = 5 seconds)

void setup() {
  Serial.begin(115200);
  while (!Serial) {
    delay(10);
  }
  Serial.println("I'm awake!");

  // Initialize LCD (also initializes the I2C bus for the sensor)
  lcd.init();
  lcd.backlight();

  // Read sensor values (no sensor.begin() needed - lcd.init() already set up I2C)
  temp = sensor.readTemperature();
  float tempF = (temp * 9.0 / 5.0) + 32.0;
  humidity = sensor.readHumidity();

  // Build minimal display strings
  sprintf(tempStr,     "T=%.1fF",  tempF);
  sprintf(humidityStr, "H=%.1f%%", humidity);

  // Print to serial
  Serial.print(tempStr);
  Serial.print(" ");
  Serial.println(humidityStr);

  // Display on LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(tempStr);
  lcd.setCursor(0, 1);
  lcd.print(humidityStr);

  // Announce upcoming sleep - no newline so dots follow on same line
  Serial.print("I'm getting sleepy");
}

void loop() {
  // Print 50 dots, one every 100ms (5 seconds total of active measurement)
  for (int i = 0; i < DOT_COUNT; i++) {
    Serial.print(".");
    delay(DOT_INTERVAL_MS);
  }
  Serial.println();
  Serial.println("Good night!");

  // Configure timer wakeup and enter deep sleep
  esp_sleep_enable_timer_wakeup(SLEEP_TIME_SEC * uS_TO_S_FACTOR);
  esp_deep_sleep_start();
}
