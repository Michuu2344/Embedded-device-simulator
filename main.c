#include <stdio.h>
#include <stdbool.h>
#include "device.h"

int show_menu(void){
    int choice;
    printf("========================\n");
    printf("EMBEDDED DEVICE\n");
    printf("========================\n");
    printf("1. Device status\n");
    printf("2. Set temperature\n");
    printf("3. Toggle LED\n");
    printf("4. Show errors\n");
    printf("5. Exit\n");
    printf("Select: \n");


    if(scanf("%d",&choice) != 1){
        printf("You have to type a number  ");

        int c;
        while((c = getchar()) != '\n' && c != EOF);
        return -1;
        
    }
   return choice;

    // trzeba wymyslic co robic gdy choice nie jest liczba
}

int main(){
    
    Device device;
    int running = true;
    float temperature;
    device_init(&device);
    int user_choice = 0;
    while(running){
        user_choice = show_menu();
        switch (user_choice)
    {
    case 1:
        show_status(&device);
        break;
    
    case 2:
        printf("Set the temperature: ");
        scanf("%f",&temperature);
        set_temperature(&device,temperature);
        break;
    case 3:
        toggle_led(&device);
        break;
    case 4:
    printf("");
        break;
    case 5:
        printf("Device is turning off\n");
        running = false;
        break;
    default:
        printf("Invalid number try again\n");
        break;
    }
    }
    return 0;

   
}

// make the params random
    // bit manipulation
    // uart

     //debugging
    //big picture     