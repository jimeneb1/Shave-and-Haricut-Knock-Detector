#include "mbed.h"
#include "time.h" 



AnalogIn   input1(PA_3);

DigitalOut myled(LED4);
DigitalOut error1(LED1);


int main(){

    //This initializes my arrays. When in get recursively called it gets cleared
    int inTime[5] = {NULL, NULL, NULL, NULL, NULL}; //use int because .read_ms stores time as int
    int delta[4] = {NULL, NULL, NULL, NULL};
    int iTag[4] = {NULL, NULL, NULL, NULL};
    
    int currentTime;

    int flag = 0;
    
    int secret[4] = {500, 1000, 1000, 500};
    
    //When ON it indicates that the user can begin to knock
    myled = 1;
    
    Timer timer;
    timer.start();

    
    while(flag == 0){ //originally had true && flag == 0 as conditional
        
        //Threshold Value
        unsigned int hexval = 0x0222U;
        
        if (input1.read_u16() > hexval){ //could prob just write the code directly
            currentTime = timer.read_ms(); //records the time at each knock
            
            if(inTime[0] == NULL)
                inTime[0] = currentTime;
            else if(inTime[1] == NULL)
                inTime[1] = currentTime;
            else if(inTime[2] == NULL)
                inTime[2] = currentTime;
            else if(inTime[3] == NULL)
                inTime[3] = currentTime;
            else if(inTime[4] == NULL)
                inTime[4] = currentTime;
            
            HAL_Delay(100); 
        }
        
        if (inTime[0] != NULL && inTime[1] != NULL && inTime[2] != NULL && inTime[3] != NULL && inTime[4] != NULL){
            flag = 1; //Breaks out of the while loop once the array has been filled
            }
    }
    
    //This calculates the time between each knocks
     delta[0] = inTime[1] - inTime[0];
     delta[1] = inTime[2] - inTime[1];
     delta[2] = inTime[3] - inTime[2];
     delta[3] = inTime[4] - inTime[3];
     
     
    //Checks if the the knock spacing is within the allowed range 
    if ( ((secret[0] * .9) > delta[0]) && (delta[0] < (secret[0] * 1.1)) ){ 
        iTag[0] = 1;
        }
    else{ 
          myled = 0;                //Error Handling Code
          for(int i; i<10; i++){    //This will make LEDs 1 blink on and off
              error1 = 1;           //indicating password is wrong
                                    //After few seconds the code will reset
              HAL_Delay(500);
              error1 = 0;
              HAL_Delay(500);
              }
          HAL_Delay(500);
          main();
        }
    
    if ( ((secret[1] * .9) > delta[1]) && (delta[1] < (secret[1] * 1.1)) ){
        iTag[1] = 1;
        }
    else{ 
          myled = 0;                //Error Handling Code
          for(int i; i<10; i++){    //This will make LEDs 1 blink on and off
              error1 = 1;           //indicating password is wrong
                                    //After few seconds the code will reset
              HAL_Delay(500);
              error1 = 0;
              HAL_Delay(500);
              }
          HAL_Delay(500);
          main();
        }
     
    if ( ((secret[2] * .9) > delta[2]) && (delta[2] < (secret[2] * 1.1)) ){
        iTag[2] = 1;
        }
    else{ 
          myled = 0;                //Error Handling Code
          for(int i; i<10; i++){    //This will make LEDs 1 blink on and off
              error1 = 1;           //indicating password is wrong
                                    //After few seconds the code will reset
              HAL_Delay(500);
              error1 = 0;
              HAL_Delay(500);
              }
          HAL_Delay(500);
          main();
        
        }
     
    if ( ((secret[3] * .9) > delta[3]) && (delta[3] < (secret[3] * 1.1)) ){
        iTag[3] = 1;
        }
    else{ 
          myled = 0;                //Error Handling Code
          for(int i; i<10; i++){    //This will make LEDs 1 blink on and off
              error1 = 1;           //indicating password is wrong
                                    //After few seconds the code will reset
              HAL_Delay(500);
              error1 = 0;
              HAL_Delay(500);
              }
          HAL_Delay(500);
          main();
        }

    if(iTag[0] == 1 && iTag[1] == 1 && iTag[2] == 1 && iTag[3] ==1){

        DigitalOut(PD_0,1);
        myled = 0;
        HAL_Delay(3000);       //Resets after a 3 second delay
        DigitalOut(PD_0,0);


        main(); //recursively calls the function so it runs a forever loop
        }
    

    return 0;
}

