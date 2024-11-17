#include "Arduino.h"
#include "StepMotor.h"

TicTacToeArtist::TicTacToeArtist(int board_width_mm, int board_height_mm, Stepper* stepper_x, Stepper* stepper_y, Stepper* stepper_z)
  :stepper_x(stepper_x), stepper_y(stepper_y), stepper_z(stepper_z), multi_stepper(stepper_x, stepper_y) {

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
}

// draw O, X, game board
void TicTacToeArtist::drawCircle(int position) {
    float one_side = sqrt(2) / (2 + sqrt(2));
    float one_diag = 1 / (2 + sqrt(2));

    int side_step = round(this->step_distance * one_side * (this->cell_width - 2)); // 원래 FLOAT인데 수정,,, 아니면 MOVE를 바꿔야 함 
    int diag_step = round(this->step_distance * one_diag * (this->cell_width - 2));

    // 위치 잡기
    this->setPosition(position);
    this->move(this->step_distance, this->step_distance, 1, 1);

    // 그리기
    this->move(diag_step, 0, 1, 1);
    this->penDown();
    this->move(side_step, 0, 1, 1);
    this->moveDiagonally(diag_step, 1, 1);
    this->move(0, side_step, 1, 1);
    this->moveDiagonally(diag_step, -1, 1);
    this->move(side_step, 0, -1, 1);
    this->moveDiagonally(diag_step, -1, -1);
    this->move(0, side_step, 1, -1);
    this->moveDiagonally(diag_step, 1, -1);
    this->penUp();

    // 원위치로
    this->resetPosition();
}

void TicTacToeArtist::drawX(int position) { 
    float n_step = this->step_distance * (this->cell_width - 2);

    // 위치 잡기
    this->setPosition(position);
    // this->move(this->step_distance, this->step_distance); // (int x_steps, int y_steps, int x_direction, int y_direction
    // setPosition func에 위치 이동이 포함되어 있음 

    // 그리기
    this->penDown();
    this->moveDiagonally(n_step, 1, 1);
    this->penUp();
    this->move(n_step, 0 ,-1, 1);
    this->penDown();
    this->moveDiagonally(n_step, 1, -1);
    this->penUp();

    // 원위치로
    this->resetPosition();
}

void TicTacToeArtist::drawGameBoard() {
    this->move(this->cell_width, 0, 1, 1);
    this->penDown();
    this->move(0, this->board_height, 1, 1);
    this->penUp();
    this->move(this->cell_width, 0, 1, 1);
    this->penDown();
    this->move(0, this->board_height, 1, -1);
    this->penUp();
    this->move(this->cell_width, this->cell_height, 1, 1);
    this->penDown();
    this->move(this->board_width,0, -1, 1);
    this->penUp();
    this->move(0, this->cell_height, 1, 1);
    this->penDown();
    this->move(this->board_width, 0, 1, 1);
    this->penUp();

    // 원위치로
    this->resetPosition();
}

// methods handling positions 
void TicTacToeArtist::move(int x_steps, int y_steps, int x_direction, int y_direction) {
    stepper_x->step(x_steps, x_direction);
    delay(2000);
    stepper_y->step(y_steps, y_direction);
    delay(2000);

    x_steps = abs(x_steps); // 혹시 음수로 값을 주면 양수로 변경, 차후에 오류가 아예 발생하도록 수정 
    y_steps = abs(y_steps);

    // update cumulated_steps 
    stepper_x->cumulated_steps += x_steps * x_direction;
    stepper_y->cumulated_steps += y_steps * y_direction;
}

void TicTacToeArtist::moveDiagonally(int n_steps, int x_direction, int y_direction) {
    multi_stepper.step(n_steps, x_direction, y_direction);
    delay(2000);
    
    n_steps = abs(n_steps);
    
    stepper_x->cumulated_steps += n_steps * x_direction;
    stepper_y->cumulated_steps += n_steps * y_direction;
}

void TicTacToeArtist::resetPosition() {
    // return to init position

    // find direction 
    int x_direction = (stepper_x->cumulated_steps >= 0) ? 1 : -1;
    int y_direction = (stepper_y->cumulated_steps >= 0) ? 1 : -1;
    
    this->move(stepper_x->cumulated_steps, stepper_x->cumulated_steps, x_direction, y_direction);

    // reset the params
    stepper_x->cumulated_steps = 0;
    stepper_y->cumulated_steps = 0;
}

void TicTacToeArtist::setPosition(int position) {
    switch (position){
        case 0:
            break;

        case 1:
            this->move(this->cell_width, 0, 1, 1);
            break;

        case 2:
            this->move(this->cell_width * 2, 0, 1, 1);
            break;

        case 3:
            this->move(0, this->cell_height, 1, 1);
            break;

        case 4:
            this->move(this->cell_width, this->cell_height, 1, 1);
            break;

        case 5:
            this->move(this->cell_width * 2, this->cell_height, 1, 1);
            break;

        case 6:
            this->move(0, this->cell_height * 2, 1, 1);
            break;

        case 7:
            this->move(this->cell_width, this->cell_height * 2, 1, 1);
            break;

        case 8:
            this->move(this->cell_width * 2, this->cell_height * 2, 1, 1);
            break;

        default:
            break;
    }
}

// handling pen
// 방향과 정도 수정 

void TicTacToeArtist::penUp() {
    stepper_z->step(this->step_distance*5, 1);
}

void TicTacToeArtist::penDown() {
    stepper_z->step(this->step_distance*5, -1);
}

