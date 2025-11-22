# DCMotorController

This arduino library is meant to simplify the use of DC motor drivers.
It supports motor drivers that both:

1. Take a single PWM speed input for speed (e.g., Spark Max)
2. Take three wires: one PWM input for speed, and two digital inputs for direction (forward and reverse). This supports the L298N driver or similar.

### Usage

First, initialize the motor controller with the appropriate pins. If you're using a driver that takes three wires, use the following constructor:

```
//                       (PWM-capable pin, Forward pin, Reverse pin)
DCMotorController dcMotor(3,                7,          8);
dcMotor.begin(); 
```

Otherwise, if you're using a driver that uses only a single PWM input, input only that pin to the constructor:
```
//                      (PWM-capable pin)
DCMotorController dcMotor(3);
dcMotor.begin(); 
```

Finally, the motor driver can be used with the setSpeed function. The speed parameter is a float between -1 and 1, where -1 is full reverse and 1 is full forward (0 is stop).
```
dcMotor.setSpeed(0.5);
```
