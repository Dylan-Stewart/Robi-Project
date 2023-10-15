#include<stdio.h>
#include<regex.h>
#include<fcntl.h>
#include<unistd.h>
#include<bcm2835.h>

#ifndef I2C
#define I2C

typedef struct bussAddress{
	int address;
	int bussNumber;
}Address;

// int getPiI2CBusNumber();

int i2cInit(int address);

int write8(unsigned char reg, unsigned char value);

unsigned int read8(unsigned char reg);


#endif
