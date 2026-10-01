#include <stdio.h>
#include <stdbool.h>
#include "device.h"
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>



pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

static bool thread_running = true;
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
        pthread_mutex_lock(&mutex);
        if(!thread_running){
            pthread_mutex_unlock(&mutex);
            break;
        }
        device_tick(device);
        pthread_mutex_unlock(&mutex);
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
    pthread_t tid;

    if(pthread_create(&tid,NULL,device_thread,&device) != 0){ // jesli to nie jest zerem to nie utworzylismy watku
        printf("Failed to create device thread");
        return 1;
    }


    int user_choice = 0;
    while(running){
        user_choice = show_menu();
        switch (user_choice)
    {
    case 1:
        pthread_mutex_lock(&mutex);

        update_status(&device);
        show_status(&device);
        pthread_mutex_unlock(&mutex);
        break;
    
    case 2:
        printf("Set the temperature: ");
        if(scanf("%f",&temperature) != 1){
            printf("You have to type a float number\n");
            int c;
            while((c = getchar()) != '\n' && c !=EOF);
            break;
        };
        pthread_mutex_lock(&mutex); // blokujemy watek aby nie doszlo do kolizji w ktorej dwie funkcje chca zmienic ta sama zmienna
        set_temperature(&device,temperature);
        pthread_mutex_unlock(&mutex); // odblokowujemy
        break;
    case 3:
        pthread_mutex_lock(&mutex);
        toggle_led(&device);
        pthread_mutex_unlock(&mutex);
        break;
    case 4:
        pthread_mutex_lock(&mutex);
        update_errors(&device);
        show_errors(&device);
        pthread_mutex_unlock(&mutex);
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
    pthread_mutex_lock(&mutex); 
    thread_running = false;
    pthread_mutex_unlock(&mutex);
    pthread_join(tid,NULL);
    pthread_mutex_destroy(&mutex);
    return 0;

   
}
// musimy zrobic tak zeby dwie funkcje nie probowaly zmienic jednej rzeczy w tym samym czasie
// 1.ustawiamy lock
// 2. definijemy watki
// 3. blokujemy watek jesli funkcja ma edytowac cos
// 4. po wykonaniu sie funkcji musimy odblokowac watek

