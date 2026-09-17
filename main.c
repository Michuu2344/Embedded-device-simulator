#include <stdio.h>
#include <stdbool.h>
#include "device.h"
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
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
}
void *device_thread(void *arg){
    Device *device = (Device *)arg;

    while(1){
        sleep(1);
        device_tick(device);
    }
    return NULL;
}
int main(){
    srand(time(NULL));
    Device device;
    
    int running = true;
    float temperature;
    device_init(&device);
    if(generate_random_params(&device)){
        printf("Parameters generated succesfully!\n");
    }
    else{
        printf("Failed to generate parameters\n");
    }
    pthread_t thread;

    if(pthread_create(&thread,NULL,device_thread,&device) != 0 ){
        printf("Failed to create device thread\n");
        return 1;
    }
    int user_choice = 0;
    while(running){
        user_choice = show_menu();
        switch (user_choice)
    {
    case 1:
        update_status(&device);
        show_status(&device);

        break;
    
    case 2:
        printf("Set the temperature: ");
        if(scanf("%f",&temperature) != 1){
            printf("You have to type a float number\n");
            int c;
            while((c = getchar()) != '\n' && c !=EOF);
            break;
        };
        set_temperature(&device,temperature);
        break;
    case 3:
        toggle_led(&device);
        break;
    case 4:
        update_errors(&device);
        show_errors(&device);

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
