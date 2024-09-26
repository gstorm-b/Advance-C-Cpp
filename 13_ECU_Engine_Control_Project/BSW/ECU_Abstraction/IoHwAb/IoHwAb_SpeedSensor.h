/***************************************************************************
 * @file    IoHwAb_SpeedSensor.h
 * @brief   Khai báo các hàm và cấu trúc liên quan đến cảm biến tốc độ.
 * @details File cung cấp cấu trúc dữ liệu, function khởi tạo, function đọc 
 *          giá trị tốc độ.
 * @version 1.0
 * @date    2024-09-26
 * @author  HALA Academy
 ***************************************************************************/

#ifndef IOHWAB_SPEEDSENSOR_H
#define IOHWAB_SPEEDSENSOR_H

#include "Std_Types.h"

/**
 * @brief Cấu hình cho cảm biến tốc độ
 */
typedef struct {
    uint8_t SpeedSensor_Channel;   // Kênh ADC để đọc giá trị từ cảm biến tốc độ
    uint16_t SpeedSensor_MaxValue; // Giá trị tốc độ tối đa mà cảm biến có thể đọc (km/h)
} SpeedSensor_ConfigType;

/**
 * @brief   Prototype cho hàm khởi tạo cảm biến tốc độ.
 * @param   ConfigPtr Địa chỉ biến khởi tạo.
 * @return  Trả về trạng thái khởi tạo.
 */
Std_ReturnType IoHwAb_SpeedSensor_Init(const SpeedSensor_ConfigType* ConfigPtr);

/**
 * @brief   Prototype cho hàm đọc giá trị từ cảm biến tốc độ.
 * @param   SpeedValue Địa chỉ biến lưu giá trị cảm biến đọc được.
 * @return  Trả về trạng thái đọc dữ liệu.
 */
Std_ReturnType IoHwAb_SpeedSensor_Read(float* SpeedValue);

#endif /* IOHWAB_SPEEDSENSOR_H */
