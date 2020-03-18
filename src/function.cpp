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
StepperMotor::StepperMotor(const int A, const int B, const int C, const int D,
                           const bool DEBUG) {
    _phaseA1 = A;
    _phaseB1 = B;
    _phaseA2 = C;
    _phaseB2 = D;
    _debug = DEBUG;
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
    if (_debug)
        Serial.println(_counter);
    activePhase(_counter);
    _counter++;
    _counter = _counter == 4 ? 0 : _counter;
}

void StepperMotor::moveCCW() {
    if (_debug)
        Serial.println(_counter);
    activePhase(_counter);
    _counter--;
    _counter = _counter == -1 ? 3 : _counter;
}
