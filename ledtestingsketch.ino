#include <FastLED.h>
#define NUM_LEDS 60
#define DATA_PIN 4

CRGB leds[NUM_LEDS];
void setup() { 
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS); 
}
void loop() {
  for(int i = 0; i < 10; i++) {
    leds[i] = CRGB::MediumVioletRed; FastLED.show(); delay(200);
	  leds[i] = CRGB::Black; FastLED.show(); delay(200);    
  }
	
 // leds[1] = CRGB::MediumSeaGreen; wFastLED.show(); delay(300);
 // leds[1] = CRGB::DarkOliveGreen; FastLED.show(); delay(300);
}