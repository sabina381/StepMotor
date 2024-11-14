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

class Stepper {
private:
    // movement information
    int step_signal;    // current step signal; range 0-7
    int direction;      // 1: clockwise, 0: counterclockwise
    int n_steps;        // remaining steps

public:
    Stepper(int n_steps, int motor_pin_1, int motor_pin_2, int motor_pin_3, int motor_pin_4);

    void setSpeed(long speed);
    void step(int n_steps);
    int version(void);

    void stepper();               // return signal per position
    void controlSignal();          // control steps by direction and defined range of step_signal
    void pinSignal(int a, int b, int c, int d); // pin step signal 

    // motor pin numbers
    int motor_pin_1;
    int motor_pin_2;
    int motor_pin_3;
    int motor_pin_4;

};

class MultiStepper {
private:             
    // movement information
    int x_step_signal;    // current step signal; range 0-7
    int y_step_signal;
    int x_direction;      // 1: clockwise, 0: counterclockwise
    int y_direction;
    int x_steps;        // remaining steps
    int y_steps;

public:
    MultiStepper(int x_steps, int y_steps, int motor_pin_x1, int motor_pin_x2, int motor_pin_x3, int motor_pin_x4, int motor_pin_y1, int motor_pin_y2, int motor_pin_y3, int motor_pin_y4);

    void setSpeed(long speed);
    void step(int x_steps, int y_steps);
    int version(void);

    void multi_stepper_CW();
    void multi_stepper_CCW();
    void pinSignal(int a1, int b1, int c1, int d1, int a2, int b2, int c2, int d2);
    void controlSignal();

    // motor pin numbers
    int motor_pin_x1;
    int motor_pin_x2;
    int motor_pin_x3;
    int motor_pin_x4;
    int motor_pin_y1;
    int motor_pin_y2;
    int motor_pin_y3;
    int motor_pin_y4;

};

// drawing class  
class TicTacToeArtist {
private:
    // define stepper motors
    Stepper &stepper_x;
    Stepper &stepper_y; 
    Stepper &stepper_z;
    MultiStepper &multistepper;

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

public:

    TicTacToeArtist(int board_width_mm, int board_height_mm, Stepper &stepper_x, Stepper &stepper_y, Stepper &stepper_z, MultiStepper &multistepper);

    // drawing methods
    void drawCircle(int position);
    void drawX(int position);
    void drawGameBoard();

        // control pen
    void step(Stepper &stepper, int n_steps);
    void penUp();                    // lift pen to stop drawing
    void penDown();                  // put down pen to start drawing

    // method for positions
    void resetPosition();            // return to position (0,0)
    void setPosition(int position);
    void move(int x_steps, int y_steps); // move to (x, y)
    void moveDiagonally(int x_steps, int y_steps);
    
};

#endif