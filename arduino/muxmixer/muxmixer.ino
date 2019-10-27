//#include <Encoder.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <EEPROM.h>


//#define DEBUG
//#define BALANCE

// Configs
#define VERSION 0.2
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SMALL_TEXT  display.setTextSize(1)
#define MEDIUM_TEXT display.setTextSize(2)
#define LARGE_TEXT display.setTextSize(3)
#define SHOW display.display();
#define CLEAR display.clearDisplay()
#define BUTTON_TIME 10
#define SLEEPTIME 10000000
#define SWITCHTIME 100000
#define SAVETIME 2500000
#define LOGO_WIDTH 128
#define LOGO_HEIGHT 32


#if defined (LOGO)
const unsigned char logo [] PROGMEM = {
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xe7, 0xbf, 0x9e, 0xff, 0xe3, 0xef, 0xff, 0xff, 0xff, 0xfe, 0x7b, 0xf8, 0x09, 0xc7, 0xdf,
  0xff, 0xc3, 0x17, 0x04, 0xef, 0xc1, 0xc3, 0xff, 0xff, 0xff, 0xfc, 0x31, 0x78, 0x13, 0x83, 0x87,
  0xff, 0x82, 0x86, 0x00, 0xc5, 0x81, 0xc1, 0xff, 0xff, 0xff, 0xf8, 0x28, 0x72, 0x23, 0x03, 0x83,
  0xff, 0x20, 0x86, 0x00, 0xc1, 0xb0, 0xc3, 0xff, 0xff, 0xff, 0xf2, 0x08, 0x77, 0x27, 0x61, 0x87,
  0xfe, 0x62, 0xce, 0xe0, 0xa3, 0xf8, 0xd3, 0xff, 0xff, 0xff, 0xe6, 0x2c, 0xff, 0x27, 0xf1, 0xa7,
  0xfe, 0x62, 0xce, 0xc8, 0xe3, 0xf8, 0xbf, 0xff, 0xff, 0xff, 0xe6, 0x2c, 0xff, 0x27, 0xf1, 0x7f,
  0xfc, 0x62, 0xce, 0xc8, 0xe3, 0xf8, 0xbf, 0xff, 0xff, 0xff, 0xc6, 0x2c, 0xfe, 0x27, 0xf1, 0x7f,
  0xfc, 0x62, 0xcf, 0x92, 0xe3, 0xfc, 0x3f, 0xff, 0xff, 0xff, 0xc6, 0x2c, 0xfe, 0x27, 0xf8, 0x7f,
  0xfd, 0x62, 0xcf, 0x92, 0xe3, 0xfc, 0x7f, 0xff, 0xff, 0xff, 0xd6, 0x2c, 0xfe, 0x23, 0xf8, 0xff,
  0xfd, 0x62, 0xcf, 0x32, 0x63, 0xf0, 0x03, 0xff, 0xff, 0xff, 0xd6, 0x2c, 0xf8, 0x23, 0xe0, 0x07,
  0xfd, 0x40, 0x4f, 0x32, 0x83, 0xe0, 0x03, 0xff, 0xff, 0xff, 0xd4, 0x04, 0xf0, 0x23, 0xc0, 0x07,
  0xf9, 0x00, 0xcf, 0x32, 0xe3, 0xe0, 0x07, 0xff, 0xff, 0xff, 0x90, 0x0c, 0xf6, 0x23, 0xc0, 0x0f,
  0xf1, 0x62, 0xce, 0x32, 0xe3, 0xfe, 0x3f, 0xff, 0xff, 0xff, 0x16, 0x2c, 0xff, 0x23, 0xfc, 0x7f,
  0xe1, 0x62, 0xce, 0x32, 0x03, 0xfe, 0x1f, 0xff, 0xff, 0xfe, 0x16, 0x2c, 0xff, 0x33, 0xfc, 0x3f,
  0xe9, 0x62, 0xce, 0x32, 0xe3, 0xfd, 0x1f, 0xff, 0xff, 0xfe, 0x96, 0x2c, 0xff, 0x33, 0xfa, 0x3f,
  0xfd, 0x62, 0xce, 0x32, 0xe3, 0xfd, 0x1f, 0xff, 0xff, 0xff, 0xd6, 0x2c, 0xff, 0x33, 0xfa, 0x3f,
  0xfd, 0x62, 0xcf, 0x32, 0xe3, 0xfd, 0x1f, 0xff, 0xff, 0xff, 0xd6, 0x2c, 0xff, 0x33, 0xfa, 0x3f,
  0xfd, 0x62, 0xcf, 0x12, 0xe3, 0xfd, 0x8f, 0xff, 0xff, 0xff, 0xd6, 0x2c, 0xff, 0x33, 0xfb, 0x1f,
  0xfd, 0x62, 0x4f, 0x16, 0xe3, 0xc3, 0x8f, 0xff, 0xff, 0xff, 0xd6, 0x24, 0xf8, 0x73, 0x87, 0x1f,
  0xfd, 0x60, 0xcb, 0x0e, 0xc3, 0xc3, 0x8b, 0xff, 0xff, 0xff, 0xd6, 0x0c, 0xb0, 0xf3, 0x87, 0x17,
  0xfd, 0x70, 0xc3, 0x06, 0x83, 0x83, 0xc3, 0xff, 0xff, 0xff, 0xd7, 0x0c, 0x20, 0x73, 0x07, 0x87,
  0xf0, 0x71, 0xc7, 0x80, 0x00, 0xe7, 0xc7, 0xff, 0xff, 0xff, 0x07, 0x1c, 0x60, 0x07, 0xcf, 0x8f,
  0xe0, 0x7b, 0xef, 0xc0, 0x21, 0xf7, 0xef, 0xff, 0xff, 0xfe, 0x07, 0xbe, 0xee, 0x0f, 0xef, 0xdf,
  0xc0, 0xff, 0xff, 0xe0, 0x73, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xd9, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfd, 0x9f, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xdf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfd, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
};
#endif

