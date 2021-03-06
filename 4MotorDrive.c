#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, in2,    pwrExtend,      sensorAnalog)
#pragma config(Sensor, I2C_1,  rmEnc0,         sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Sensor, I2C_2,  lmEnc1,         sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Motor,  port8,           LeftMotor,     tmotorVex393_MC29, openLoop, encoderPort, I2C_1)
#pragma config(Motor,  port9,           RightMotor,    tmotorVex393_MC29, openLoop, reversed, encoderPort, I2C_2)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//----------------------------------------------------------------------------------------------------
// 4 wheel drive - left two wheels and right two wheels are powered together using a 29
// module for each motor and a power Y cable from the the power extender.  Motors are
// powered from port 8 - left side and port 9 - right side.
//
// Rear wheel motors on both left and right each have encoders installed.
//
// Drive control uses two tasks - one task is used to monitor the turbo button
// the second task is used to control the driving with joysticks
//
// LCD display is used to display battery statuses - two core bateries and backup
// 9V battery for cortex
//----------------------------------------------------------------------------------------------------

//+++++++++++++++++++++++++++++++++++++ Global Variables +++++++++++++++++++++++++++++++++++++++++++++
int turboButtonState = 0;
bool buttonPressed = false;

//++++++++++++++++++++++++++++++++++++ turbo Task ++++++++++++++++++++++++++++++++++++++++++++++++++++
task turboControl()
{
	while(true)
	{
		if( vexRT[ Btn8U ] == 1 )
    {
    	if( ! buttonPressed )
      {
      	// change the toggle state
        turboButtonState = 1 - turboButtonState;
        // Note the button is pressed
        buttonPressed = true;
      }
    }
    else
    {
    	// the button is not pressed
      buttonPressed = false;
    }
    wait1Msec(100);				// give loop a bit of time so we don't flip-flop
  }
}

//+++++++++++++++++++++++++++++++++++++ LCD Task +++++++++++++++++++++++++++++++++++++++++++++++++++++
task lcdControl()
{
	bLCDBacklight = true;									// Turn on LCD Backlight
	string mainBattery, extendBattery, backupBattery;

	while(true)														// An infinite loop to keep the program running until you terminate it
	{
		clearLCDLine(0);											// Clear line 1 (0) of the LCD
		clearLCDLine(1);											// Clear line 2 (1) of the LCD

		//Display the Primary Robot battery voltage
		displayLCDString(0, 0, "P: ");
		sprintf(mainBattery, "%1.2f%c", nImmediateBatteryLevel/1000.0,'V'); //Build the value to be displayed
		displayNextLCDString(mainBattery);
		// Get battery on power extender
    displayLCDString(0, 9, "E: ");
		sprintf(extendBattery, "%1.2f%c", (SensorValue(pwrExtend)/70.0)/4,'V'); //Build the value to be displayed
		displayNextLCDString(extendBattery);

		//Display the Backup battery voltage
		displayLCDString(1, 0, "Cortex Bat: ");
		sprintf(backupBattery, "%1.2f%c", BackupBatteryLevel/1000.0, 'V');	//Build the value to be displayed
		displayNextLCDString(backupBattery);

		//Short delay for the LCD refresh rate
		wait1Msec(100);
	}
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//+++++++++++++++++++++++++++++++++++ Drive Task +++++++++++++++++++++++++++++++++++++++++++++++++++++
task driveControl()
{
	int threshold = 10;

  while(1 == 1)
  {
  	if(abs(vexRT[Ch3]) > threshold)         // If the left joystick is greater than or less than the threshold:
    {
    	if(turboButtonState == 1)
    	{
	    	motor[RightMotor] = vexRT[Ch3];
	  	}
	  	else
	    {
	    	motor[RightMotor] = vexRT[Ch3] / 4;
	    }
	  }
    else                                    // If the left joystick is within the threshold:
    {
	    motor[RightMotor] = 0;			          // Stop the left motor (cancel noise)
    }

    if(abs(vexRT[Ch2]) > threshold)         // If the right joystick is greater than or less than the threshold:
    {
      if(turboButtonState == 1)
    	{
	    	motor[LeftMotor] = vexRT[Ch2];
	  	}
	  	else
	    {
	    	motor[LeftMotor] = vexRT[Ch2] / 4;
	    }
		}
    else                                    // If the right joystick is within the threshold:
    {
	    motor[LeftMotor] = 0;
    }
  }
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//+++++++++++++++++++++++++++++++++++++++++++++| MAIN |+++++++++++++++++++++++++++++++++++++++++++++++
task main()
{
  startTask(lcdControl);
  startTask(turboControl);
  startTask(driveControl);

  while(true)
  {
  	wait1Msec(1);
    // Keep the program alive
  }
}


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
