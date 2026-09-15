#include <stdio.h>
#include <stddef.h>
#include "device.h"

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
    device->motor_on = !(device->led_on);

}
float set_temperature(Device *device,float temperature){
    if(device == NULL){
        return 0.0f;
    }
    device->temperature = temperature;

}