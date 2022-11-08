#define USE_ARDUINO_INTERRUPTS true    // Set-up low-level interrupts for most acurate BPM math.
#include <PulseSensorPlayground.h>     // Includes the PulseSensorPlayground Library.   

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for SSD1306 display connected using software SPI (default case):
#define OLED_MOSI   9
#define OLED_CLK   10
#define OLED_DC    11
#define OLED_CS    12
#define OLED_RESET 8

const int PulseWire = 0;       // PulseSensor PURPLE WIRE connected to ANALOG PIN 0
const int LED13 = 13;          // The on-board Arduino LED, close to PIN 13.
int Threshold = 555;           // Determine which Signal to "count as a beat" and which to ignore.

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT,
  OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

// 'eeworldonlineblack-135x45', 130x45px
const unsigned char epd_bitmap_eeworldonlineblack_135x45 [] PROGMEM = {
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x1f, 0xff, 0xf8, 
  0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x1f, 0xff, 
  0xf8, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x1f, 
  0xff, 0xf8, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 
  0x1f, 0xff, 0xf8, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xfc, 0x1f, 0xff, 0xf8, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xfc, 0x1f, 0xff, 0xf8, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xfc, 0x1f, 0xff, 0xf8, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xfc, 0x1f, 0xff, 0xf8, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xfc, 0x1f, 0xff, 0xf8, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x1f, 0xff, 0xf8, 0x00, 0xe0, 0x00, 0x60, 0x00, 0x67, 0xf8, 
  0x1f, 0xc1, 0xf8, 0x00, 0x3f, 0x06, 0x0c, 0x1f, 0xe0, 0x18, 0x00, 0xe0, 0x00, 0x60, 0x00, 0x67, 
  0xf0, 0x1f, 0xc1, 0xe0, 0x00, 0x1f, 0x04, 0x0c, 0x1f, 0x80, 0x00, 0x00, 0xe0, 0x00, 0x60, 0x00, 
  0x47, 0xf0, 0x1f, 0xc1, 0xe0, 0x00, 0x0f, 0x00, 0x0c, 0x1f, 0x00, 0x00, 0x00, 0xe1, 0xff, 0xe1, 
  0xff, 0xc3, 0xf0, 0x1f, 0xc1, 0xc0, 0x00, 0x0f, 0x00, 0x0c, 0x1f, 0x00, 0x00, 0x00, 0xe3, 0xff, 
  0xe1, 0xff, 0xc3, 0xf0, 0x0f, 0xc3, 0xc0, 0x00, 0x07, 0x00, 0x0c, 0x1e, 0x00, 0x00, 0x00, 0xe3, 
  0xff, 0xe3, 0xff, 0xc3, 0xe0, 0x0f, 0x83, 0xc1, 0xfe, 0x07, 0x03, 0xfc, 0x1e, 0x07, 0xf0, 0x00, 
  0xc3, 0xff, 0xe3, 0xff, 0xc3, 0xe0, 0x0f, 0x83, 0xc1, 0xff, 0x07, 0x07, 0xfc, 0x1e, 0x0f, 0xf8, 
  0x00, 0xc3, 0xff, 0xc3, 0xff, 0xc3, 0xe1, 0x0f, 0x83, 0x83, 0xff, 0x07, 0x07, 0xfc, 0x1e, 0x0f, 
  0xf8, 0x00, 0xc3, 0xff, 0xc3, 0xff, 0xc1, 0xe1, 0x07, 0x87, 0x83, 0xff, 0x07, 0x07, 0xfc, 0x1e, 
  0x0f, 0xf8, 0x00, 0xc3, 0xff, 0xc3, 0xff, 0xc1, 0xe1, 0x07, 0x87, 0x83, 0xff, 0x07, 0x07, 0xfc, 
  0x1e, 0x0f, 0xf8, 0x00, 0xc0, 0x00, 0xc0, 0x00, 0xc1, 0xc1, 0x87, 0x07, 0x83, 0xff, 0x07, 0x07, 
  0xfc, 0x1e, 0x0f, 0xf8, 0x00, 0xc0, 0x00, 0xc0, 0x00, 0xe1, 0xc1, 0x87, 0x07, 0x83, 0xff, 0x07, 
  0x07, 0xfc, 0x1e, 0x0f, 0xf8, 0x00, 0xc0, 0x00, 0xc0, 0x00, 0xe0, 0xc3, 0x87, 0x07, 0x83, 0xff, 
  0x07, 0x07, 0xfc, 0x1e, 0x0f, 0xf8, 0x00, 0x80, 0x01, 0xc0, 0x01, 0xe0, 0xc3, 0x83, 0x0f, 0x83, 
  0xff, 0x07, 0x07, 0xfc, 0x1e, 0x0f, 0xf8, 0x00, 0x87, 0xff, 0x87, 0xff, 0xe0, 0xc3, 0xc3, 0x0f, 
  0x83, 0xff, 0x07, 0x07, 0xfc, 0x1e, 0x0f, 0xf8, 0x00, 0x87, 0xff, 0x87, 0xff, 0xf0, 0x83, 0xc2, 
  0x0f, 0x83, 0xff, 0x07, 0x07, 0xfc, 0x1e, 0x0f, 0xf8, 0x00, 0x87, 0xff, 0x87, 0xff, 0xf0, 0x87, 
  0xc2, 0x0f, 0x83, 0xff, 0x07, 0x07, 0xfc, 0x1e, 0x0f, 0xf8, 0x00, 0x8f, 0xff, 0x87, 0xff, 0xf0, 
  0x07, 0xc2, 0x1f, 0xc1, 0xff, 0x07, 0x07, 0xfc, 0x1e, 0x0f, 0xf8, 0x00, 0x8f, 0xff, 0x87, 0xff, 
  0xf0, 0x07, 0xc0, 0x1f, 0xc1, 0xfe, 0x07, 0x07, 0xfc, 0x1e, 0x07, 0xf0, 0x00, 0x8f, 0xff, 0x8f, 
  0xff, 0xf0, 0x07, 0xe0, 0x1f, 0xc0, 0x00, 0x07, 0x07, 0xfc, 0x1e, 0x00, 0x00, 0x00, 0x00, 0x03, 
  0x80, 0x03, 0xf8, 0x0f, 0xe0, 0x1f, 0xc0, 0x00, 0x0f, 0x07, 0xfc, 0x1f, 0x00, 0x00, 0x00, 0x00, 
  0x03, 0x80, 0x01, 0xf8, 0x0f, 0xe0, 0x1f, 0xe0, 0x00, 0x0f, 0x07, 0xfc, 0x1f, 0x00, 0x00, 0x00, 
  0x00, 0x03, 0x00, 0x03, 0xf8, 0x0f, 0xe0, 0x3f, 0xf0, 0x00, 0x1f, 0x07, 0xfc, 0x1f, 0x80, 0x08, 
  0x00, 0x00, 0x03, 0x00, 0x03, 0xf8, 0x0f, 0xf0, 0x3f, 0xf8, 0x00, 0x7f, 0x07, 0xfc, 0x1f, 0xe0, 
  0x3c, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xc0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xc0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x83, 0xff, 0x7d, 0xfe, 0x7f, 
  0xf7, 0xfb, 0xef, 0xf0, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7d, 0xff, 0x3d, 0xfe, 
  0x7f, 0xf7, 0xf9, 0xef, 0xf7, 0xc0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7e, 0xff, 0x5d, 
  0xfe, 0x7f, 0xf7, 0xfa, 0xef, 0xf7, 0xc0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xfe, 0xff, 
  0x4d, 0xfe, 0x7f, 0xf7, 0xfa, 0xef, 0xf3, 0xc0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xfe, 
  0xff, 0x6d, 0xfe, 0x7f, 0xf7, 0xfb, 0x6f, 0xf0, 0x40, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 
  0xfe, 0xff, 0x75, 0xfe, 0x7f, 0xf7, 0xfb, 0xaf, 0xf7, 0xc0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0x7e, 0xff, 0x71, 0xfe, 0x7f, 0xf7, 0xfb, 0x8f, 0xf7, 0xc0, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0x3d, 0xff, 0x79, 0xfe, 0x7f, 0xf7, 0xfb, 0xcf, 0xf7, 0xc0, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0x83, 0xff, 0x7d, 0xff, 0x0f, 0xf7, 0xfb, 0xef, 0xf8, 0x00
};

