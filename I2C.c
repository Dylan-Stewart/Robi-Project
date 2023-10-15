#include<stdio.h>
#include<regex.h>
#include<fcntl.h>
#include<unistd.h>
#include<bcm2835.h>
#include"I2C.h"

#define BUFFERSIZE 4096


extern int write8(unsigned char reg, unsigned char value){
	
	char buff[2];
	buff[0] = reg; 
	buff[1] = value;
	uint8_t result;
	result = bcm2835_i2c_write(buff, 2);
	return result;
}

extern unsigned int read8(unsigned char reg){

	unsigned char buff[2];
    buff[0] = reg;
    uint8_t code = bcm2835_i2c_read(buff,2);
    return buff[0];

}
// void  write8(unsigned char reg, unsigned char value){
// 	char buff[2];
// buff[0] = reg;
// buff[1] = value;
// 	uint8_t result;
// 	result = bcm2835_i2c_write(buff,2);
// }

/*
def write8(self, reg, value):
    "Writes an 8-bit value to the specified register/address"
    try:
      self.bus.write_byte_data(self.address, reg, value)
      if self.debug:
        print "I2C: Wrote 0x%02X to register 0x%02X" % (value, reg)
    except IOError, err:
      return self.errMsg()
	  */

extern int i2cInit(int address){
	Address *theAddress;
	
	theAddress = (Address*)malloc(sizeof(Address));
	
	theAddress->address = address;
	
	//i2c initialization should also go here.
	
	if (!bcm2835_init())
    	{
     		printf("bcm2835_init failed. Are you running as root??\n");
      		return 1;
    	}//if bcm_init
	
	if (!bcm2835_i2c_begin())
    	{
		printf("bcm2835_i2c_begin failed. Are you running as root??\n");
		return 1;
	}//if i2c_begin

	bcm2835_i2c_setSlaveAddress(address); //set HAT address to 0x41
	return 0;
	
	
}





