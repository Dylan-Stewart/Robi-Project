#include<bcm2835.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<sys/time.h>

#define ECHO RPI_V2_GPIO_P1_18
#define TRIG RPI_V2_GPIO_P1_16

double get_time()
{
	struct timeval t;
	gettimeofday(&t, NULL);
	return t.tv_usec;
}

void gpio_reset()
{
	bcm2835_gpio_set_pud(RPI_V2_GPIO_P1_18, BCM2835_GPIO_PUD_OFF);
	bcm2835_gpio_set_pud(RPI_V2_GPIO_P1_16, BCM2835_GPIO_PUD_OFF);

	bcm2835_gpio_fsel(RPI_V2_GPIO_P1_18, BCM2835_GPIO_FSEL_INPT);
	bcm2835_gpio_fsel(RPI_V2_GPIO_P1_16, BCM2835_GPIO_FSEL_INPT);
}

extern double getDistance()
{
	
	double pulse_start, pulse_end, pulse_duration;
	double distance;

	if (!bcm2835_init())
		return 1;

	bcm2835_gpio_fsel(ECHO, BCM2835_GPIO_FSEL_INPT);
	bcm2835_gpio_fsel(TRIG, BCM2835_GPIO_FSEL_OUTP);

	bcm2835_gpio_write(TRIG,LOW);

	// printf("Waiting for sensor to settle\n");

	// bcm2835_delay(2000);

	// printf("Set TRIG to true\n");

	bcm2835_gpio_write(TRIG,HIGH);

	// printf("Sleep\n");

	bcm2835_delayMicroseconds(10);

	// printf("Set TRIG to false\n");

	bcm2835_gpio_write(TRIG,LOW);

	// printf("First while loop\n");

	while (bcm2835_gpio_lev(ECHO)==0)
		pulse_start = get_time();//get the time in microseconds

	// printf("pulse start: %Lf\n",pulse_start);

	// printf("Second while loop\n");

	while(bcm2835_gpio_lev(ECHO)==1)
		pulse_end = get_time();//get the time in micorseconds

	// printf("pulse end:%Lf\n",pulse_end);

	//pulse_duration = (double)(pulse_end - pulse_start)/CLOCKS_PER_SEC;
	//CLOCKS_PER_SEC is equal to 1000000 on the raspberry pi.
	//in order for this to work, you have to get the time in micro seconds.

	pulse_duration = (pulse_end - pulse_start)/1000000;

	// printf("pulse duration:%Lf\n",pulse_duration);

	distance = pulse_duration * 17150;

	// printf("Distance:%.2f cm\n",distance);

	gpio_reset();
	return distance;

}
