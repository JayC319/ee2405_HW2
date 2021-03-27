c#include "mbed.h"
#include "wave.h"
#include "uLCD_4DGL.h"
#include<iostream>
using namespace std::chrono;
using namespace std;

AnalogIn Ain(A0);
uLCD_4DGL uLCD(D1, D0, D2); // serial tx, serial rx, reset pin;
BusIn Buttons(D12, D11, D10);
int frequency[9] = {10,20,30,40,50,100,200,400,800};
float ADCdata[500];
float period;

EventQueue eventQueue;
EventQueue printfQueue;

Thread thread;

void sampling() {
    while(1) {

        for (int i = 0; i < 500; i++){
            ADCdata[i] = Ain;
           ThisThread::sleep_for(2ms);
        }
        for (int i = 0; i < 500; i++){
            cout << ADCdata[i] << "\r\n";
            //printf("%f\r\n", ADCdata[i]);
        }
        ThisThread::sleep_for(5000ms);
    }
}


int main()

{

    // basic printf demo = 16 by 18 characters on screen
    uLCD.color(GREEN);
    float period;
    uLCD.printf("\nHello uLCD World\n"); //Default Green on black text

    uLCD.printf("\n  Starting Demo...");

    ThisThread::sleep_for(500ms);

    uLCD.cls();

    uLCD.text_width(2); //4X size text

    uLCD.text_height(4);

    uLCD.color(GREEN);

    uLCD.locate(1,2);

    uLCD.printf(" 720hz\n------");

int barLevel  = 5;
bool whileBreaker = false;

while (1){
    
        switch(Buttons){
        case 0x4:
            if(barLevel >= 8)
            {
                uLCD.cls();
                uLCD.text_width(2); //4X size text

                uLCD.text_height(4);

                uLCD.color(WHITE);

                uLCD.locate(1,2);
                uLCD.printf(" N\\A");
                 ThisThread::sleep_for(50ms);
                char bar[9] = "";
                 for(int count = 0; count <= barLevel; count++)
                    {
                     bar[count] = '-';
                    }
                uLCD.cls();
                uLCD.text_width(2); //4X size text

                uLCD.text_height(4);

                uLCD.color(BLUE);

                uLCD.locate(1,2);
                uLCD.printf(" %dhz\n%s",frequency[barLevel],bar);

                
            }
                    
            else{
                uLCD.cls();
                barLevel++;
                uLCD.text_width(2); //4X size text

                uLCD.text_height(4);

                if(barLevel >= 6)
                    uLCD.color(BLUE);
                else if(barLevel <= 2)
                    uLCD.color(RED);
                else
                    uLCD.color(GREEN);

                uLCD.locate(1,2);

                char bar[9] = "";
                for(int count = 0; count <= barLevel; count++)
                {
                    bar[count] = '-';
                }
                uLCD.printf(" %dhz\n%s",frequency[barLevel],bar);

                    ThisThread::sleep_for(200ms);
            }        
            break;

        case 0x2:
            uLCD.cls();
            uLCD.locate(1,1);
            uLCD.printf("You select %dhz",frequency[barLevel]);
            whileBreaker = true;
            break;

        case 0x1:
            if(barLevel <= 0)
            {
                uLCD.cls();
                uLCD.text_width(2); //4X size text

                uLCD.text_height(4);

                uLCD.color(WHITE);

                uLCD.locate(1,2);
                uLCD.printf(" N\\A");
                ThisThread::sleep_for(50ms);

                char bar[9] = "";
                for(int count = 0; count <= barLevel; count++)
                {
                    bar[count] = '-';
                }

                uLCD.cls();
                uLCD.text_width(2); //4X size text

                uLCD.text_height(4);

                uLCD.color(RED);

                uLCD.locate(1,2);
                uLCD.printf(" %dhz\n%s",frequency[barLevel],bar);
            }
            
            else{
                uLCD.cls();
                barLevel--;
                uLCD.text_width(2); //4X size text

                uLCD.text_height(4);

                    if(barLevel<=2)
                        uLCD.color(RED);
                    else if(barLevel >=6)
                        uLCD.color(BLUE);
                    else
                        uLCD.color(GREEN);

                uLCD.locate(1,2);
                
                char bar[9] = "";
                for(int count = 0; count <= barLevel; count++)
                {
                    bar[count] = '-';
                }
                uLCD.printf(" %dhz\n%s",frequency[barLevel],bar);
                ThisThread::sleep_for(200ms);
            }          
            break;
    }

            if (whileBreaker == true){ 
                break;
            }
    
    }
    
    
    
    eventQueue.call(&sampling);
    Thread eventThread(osPriorityNormal);
    eventThread.start(callback(&eventQueue, &EventQueue::dispatch_forever));
    wave(frequency[barLevel]);
    
   
}