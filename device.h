#pragma once
#include <stdbool.h>

typedef enum {
    DEVICE_OK,
    DEVICE_WARNING,
    DEVICE_ERROR 
} DeviceStatus;
typedef struct {
    float temperature;
    float voltage;
    int led_on;
    int motor_on;
    unsigned int errors;
    DeviceStatus status;
} Device;




void device_init(Device *device);
void show_status(const Device *device);
void toggle_led(Device *device);
bool set_temperature(Device *device,float temperature);

bool generate_random_params(Device *device);
void update_errors(Device *device);
void show_errors(Device *device);
void update_errors(Device *device);
void update_status(Device *device);
void device_tick(Device *device);
void simulating_changes_in_params(Device *device);