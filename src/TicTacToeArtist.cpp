#include "Arduino.h"
#include "StepMotor.h"

TicTacToeArtist::TicTacToeArtist(int board_width_grid, int board_height_grid, Stepper* stepper_x, Stepper* stepper_y, Stepper* stepper_z)
  :stepper_x(stepper_x), stepper_y(stepper_y), stepper_z(stepper_z), multi_stepper(stepper_x, stepper_y), board_width_grid(board_width_grid), board_height_grid(board_height_grid)  {

    // define cell 
    this->cell_width_grid = round(this->board_width_grid / 3);  // 사실 7
    this->cell_height_grid = round(this->board_height_grid / 3);  // 사실 7

    // size limit
    this->x_grid_line = min(this->cell_height_grid, this->cell_width_grid) - 2; // 사실 5다. 
    this->circle_grid_line = round(min(this->cell_height_grid, this->cell_width_grid) / 3); // 사실 2다. 
}

// draw O, X, game board
void TicTacToeArtist::drawCircle(int position) {
    // 모눈력 -> step으로 환산 
    int side_step = this->circle_grid_line * this->steps_per_grid; 
    int diag_step = round(this->circle_grid_line / sqrt(2)) * this->steps_per_grid; // 반올림되는거 주의 

    // 초기 위치 잡기
    int init_x_step = round(this->steps_per_grid * 2.5);
    this->setPosition(position);
    this->move(init_x_step, 1, 1, 1);

    // 그리기
    this->penDown();
    this->moveDiagonally(diag_step, -1, 1);
    this->moveY(side_step, 1);
    this->moveDiagonally(diag_step, 1, 1);
    this->moveX(side_step, 1);
    this->moveDiagonally(diag_step, 1, -1);
    this->moveY(side_step, -1);
    this->moveDiagonally(diag_step, -1, -1);
    this->moveX(side_step, -1);
    this->penUp();

    // 원위치로
    this->resetPosition();
}

void TicTacToeArtist::drawX(int position) { 
    // X의 크기를 모눈력에서 스텝으로 환산 : 5 모눈력 
    int n_step = this->steps_per_grid * this->x_grid_line; 

    // 위치 잡기
    this->setPosition(position);
    this->move(1, 1, 1, 1); // 시작 지점으로 이동 

    // 그리기
    this->penDown();
    this->moveDiagonally(n_step, 1, 1);
    this->penUp();
    this->moveX(n_step, -1);
    this->penDown();
    this->moveDiagonally(n_step, 1, -1);
    this->penUp();

    // 원위치로
    this->resetPosition();
}

void TicTacToeArtist::drawGameBoard() {

    this->moveY(this->cell_height_grid, 1);
    this->penDown();
    this->moveX(this->board_width_grid, 1);
    this->penUp();

    this->moveY(this->cell_height_grid, 1);
    this->penDown();
    this->moveX(this->board_width_grid, -1);
    this->penUp();

    this->move(this->cell_width_grid, this->cell_height_grid, 1, 1);
    this->penDown();
    this->moveY(this->board_height_grid, -1);
    this->penUp();

    this->moveX(this->cell_width_grid, 1);
    this->penDown();
    this->moveX(this->board_height_grid, 1);;
    this->penUp();

    // 원위치로
    this->resetPosition();
}

// methods handling positions 
void TicTacToeArtist::move(int x_grids, int y_grids, int x_direction, int y_direction) {
    x_grids = abs(x_grids); // 혹시 음수로 값을 주면 양수로 변경, 차후에 오류가 아예 발생하도록 수정 
    y_grids = abs(y_grids);

    // 모눈력 -> 스텝으로 변환 
    int x_steps = x_grids * this->steps_per_grid;
    int y_steps = y_grids * this->steps_per_grid;

    stepper_x->step(x_steps, x_direction);
    delay(500);
    stepper_y->step(y_steps, y_direction);
    delay(500);
}

void TicTacToeArtist::moveDiagonally(int n_grids, int x_direction, int y_direction) {
    n_grids = abs(n_grids);

    // 모눈력 -> 스텝 수로 변환 
    int n_steps = n_grids * this->steps_per_grid;

    multi_stepper.step(n_steps, x_direction, y_direction);
    delay(500);
}

void TicTacToeArtist::moveX(int n_grids, int direction) {
    int n_grids = abs(n_grids); 

    // 모눈력 -> 스텝으로 변환 
    int n_steps = n_grids * this->steps_per_grid;

    stepper_x->step(n_steps, direction);
    delay(500);
}

void TicTacToeArtist::moveY(int n_grids, int direction) {
    int n_grids = abs(n_grids); 

    // 모눈력 -> 스텝으로 변환 
    int n_steps = n_grids * this->steps_per_grid;

    stepper_y->step(n_steps, direction);
    delay(500);
}

void TicTacToeArtist::resetPosition() {
    // return to init position
    stepper_x->reset();
    stepper_y->reset();
}

void TicTacToeArtist::setPosition(int position) {
    // starting at init position.
    switch (position){
        case 0:
            break;

        case 1:
            this->moveX(this->cell_width_grid, 1);
            break;

        case 2:
            this->moveX(this->cell_width_grid*2, 1);
            break;

        case 3:
            this->moveY(this->cell_height_grid, 1);
            break;

        case 4:
            this->move(this->cell_width_grid, this->cell_height_grid, 1, 1);
            break;

        case 5:
            this->move(this->cell_width_grid * 2, this->cell_height_grid, 1, 1);
            break;

        case 6:
            this->moveY(this->cell_height_grid * 2, 1);
            break;

        case 7:
            this->move(this->cell_width_grid, this->cell_height_grid * 2, 1, 1);
            break;

        case 8:
            this->move(this->cell_width_grid * 2, this->cell_height_grid * 2, 1, 1);
            break;

        default:
            break;
    }
}

// handling pen
// 방향과 정도 수정 

void TicTacToeArtist::penUp() {
    stepper_z->step(this->step_distance*5, -1);
}

void TicTacToeArtist::penDown() {
    stepper_z->step(this->step_distance*5, 1);
}
