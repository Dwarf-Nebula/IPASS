
//         Copyright Jasper van Poelgeest 2018.
// Distributed under the Boost Software License, Version 1.0.
//      (See accompanying file LICENSE_1_0.txt)

#include "hwlib.hpp"
#include "dmx_ws2812b.hpp"

int main( void ){	
	// kill the watchdog
	WDT->WDT_MR = WDT_MR_WDDIS;
	
	// choose a program:
	// 0 = dmx mode
	// 1 = show mode
	// 2 = test mode
	uint8_t programma = 0;
	
	if(programma == 0){
		uint16_t channelModes[] = {1, 2, 3, 4, 5, 6, 8, 10, 12, 15, 20, 24, 30, 40, 60, 120};
		dwarfNebula::DMX_WS2812B lamp(1, 120, channelModes, 16);
		lamp.start();
	}
	
	else if(programma == 1){
		int numLeds = 120;
		dwarfNebula::WS2812B strip(numLeds);
		
		int wait = 50;
		int cycles = 5;
		
		while(1){
			strip.theaterChase(dwarfNebula::Color(255, 0, 0), wait, cycles);
			strip.theaterChase(dwarfNebula::Color(255, 255, 0), wait, cycles);
			strip.theaterChase(dwarfNebula::Color(0, 255, 0), wait, cycles);
			strip.theaterChase(dwarfNebula::Color(0, 255, 255), wait, cycles);
			strip.theaterChase(dwarfNebula::Color(0, 0, 255), wait, cycles);
			strip.theaterChase(dwarfNebula::Color(255, 0, 255), wait, cycles);
			strip.colorWipe(dwarfNebula::Color(255, 255, 255), wait/10);
			strip.setColor(dwarfNebula::Color(0, 0, 0));
		}
	}
	
	else if(programma == 2){
		hwlib::cout << "\n\n";
		hwlib::wait_ms(500);
		hwlib::cout << "Start test\n";
		hwlib::wait_ms(50);
		unsigned int numLeds = 10;
		dwarfNebula::WS2812B strip(numLeds);
		for (unsigned int i = 0; i < numLeds; i++){
			strip.setPixelColor(i, dwarfNebula::Color(0));
		}
		hwlib::wait_ms(50);
		for (unsigned int i = 0; i < numLeds; i++){
			if(strip.test(i, dwarfNebula::Color(0))){
				hwlib::cout << "pixel " << i+1 << " passed the test!\n";
				hwlib::wait_ms(50);
			}
			else{
				hwlib::cout << "pixel " << i+1 << " failed the test!\n";
				hwlib::wait_ms(50);
			}
		}
		hwlib::cout << "End of test\n";
	}
}
