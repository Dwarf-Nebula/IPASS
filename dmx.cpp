#include "dmx.hpp"
#include "hwlib.hpp"
#include <array>

int DMX::DMX::get_data(std::array<int,512> & dmx_data){
	static  uint16_t dmx_count;
	int break_detect = 0;
	enum {IDLE, STARTB, GET_DATA}; //DMX states

	volatile uint8_t dmx_state;
	for(;;){
		if (REG_USART0_CSR&(0x01<<0)){

			uint8_t  USARTstate= REG_USART0_CSR;    //get state before data!
			uint8_t  DmxByte   = REG_USART0_RHR;    //get data

			if (USARTstate &(1<<2) && break_detect==0){  //check for break
				break_detect =1;
				REG_USART0_CR |= (0x01<<8);
				REG_USART0_CR |= (0<<8);
			}
			else if (USARTstate &(1<<2) && break_detect==1) {
				dmx_count =  1;   //reset channel counter (count channels before start address)
				dmx_state= STARTB;
				REG_USART0_CR |= (0x01<<8);
				REG_USART0_CR |= (0<<8);
			}

			else if (dmx_state == STARTB){
				if (--dmx_count == 0){    //start address reached?
					dmx_count= 1;            //set up counter for required channels
					dmx_data[0]= DmxByte/2.55; //get 1st DMX channel of device
					dmx_state= GET_DATA;

				}
			}

			else if (dmx_state == GET_DATA){
				dmx_data[dmx_count++]= DmxByte/2.55;        //get channel
				if (dmx_count >= dmx_data.size()){ //all ch received?
					dmx_state= IDLE;        //wait for next break
					return 0;
				}
			}

		}
	}
}
  
void DMX::enable_dmx(){
    REG_PMC_PCER0 |= PMC_PCER0_PID17; // enable usart0
	REG_USART0_CR  |= (0x01<<4); // enable reciever 
    REG_USART0_CR |= (0x01<<8);//reset status bits
	REG_USART0_MR |= (0x03<<6); //set character length to 8 bits
	REG_USART0_MR |= (0x04<<9); // set parity to non
	REG_USART0_MR |= (0x02<<12);//set stopbits to 2
	REG_USART0_BRGR |= (21<<0); //set baudrate to 250kbit
}
