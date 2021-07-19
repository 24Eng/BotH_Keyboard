// 24 Hour Engineer
// Brian McEvoy
// https://www.24hourengineer.com/

// This code was tested on "Heltec WiFi Kit 32"
// https://robotzero.one/heltec-wifi-kit-32/
// https://www.amazon.com/KeeYees-Internet-Development-Display-Bluetooth/dp/B07THGMMV8

// The Bluetooth keyboard library comes from
// https://github.com/T-vK/ESP32-BLE-Keyboard

// The accelerometer library is from good ole' Adafruit
// https://learn.adafruit.com/adafruit-lis3dh-triple-axis-accelerometer-breakout/arduino

#include <BleKeyboard.h>
BleKeyboard bleKeyboard("BackOfTheHand Keyboard", "24Eng", 100);

#include <Arduino.h>
#include <U8g2lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, /* clock=*/ 15, /* data=*/ 4, /* reset=*/ 16);

// Add the libraries exclusive to the accelerometer
// Some of the previous libraries are also necessary
#include <Adafruit_LIS3DH.h>
#include <Adafruit_Sensor.h>
Adafruit_LIS3DH lis = Adafruit_LIS3DH();

#include <EEPROM.h>
/*
Each setting gets its own EEPROM address for non-volatile storage, even bools
Usage:      EEPROM.write(addr, val);

  Table
EEPROM.write(0, vibrationSetting);
EEPROM.write(1, audioSetting);
EEPROM.write(2, screenTimeout);
EEPROM.write(3, volumeAdjustmentFactor);
EEPROM.write(4, diagnosticPrintBit);
EEPROM.write(5, AppleProducts);
 */

int keyswitchLocations[] = {36, 37, 38, 39};
int encoderPinLocations[] = {34, 35, 32};
int vibratorPin = 23;
int piezoElementPin = 19;

bool startupBit = true;
bool diagnosticPrintBit = HIGH;
bool oldReading[4];
bool currentState[4];
bool risingEdge[4];
bool fallingEdge[4];
long cooldownTimer[5];
int cooldownWait = 100;
int encoderPinLevels[4];
bool encoderPinStates[4];
bool encoderUntriggered = HIGH;
bool encoderButtonUntriggered = HIGH;
int currentLayer = 2;
int totalLayers = 7;  // This is zero-justified
String layerNames[] = {"Settings 1", "Settings 2", "Media Control", "Work Macros", "Function Keys", "More F Keys", "Pokemon Go (-o-)", "Repeating Functions"};
String layerKeys[] = {
  "Vib    Snd    Scrn   Vol*",
  "BT    SrlDiag    OS      --",
  "Vol    Bk     Fwd    Play",
  "Vol+  Vol-    F24     Rtn",
  "F21     F22     F23     F24",
  "F17     F18     F19     F20",
  "Vol    Play    OK     <2*",
  "F5      //     Ctrl     rPlay"};
bool vibratingSettingBit = HIGH;
bool piezoSettingBit = HIGH;
long oldAccelerometerPosition;
long newAccelerometerPosition;
int volumeAdjustmentFactor = 3; // A phone OS can use 1, but a computer should use 3
bool suppressBuzzer = LOW;
bool vibrationSetting = HIGH;
bool audioSetting = HIGH;
int screenTimeout = 10;
bool BTStatus = HIGH;
long screenSleepTimer = 20000;
bool screenBlanked = LOW;
bool AppleProducts = HIGH;
long repeatingCooldownTimeout = 0;
int repeatingIntervalMultiplier = 0;
int repeatingIntervalMillis = 0;
int repeatingKeySequence = 5; // This just has to be larger than the number of keyswitches



