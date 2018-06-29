
//         Copyright Jasper van Poelgeest 2018.
// Distributed under the Boost Software License, Version 1.0.
//      (See accompanying file LICENSE_1_0.txt)

#ifndef DMX_WS2812B_HPP
#define DMX_WS2812B_HPP

#include "hwlib.hpp" //used for timing
#include "oled.hpp"
#include "encoder.hpp"
#include "dmx.hpp"
#include "ws2812b.hpp"

///\brief
/// Namespace for my own projects
///\details
/// Namespace that contains all the classes that are used for the DMX-to-WS2812B
namespace dwarfNebula {

///\brief
/// DMX-to-WS2812B class
///\details
/// Class to easily initialize a led strip and the DMX
class DMX_WS2812B {
private:
	uint16_t numLeds;
	uint16_t channel;   //start channel (min = 1, max = 508)
	uint8_t channelMode; //amount of channels (min = 4, max = 128 (256/4))
	char menu;
	bool settings;
	WS2812B strip;
	DMX::DMX Dmx;
	oled screen;
	encoder rotary;
	uint16_t channelModes[16];
	uint8_t maxChannelMode;
	int dmx_data[512];
	
	///\brief
	/// Fills the dmx_data array
	///\details
	/// Predefined array with values from 0-255, just to test without using DMX input
	void get_data();
	
public:
	///\brief
	/// Constructor
	///\details
	/// Initialize a new DMX-to-WS2812B object, with a start channel, number of leds on the strip,
	/// the different channel modes it has and the amount of channel modes
	DMX_WS2812B(uint16_t channel, uint16_t numLeds, uint16_t channelModes[64], uint8_t maxChannelMode);
	
	///\brief
	/// Start the DMX-to-WS2812B object
	///\details
	/// It will first read the encoder to check if it's pushed, if it isn't it will read the DMX and change,
	/// the leds on the strip to their value
	void start();
};}

#endif // DMX_WS2812B_HPP
