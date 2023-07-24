#include "mbed.h"

DigitalOut redLed(D6);
DigitalOut blueLed(D8);

InterruptIn myButton(USER_BUTTON);

double tempo = 0.5;

void changeTempo(){
    if(tempo == 0.5){
        tempo = 0.25;
    }else{
        tempo = 0.5;
    }   
}

// main() runs in its own thread in the OS
int main()
{
    redLed = 0;
    blueLed = 0;

    myButton.fall(&changeTempo);

    while (true) {
        redLed = 1;
        wait(tempo);
        redLed = 0;
        blueLed = 1;
        wait(tempo);
        blueLed = 0;
    }
}

