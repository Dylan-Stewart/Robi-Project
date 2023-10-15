# build an executable
all: I2C.o PWM.o MotorHat.o Robot.o RobiBanger.c
	# gcc -c I2C.c -lbcm2835
	# gcc -c PWM.c I2C.o -lbcm2835
	# gcc -c MotorHat.c PWM.o -lbcm2835
	# gcc -c Robot.c MotorHat.o -lbcm2835
	gcc -o RobiBanger RobiBanger.c I2C.c PWM.c MotorHat.c Robot.c sensor.c -lbcm2835 -lm
clean:
	$(RM) I2C.o
	$(RM) PWM.o
	$(RM) MotorHat.o
	$(RM) Robot.o
	$(RM) sensor.o
	$(RM) RobiBanger