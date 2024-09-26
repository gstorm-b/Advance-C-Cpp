/***************************************************************************
 * @file    Torque_Control.h
 * @brief   Khai báo các hàm khởi tạo và cập nhật mô-men xoắn.
 * @details File cung cấp function khởi tạo mô-men xoắn và cập nhật giá trị
 *          của mô-men xoắn.
 * @version 1.0
 * @date    2024-09-26
 * @author  Duong Gia Bao
 ***************************************************************************/

#ifndef TORQUE_CONTROL_H
#define TORQUE_CONTROL_H

// Định nghĩa mô-men xoắn tối đa và tối thiểu
#define MAX_TORQUE 100.0f
#define MIN_TORQUE 0.0f

/**
 * @brief   Hàm khởi tạo hệ thống điều khiển mô-men xoắn.
 * @return  void
 */
void TorqueControl_Init(void);

/**
 * @brief   Hàm cập nhật hệ thống điều khiển mô-men xoắn.
 * @return  void
 * 
 * @details Gọi các API và thực hiện hiển thị giá trị của các thành phần liên quan.
 */
void TorqueControl_Update(void);

#endif // TORQUE_CONTROL_H
