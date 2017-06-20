#include <Arduino.h>
#include "motor.h"
#include "motorController.h"
//#include "motorController.h"

// 13 12 11 Front Left   Positive -true-> Negative    COSINE
// 10 9  8  Back Left    Negative -false-> Negative   SINE
// 7  6  5  Back Right   Positive -false-> Positive   COSINE
// 4  3  2  Front Right  Negative -true-> Positive    SINE

/*
      	 	 0
					_  _
				/	 V	\
	90	|       |   270
			\______/
			   180
*/

MotorController motor;

void setup(){
	motor.Setup();
}

void loop(){
	for (int i = 1; i < 256; i++) {
		motor.Move(100, i);
		delay(100);
	}
}