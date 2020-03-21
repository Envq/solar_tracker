#include "functions.hpp"


// PHOTORES ###############################################
/*                V2
    V1 --- R1 --- | --- R2 --- GND

==> V2 = V1 * R2 / (R1 + R2)
    R1 = ((V1 * R2) / V2 ) - R2
    R2 = R1 * V2 / (V1 - V2)
*/

const double MIDDLE_ADC = MAX_VOLT / 2.0;
int compare_photores_fix(const double ADC_VAL, const double EPSILON,
                         const bool DEBUG) {
    double ADC_VOLT = ADC_VAL * VOLTS_PER_BIT;
    int res;
    if (ADC_VOLT < MIDDLE_ADC - EPSILON)
        res = -1;
    else if (ADC_VOLT > MIDDLE_ADC + EPSILON)
        res = 1;
    else
        res = 0;
    if (DEBUG)
        Serial.println(res);
    return res;
}


double epsilon = 0.0;
int last = 0;

int compare_photores_var(const double ADC_VAL, const double INCREMENT,
                         const bool DEBUG) {
    double ADC_VOLT = ADC_VAL * VOLTS_PER_BIT;
    int res;
    if (ADC_VOLT < MIDDLE_ADC - epsilon) {
        res = -1;
        if (last != res)
            epsilon += INCREMENT;
        last = res;
    } else if (ADC_VOLT > MIDDLE_ADC + epsilon) {
        res = 1;
        if (last != res)
            epsilon += INCREMENT;
        last = res;
    } else {
        res = 0;
        last = res;
        epsilon = 0.0;
    }
    if (DEBUG) {
        Serial.print("VOLT: ");
        Serial.println(ADC_VOLT);
        Serial.print("EPSILON: ");
        Serial.println(epsilon, 4);
        Serial.print("LAST: ");
        Serial.println(last);
        Serial.print("RES: ");
        Serial.println(res);
        Serial.print("DIRECTION: ");
        Serial.println((res == -1) ? "C-CLK" : (res == 1) ? "CLK" : "STOP");
        Serial.println("------");
    }
    return res;
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