// Setup
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


//
void sleepDisplay(Adafruit_SSD1306* display) {
  display->ssd1306_command(SSD1306_DISPLAYOFF);
}
void wakeDisplay(Adafruit_SSD1306* display) {
  display->ssd1306_command(SSD1306_DISPLAYON);
}


// Globals

typedef struct  {
  byte volume;
  byte mix;
} configData;
configData runningConfig[4];
configData savedConfig[4];
volatile int lastEncoded = 0;
bool savePending = false;
volatile unsigned long lastInput = 0;

volatile bool intTriggered = false;


long oldPosition  = 10;
int selection = 1;
int active = 0;
int pos = 0;
int volume;
int input;
int mix;
int balance = 50;
int value;
unsigned long buttonPressedTime;

void setup() {
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setTextColor(SSD1306_WHITE);
  display.cp437(true);

  CLEAR;
  display.clearDisplay();
#if defined (LOGO)
  display.drawBitmap(
    (display.width()  - LOGO_WIDTH ) / 2,
    (display.height() - LOGO_HEIGHT) / 2,
    logo, LOGO_WIDTH, LOGO_HEIGHT, 1);
  display.display();
  delay(2000);
#endif
  active = EEPROM.read(0);
  if ( active == 255 ) { // Empty EEPROM.
    active = 0;
  }
  for ( int i = 0; i < 4; i++) {
    EEPROM.get((i * 2) + 1, runningConfig[i]);
    savedConfig[i] = runningConfig[i];
#if defined (DEBUG)
    CLEAR;
    display.setCursor(0, 0);
    display.println(i);
    display.print(runningConfig[i].volume);
    display.print(" ");
    display.print(runningConfig[i].mix);
    SHOW;
    delay(1000);
#endif
  }


  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  attachInterrupt(0, updateEncoder, CHANGE);
  attachInterrupt(1, updateEncoder, CHANGE);
  volume = runningConfig[active].volume;
  mix = runningConfig[active].mix;

}

