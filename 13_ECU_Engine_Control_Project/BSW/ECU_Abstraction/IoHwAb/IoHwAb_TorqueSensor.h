/***************************************************************************
 * @file    IoHwAb_TorqueSensor.h
 * @brief   Khai báo các hàm và cấu trúc liên quan đến cảm biến mô-men xoắn.
 * @details File cung cấp cấu trúc dữ liệu, function khởi tạo, function đọc 
 *          giá trị cảm biến cảm biến mô-men xoắn.
 * @version 1.0
 * @date    2024-09-26
 * @author  HALA Academy
 ***************************************************************************/

#ifndef IOHWAB_TORQUESENSOR_H
#define IOHWAB_TORQUESENSOR_H

#include "Std_Types.h"

/**
 * @brief Cấu hình cho cảm biến mô-men xoắn
 */
typedef struct {
    uint8_t TorqueSensor_Channel;   // Kênh ADC để đọc giá trị từ cảm biến mô-men xoắn
    uint16_t TorqueSensor_MaxValue; // Giá trị mô-men xoắn tối đa (Nm)
} TorqueSensor_ConfigType;

/**
 * @brief   Hàm khởi tạo cảm biến mô-men xoắn với cấu hình.
 * @param   ConfigPtr Địa chỉ biến khởi tạo.
 * @return  Trả về trạng thái khởi tạo.
 */
Std_ReturnType IoHwAb_TorqueSensor_Init(const TorqueSensor_ConfigType* ConfigPtr);

/**
 * @brief   Hàm đọc giá trị từ cảm biến mô-men xoắn.
 * @param   TorqueValue Địa chỉ biến lưu giá trị cảm biến đọc được.
 * @return  Trả về trạng thái đọc cảm biến.
 */
Std_ReturnType IoHwAb_TorqueSensor_Read(float* TorqueValue);

#endif /* IOHWAB_TORQUESENSOR_H */
