
//         Copyright Jasper van Poelgeest 2018.
// Distributed under the Boost Software License, Version 1.0.
//      (See accompanying file LICENSE_1_0.txt)

#ifndef ENCODER_HPP
#define ENCODER_HPP

#include "hwlib.hpp" //used to initialize the encoder pins

///\brief
/// Namespace for my own projects
///\details
/// Namespace that contains all the classes that are used for the DMX-to-WS2812B
namespace dwarfNebula{

///\brief
/// Encoder class for a rotary encoder
///\details
/// The class can read out the pushbutton of the encoder and in which direction it is turning
class encoder{
private:
	hwlib::target::pin_in sw;  //switch
	hwlib::target::pin_in clk; //clock (output A)
	hwlib::target::pin_in dt;  //data (output B)
	bool aState;
	bool aLastState;
public:
	///\brief
	/// Constructor
	///\details
	/// Initialize a encoder
	encoder();
	
	///\brief
	/// State of rotation
	///\details
	/// If the encoder is rotating clockwise it will return a 'r' from right
	/// If the encoder is rotating counterclockwise it will return a 'l' from left
	/// If the encoder is stationary it will return a 's'
	char getState();
	
	///\brief
	/// Check if button is pushed
	///\details
	/// Return a 1 when pushed, return a 0 when it isn't
	bool buttonPushed();

};}

#endif // ENCODER_HPP
