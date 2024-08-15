/* Viết function handle case cho nhiều loại cảm biến khác nhau */

#include <stdio.h>
#include <stdarg.h>
#include <assert.h>

typedef enum {
    TEMPERATURE_SENSOR = 0,
    DISTANCE_SENSOR,
    COLOR_SENSOR,
    MAGNETIC_ENCODER_SENSOR
}SensorType;

typedef enum {
    ENC_POSISTIVE,
    ENC_NEGATIVE
}EncoderDirection;

#define CASE_TYPE(type, case_function)      \
    case type:                              \
        case_function;                      \
        break;

void handleSensorTemperature(va_list *args) {
    double target_temp = va_arg(*args, double);
    double current_temp = va_arg(*args, double);
    printf("------ Temperature data\n");
    printf("Tagert cpu temperature: %.3f.\n", target_temp);
    printf("Current cpu temperature: %.3f.\n", current_temp);
    printf("Error: %.3f.\n\n", target_temp - current_temp);
}

void handleSenorDistance(va_list *args) {
    printf("------ Distance data\n");
    printf("Distance to target: %.1fm.\n\n", va_arg(*args, double));
}

void handleSenorColor(va_list *args) {
    printf("------ Color detect\n");
    printf("RGB - [%d, %d, %d].\n\n", va_arg(*args, int), va_arg(*args, int), va_arg(*args, int));
}

void handleSensorMagEncoder(va_list *args) {
    // direction, absolute angle
    EncoderDirection direction = va_arg(*args, int);
    int angle = va_arg(*args, int);
    double absolute_angle = (double)angle / 4096.0;
    printf("------ Encoder angle\n");
    printf("Direction: %s\n", (direction == ENC_POSISTIVE) ? "Positive" : "Negative");
    printf("Magnetic position: %d.\n", angle);
    printf("Absolute angle: %.3f.\n\n", absolute_angle);
}

void handleSensor(SensorType type, ...) {
    va_list args;
    va_start(args, type);

    switch (type) {
        CASE_TYPE(TEMPERATURE_SENSOR, handleSensorTemperature(&args));
        CASE_TYPE(DISTANCE_SENSOR, handleSenorDistance(&args));
        CASE_TYPE(COLOR_SENSOR, handleSenorColor(&args));
        CASE_TYPE(MAGNETIC_ENCODER_SENSOR, handleSensorMagEncoder(&args));
        
        default:
            assert(0 && "Invalid sensor type!");
            break;
    }

    va_end(args);
}

int main() {

    // handleSensor(6, 0);

    handleSensor(TEMPERATURE_SENSOR, 12.5, 15.999);
    handleSensor(DISTANCE_SENSOR, 180.9);
    handleSensor(COLOR_SENSOR, 255, 0, 122);
    handleSensor(MAGNETIC_ENCODER_SENSOR, ENC_POSISTIVE, 200);
    
    return 0;
}