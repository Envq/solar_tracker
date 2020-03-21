#include "functions.hpp"

// Pins
const int PIN_PHOTORES = A7;
const int MOTOR_IN1 = 9;   // PHASEA1 - A
const int MOTOR_IN2 = 10;  // PHASEB1 - B
const int MOTOR_IN3 = 11;  // PHASEA2 - C
const int MOTOR_IN4 = 12;  // PHASEB2 - D

// Config
const int DELAY_TRACKER = 3000;
const int DELAY_MOTOR_IN = 5;
const double PARAM_RES = 0.01;
const bool DEBUG_RES = false;
const bool DEBUG_MOTOR = false;

// Variables
double ADC_val = 0.0;
int direction = 0;
StepperMotor motor(MOTOR_IN1, MOTOR_IN2, MOTOR_IN3, MOTOR_IN4, DEBUG_MOTOR);


void setup() {
    pinMode(PIN_PHOTORES, INPUT);
    pinMode(MOTOR_IN1, OUTPUT);
    pinMode(MOTOR_IN2, OUTPUT);
    pinMode(MOTOR_IN3, OUTPUT);
    pinMode(MOTOR_IN4, OUTPUT);
    Serial.begin(9600);
}

void loop() {
    while ((direction = compare_photores_var(analogRead(PIN_PHOTORES),
                                             PARAM_RES, DEBUG_RES)) != 0) {
        if (direction == 1)
            motor.moveCW();
        else
            motor.moveCCW();
        delay(DELAY_MOTOR_IN);
    }
    delay(DELAY_TRACKER);
}