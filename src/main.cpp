#include "functions.hpp"

// Pins
const int PIN_PHOTORES = A0;
const int MOTOR_IN1 = 8;   // PHASEA1 - A
const int MOTOR_IN2 = 9;   // PHASEB1 - B
const int MOTOR_IN3 = 10;  // PHASEA2 - C
const int MOTOR_IN4 = 11;  // PHASEB2 - D

// Config
const int DELAY_TRACKER = 3000;
const int DELAY_MOTOR_IN = 5;
const bool DEBUG = true;

// Variables
double ADC_val = 0.0;
int direction = 0;
StepperMotor motor(MOTOR_IN1, MOTOR_IN2, MOTOR_IN3, MOTOR_IN4, DEBUG);


void setup() {
    pinMode(PIN_PHOTORES, INPUT);
    pinMode(MOTOR_IN1, OUTPUT);
    pinMode(MOTOR_IN2, OUTPUT);
    pinMode(MOTOR_IN3, OUTPUT);
    pinMode(MOTOR_IN4, OUTPUT);
    Serial.begin(9600);
}

void loop() {
    // Read the ADC value
    ADC_val = analogRead(PIN_PHOTORES);

    // Get direction from photoresistences comparing
    while ((direction = compare_photores(ADC_val)) != 0) {
        if (direction == 1)
            motor.moveCW();
        else
            motor.moveCCW();
        delay(DELAY_MOTOR_IN);
    }
    delay(DELAY_TRACKER);
}