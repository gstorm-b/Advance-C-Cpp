/***************************************************************************
 * @file    Rte_TorqueControl.c
 * @brief   Khai báo các API để gọi hàm liên quan đến giám sát và điều khiển 
 *          mô-men xoắn.
 * @details File cung cấp các API cho việc giám sát và điều khiển mô-men 
 *          xoắn bao gồm bàn đạp ga, cảm biến tốc độ, cảm biến mô-men xoắn, 
 *          cảm biến tải trọng, điều khiển động cơ.
 * @version 1.0
 * @date    2024-09-26
 * @author  Duong Gia Bao
 ***************************************************************************/

#ifndef RTE_TORQUECONTROL_H
#define RTE_TORQUECONTROL_H

#include "Std_Types.h"

/**
 * @brief   API để đọc dữ liệu từ cảm biến bàn đạp ga.
 * @param   ThrottlePosition Địa chỉ biến ghi giá trị bàn đạp ga.
 * @return  Trả về trạng thái đọc dữ liệu
 */
Std_ReturnType Rte_Read_RpThrottleSensor_ThrottlePosition(float* ThrottlePosition);

/**
 * @brief   API để đọc dữ liệu từ cảm biến tốc độ.
 * @param   Speed Địa chỉ biến ghi giá trị tốc độ.
 * @return  Trả về trạng thái đọc dữ liệu.
 */
Std_ReturnType Rte_Read_RpSpeedSensor_Speed(float* Speed);

/**
 * @brief   API để đọc dữ liệu từ cảm biến tải trọng.
 * @param   LoadWeight Địa chỉ biến ghi giá trị tải trọng.
 * @return  Trả về trạng thái đọc dữ liệu.
 */
Std_ReturnType Rte_Read_RpLoadSensor_LoadWeight(float* LoadWeight);

/**
 * @brief   API để đọc mô-men xoắn thực tế từ cảm biến mô-men xoắn.
 * @param   ActualTorque Địa chỉ biến ghi giá trị mô-men xoắn.
 * @return  Trả về trạng thái đọc dữ liệu.
 */
Std_ReturnType Rte_Read_RpTorqueSensor_ActualTorque(float* ActualTorque);

/**
 * @brief   API để ghi dữ liệu mô-men xoắn yêu cầu tới bộ điều khiển động cơ.
 * @param   TorqueValue Giá trị mô-men xoắn yêu cầu.
 * @return  Trả về trạng thái ghi dữ liệu.
 */
Std_ReturnType Rte_Write_PpMotorDriver_SetTorque(float TorqueValue);

/**
 * @brief   API khởi tạo cảm biến bàn đạp ga.
 * @return  Trả về trạng thái khởi tạo.
 */
Std_ReturnType Rte_Call_RpThrottleSensor_Init(void);

/**
 * @brief   API khởi tạo cảm biến tốc độ.
 * @return  Trả về trạng thái khởi tạo.
 */
Std_ReturnType Rte_Call_RpSpeedSensor_Init(void);

/**
 * @brief   API khởi tạo cảm biến tải trọng.
 * @return  Trả về trạng thái khởi tạo.
 */
Std_ReturnType Rte_Call_RpLoadSensor_Init(void);

/**
 * @brief   API khởi tạo cảm biến mô-men xoắn.
 * @return  Trả về trạng thái khởi tạo.
 */
Std_ReturnType Rte_Call_RpTorqueSensor_Init(void);

/**
 * @brief   API khởi tạo bộ điều khiển mô-men xoắn.
 * @return  Trả về trạng thái khởi tạo.
 */
Std_ReturnType Rte_Call_PpMotorDriver_Init(void);

#endif // RTE_TORQUECONTROL_H
