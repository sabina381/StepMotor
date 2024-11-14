#include "StepMotor.h"

Stepper stepperX(0, 8, 9, 10, 11);
Stepper stepperY(0, 3, 4, 5, 6);
Stepper stepperZ(0, A5, A4, A3, A2);

MultiStepper multistepper(0, 0, 8, 9, 10, 11, 3, 4, 5, 6);

TicTacToeArtist artist(110, 110, stepperX, stepperY, stepperZ, multistepper);

void setup(){
    Serial.begin(115200);
    Serial.println("Setup complete");
};

void loop() {
    // Serial.println("Drawing game board...");
    // artist.drawGameBoard();   // 게임 보드 그리기
    // delay(5000);              // 잠시 대기

    // Serial.println("Drawing X...");
    // artist.drawX(0);           // 'X' 그리기
    // delay(2000);              // 잠시 대기
    
    // Serial.println("Drawing Circle...");
    // artist.drawCircle(4);      // 'O' 그리기
    // delay(2000);              // 잠시 대기

    Serial.println("start");
    artist.move(-2000, -2000);
    artist.moveDiagonally(1000, 1000);
    Serial.println("end");
    delay(2000);


};