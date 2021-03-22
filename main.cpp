#include "mbed.h"

#include "uLCD_4DGL.h"


uLCD_4DGL uLCD(D1, D0, D2); // serial tx, serial rx, reset pin;
BusIn Buttons(D13, D12, D11);
int frequency[9] = {120,240,360,480,600,720,840,960,1080};
int main()

{

    // basic printf demo = 16 by 18 characters on screen
    uLCD.color(GREEN);

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

    if (whileBreaker == true)
    {
        uLCD.cls();
        break;
    }
        

}


     

}