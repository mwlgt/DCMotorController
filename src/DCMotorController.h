/*
  MotorController.h - Library for PWM input for spark max or similar motor controllers
  
  Created by Mauricio Caballero
  September 13, 2025
*/

#ifndef MotorController_h
#define MotorController_h

#include <Arduino.h>

class DCMotorController
{
  public:
    DCMotorController(uint8_t pwmPin);
    DCMotorController(uint8_t pwmPin,uint8_t forwardPin,uint8_t reversePin);
    void begin();
    void setSpeed(float speed);
    void stop();

  private:
    uint8_t _mainPin, _forwardPin = 0, _reversePin = 0;
    bool isThreeWire;
};

#endif