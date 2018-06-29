
//         Copyright Jasper van Poelgeest 2018.
// Distributed under the Boost Software License, Version 1.0.
//      (See accompanying file LICENSE_1_0.txt)

#include "encoder.hpp"

dwarfNebula::encoder::encoder():
	sw(hwlib::target::pins::d53),  //switch
	clk(hwlib::target::pins::d51), //clock (output A)
	dt(hwlib::target::pins::d52),  //data (output B)
	aLastState(clk.get())
{}

char dwarfNebula::encoder::getState(){
	aState = clk.get(); // Reads the "current" state of the clk
	char state = 's';
	// If the previous and the current state of the clk are different, that means a Pulse has occured
	if (aState != aLastState){     
		// If the dt state is different to the clk state, that means the encoder is rotating clockwise
		if (dt.get() != aState) { 
			state = 'r';
		}
		// If the dt state is different to the clk state, that means the encoder is rotating clockwise
		else {
			state = 'l';
		}
	}
	aLastState = aState; // Updates the previous state of the clk with the current state
	return state;
}

bool dwarfNebula::encoder::buttonPushed(){
	return !(sw.get()); //the switch is active low, but we want to return a 1 if high
}
