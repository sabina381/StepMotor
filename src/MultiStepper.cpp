// Switching Seq 
// Step  | IN1 IN2 IN3 IN4
// ----- | ----------------
//   0   |  0   0   0   1
//   1   |  0   0   1   1
//   2   |  0   0   1   0
//   3   |  0   1   1   0
//   4   |  0   1   0   0
//   5   |  1   1   0   0
//   6   |  1   0   0   0
//   7   |  1   0   0   1

#include "Arduino.h"
#include "StepMotor.h"

MultiStepper::MultiStepper(int x_steps, int y_steps, int motor_pin_x1, int motor_pin_x2, int motor_pin_x3, int motor_pin_x4, int motor_pin_y1, int motor_pin_y2, int motor_pin_y3, int motor_pin_y4)
  {
    this->x_step_signal = 0; // signal range (0-7)
    this->y_step_signal = 0;
    this->x_direction = 1; // init direction : clock wise
    this->y_direction = 1;
    this->x_steps = x_steps; // 4095 steps for 360 degree, 8 steps for 5.625 degree
    this->y_steps = y_steps;

    // define pin attributes
    this->motor_pin_x1 = motor_pin_x1;
    this->motor_pin_x2 = motor_pin_x2;
    this->motor_pin_x3 = motor_pin_x3;
    this->motor_pin_x4 = motor_pin_x4;

    this->motor_pin_y1 = motor_pin_y1;
    this->motor_pin_y2 = motor_pin_y2;
    this->motor_pin_y3 = motor_pin_y3;
    this->motor_pin_y4 = motor_pin_y4;
    
    // setup pins 
    pinMode(this->motor_pin_x1, OUTPUT);
    pinMode(this->motor_pin_x2, OUTPUT);
    pinMode(this->motor_pin_x3, OUTPUT);
    pinMode(this->motor_pin_x4, OUTPUT);

    pinMode(this->motor_pin_y1, OUTPUT);
    pinMode(this->motor_pin_y2, OUTPUT);
    pinMode(this->motor_pin_y3, OUTPUT);
    pinMode(this->motor_pin_y4, OUTPUT);
}

void MultiStepper::step(int x_steps, int y_steps) {
    this->x_direction = (x_steps >= 0) ? 1 : 0;
    this->y_direction = (y_steps >= 0) ? 1 : 0;
    x_steps = abs(x_steps);
    y_steps = abs(y_steps);

    unsigned long previous_time;
    unsigned long current_millis;
    long time;

    if (this->x_direction == this->y_direction) {
      while (x_steps > 0 and y_steps > 0) {
        current_millis = micros();
        if (current_millis - previous_time >= 800) {

            this->multi_stepper_CW(); // move single step 
            time += micros() - previous_time;
            previous_time = micros();
            x_steps--;
            y_steps--;
        }
      }
    } else{
      while (x_steps > 0 and y_steps > 0) {
        current_millis = micros();
        if (current_millis - previous_time >= 800) {
            this->multi_stepper_CCW(); // move single step 
            time += micros() - previous_time;
            previous_time = micros();
            x_steps--;
            y_steps--;
        }
      }
    }
}

void MultiStepper::multi_stepper_CW() {
    switch (this->x_step_signal) {
        case 0: // 0001
            this->pinSignal(LOW, LOW, LOW, HIGH, LOW, LOW, LOW, HIGH);
            break;

        case 1: // 0011
            this->pinSignal(LOW, LOW, HIGH, HIGH, LOW, LOW, HIGH, HIGH);
            break;

        case 2: // 0010
            this->pinSignal(LOW, LOW, HIGH, LOW, LOW, LOW, HIGH, LOW);
            break;

        case 3: // 0110
            this->pinSignal(LOW, HIGH, HIGH, LOW, LOW, HIGH, HIGH, LOW);
            break;

        case 4: // 0100
            this->pinSignal(LOW, HIGH, LOW, LOW, LOW, HIGH, LOW, LOW);
            break;

        case 5: // 1100
            this->pinSignal(HIGH, HIGH, LOW, LOW, HIGH, HIGH, LOW, LOW);
            break;

        case 6: // 1000
            this->pinSignal(HIGH, LOW, LOW, LOW, HIGH, LOW, LOW, LOW);
            break;

        case 7: // 1001
            this->pinSignal(HIGH, LOW, LOW, HIGH, HIGH, LOW, LOW, HIGH);
            break;

        default:
            digitalWrite(this->motor_pin_x1, LOW);
            digitalWrite(this->motor_pin_y1, LOW);
    }
    this->controlSignal(); // set 
}



void MultiStepper::multi_stepper_CCW() {
    switch (this->x_step_signal) { // x signal 기준으로
        case 0: // 0001
            this->pinSignal(LOW, LOW, LOW, HIGH, HIGH, LOW, LOW, HIGH);
            break;

        case 1: // 0011
            this->pinSignal(LOW, LOW, HIGH, HIGH, HIGH, LOW, LOW, LOW);
            break;

        case 2: // 0010
            this->pinSignal(LOW, LOW, HIGH, LOW, HIGH, HIGH, LOW, LOW);
            break;

        case 3: // 0110
            this->pinSignal(LOW, HIGH, HIGH, LOW, LOW, HIGH, LOW, LOW);
            break;

        case 4: // 0100
            this->pinSignal(LOW, HIGH, LOW, LOW, LOW, HIGH, HIGH, LOW);
            break;

        case 5: // 1100
            this->pinSignal(HIGH, HIGH, LOW, LOW, LOW, LOW, HIGH, LOW);
            break;

        case 6: // 1000
            this->pinSignal(HIGH, LOW, LOW, LOW, LOW, LOW, HIGH, HIGH);
            break;

        case 7: // 1001
            this->pinSignal(HIGH, LOW, LOW, HIGH, LOW, LOW, LOW, HIGH);
            break;

        default:
            digitalWrite(this->motor_pin_x1, LOW);
            digitalWrite(this->motor_pin_y1, LOW);
    }
    this->controlSignal(); // set 
}


void MultiStepper::pinSignal(int a1, int b1, int c1, int d1, int a2, int b2, int c2, int d2){
    digitalWrite(this->motor_pin_x1, a1);
    digitalWrite(this->motor_pin_x2, b1);
    digitalWrite(this->motor_pin_x3, c1);
    digitalWrite(this->motor_pin_x4, d1);

    digitalWrite(this->motor_pin_y1, a2);
    digitalWrite(this->motor_pin_y2, b2);
    digitalWrite(this->motor_pin_y3, c2);
    digitalWrite(this->motor_pin_y4, d2);
}

void MultiStepper::controlSignal() {

    // by using direction & step_signal attribute, 
    // control step_signal sequence.
    // control step_signal by direction. 
    
    // x
    if (this->x_direction == 0) {
        this->x_step_signal++;
    } else {
        this->x_step_signal--;
    }
    // keep range 0-7
    if (this->x_step_signal > 7) {
        this->x_step_signal = 0;
    }
    if (this->x_step_signal < 0) {
        this->x_step_signal = 7;
    }

    // y
    if (this->y_direction == 0) {
        this->y_step_signal++;
    } else {
        this->y_step_signal--;
    }
    // keep range 0-7
    if (this->y_step_signal > 7) {
        this->y_step_signal = 0;
    }
    if (this->y_step_signal < 0) {
        this->y_step_signal = 7;
    }
}

int MultiStepper::version(void)
{
  return 1;
}
