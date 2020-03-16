#include "functions.hpp"

// Pins
const int PIN_PHOTORES = A0;
const int MOTOR1 = 8;   // PHASEA1
const int MOTOR2 = 9;   // PHASEB1
const int MOTOR3 = 10;  // PHASEA2
const int MOTOR4 = 11;  // PHASEB2

// Config
const int DELAY_TRACKER = 3000;
const int DELAY_MOTOR = 5;

// Variables
double ADC_val = 0.0;
int direction = 0;
StepperMotor motor(MOTOR1, MOTOR2, MOTOR3, MOTOR4);


void setup() {
    pinMode(PIN_PHOTORES, INPUT);
    pinMode(MOTOR1, OUTPUT);
    pinMode(MOTOR2, OUTPUT);
    pinMode(MOTOR3, OUTPUT);
    pinMode(MOTOR4, OUTPUT);
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
        delay(DELAY_MOTOR);
    }
    Serial.println("FINE");
    delay(DELAY_TRACKER);
}