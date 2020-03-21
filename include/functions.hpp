#pragma once
#include <Arduino.h>


// Arduino
const int MAX_VOLT = 5;  // [V]
const int BIT_ADC = 1023;
const double VOLTS_PER_BIT = static_cast<double>(MAX_VOLT) / BIT_ADC;


int compare_photores_fix(const double ADC_VAL, const double EPSILON,
                         const bool DEBUG);
int compare_photores_var(const double ADC_VAL, const double INCREMENT,
                         const bool DEBUG);


class StepperMotor {
  private:
    int _phaseA1;  // _A
    int _phaseB1;  // _B
    int _phaseA2;  // _C
    int _phaseB2;  // _D
    bool _debug;
    int _counter;

  public:
    StepperMotor(const int A, const int B, const int C, const int D,
                 const bool DEBUG);

    void activePhase(const int phase);

    void moveCW();

    void moveCCW();
};