#pragma once

typedef struct {
    float temperature;
    float voltage;
    int led_on;
    int motor_on;
} Device;

void device_init(Device *device);
void show_status(const Device *device);
void toggle_led(Device *device);
float set_temperature(Device *device,float temperature);
