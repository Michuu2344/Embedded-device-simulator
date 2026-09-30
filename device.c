#include <stdio.h>
#include <stddef.h>
#include "device.h"
#include <stdlib.h>
#include <stdbool.h>

#define ERROR_NONE 0
#define ERROR_OVERHEAT (1 << 0)
#define ERROR_LOW_VOLTAGE (1 << 1)
#define ERROR_HIGH_VOLTAGE (1 << 2)


void device_init(Device *device){
    if (device == NULL){
        return;
    }
    device->temperature = 0.0f;
    device->voltage = 0.0f;
    device->led_on = 0;
    device->motor_on = 0;
}

void show_status(const Device *device){
    printf("\n===== DEVICE STATUS =====\n");
    printf("Temperature: %.1f C\n",device->temperature);
    printf("Voltage: %.2f V\n",device->voltage);
    printf("LED: %s\n",device->led_on ? "ON" : "OFF");
    printf("MOTOR: %s\n",device->motor_on ? "ON" : "OFF");
    switch(device->status){
        case DEVICE_OK:
            printf("STATUS : OK\n");
            break;
        case DEVICE_WARNING:
            printf("STATUS : WARNING\n");
            break;
        case DEVICE_ERROR:
            printf("STATUS : ERROR\n");
            break;
    }
}
void toggle_led(Device *device){
    if(device == NULL){
        return;
    }
    device->led_on = !(device->led_on);

}
void toggle_motor(Device *device){
    if(device == NULL){
        return;
    }
    device->motor_on = !(device->motor_on);

}
bool set_temperature(Device *device,float temperature){
    if(device == NULL){
        return false;
    }
    if(temperature < -20.0f || temperature > 80.0f ){
        return false;
    }


    device->temperature = temperature;
    return true;
}
bool generate_random_params(Device *device){
    if(device == NULL){
        return false;
    }

    float min_voltage = 1.8f;
    float max_voltage = 5.0f;

    float r =(float)rand() /(float)RAND_MAX;

    float generated_voltage = min_voltage + r *(max_voltage-min_voltage);
    device->voltage = generated_voltage;

    float min_temperature = -20.0f;
    float max_temperature = 80.0f;

    float rt = (float)rand() / (float)RAND_MAX;
    float generated_temperature = min_temperature + rt *(max_temperature - min_temperature);
    device->temperature = generated_temperature;

    int led_status = rand() % 2;
    device->led_on = led_status; 


    int motor_status = rand() % 2;
    device->motor_on = motor_status; 

    return true;
}
void update_errors(Device *device){
    device->errors = ERROR_NONE;

    if(device->temperature > 70.0f){
        device->errors |= ERROR_OVERHEAT;
    }
    if(device->voltage < 2.0f){
        device->errors |= ERROR_LOW_VOLTAGE;
    }
    if(device->voltage > 4.8f){
        device->errors |= ERROR_HIGH_VOLTAGE;
    }

}

void show_errors(Device *device){
    if(device->errors == ERROR_NONE){
        printf("No errors.\n");
    }
    if(device->errors & ERROR_OVERHEAT){
        printf("[ERROR] Device is overheating.\n");
    }
    if(device->errors & ERROR_LOW_VOLTAGE){
        printf("[ERROR] Voltage is too low.\n");
    }
    if(device->errors & ERROR_HIGH_VOLTAGE){
        printf("[ERROR] Voltage is too high.\n");
    }
    
}
void update_status(Device *device){
    if(device->temperature > 70.0f || device->voltage < 1.8f || device->voltage > 4.8f){
        device->status = DEVICE_ERROR;
    } else if(device->temperature > 60.0f || device->voltage < 2.0f || device->voltage > 4.6f){
        device->status = DEVICE_WARNING;
    } else {
        device->status = DEVICE_OK;
    } 
}

float random_params_change(float min,float max){
    float r = (float)rand() /(float)RAND_MAX;

    float change = min + r * (max-min);
    return change;
}
void simulating_changes_in_params(Device *device){
    float min_change_temp = -0.2f;
    float max_change_temp = 0.4f;
    float temp_change = random_params_change(min_change_temp,max_change_temp);
    if((device->temperature + temp_change) > 80.0f ||(device->temperature + temp_change)< -20.0f){
        return;
    }
    else{
        device->temperature += temp_change;
    }

    float min_change_voltage = -0.1f;
    float max_change_voltage= 0.2f;
    float voltage_change = random_params_change(min_change_voltage,max_change_voltage);
    if((device->voltage + voltage_change ) > 5.0f ||(device->voltage + voltage_change )< 1.8f){
        return;
    }
    else{
        device->voltage += voltage_change;
    }
    



}
void device_tick(Device *device){
    
    if(device == NULL){
        return;
    }
    simulating_changes_in_params(device);
    update_errors(device);
    update_status(device);

}
// wystepowanie wielu bledow jednoczesnie np

// 000
// │││
// ││└── overheat
// │└─── low voltage
// └──── high voltage

