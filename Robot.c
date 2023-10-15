#include <stdio.h>
#include <bcm2835.h>
#include <time.h>
#include <assert.h>
#include "MotorHat.h"
#include "Robot.h"

static int _left;
static int _right;
static int _left_trim;
static int _right_trim;

extern void initRobot(unsigned int addr, int stop_at_exit){
    initHat(0x60, 1600);
    _left = 0;
    _right = 1;
    _left_trim = 0; 
    _right_trim = 0;
    run(RELEASE, _left);
    run(RELEASE, _right);
    if (stop_at_exit){
        stop();
    }
}

extern void stop(){
    run(RELEASE, _left);
    run(RELEASE, _right); 
}

void _left_speed(int speed){
    assert(0 <= speed <= 255);
    speed += _left_trim;
    setSpeed(speed, 0);
}

void _right_speed(int speed){
    assert(0 <= speed <= 255);
    speed += _right_trim;
    setSpeed(speed, 1);
}


extern void forward(int speed, int seconds){
    _left_speed(speed);
    _right_speed(speed);
    run(FORWARD, _left);
    run(FORWARD, _right);
    if (seconds != 0){
        bcm2835_delay(seconds*1000);
        stop();
    }
}

extern void backward(int speed, int seconds){
    _left_speed(speed);
    _right_speed(speed);
    run(BACKWARD, _left);
    run(BACKWARD, _right);
    if (seconds != 0){
        bcm2835_delay(seconds*1000);
        stop();
    }
}

extern void right(int speed, int seconds){
    _left_speed(speed);
    _right_speed(speed);
    run(FORWARD, _right);
    run(BACKWARD, _left);
    if (seconds != 0){
        bcm2835_delay(seconds*1000);
        stop();
    }
}

extern void left(int speed, int seconds){
    _left_speed(speed);
    _right_speed(speed);
    run(FORWARD, _left);
    run(BACKWARD, _right);
    if (seconds != 0){
        bcm2835_delay(seconds*1000);
        stop();
    }
}
