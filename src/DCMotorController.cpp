/*
  MotorController.cpp - Library for PWM input for spark max or similar motor controllers
  
  Created by Mauricio Caballero
  September 13, 2025
*/


#include <Arduino.h>
#include "DCMotorController.h"
// This library uses the built-in servo libray for pwm timings to ensure compatibility accross all boards
#include <Servo.h>
Servo motorax;


/// @brief Instantiates new Motor Controller object with only pwm control.
/// @param pwmPin the pin for pwm signal connection.
/// @note the pwmPin needs to support PWM, check board labeling.
DCMotorController::DCMotorController(uint8_t pwmPin)
{
  _mainPin = pwmPin;
  isThreeWire = false;
}

/// @brief Instantiates new Motor Controller object with three wire control, such as the L298N motor driver
/// @param pwmPin The pin connected to the motor controller's PWM input.
/// @param forwardPin The pin connected to the motor controller's direction input for forward motion.
/// @param reversePin The pin connected to the motor controller's direction input for reverse motion.
/// @note the pwmPin needs to support PWM, check board labeling. Forward and reverse pins are regular digital pins.
DCMotorController::DCMotorController(uint8_t pwmPin,uint8_t forwardPin,uint8_t reversePin){
  _mainPin = pwmPin;
  _forwardPin = forwardPin;
  _reversePin = reversePin;
  isThreeWire = true;
}


/// @brief Initialize motor controller pins for PWM signal output. Calling this function is necessary before using the motor controller
void DCMotorController::begin()
{
  if(isThreeWire){
    pinMode(_forwardPin,OUTPUT);
    pinMode(_reversePin,OUTPUT);
    pinMode(_mainPin,OUTPUT);
  }else{
    motorax.attach(_mainPin);
  }
}

/// @brief Set the motor speed
/// @param speed Float between -1 and 1:
///         -1: Full reverse
///          1: Full forward
///          0: No power to the motor
void DCMotorController::setSpeed(float speed)
{
  // Constrain speed value to correct bounds
  if(speed > 1){
    speed = 1;
  }else if (speed < -1){
    speed = -1;
  }
  

  if(isThreeWire){
    if(speed > 0){
      digitalWrite(_forwardPin,HIGH);
      digitalWrite(_reversePin,LOW);
    }else{
      digitalWrite(_forwardPin,LOW);
      digitalWrite(_reversePin,HIGH);
    }
    // Convert speed to range between 0 and 255
    analogWrite(_mainPin,abs((int)(speed * 255)));
    return;
  }

  // Convert speed values to servo angles (for built-in servo library use)
  speed *= 90;
  speed += 90;
  
  // Call servo library to send PWM signal
  motorax.write(speed);
}

/// @brief stop function to set speed to zero and stop the motor
void DCMotorController::stop(){
  if(isThreeWire){
    digitalWrite(_forwardPin,LOW);
    digitalWrite(_reversePin,LOW);
    analogWrite(_mainPin,0);
  }else{
    motorax.write(90);
  }
}