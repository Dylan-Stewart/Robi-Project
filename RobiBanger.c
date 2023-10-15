#include <stdlib.h>
#include <time.h>
#include "Robot.h"
#include "MotorHat.h"
#include "sensor.h"

int main(){
    double distanceVal;
    double distanceLeft;
    double distanceRight;
    initRobot(0x60, 0);

    while (1){
        forward(100,1);
        sleep(2);
        distanceVal = getDistance();
        printf("Forward Distance: %f \n", distanceVal);
        if (distanceVal > 50){
            continue;
        }
        distanceVal = getDistance();
        if (distanceVal < 50){
            right(120,0.9); 
            sleep(2);
            distanceLeft = getDistance();
            printf("Left Distance: %f \n", distanceVal);
            left(210,1);
            sleep(2);
            distanceRight = getDistance();
            printf("Right Distance: %f \n", distanceVal);

                if (distanceLeft > distanceRight && distanceLeft > 50){
            	    printf("Choose Right! \n");
                    right(120,0.9); 
                    sleep(2);
                    forward(100,1);
                    stop();
                }
                if (distanceRight > distanceLeft && distanceRight > 50){
            	    printf("Choose Left! \n");
                    left(210,1);
                    sleep(2);
                    forward(100,1);
                    stop();
                }
		if (distanceRight == distanceLeft){
		    stop();
		    break;
		}
		stop();
		break;
        } else {
                stop();
                break;
                }
    }
    return 0;
}


