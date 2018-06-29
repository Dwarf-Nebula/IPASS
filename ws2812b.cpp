
//         Copyright Jasper van Poelgeest 2018.
// Distributed under the Boost Software License, Version 1.0.
//      (See accompanying file LICENSE_1_0.txt)

#include "ws2812b.hpp"

//Code van Wouter van Ooijen om een korte tijd te wachten
void __attribute__((noinline)) busy_delay_ticks( int32_t n ){
   __asm volatile(                  
      "   .align 4           \t\n"  
      "1: subs.w  r0, #3     \t\n"  
      "   bgt 1b             \t\n"  
      : : "r" ( n )          // uses (reads) n         
   );
}

void dwarfNebula::WS2812B::setPixelColor(unsigned int pixel, Color color){
	leds[pixel] = color;
}

void dwarfNebula::WS2812B::sentBits(volatile bool x[]){
	for (unsigned int i = 0; i < numLeds*24; i++){ //go through the array
		if (x[i]){
			pinOut.set(1);
			busy_delay_ticks(40); //wait for +- 700ns
			pinOut.set(0);
		}
		else {
			pinOut.set(1);
			busy_delay_ticks(3); //wait for +- 250ns
			pinOut.set(0);      
		}
		busy_delay_ticks( 60 ); //wait for less than 5ms
	}
}

void dwarfNebula::WS2812B::show(){
	volatile bool ledColors[numLeds*24]; //make a new array with space for every leds color
	
	for (unsigned int i = 0; i < numLeds; i++){
		int32_t ledColor = leds[i].getColor(); //get the color value of a led
		
		for (unsigned int j = 1; j < 25; j++){
			if ((ledColor & (0x1 << (24-j))) == (0x1 << (24-j))){ //read bit
				ledColors[i*24 + j-1] = 1;
				hwlib::wait_us(1);
			}
			else {
				ledColors[i*24 + j-1] = 0;
				hwlib::wait_us(1);
			}
		}
	}
	sentBits(ledColors);
}

// Fill the strip with one color
void dwarfNebula::WS2812B::setColor(dwarfNebula::Color c) {
  for(uint16_t i = 0; i < numLeds; i++) {
    setPixelColor(i, c);
  }
  show();
}

// Fill the dots one after the other with a color
void dwarfNebula::WS2812B::colorWipe(dwarfNebula::Color c, uint8_t wait) {
  for(uint16_t i = 0; i < numLeds; i++) {
    setPixelColor(i, c);
    show();
    hwlib::wait_ms(wait);
  }
}

//Theatre-style crawling lights.
void dwarfNebula::WS2812B::theaterChase(dwarfNebula::Color c, uint8_t wait, uint8_t cycles) {
	for (int j = 0; j < cycles; j++) {
		for (int q=0; q < 3; q++) {
			for (uint16_t i=0; i <numLeds; i=i+3) {
				setPixelColor(i+q, c);
			}
			show();
			hwlib::wait_ms(wait);
			for (uint16_t i=0; i < numLeds; i=i+3) {
				setPixelColor(i+q, 0);
			}
		}
	}
}

//test function, 1 if okay, 0 if fail
bool dwarfNebula::WS2812B::test(uint16_t pixel, Color c){
	return leds[pixel] == c;
}
