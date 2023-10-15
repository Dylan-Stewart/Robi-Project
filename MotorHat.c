#include <stdio.h>
#include <bcm2835.h>
#include "PWM.h"
#include "MotorHat.h"

extern void initMotors(int num){

    if (num == 0){
        motors[0].pwm = 8;
        motors[0].in2 = 9;
        motors[0].in1 = 10;
    }
    else if (num == 1){
        motors[1].pwm = 13;
        motors[1].in2 = 12;
        motors[1].in1 = 11;
    }
    else{
        printf("MotorHat Motor must be between 0 and 1 inclusive");
    }
}

extern void initHat(unsigned int addr, int freq){
    unsigned int i2caddr = addr;
    int frequency = freq;
    initMotors(0);
    initMotors(1);
    PWMInit(addr);
    setPWMFreq(freq);
}

extern void run(unsigned char command, int motorID){
    if (command == FORWARD){
        setPin(motors[motorID].in2, 0);
        setPin(motors[motorID].in1, 1);
    }
    if (command == BACKWARD){
        setPin(motors[motorID].in1, 0);
        setPin(motors[motorID].in2, 1);
    }
    if (command == RELEASE){
        setPin(motors[motorID].in2, 0);
        setPin(motors[motorID].in1, 0);
    }
}

extern void setSpeed(int speed, int motorNum){
    if (speed < 0){
        speed = 0;
    }
    if (speed > 255){
        speed = 255;
    }
    setPWM(motors[motorNum].pwm, 0, speed*16);
}

extern void setPin(unsigned char pin, unsigned char value){
    if (pin < 0 || pin > 15){
        printf("PWM Pin must be between 0 and 15 inclusive");
    }
    if (value != 0 && value != 1){
        printf("Pin value must be 0 or 1!");
    }
    if (value == 0){
        setPWM(pin, 0, 4096);
    }
    if (value == 1){
        setPWM(pin, 4096, 0);
    }
}
