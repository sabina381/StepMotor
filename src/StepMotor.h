// This StepMotor Library is for 28BYJ-48(5V) Step Motor.
// UniPolar 5 wire, half-step sequence

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

// [ Coding Rule ]
// methods naming : Camel Casing
// attribute naming : Snake Casing

#ifndef StepMotor_h
#define StepMotor_h

#include <utility>  // for std::pair

class Stepper {
public:
    Stepper(int n_steps, int motor_pin_1, int motor_pin_2, int motor_pin_3, int motor_pin_4);

    void setSpeed(long speed);
    void step(int n_steps);
    int version(void);

private:
    void stepper();               // return signal per position
    void controlSignal();          // control steps by direction and defined range of step_signal
    void pinSignal(int a, int b, int c, int d); // pin step signal 

    // movement information
    int step_signal;    // current step signal; range 0-7
    int direction;      // 1: clockwise, 0: counterclockwise
    int n_steps;        // remaining steps

    // motor pin numbers
    int motor_pin_1;
    int motor_pin_2;
    int motor_pin_3;
    int motor_pin_4;
};

// drawing class  
class TicTacToeArtist {
public:
    TicTacToeArtist(int board_width_mm, int board_height_mm, Stepper &stepper_x, Stepper &stepper_y, Stepper &stepper_z);

    // drawing methods
    void drawCircle();
    void drawX();
    void drawGameBoard();

    // method for positions
    void resetPosition();            // return to position (0,0)
    void setPosition(int position);
    void move(int x_steps, int y_steps); // move to (x, y)
    void moveDiagonally(int x_steps, int y_steps);
    std::pair<int, int> moveTogether(int x_steps, int y_steps);

private:
    // define stepper motors
    StepMotor &stepper_x;
    StepMotor &stepper_y; 
    StepMotor &stepper_z;

    // control pen
    void penUp();                    // lift pen to stop drawing
    void penDown();                  // put down pen to start drawing

    // define board size 
    int board_width;
    int board_height;

    int cell_width;
    int cell_height;

    int max_symbol_size;
    int cumulated_x_steps;
    int cumulated_y_steps;
    int cumulated_z_steps;

    // stepper settings
    float step_distance;            // distance per step (float type if more precision is needed)
    int steps_per_rotation;         // steps for one full rotation
    int circumference_distance;     // distance covered in one full rotation
};

#endif