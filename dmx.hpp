/// @file



#ifndef DMX_HPP
#define DMX_HPP
#include <array>


///\brief
/// namespace for DMX library
///\details
/// this namespace contains all the functions for the DMX class
namespace DMX
{

///\brief
/// DMX class that recieves 4 channels using USART0 
///\details
/// This DMX class can be used to recieve dmx data using the arduino due's usart0
/// note: if using other usart line or other board register names may vary
class DMX
{
   public:
	   ///\brief 
		 /// constructor 
		 ///\details
		 /// this constructor initializes the DMX object
	  DMX(){}
	  
		  ///\brief
		  /// Get dmx data and store in array
		  ///\details
		  /// this function is used to get the dmx data from the usart controller
		  /// an array needs to be passed as reference and the function will change the values in this array corresponding to recieved data \n
		  /// the size of the array determines the amount of channels that wil be recieved
		  /// note: array that is passed needs to be the same size as in this function
	  int get_data(std::array<int,512> & dmx_data);
	
};
   ///\brief
   /// enables dmx functionality
   ///\details
   /// enables the dmx functionality by setting up the USART0 controller of the arduino DUE
   /// also sets up baudrate to 250kbit/s, stopbits to 2, parity to none, byte length to 8
   void enable_dmx();

}

#endif // DMX_HPP