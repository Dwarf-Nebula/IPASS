
//         Copyright Jasper van Poelgeest 2018.
// Distributed under the Boost Software License, Version 1.0.
//      (See accompanying file LICENSE_1_0.txt)

#include "color.hpp"

dwarfNebula::Color::Color():
	red(0),
	green(0),
	blue(0)
{}

dwarfNebula::Color::Color(const uint8_t & red, const uint8_t & green, const uint8_t & blue):
	red(red),
	green(green),
	blue(blue)
{}

dwarfNebula::Color::Color(const uint32_t & hex){
	blue  = hex       & 0xFF;
	green = hex >> 8  & 0xFF;
	red   = hex >> 16 & 0xFF;
}

void dwarfNebula::Color::setRed(const uint8_t & value){
	red = value;
}

void dwarfNebula::Color::setGreen(const uint8_t & value){
	green = value;
}

void dwarfNebula::Color::setBlue(const uint8_t & value){
	blue = value;
}

uint8_t dwarfNebula::Color::getRed(){
	return red;
}

uint8_t dwarfNebula::Color::getGreen(){
	return green;
}

uint8_t dwarfNebula::Color::getBlue(){
	return blue;
}

uint32_t dwarfNebula::Color::getColor(){
	uint32_t returnColor = green;
	returnColor <<= 8;
	returnColor |= red;
	returnColor <<= 8;
	returnColor |= blue;
	return returnColor;
}
