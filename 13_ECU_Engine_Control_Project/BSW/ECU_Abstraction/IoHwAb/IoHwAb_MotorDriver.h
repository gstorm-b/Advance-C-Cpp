/***************************************************************************
 * @file    IoHwAb_MotorDriver.h
 * @brief   Khai báo các hàm và cấu trúc liên quan đến driver động cơ.
 * @details File cung cấp cấu trúc dữ liệu, function khởi tạo, function điều 
 *          chỉnh mô-men xoắn động cơ.
 * @version 1.0
 * @date    2024-09-26
 * @author  HALA Academy
 ***************************************************************************/

#ifndef IOHWAB_MOTORDRIVER_H
#define IOHWAB_MOTORDRIVER_H

#include "Std_Types.h"

/**
 * @brief Cấu trúc cấu hình cho mô-tơ
 */
typedef struct {
    uint8_t Motor_Channel;      // Kênh PWM điều khiển mô-tơ
    uint16_t Motor_MaxTorque;   // Mô-men xoắn tối đa (Nm)
} MotorDriver_ConfigType;

/**
 * @brief   Prototype khởi tạo mô-tơ.
 * @param   ConfigPtr Cấu hình MotorDriver.
 * @return  Trả về trạng thái điều chỉnh.
 */
Std_ReturnType IoHwAb_MotorDriver_Init(const MotorDriver_ConfigType* ConfigPtr);

/**
 * @brief   Prototype điều chỉnh mô-men xoắn của mô-tơ.
 * @param   TorqueValue Giá trị mô-men điều chỉnh.
 * @return  Trả về trạng thái điều chỉnh.
 */
Std_ReturnType IoHwAb_MotorDriver_SetTorque(float TorqueValue);

#endif /* IOHWAB_MOTORDRIVER_H */
