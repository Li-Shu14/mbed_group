// some change
#include "mbed.h"
#define Fs 10000
#define T 5
#define N 2
#define L (Fs*T*N)



#include "USBSerial.h"

//Virtual serial port over USB
USBSerial serial;



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

    flipper.detach();

    printf("ptr=%d\n", ptr);
    wait(1);

    int already_sent = 0;
    send_nb(sound+ptr, sizeof(float)*(L - ptr), &already_sent);
    while(already_sent < L - ptr)
        ;
    
    already_sent = 0;
    send_nb(sound, sizeof(float)*ptr, &already_sent);
    while(already_sent < ptr)
        ;

}
