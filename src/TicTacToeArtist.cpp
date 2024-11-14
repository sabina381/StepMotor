#include "Arduino.h"
#include "StepMotor.h"

TicTacToeArtist::TicTacToeArtist(int board_width_mm, int board_height_mm, Stepper &stepper_x, Stepper &stepper_y, Stepper &stepper_z, MultiStepper &multistepper)
  :stepper_x(stepper_x), stepper_y(stepper_y), stepper_z(stepper_z), multistepper(multistepper) {
    // get steppers 
    this->stepper_x = stepper_x;
    this->stepper_y = stepper_y; 
    this->stepper_z = stepper_z; 
    this->multistepper = multistepper;

    // define board
    this->board_width = round(board_width_mm * this->step_distance);
    this->board_height = round(board_height_mm * this->step_distance);

    // define cell 
    this->cell_width = round(this->board_width / 3);
    this->cell_height = round(this->board_height / 3);

    // stepper's setting 
    this->steps_per_rotation = 4095; // steps
    this->circumference_distance = 46; // (mm)
    this->step_distance = this->steps_per_rotation / this->circumference_distance; // 단위 : (step / mm)

    // size limit
    this->max_symbol_size = min(this->cell_height, this->cell_width) - 7;

    // init value 
    this->cumulated_x_steps = 0;
    this->cumulated_y_steps = 0;
    this->cumulated_z_steps = 0;
}

// draw O, X, game board
void TicTacToeArtist::drawCircle(int position) {
    float one_side = sqrt(2) / (2 + sqrt(2));
    float one_diag = 1 / (2 + sqrt(2));

    float side_step = this->step_distance * one_side * (this->cell_width - 2);
    float diag_step = this->step_distance * one_diag * (this->cell_width - 2);

    // 위치 잡기
    this->setPosition(position);
    this->move(this->step_distance, this->step_distance);

    // 그리기
    this->move(diag_step, 0);
    this->penDown();
    this->move(side_step, 0);
    this->moveDiagonally(diag_step, diag_step);
    this->move(0, side_step);
    this->moveDiagonally(-diag_step, diag_step);
    this->move(-side_step, 0);
    this->moveDiagonally(-diag_step, -diag_step);
    this->move(0, -side_step);
    this->moveDiagonally(diag_step, -diag_step);
    this->penUp();

    // 원위치로
    this->resetPosition();
}

void TicTacToeArtist::drawX(int position) { 
    float x_step = this->step_distance * (this->cell_width - 2);
    float y_step = this->step_distance * (this->cell_height - 2);

    // 위치 잡기
    this->setPosition(position);
    this->move(this->step_distance, this->step_distance);

    // 그리기
    this->penDown();
    this->moveDiagonally(x_step, y_step);
    this->penUp();
    this->move(-x_step, 0);
    this->penDown();
    this->moveDiagonally(x_step, -y_step);
    this->penUp();

    // 원위치로
    this->resetPosition();
}

void TicTacToeArtist::drawGameBoard() {
    this->move(this->cell_width, 0);
    this->penDown();
    this->move(0, this->board_height);
    this->penUp();
    this->move(this->cell_width, 0);
    this->penDown();
    this->move(0, -this->board_height);
    this->penUp();
    this->move(this->cell_width, this->cell_height);
    this->penDown();
    this->move(-this->board_width,0);
    this->penUp();
    this->move(0, this->cell_height);
    this->penDown();
    this->move(this->board_width, 0);
    this->penUp();

    // 원위치로
    this->resetPosition();
}

// methods handling positions 
void TicTacToeArtist::move(int x_steps, int y_steps) {
  
    this->stepper_x.step(x_steps);
    delay(2000);
    this->stepper_y.step(y_steps);
    delay(2000);

    // 이거 여기에 넣어도 되겟지?
    this->cumulated_x_steps += x_steps;
    this->cumulated_y_steps += y_steps;
}

void TicTacToeArtist::moveDiagonally(int x_steps, int y_steps) {
    this->multistepper.step(x_steps, y_steps);

    this->cumulated_x_steps += x_steps;
    this->cumulated_y_steps += y_steps;
}

void TicTacToeArtist::step(Stepper &stepper, int n_steps) {
    stepper.step(n_steps);
}

void TicTacToeArtist::resetPosition() {
    // return to init position
    this->move(-this->cumulated_x_steps, -this->cumulated_y_steps);

    // reset the params
    this->cumulated_x_steps = 0;
    this->cumulated_y_steps = 0;
}

void TicTacToeArtist::setPosition(int position) {
    switch (position){
        case 0:
            break;

        case 1:
            this->move(this->cell_width, 0);
            break;

        case 2:
            this->move(this->cell_width * 2, 0);
            break;

        case 3:
            this->move(0, this->cell_height);
            break;

        case 4:
            this->move(this->cell_width, this->cell_height);
            break;

        case 5:
            this->move(this->cell_width * 2, this->cell_height);
            break;

        case 6:
            this->move(0, this->cell_height * 2);
            break;

        case 7:
            this->move(this->cell_width, this->cell_height * 2);
            break;

        case 8:
            this->move(this->cell_width * 2, this->cell_height * 2);
            break;

        default:
            break;
    }
}

// handling pen
// 방향과 정도 수정 

void TicTacToeArtist::penUp() {
    this->stepper_z.step(this->step_distance*5);
}

void TicTacToeArtist::penDown() {
    this->stepper_z.step(-this->step_distance*5);
}

