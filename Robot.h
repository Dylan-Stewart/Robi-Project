#include <stdio.h>
#include <bcm2835.h>
#include <time.h>
#include <assert.h>
#include "MotorHat.h"

#ifndef ROBOT
#define ROBOT

void initRobot(unsigned int addr, int stop_at_exit);

void stop();

void forward(int speed, int seconds);

void backward(int speed, int seconds);

void right(int speed, int seconds);

void left(int speed, int seconds);

#endif

