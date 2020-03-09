#include <Adafruit_NeoPixel.h>

int fx[] = {12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2};
int bcd[] = {A0, A1, A2, A3};
int trigger = A4;
int ledPin = 13; 
int npixels = 256;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(npixels, ledPin, NEO_GRB + NEO_KHZ800);

void setup() {

//  Serial.begin(9600);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'

  // initialise all audio FX triggers, pull them high
  for (int i = 0; i < 10; i++)
  {
      pinMode(fx[i], OUTPUT);
      digitalWrite(fx[i], HIGH);
  }
  
  // initialise all BCD input pins
  for (int i = 0; i < 4; i++)
  {
      pinMode(bcd[i], INPUT_PULLUP);
  }

  pinMode(trigger, INPUT_PULLUP);

}

void loop() {

    if (digitalRead(trigger) == 0) {
      // Build the index of the requested behavior.
      
      int addr = 0;
      for (int i = 0; i < 4; i++) {
         addr |= (1 - digitalRead(bcd[i])) << i;
      }

//        Serial.println(addr);
        digitalWrite(fx[addr], LOW);
        delay(150);
        digitalWrite(fx[addr], HIGH);
        epicFlash(strip.Color(255, 0, 0), 1);

    }
}


void epicFlash(uint32_t c, uint8_t wait) {
  uint16_t i;
  strip.setBrightness(255);
   for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
    }
    
    for(i=255; i>0; i--) {
      strip.setBrightness(i);
      strip.show();
      delay(wait);
  }
  strip.setBrightness(0);
  strip.show();
}
