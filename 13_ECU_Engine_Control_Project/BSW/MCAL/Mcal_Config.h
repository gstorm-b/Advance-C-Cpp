#ifndef MCAL_CONFIG_H
#define MCAL_CONFIG_H

#include <stdio.h>

// Cấu hình và khởi tạo toàn bộ MCAL
void Mcal_ConfigInit(void);

// Cấu hình và khởi tạo ADC
void Adc_ConfigInit(void);

// Cấu hình và khởi tạo DIO
void Dio_ConfigInit(void);

// Cấu hình và khởi tạo PWM
void Pwm_ConfigInit(void);

// Cấu hình và khởi tạo CAN
void Can_ConfigInit(void);

#endif

