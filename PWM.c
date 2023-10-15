#include <stdio.h>
#include <bcm2835.h>
#include <math.h>
#include "I2C.h"
#include "PWM.h"

extern void setAllPWM(int on, int off){
    write8(__ALL_LED_ON_L, on & 0xFF);
    write8(__ALL_LED_ON_H, on >> 8);
    write8(__ALL_LED_ON_L, off & 0xFF);
    write8(__ALL_LED_ON_H, off & 0xFF);
}

extern void PWMInit(unsigned int address){
    int i2c = i2cInit(address);
    address = address;

      printf ("Reseting PCA9685 MODE1 (without SLEEP) and MODE2");
    setAllPWM(0, 0);
    write8(__MODE2, __OUTDRV);
    write8(__MODE1, __ALLCALL);
    bcm2835_delay(5);                                       // wait for oscillator

    int mode1 = read8(__MODE1);
    mode1 = mode1 & ~__SLEEP;                 // wake up (reset sleep)
    write8(__MODE1, mode1);
    bcm2835_delay(5);    
}

extern void setPWMFreq(int freq){
    double prescaleval = 25000000.0;    // 25MHz
    prescaleval /= 4096.0;    // 12-bit
    prescaleval /= (double)freq;
    prescaleval -= 1.0;
    printf ("Setting PWM frequency to %d Hz\n", freq);
    printf("Estimated pre-scale: %d\n", prescaleval);
    double prescale = floor(prescaleval + 0.5);
    printf ("Final pre-scale: %d\n", prescale);

    int oldmode = read8(__MODE1);
    int newmode = (oldmode & 0x7F) | 0x10;             // sleep
    write8(__MODE1, newmode);        // go to sleep
    write8(__PRESCALE, (int)floor(prescale));
    write8(__MODE1, oldmode);
    bcm2835_delay(5);
    write8(__MODE1, oldmode | 0x80);
}

extern void setPWM(int channel, int on, int off){
    write8(__LED0_ON_L+4*channel, on & 0xFF);
    write8(__LED0_ON_H+4*channel, on >> 8);
    write8(__LED0_OFF_L+4*channel, off & 0xFF);
    write8(__LED0_OFF_H+4*channel, off >> 8);
}
