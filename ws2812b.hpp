
//         Copyright Jasper van Poelgeest 2018.
// Distributed under the Boost Software License, Version 1.0.
//      (See accompanying file LICENSE_1_0.txt)

#ifndef WS2812B_HPP
#define WS2812B_HPP

#include "hwlib.hpp" //for pins and wait
#include "color.hpp"

///\brief
/// Namespace for my own projects
///\details
/// Namespace that contains all the classes that are used for the DMX-to-WS2812B
namespace dwarfNebula {

///\brief
/// WS2812B Class
///\details
/// Control easily a WS2812B led-strip, let simple animation do their job or control each pixel
class WS2812B {
private:
	const uint16_t numLeds;
	hwlib::target::pin_out pinOut;
	Color leds[512];
	
	///\brief
	/// Update the leds
	///\details
	/// This will sent all numLeds*24 bits to the leds
	void sentBits(volatile bool x[]);
	
public:
	///\brief
	/// Constructor
	///\details
	/// Make a new ledstrip and set the amount of leds it has
	WS2812B(const uint16_t numLeds):
		numLeds(numLeds),
		pinOut(hwlib::target::pins::d6)
	{
		for (unsigned int i = 0; i < numLeds; i++){
			setPixelColor(i, Color(0));
		}
	}
	
	///\brief
	/// Give the leds their new color
	///\details
	/// This will make a large array with all bits from all leds one afther each other
	void show(void);
	
	///\brief
	/// Set the color of one pixel
	///\details
	/// Change the color of one pixel, it isn't showed untill you call show()
	void setPixelColor(unsigned int pixel, Color color);
	
	///\brief
	/// Set the whole strip in one color
	///\details
	/// Instant set the whole strip in one color
	void setColor(Color color);
	
	///\brief
	/// Simple animation that makes all the leds the same color
	///\details
	/// Fill the dots one after the other with a color
	void colorWipe(Color c, uint8_t wait);
	
	///\brief
	/// Theatre-style animation
	///\details
	/// Theatre-style crawling lights
	void theaterChase(Color c, uint8_t wait, uint8_t cycles);
	
	///\brief
	/// A test function for the given pixel and color
	///\details
	/// This function will check if the given color and pixel color are equal
	bool test(uint16_t pixel, Color c);
};}

#endif // WS2812B_HPP
