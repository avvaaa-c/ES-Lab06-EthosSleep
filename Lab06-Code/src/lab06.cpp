#include <Arduino.h>
#include <esp.h>
//#include <Wifi.h>
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
// be able to talk.
#define SCL 22  // Use default SCL for Huzzah32
#define SDA 23  // Use default SDA for Huzzah32
#define SensorI2CAddress 0x40  // This is the default address for the 7021 and HTU21DF Sensor.

// Support for 2 sensor boards:  Si7021(5-pin with unpined 3.3V), HTU21D (4-pin smaller board)
// If you have the HTU21DF part, uncomment the next #define line!
//#define HTU21DF true
#ifndef HTU21DF
Adafruit_Si7021 sensor = Adafruit_Si7021();
#else
Adafruit_HTU21DF sensor = Adafruit_HTU21DF();
#endif

// Sensor variables
float humidity = 0;
float temp = 0;

// Sleep Time  Need to figure out proper time
#define deepSleepTime TBD
fix_above_line_then_delete_this_line_compile_error();

// Prototype Functions
void dummyPrototypeFunction ();

void setup() {
  Serial.begin(115200);
  // wait for serial port to open
  while (!Serial) {
    delay(10);
  }
  Serial.println("I'm awake!");

  
  // Prep the sleep routine
  Serial.print("I'm getting sleepy");
}

void loop() {
 
}

void dummyProtoFunction () {
  // Dummy function
}
