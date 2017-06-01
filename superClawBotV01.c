#pragma config(UART_Usage, UART1, uartVEXLCD, baudRate19200, IOPins, None, None)
#pragma config(UART_Usage, UART2, uartNotUsed, baudRate4800, IOPins, None, None)
#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, in1,    leftLine,       sensorReflection)
#pragma config(Sensor, in2,    centerLine,     sensorReflection)
#pragma config(Sensor, in3,    rightLine,      sensorReflection)
#pragma config(Sensor, dgtl1,  sonarIn,        sensorSONAR_cm)
#pragma config(Sensor, dgtl3,  upperLimit,     sensorTouch)
#pragma config(Sensor, dgtl4,  lowerLimit,     sensorTouch)
#pragma config(Sensor, dgtl5,  bumperBack,     sensorTouch)
#pragma config(Sensor, dgtl6,  elbowEncoder,   sensorQuadEncoder)
#pragma config(Sensor, dgtl8,  shoulderEncoder, sensorQuadEncoder)
#pragma config(Sensor, I2C_1,  leftEncoder,    sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_2,  rightEncoder,   sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Motor,  port1,           leftMotor,     tmotorVex393_HBridge, openLoop, reversed, driveLeft, encoderPort, I2C_1)
#pragma config(Motor,  port2,           clawMotor,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           wristMotor,    tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           elbowMotor,    tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           shoulderMotor, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port10,          rightMotor,    tmotorVex393_HBridge, openLoop, driveRight, encoderPort, I2C_2)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*----------------------------------------------------------------------------------------------------*\

\*----------------------------------------------------------------------------------------------------*/

//+++++++++++++++++++++++++++++++++++++++++++++| MAIN |+++++++++++++++++++++++++++++++++++++++++++++++

task main()
{
  while(1 == 1)
  {
    //Driving Motor Control
    motor[leftMotor] = vexRT[Ch3] / 2;
    motor[rightMotor] = vexRT[Ch2] / 2;

    //Arm Control
    if(vexRT[Btn6U] == 1)
    {
      motor[elbowMotor] = -100;
    }
    else if(vexRT[Btn6D] == 1)
    {
      motor[elbowMotor] = 40;
    }
    else
    {
      motor[elbowMotor] = 0;
    }

    //Arm Control
    if(vexRT[Btn5U] == 1)
    {
      motor[shoulderMotor] = -100;
    }
    else if(vexRT[Btn5D] == 1)
    {
      motor[shoulderMotor] = 100;
    }
    else
    {
      motor[shoulderMotor] = 0;
    }

  }
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++