// Array of all bitmaps for convenience. (Total bytes used to store images in PROGMEM = 784)
const int epd_bitmap_allArray_LEN = 1;
const unsigned char* epd_bitmap_allArray[1] = {
  epd_bitmap_eeworldonlineblack_135x45
};

                               
PulseSensorPlayground pulseSensor;  // Creates an instance of the PulseSensorPlayground object called "pulseSensor"

void setup() {   
  Serial.begin(9600);          // For Serial Monitor
  // Configure the PulseSensor object, by assigning our variables to it. 
  pulseSensor.analogInput(PulseWire);   
  pulseSensor.blinkOnPulse(LED13);       //auto-magically blink Arduino's LED with heartbeat.
  pulseSensor.setThreshold(Threshold);   
  // Double-check the "pulseSensor" object was created and "began" seeing a signal. 
  if (pulseSensor.begin()) {
    //Serial.println("HeartBeat Monitor");  //This prints one time at Arduino power-up,  or on Arduino reset.  
  }
  display.begin(SSD1306_SWITCHCAPVCC);
  display.display();
  drawbm();
  display.display();
}

void loop() {
  display.clearDisplay();
  display.setTextSize(2); 
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Heartbeat Monitor");
  
  int myBPM = pulseSensor.getBeatsPerMinute();  //Returns BPM as an "int".
  if (pulseSensor.sawStartOfBeat()) {            // Constantly test to see if "a beat happened". 
   // Serial.println("♥  A HeartBeat Happened ! "); // If test is "true", print a message "a heartbeat happened".
    //Serial.print("BPM: ");                        // Print phrase "BPM: " 
    //Serial.println(myBPM);                        // Print the Heartbeat Rate 
    display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text
    display.print("BPM: ");
    display.println(myBPM);
    display.display();
    
  }
  delay(20);                    
}

void drawbm(void) {
display.clearDisplay();
display.drawBitmap(0, 0, epd_bitmap_eeworldonlineblack_135x45, 130, 45, WHITE);
display.display();
delay(1000);
}
