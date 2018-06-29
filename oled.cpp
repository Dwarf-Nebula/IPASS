
//         Copyright Jasper van Poelgeest 2018.
// Distributed under the Boost Software License, Version 1.0.
//      (See accompanying file LICENSE_1_0.txt)

#include "oled.hpp"

dwarfNebula::oled::oled(uint16_t channel, uint8_t channelMode):
	channel(channel),
	channelMode(channelMode)
{}

void dwarfNebula::oled::changeChannel(uint16_t newChannel){
	channel = newChannel;
	changeMenu('d');
}

void dwarfNebula::oled::changeChannelMode(uint16_t newChannelMode){
	channelMode = newChannelMode;
	changeMenu('n');
}

void dwarfNebula::oled::changeMenu(char menu){
	if(menu == 'c'){
		display
			<< "\f" << ""
			<< "\t0001" << "Channel:"
			<< "\t0302" << channel
			<< hwlib::flush; //display the channel number
	}
	else if(menu == 'd'){
		display
			<< "\f" << "***"
			<< "\t0001" << "Channel:"
			<< "\t0302" << channel
			<< hwlib::flush; //display the channel number with stars
	}
	else if(menu == 'm'){
		display
			<< "\f" << ""
			<< "\t0001" << "C-Mode:"
			<< "\t0302" << channelMode*4
			<< hwlib::flush; //display the channelmode
	}
	else if(menu == 'n'){
		display
			<< "\f" << "***"
			<< "\t0001" << "C-Mode:"
			<< "\t0302" << channelMode*4
			<< hwlib::flush; //display the channelmode with stars
	}
}
