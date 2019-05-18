// some change
#include "mbed.h"
#define Fs 10000
#define T 5
#define N 2
#define L (Fs*T*N)


float sound[Fs*T*N];
int ptr;
Ticker flipper;

// Initialize a pins to perform analog input and digital output functions
AnalogIn   mic1(A5);
AnalogIn   mic2(A4);
AnalogIn   lumin(A1);
DigitalOut dout(LED1);
DigitalOut dout_2(LED2);

// float storage[SAMPLE_RATE * TIME_LENGTH * NUM_SOUND];

void log_sound()
{
    sound[ptr++] = mic1.read();
    sound[ptr++] = mic2.read();
    // ....
}

int main(void)
{       
    ptr = 0;
    flipper.attach(&log_sound, 1/Fs);

    wait(10.0f);

    int i = 0;
    printf("ptr=%d\n", ptr);
    wait(1);
    for (i=0; i<20; i++)
    {
        printf("sound[%d]=%.3f\n", (i+ptr)%L, sound[(i+ptr)%L]);
        wait(.1f);
    } 

    // while (1) {
        
    //     flipper.attach(&log_sound, 1/Fs);
    //     // test the voltage on the initialized analog pin
    //     //  and if greater than 0.3 * VCC set the digital pin
    //     //  to a logic 1 otherwise a logic 0
    //     if(mic1 > 0.02f) {
    //         dout = 1;
    //     } else {
    //         dout = 0;
    //     }
    //     if(mic2 > 0.02f) {
    //         dout_2 = 1;
    //     } else {
    //         dout_2 = 0;
    //     }
        
    //     // print the percentage and 16 bit normalized values
    //     printf("loudness_5: %3.3f%%\n", mic1.read()*100.0f);
    //     printf("    ");
    //     printf("loudness_4: %3.3f%%\n", mic2.read()*100.0f);
    //     printf("    ");
    //     // printf("light: %3.3f%%\r\n", lumin.read()*100.0f);
    //     wait(0.2f);
    // }
}
