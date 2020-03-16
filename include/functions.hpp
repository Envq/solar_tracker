#pragma once
#include <Arduino.h>


// Arduino
const int MAX_VOLT = 5;  // [V]
const int BIT_ADC = 1023;
const double VOLTS_PER_BIT = static_cast<double>(MAX_VOLT) / BIT_ADC;


int compare_photores(const double ADC_VAL);


class StepperMotor {
  private:
    int _phaseA1; // _A
    int _phaseB1; // _B
    int _phaseA2; // _C
    int _phaseB2; // _D
    int _counter;

  public:
    StepperMotor(const int PHASEA1, const int PHASEB1,
                           const int PHASEA2, const int PHASEB2);

    void activePhase(const int phase);

    void moveCW();

    void moveCCW();
};