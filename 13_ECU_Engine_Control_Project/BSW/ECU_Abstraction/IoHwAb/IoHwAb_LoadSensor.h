/***************************************************************************
 * @file    IoHwAb_LoadSensor.h
 * @brief   Khai báo các hàm và cấu trúc liên quan đến cảm biến tải trọng.
 * @details File cung cấp cấu trúc dữ liệu, function khởi tạo và đọc giá 
 *          trị cảm biến tải trọng.
 * @version 1.0
 * @date    2024-09-26
 * @author  HALA Academy  
 ***************************************************************************/

#ifndef IOHWAB_LOADSENSOR_H
#define IOHWAB_LOADSENSOR_H

#include "Std_Types.h"

/**
 * @brief Cấu hình cho cảm biến tải trọng (Load Sensor)
 */
typedef struct {
    uint8_t LoadSensor_Channel;   // Kênh ADC để đọc giá trị từ cảm biến
    uint16_t LoadSensor_MaxValue; // Giá trị tải trọng tối đa mà cảm biến có thể đọc
} LoadSensor_ConfigType;

/**
 * @brief   Khởi tạo cảm biến tải trọng.
 * @param   ConfigPtr Địa chỉ biến khởi tạo.
 * @return  Trả về trạng thái khởi tạo.
 */
Std_ReturnType IoHwAb_LoadSensor_Init(const LoadSensor_ConfigType* ConfigPtr);

/**
 * @brief   Hàm đọc giá trị từ cảm biến tải trọng.
 * @param   LoadValue Địa chỉ biến lưu giá trị cảm biến đọc được.
 * @return  Trả về trạng thái đọc cảm biến.
 */
Std_ReturnType IoHwAb_LoadSensor_Read(float* LoadValue);

#endif /* IOHWAB_LOADSENSOR_H */