void loop() {
  buttonPressedTime = micros();
  while ( ! digitalRead(4) ) {
    //    display.ssd1306_command(SSD1306_DISPLAYON);
    lastInput = micros();
  }
  if ( micros() > buttonPressedTime + SAVETIME && savePending ) {
    saveConfig();
  } else  if ( micros() > buttonPressedTime + SWITCHTIME)
    selection++;
#if defined (BALANCE)
  if ( selection  > 4 )
#else
  if ( selection  > 3 )
#endif
    selection = 1;



  noInterrupts();
  volume = runningConfig[input].volume;
  mix = runningConfig[input].mix;

  if ( pos ) {
    switch ( selection ) {
      case 1:
        volume = volume + pos * 5;
        if ( volume < 0 )
          volume = 0;
        if ( volume > 100 )
          volume = 100;
        runningConfig[input] = {volume, mix};
        break;
      case 3:
        input = input + pos;
        if ( input > 3 )
          input = 0;
        if (input < 0)
          input = 3;
        break;
      case 2:
        mix = mix + pos * 5;
        if ( mix < 0 )
          mix = 0;
        if ( mix > 100 )
          mix = 100;
        runningConfig[input] = {volume, mix};
        break;
      case 4:
        balance = balance + pos * 5;
        if ( balance < 0 )
          balance = 0;
        if ( balance > 100)
          balance = 100;
        break;
    }
    //runningConfig[input] = {volume, mix};
  }

  interrupts();

  if ( memcmp(&runningConfig, &savedConfig, sizeof(runningConfig)) ) {
    savePending = true;

  }
  pos = 0;
  printLayout(input, volume, mix, balance, selection);

}


void printLayout(int input, int volume, int mix, int balance, int selection) {
  SMALL_TEXT;
  CLEAR;
  printMix(mix);
  printVolume(volume);
  printInput(input);
  printBalance(balance);
  printSelection(selection);
  printSaveState();
  SHOW;
}

void printSaveState() {
  display.setCursor(120, 0);
  if ( savePending )
    display.print("*");
}
void printVolume(int volume) {
  display.setCursor(1, 1);
#if defined (DEBUG)
  display.print(volume);
#else
  display.print("Volume");
#endif

  display.fillRect(0, 10, map(volume, 0, 100, 0, (display.width() / 2) - 2), (display.height() / 2) - 4, SSD1306_INVERSE);
}

void printInput(int input) {
  display.setCursor(0, 24);
#if defined (DEBUG)
  display.print(input);
  display.print("     ");

#else
  display.print("Input ");
#endif
  display.print("1234");

  int start = 36 + (input * 6);
  display.fillRect(start, 23, 5, 32, SSD1306_INVERSE);
}

void printMix(int mix) {
  display.setCursor((display.width() / 2), 1);
#if defined (DEBUG)
  display.print(mix);
#else
  display.print("Mix");
#endif
  int left =  map(mix, 0, 100, display.width() / 2, 92);
  int right = map(mix, 0, 100, display.width() - 8, 92);
  display.fillRect(left, 10, 8, (display.height() / 2) - 4, SSD1306_WHITE);
  display.fillRect(right, 10, 8, (display.height() / 2) - 4, SSD1306_WHITE);
}
void printBalance(int balance) {
  display.setCursor(display.width() / 2, 24);
#if defined (BALANCE)
  display.print("Bal ");
  display.print(map(balance, 0, 100, 0, 100));
  display.print("/");
  display.print(map(balance, 0, 100, 100, 0));
#else
  display.print("muxmix ");
  display.print(VERSION);
#endif
}

void printSelection(int selection ) {
  if ( selection == 1 )
    display.fillRect(0, 0, 37, 9, SSD1306_INVERSE);
  if ( selection == 3 )
    display.fillRect(0, 23, 30, 9, SSD1306_INVERSE);
  if ( selection == 2 )
    display.fillRect(63, 0, 19, 9, SSD1306_INVERSE);
#if defined (BALANCE)
  if ( selection == 4 )
    display.fillRect(63, 23, 18, 9, SSD1306_INVERSE);
#endif
}

void updateEncoder() {
  noInterrupts();
  // display.ssd1306_command(SSD1306_DISPLAYON);

  lastInput = micros();
  int MSB = digitalRead(3); //MSB = most significant bit
  int LSB = digitalRead(2); //LSB = least significant bit
  int encoded = (MSB << 1) | LSB; //converting the 2 pin value to single number
  int sum  = (lastEncoded << 2) | encoded; //adding it to the previous encoded value
  if (sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) pos = 1;
  if (sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) pos = -1;
  lastEncoded = encoded; //store this value for next time
  interrupts();
}

void saveConfig() {
  savePending = false;
  for ( int i = 0; i < 4; i++) {
    EEPROM.put((i * 2) + 1, runningConfig[i]);
    savedConfig[i] = runningConfig[i];
#if defined (DEBUG)
    CLEAR;
    display.setCursor(0, 0);
    display.println(i);
    display.print(runningConfig[i].volume);
    display.print(" ");
    display.print(runningConfig[i].mix);
    SHOW;
    delay(1000);
#endif
  }
}
