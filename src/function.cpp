#include "functions.hpp"


// PHOTORES ###############################################
/*                V2
    V1 --- R1 --- | --- R2 --- GND

==> V2 = V1 * R2 / (R1 + R2)
    R1 = ((V1 * R2) / V2 ) - R2
    R2 = R1 * V2 / (V1 - V2)
*/

const double MIDDLE_ADC = BIT_ADC / 2.0;

int count = 0;
bool inv = true;
int compare_photores(const double ADC_VAL) {
    if (ADC_VAL == MIDDLE_ADC)
        return 0;
    else if (ADC_VAL > MIDDLE_ADC)
        return 1;
    else
        return -1;
}


// STEP MOTOR #############################################
StepperMotor::StepperMotor(const int PHASEA1, const int PHASEB1,
                           const int PHASEA2, const int PHASEB2) {
    _phaseA1 = PHASEA1;
    _phaseB1 = PHASEB1;
    _phaseA2 = PHASEA2;
    _phaseB2 = PHASEB2;
    _counter = 0;
    Serial.println("START!");
}

void StepperMotor::activePhase(const int phase) {
    /*  PHASES:
             A1
             -
        A2 - - - B1
             -
             A2
    */
    switch (phase) {
    case 0:
        digitalWrite(_phaseA1, HIGH);
        digitalWrite(_phaseB1, HIGH);
        digitalWrite(_phaseA2, LOW);
        digitalWrite(_phaseB2, LOW);
        break;

    case 1:
        digitalWrite(_phaseA1, LOW);
        digitalWrite(_phaseB1, HIGH);
        digitalWrite(_phaseA2, HIGH);
        digitalWrite(_phaseB2, LOW);
        break;

    case 2:
        digitalWrite(_phaseA1, LOW);
        digitalWrite(_phaseB1, LOW);
        digitalWrite(_phaseA2, HIGH);
        digitalWrite(_phaseB2, HIGH);
        break;

    case 3:
        digitalWrite(_phaseA1, HIGH);
        digitalWrite(_phaseB1, LOW);
        digitalWrite(_phaseA2, LOW);
        digitalWrite(_phaseB2, HIGH);
        break;
    }
}

void StepperMotor::moveCW() {
    activePhase(_counter);
    _counter++;
    _counter = _counter == 5 ? 0 : _counter;
}

void StepperMotor::moveCCW() {
    activePhase(_counter);
    _counter--;
    _counter = _counter == -1 ? 4 : _counter;
}
