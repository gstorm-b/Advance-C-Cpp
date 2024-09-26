#include "Mcal_Config.h"
#include "Adc.h"
#include "Dio.h"
#include "Pwm.h"
#include "Can.h"

// Cấu hình và khởi tạo toàn bộ MCAL
void Mcal_ConfigInit(void) {
    printf("Initializing MCAL configuration...\n");

    // Khởi tạo và cấu hình từng mô-đun
    Adc_ConfigInit();
    Dio_ConfigInit();
    Pwm_ConfigInit();
    Can_ConfigInit();

    printf("MCAL configuration complete.\n");
}

// Cấu hình và khởi tạo ADC
void Adc_ConfigInit(void) {
    printf("Configuring ADC...\n");
    Adc_Init(NULL);  // Gọi hàm khởi tạo ADC
    printf("ADC configuration complete.\n");
}

// Cấu hình và khởi tạo DIO
void Dio_ConfigInit(void) {
    printf("Configuring DIO...\n");
    Dio_Init();  // Gọi hàm khởi tạo DIO
    printf("DIO configuration complete.\n");
}

// Cấu hình và khởi tạo PWM
void Pwm_ConfigInit(void) {
    printf("Configuring PWM...\n");
    Pwm_Init(NULL);  // Gọi hàm khởi tạo PWM
    printf("PWM configuration complete.\n");
}

// Cấu hình và khởi tạo CAN
void Can_ConfigInit(void) {
    printf("Configuring CAN...\n");
    Can_Init();  // Gọi hàm khởi tạo CAN
    printf("CAN configuration complete.\n");
}
