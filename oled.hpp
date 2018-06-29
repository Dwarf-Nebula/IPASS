
//         Copyright Jasper van Poelgeest 2018.
// Distributed under the Boost Software License, Version 1.0.
//      (See accompanying file LICENSE_1_0.txt)

#ifndef OLED_HPP
#define OLED_HPP

#include "hwlib.hpp" //used to easy program the OLED

///\brief
/// Namespace for my own projects
///\details
/// Namespace that contains all the classes that are used for the DMX-to-WS2812B
namespace dwarfNebula {

///\brief
/// OLED class
///\details
/// Class to control the OLED screen for a simple UI
class oled {
private:
	hwlib::target::pin_oc scl                 = hwlib::target::pin_oc( hwlib::target::pins::scl );
	hwlib::target::pin_oc sda                 = hwlib::target::pin_oc( hwlib::target::pins::sda );
	hwlib::i2c_bus_bit_banged_scl_sda i2c_bus = hwlib::i2c_bus_bit_banged_scl_sda( scl,sda );
	hwlib::glcd_oled screen                   = hwlib::glcd_oled( i2c_bus, 0x3c );
	hwlib::font_default_16x16 font            = hwlib::font_default_16x16();
	hwlib::window_ostream display             = hwlib::window_ostream(screen, font);
	
	uint16_t channel;
	uint8_t channelMode;
	
public:
	///\brief
	/// Constructor
	///\details
	/// Initialize a OLED object with the channel and channel mode
	oled(uint16_t channel, uint8_t channelMode);
	
	///\brief
	/// Change the menu on the screen to the given menu
	///\details
	/// List of menu's to choose from:
	/// 'c': display the channel, 'd': display the channel with * so the user knows it can edit the channel
	/// 'm': display the channelmode, 'n': display the channelmode with * so the user knows it can edit the channelmode
	void changeMenu(char menu);
	
	///\brief
	/// Change channel on the screen
	///\details
	/// Change the channel for the screen class
	void changeChannel(uint16_t newChannel);
	
	///\brief
	/// Change channelmode on the screen
	///\details
	/// Change the channelmode for the screen class
	void changeChannelMode(uint16_t newChannelMode);
	
};}

#endif // OLED_HPP
