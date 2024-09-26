/***************************************************************************
 * @file    IoHwAb_ThrottleSensor.h
 * @brief   Khai báo các hàm và cấu trúc liên quan đến cảm biến bàn đạp.
 * @details File cung cấp cấu trúc dữ liệu, function khởi tạo, function đọc 
 *          giá trị cảm biến bàn đạp.
 * @version 1.0
 * @date    2024-09-26
 * @author  HALA Academy
 ***************************************************************************/

#ifndef IOHWAB_THROTTLESENSOR_H
#define IOHWAB_THROTTLESENSOR_H

#include "Std_Types.h"

/**
 * @brief Cấu hình cho cảm biến bàn đạp ga
 */
typedef struct {
    uint8_t ThrottleSensor_Channel;  // Kênh ADC để đọc giá trị từ cảm biến bàn đạp ga
} ThrottleSensor_ConfigType;

/**
 * @brief   Hàm khởi tạo cảm biến bàn đạp ga.
 * @param   ConfigPtr Địa chỉ biến khởi tạo.
 * @return  Trả về trạng thái khởi tạo.
 */
Std_ReturnType IoHwAb_ThrottleSensor_Init(const ThrottleSensor_ConfigType* ConfigPtr);

/**
 * @brief   Hàm đọc giá trị từ cảm biến bàn đạp ga.
 * @param   ThrottlePosition Địa chỉ biến lưu giá trị cảm biến đọc được.
 * @return  Trả về trạng thái đọc cảm biến.
 */
Std_ReturnType IoHwAb_ThrottleSensor_Read(float* ThrottlePosition);

#endif /* IOHWAB_THROTTLESENSOR_H */
