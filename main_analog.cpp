// some change
#include "mbed.h"
#define Fs 100
#define T 5
#define N 6
#define L (Fs*T*N)

unsigned short sound[L];
int ptr;
Ticker flipper;

// Initialize a pins to perform analog input and digital output functions
AnalogIn   mic1(A0);
AnalogIn   mic2(A1);
AnalogIn   mic3(A2);
AnalogIn   mic4(A3);
AnalogIn   mic5(A4);
AnalogIn   mic6(A5);
DigitalOut led1(LED1);

// float storage[SAMPLE_RATE * TIME_LENGTH * NUM_SOUND];
void log_sound()
{
    sound[ptr++] = mic1.read_u16();
    sound[ptr++] = mic2.read_u16();
    sound[ptr++] = mic3.read_u16();
    sound[ptr++] = mic4.read_u16();
    sound[ptr++] = mic5.read_u16();
    sound[ptr++] = mic6.read_u16();
}

#define XXX 5
void send_message()
{
    flipper.detach();
    for (int k=0; k<XXX; k++)
    {
        for (int i=0; i<L; i++)
        {
            if (sound[i] == 0xFFFF)
            {
                sound[i] = 0xFFFE;
            }
            printf("%d ", sound[i]);
        }
        printf("%d %d", ptr, 0xFFFF);
    }
    flipper.attach(&log_sound, 1/Fs);
}

int main(void)
{       
    ptr = 0;
    flipper.attach(&log_sound, 1/Fs);

    while(1)
    {
        led1 = !led1;
        wait(.5);
    }
}
