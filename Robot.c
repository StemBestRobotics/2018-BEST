#pragma config(Sensor, dgtl1,  motorJumper,    sensorTouch)
#pragma config(Sensor, dgtl2,  telescopeMax,   sensorTouch)
#pragma config(Sensor, dgtl3,  telescopeMin,   sensorTouch)
#pragma config(Motor,  port2,           driveMotor,    tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           armRotateMotor, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           armAngleMotor, tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port5,           armTelescopeMotor, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           clawRotateServo, tmotorServoStandard, openLoop)
#pragma config(Motor,  port7,           clawAngleServo, tmotorServoStandard, openLoop)
#pragma config(Motor,  port8,           clawGrabServo, tmotorServoStandard, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//------------------------------------------------------
//VARIABLES:
bool clawRotateToggle = true; 													//holds value that controls which way the claw-rotate servo is toggled (left v right)
bool clawRotateCheck = true;														//holds value that makes sure that the claw-rotate servo is only toggled once per button press
bool clawAngleToggle = true; 														//holds value that controls which way the claw-angle servo is toggled (up v down)
bool clawAngleCheck = true;															//holds value that makes sure that the claw-angle servo is only toggled once per button press
bool clawGrabToggle = true; 														//holds value that controls if the grabbing servo is toggled (open v closed)
bool clawGrabCheck = true;															//holds value that makes sure that the grabbing servo is only toggled once per button press
bool speedToggleCheck = true;														//holds value that makes sure speed is only toggled once per button press
float motorSpeed = 127;																	//holds value that is current motor speed
int deadband = 10;																			//holds value that determines size of deadband
//------------------------------------------------------
void speedToggle(){																		//SPEED TOGGLE: allows button to toggle current motor speed between 100% speed and 50% speed
	if(vexRT[Btn8A] && speedToggleCheck){
		speedToggleCheck=false;
		if(motorSpeed==127){
			motorSpeed=63.5;
		}else{
			motorSpeed=127;
		}
	}else if(!vexRT[Btn8A]){
		speedToggleCheck=true;
	}
}
//------------------------------------------------------
void driveMotors(){																			//DRIVE: Allows for inversion and controling of motors with joysticks
	if(SensorValue(motorJumper) == 1){											//JUMPER: Checks for prescence of fused pin, and inverts motor control correspondingly
		if (vexRT[Ch4] > deadband || vexRT[Ch4] < -deadband){	//DEADBAND: Utilizes Dead band for more precise movement and better calibration.
			motor[driveMotor] = vexRT[Ch4]*(motorSpeed/127); 		//INVERTED: Connects Joystick to motor
		}
		else {
			motor[driveMotor] = 0;
		}
	}else{
		if (vexRT[Ch4] > deadband || vexRT[Ch4] < -deadband) {//DEADBAND: Deadband for normal control
			motor[driveMotor] = -vexRT[Ch4]*(motorSpeed/127); 	//NORMAL: Connects Joystick to motor
		}
		else {
			motor[driveMotor] = 0;
		}
	}
}
//------------------------------------------------------
void armMotors(){																				//ARM: ALlows Joystick and Buttons to control the movement of Arm
	motor[armRotateMotor] = vexRT[Ch1]*motorSpeed/127;			//ROTATE: assigns joystick to rotate arm
	motor[armAngleMotor] = vexRT[Ch2]*motorSpeed/127;				//ANGLE: assigns joystick to raise arm
	if(vexRT[Btn5U]){																				//TELESCOPE: assigns buttons to extend and retract arm
		if(!SensorValue(telescopeMax)){											//LIMIT: uses limit switch to prevent over-extending										//LIMIT: uses limit switch to prevent over-extending
			motor[armTelescopeMotor] = 127*motorSpeed/127;
		}else{
			motor[armTelescopeMotor] = 0;
		}
	}else if(vexRT[Btn5D]){
		if(!SensorValue(telescopeMin)){
			motor[armTelescopeMotor] = -127*motorSpeed/127;			//LIMIT: uses limit switch to prevent over-retracting
		}else{
			motor[armTelescopeMotor] = 0;
		}
	}else{
		motor[armTelescopeMotor] = 0;
	}
}
//------------------------------------------------------
void clawServos(){																			//CLAW: Allows Controller to control movement of claw
	if(vexRT[Btn6U] && clawRotateCheck){										//ROTATE TOGGLE: allows buttons to toggle the rotation of claw between 0 & 90 degrees
		clawRotateCheck = false;
		if(clawRotateToggle){
 			motor[clawRotateServo] = 101.6;
 			clawRotateToggle = false;
 		}else{
 			motor[clawRotateServo] = -127;
			clawRotateToggle = true;
		}
	}else if(!vexRT[Btn6U]){
		clawRotateCheck = true;
 	}
 	if(vexRT[Btn6D] && clawAngleCheck){										//ANGLE TOGGLE: allows buttons to toggle the angle of claw between 0 & 90 degrees
		clawAngleCheck = false;
		if(clawAngleToggle){
 			motor[clawAngleServo] = 101.6;
 			clawAngleToggle = false;
 		}else{
 			motor[clawAngleServo] = -127;
			clawAngleToggle = true;
		}
	}else if(!vexRT[Btn6D]){
		clawAngleCheck = true;
 	}
 	if(vexRT[Btn8D] && clawGrabCheck){										//GRAB TOGGLE: allows buttons to toggle the grab state of claw between open and closed (0 and 90 degrees respectively)
		clawGrabCheck = false;
		if(clawGrabToggle){
 			motor[clawGrabServo] = 101.6;
 			clawGrabToggle = false;
 		}else{
 			motor[clawGrabServo] = -127;
			clawGrabToggle = true;
		}
	}else if(!vexRT[Btn8D]){
		clawGrabCheck = true;
 	}
}
//------------------------------------------------------
task main(){																						//main start task
	while(1==1) {//gurantees that the robot will constantly run throughout game
		speedToggle();
		driveMotors();
		armMotors();
		clawServos();
	}
}
