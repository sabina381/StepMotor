#include "Arduino.h"
#include <cmath>
#include <iostream>
#include <thread>
#include "StepMotor.h"

TicTacToeArtist::TicTacToeArtist(int board_width_mm=110, int board_height_mm=110, Stepper &stepper_x, Stepper &stepper_y, Stepper &stepper_z) {
    // get steppers 
    this->stepper_x = stepper_x;
    this->stepper_y = stepper_y; 
    this->stepper_z = stepper_z; 

    // define board
    this->board_width = std::round(board_width_mm * this->step_distance);
    this->board_height = std::round(board_height_mm * this->step_distance);

    // define cell 
    this->cell_width = std::round(this->board_width / 3);
    this->cell_height = std::round(board_height / 3);

    // stepper's setting 
    this->steps_per_rotation = 4095; // steps
    this->circumference_distance = 46; // (mm)
    this->step_distance = this->steps_per_rotation / this->circumference_distance ; // 단위 : (step / mm)

    // size limit
    this->max_symbol_size = std::min(this->cell_height, this->cell_width) - 7;

    // init value 
    this->cumulated_x_steps = 0;
    this->cumulated_y_steps = 0;
    this->cumulated_z_steps = 0;
}

// draw O, X, game board
TicTacToeArtist::drawCircle() {
    
}
TicTacToeArtist::drawX() { 

}
TicTacToeArtist::drawGameBoard() {

}

// methods handling positions 
TicTacToeArtist::move(int x_steps, int y_steps) {
    this->stepper_x.step(x_steps);
    delay(2000);
    this->stepper_y.step(y_steps);
    delay(2000);
}

TicTacToeArtist::moveDiagonally(int x_steps, int y_steps) {
// by using threads, processing 병렬
std::thread thread_x(TicTacToeArtist::step, std::ref(this->stepper_x), x_steps);
std::thread thread_y(TicTacToeArtist::step, std::ref(this->stepper_y), y_steps);

// 두 스레드가 모두 완료될 때까지 대기합니다.
thread_x.join();
thread_y.join();
}

TicTacToeArtist::step(Stepper &stepper, int n_steps) {
    stepper.step(n_steps);
    // 누적 증가 
}

TicTacToeArtist::resetPosition() {
    // return to init position
    this->stepper_x(this->cumulated_x_steps);
    this->stepper_y(this->cumulated_y_steps);

    // reset the params
    this->cumulated_x_steps = 0;
    this->cumulated_y_steps = 0;
}

TicTacToeArtist::setPosition(int position) {
switch (position)
{
case 0:
    break;

case 1:
    this->
    break;

case 2:
    break;

case 3:
    break;

case 4:
    break;

case 5:
    break;

case 6:
    break;

case 7:
    break;

case 8:
    break;

default:
    break;
}
}

// handling pen
// 방향과 정도 수정 

TicTacToeArtist::penUp(); {
this->stepper_z.step(this->steps_per_rotation/8) 
}

TicTacToeArtist::penDown() {
this->stepper_z.step(-this->steps_per_rotation/8) 
}

