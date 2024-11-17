#include <StepMotor.h>

int main() {
    Stepper stepper_x(8, 9, 10, 11);
    Stepper stepper_y(3, 4, 5, 6);
    Stepper stepper_z(A5, A4, A3, A2);

    TicTacToeArtist artist(110, 110, &stepper_x, &stepper_y, &stepper_z);
}

