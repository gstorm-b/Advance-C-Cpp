#include "Os.h"

// Biến lưu trữ luồng
#define MAX_TASKS 5
pthread_t task_threads[MAX_TASKS];
int task_count = 0;

// Khởi tạo hệ điều hành
void Os_Init(void) {
    printf("OS Initialized.\n");
    task_count = 0;
}

// Tạo và khởi động một luồng
void Os_CreateTask(void* (*task_func)(void*), const char* task_name) {
    if (task_count >= MAX_TASKS) {
        printf("Cannot create more tasks. Maximum task count reached.\n");
        return;
    }
    
    printf("Creating task: %s\n", task_name);
    pthread_create(&task_threads[task_count], NULL, task_func, NULL);
    task_count++;
}

// Hàm delay để dừng luồng trong một khoảng thời gian
void Os_Delay(int milliseconds) {
    usleep(milliseconds * 1000); // Sử dụng usleep cho delay tính theo mili giây
}

// Kết thúc hệ điều hành và chờ các luồng kết thúc
void Os_Shutdown(void) {
    printf("Shutting down OS and waiting for tasks to finish...\n");
    for (int i = 0; i < task_count; i++) {
        pthread_join(task_threads[i], NULL); // Chờ các luồng kết thúc
    }
    printf("All tasks have completed. OS Shutdown.\n");
}



#include "Mem.h"

int main() {
    // Khởi tạo hệ thống quản lý bộ nhớ
    Mem_Init();

    // Cấp phát một số vùng bộ nhớ
    void* block1 = Mem_Alloc(128);  // Cấp phát 128 byte
    void* block2 = Mem_Alloc(256);  // Cấp phát 256 byte
    void* block3 = Mem_Alloc(512);  // Cấp phát 512 byte

    // Kiểm tra các vùng nhớ
    Mem_Check(block1);  // Kiểm tra block1 có hợp lệ không
    Mem_Check(block2);  // Kiểm tra block2 có hợp lệ không

    // Giải phóng một số vùng bộ nhớ
    Mem_Free(block2);
    Mem_Free(block3);

    // Kiểm tra lại vùng nhớ đã giải phóng
    Mem_Check(block2);  // block2 đã giải phóng, nên sẽ không hợp lệ

    // Giải phóng vùng nhớ còn lại
    Mem_Free(block1);

    return 0;
}






#include "Dem.h"

int main() {
    // Khởi tạo hệ thống DEM
    Dem_Init();

    // Báo cáo một số sự kiện chẩn đoán
    Dem_ReportErrorStatus(1, "Overcurrent detected");
    Dem_ReportErrorStatus(2, "Overheating detected");

    // Kiểm tra trạng thái các sự kiện
    Dem_CheckErrorStatus(1);
    Dem_CheckErrorStatus(2);
    
    // In danh sách sự kiện hiện tại
    Dem_PrintEventList();

    // Xóa trạng thái lỗi của sự kiện 1
    Dem_ClearErrorStatus(1);

    // Kiểm tra lại sự kiện sau khi xóa
    Dem_CheckErrorStatus(1);

    // In lại danh sách sự kiện
    Dem_PrintEventList();

    return 0;
}




#include "Dcm.h"
#include "Dem.h"

int main() {
    // Khởi tạo hệ thống DEM và DCM
    Dem_Init();
    Dcm_Init();

    // Giả lập một số sự kiện chẩn đoán
    Dem_ReportErrorStatus(1, "Overvoltage detected");
    Dem_ReportErrorStatus(2, "Undervoltage detected");

    // Giả lập yêu cầu chẩn đoán từ thiết bị kiểm tra
    Dcm_MessageType request1 = {DIAGNOSTIC_SESSION_CONTROL, "Start Session"};
    Dcm_ProcessRequest(&request1);

    // Giả lập yêu cầu đọc DTC
    Dcm_MessageType request2 = {READ_DTC, "Read all DTC"};
    Dcm_ProcessRequest(&request2);

    // Giả lập yêu cầu xóa DTC
    Dcm_MessageType request3 = {CLEAR_DTC, "Clear all DTC"};
    Dcm_ProcessRequest(&request3);

    // Giả lập yêu cầu reset ECU
    Dcm_MessageType request4 = {ECU_RESET, "Reset ECU"};
    Dcm_ProcessRequest(&request4);

    return 0;
}







#include "Pdu_Router.h"

int main() {
    // Khởi tạo PDU Router
    PduR_Init();

    // Giả lập PDU từ giao thức CAN
    Pdu_Type can_pdu = {PROTOCOL_CAN, "CAN Data", 8};
    PduR_RoutePdu(&can_pdu);

    // Giả lập PDU từ giao thức LIN
    Pdu_Type lin_pdu = {PROTOCOL_LIN, "LIN Data", 7};
    PduR_RoutePdu(&lin_pdu);

    // Giả lập PDU từ giao thức Ethernet
    Pdu_Type ethernet_pdu = {PROTOCOL_ETHERNET, "Ethernet Data", 12};
    PduR_RoutePdu(&ethernet_pdu);

    return 0;
}