void setup() {
  
  // Set the discrete inputs to use internal PULLUP resistors. It is still
  // safe to add physical resistors.
  for(int i=0; i<4; i++){
    pinMode(keyswitchLocations[i], INPUT);
  }
    
  for(int i=0; i<3; i++){
    pinMode(encoderPinLocations[i], INPUT_PULLUP);
  }
  // Set the outputs as such
  pinMode(vibratorPin, OUTPUT);
  pinMode(piezoElementPin, OUTPUT);
  
  
  u8g2.begin();
  u8g2.clearBuffer();          // clear the internal memory
  u8g2.setFont(u8g2_font_ncenB08_tr); // choose a suitable font
  u8g2.drawStr(25,20,"B.o.t.H."); // write something to the internal memory
  u8g2.drawStr(0,40,"Back of the hand.");  // write something to the internal memory
  u8g2.sendBuffer();          // transfer internal memory to the display
  
  Serial.begin(115200);
//  mySerial.begin(piezoFrequency);
//  mySerial.print("Hello, world");
  
  if (! lis.begin(0x18)) {   // change this to 0x19 for alternative i2c address
    Serial.println("Couldnt start");
    while (1) yield();
  }
  Serial.println("Accelerometer found!");
  Serial.print("Data rate set to: ");
  switch (lis.getDataRate()) {
    case LIS3DH_DATARATE_1_HZ: Serial.println("1 Hz"); break;
    case LIS3DH_DATARATE_10_HZ: Serial.println("10 Hz"); break;
    case LIS3DH_DATARATE_25_HZ: Serial.println("25 Hz"); break;
    case LIS3DH_DATARATE_50_HZ: Serial.println("50 Hz"); break;
    case LIS3DH_DATARATE_100_HZ: Serial.println("100 Hz"); break;
    case LIS3DH_DATARATE_200_HZ: Serial.println("200 Hz"); break;
    case LIS3DH_DATARATE_400_HZ: Serial.println("400 Hz"); break;

    case LIS3DH_DATARATE_POWERDOWN: Serial.println("Powered Down"); break;
    case LIS3DH_DATARATE_LOWPOWER_5KHZ: Serial.println("5 Khz Low Power"); break;
    case LIS3DH_DATARATE_LOWPOWER_1K6HZ: Serial.println("16 Khz Low Power"); break;
  }
//  screenName(layerKeys[currentLayer], layerNames[currentLayer]);
  EEPROM.begin(512);
  // Recall settings stored in EEPROM
  vibrationSetting = EEPROM.read(0);
  audioSetting = EEPROM.read(1);
  screenTimeout = EEPROM.read(2);
  volumeAdjustmentFactor = EEPROM.read(3);
  diagnosticPrintBit = EEPROM.read(4);
  AppleProducts = EEPROM.read(5);
  if(diagnosticPrintBit){
    Serial.print("Vibration: ");
    Serial.print(EEPROM.read(0));
    Serial.print("\n");
    
    Serial.print("Audio: ");
    Serial.print(EEPROM.read(1));
    Serial.print("\n");
    
    Serial.print("Timeout: ");
    Serial.print(EEPROM.read(2));
    Serial.print("\n");
    
    Serial.print("Volume*: ");
    Serial.print(EEPROM.read(3));
    Serial.print("\n");
    
    Serial.print("Printbit: ");
    Serial.print(EEPROM.read(4));
    Serial.print("\n");
    
    Serial.print("App/Win: ");
    Serial.print(EEPROM.read(5));
    Serial.print("\n");
  }
}

void loop(){
  if(startupBit && scanKeyswitches()){
    bleKeyboard.begin();
    startupBit = LOW;
    u8g2.clearBuffer();
  }
  if(scanKeyswitches()){
    screenSleepTimer = millis() + screenTimeout*1000;
    screenBlanked = LOW;
    layerTyping();
  }
  if(currentLayer == 7){
    repeatingKeystrokes();
  }
  if(scanEncoder()){
    repeatingKeySequence = 5;
    screenSleepTimer = millis() + screenTimeout*1000;
    screenBlanked = LOW;
  }
  if((millis() > screenSleepTimer) && !screenBlanked){
    screenBlanked = HIGH;
    blankScreen();
  }
}
