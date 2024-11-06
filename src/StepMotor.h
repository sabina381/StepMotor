// This StepMotor Library is for 28BYJ-48(5V) Step Motor.
// UniPolar 5 wire, half-step sequence
// Switching Seq 
// Step IN1 IN2 IN3 IN4
//   1   0   0   0   1
//   2   0   0   1   1
//   3   0   0   1   0
//   4   0   1   1   0
//   5   0   1   0   0
//   6   1   1   0   0
//   7   1   0   0   0
//   8   1   0   0   1

#ifndef StepMotor_h
#define StepMotor_h

class StepMotor {
    public:
    StepMotor(int n_steps, int motor_pin_1, int motor_pin_2, int motor_pin_3, int motor_pin_4);

    void setSpeed(long Speed);

    void step(int n_steps);

    int version(void);

    private:
    // 
    void stepper();
    void controlSignal();
    void pinSignal(int a, int b, int c, int d);

    // etc information
    int step_signal;
    int direction;
    int n_steps;

    // motor pin numbers
    int motor_pin_1;
    int motor_pin_2;
    int motor_pin_3;
    int motor_pin_4;

};

#endif