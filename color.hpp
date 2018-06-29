
//         Copyright Jasper van Poelgeest 2018.
// Distributed under the Boost Software License, Version 1.0.
//      (See accompanying file LICENSE_1_0.txt)

#ifndef COLOR_HPP
#define COLOR_HPP

#include <cstdint>

///\brief
/// Namespace for my own projects
///\details
/// Namespace that contains all the classes that are used for the DMX-to-WS2812B.
namespace dwarfNebula {

///\brief
/// Color class
///\details
/// Class that holds a red, green and blue value.
class Color {
private:
	uint8_t red, green, blue;
public:

	///\brief
	/// Constructor black
	///\details
	/// Initialize a Color with red, green and blue as 0
	Color();
	
	///\brief
	/// Constructor decimal
	///\details
	/// Initialize a Color with the given red, green and blue, from 0-255
	Color(const uint8_t & red, const uint8_t & green, const uint8_t & blue);
	
	///\brief
	/// Constructor hexadecimal
	///\details
	/// Initialize a Color with the given red, green and blue, 0x000000 to 0xFFFFFF
	Color(const uint32_t & hex);
	
	///\brief
	/// Set red value
	///\details
	/// Set red value by the given value
	void setRed(const uint8_t & value);
	
	///\brief
	/// Set green value
	///\details
	/// Set greenn value by the given value
	void setGreen(const uint8_t & value);
	
	///\brief
	/// Set blue value
	///\details
	/// Set blue value by the given value
	void setBlue(const uint8_t & value);
	
	///\brief
	/// Get red value
	///\details
	/// Get red value as 8-bit value
	uint8_t getRed();
	
	///\brief
	/// Get green value
	///\details
	/// Get green value as 8-bit value
	uint8_t getGreen();
	
	///\brief
	/// Get blue value
	///\details
	/// Get blue value as 8-bit value
	uint8_t getBlue();
	
	///\brief
	/// Get color value
	///\details
	/// Get color value as 32-bit value in green, red, blue order
	uint32_t getColor();
	
	/// \brief   
	/// compare two Colors
	/// \details
	/// This operator tests for equality. It returns 1 if the colors are the same
	bool operator==( const Color & rhs ) const {
		return (red) == (rhs.red) && (green) == (rhs.green) && (blue) == (rhs.blue);
	}
};}

#endif // COLOR_HPP
