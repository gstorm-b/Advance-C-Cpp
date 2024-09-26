# gcc -g -Wall -IBSW/MCAL -c RTE/Rte_TorqueControl.h -o RTE/Rte_TorqueControl.o
# Tên file sau khi compile
TARGET = program

# Các folder chứa source file
SRC_DIR = .
BSW_DIR = BSW
RTE_DIR = RTE
SWC_DIR = SWC

CC = gcc
# -I thêm đường dẫn để compiler tìm kiếm file header
CFLAGS = -g -Wall -I$(BSW_DIR)/ECU_Abstraction/IoHwAb -I$(BSW_DIR)/MCAL -I$(BSW_DIR)/Services -I$(RTE_DIR) -I$(SWC_DIR)

# SRCS chứa danh sách các file cần build ra file object
SRCS = \
    $(BSW_DIR)/ECU_Abstraction/IoHwAb/IoHwAb_LoadSensor.c \
    $(BSW_DIR)/ECU_Abstraction/IoHwAb/IoHwAb_MotorDriver.c \
    $(BSW_DIR)/ECU_Abstraction/IoHwAb/IoHwAb_SpeedSensor.c \
	$(BSW_DIR)/ECU_Abstraction/IoHwAb/IoHwAb_ThrottleSensor.c \
	$(BSW_DIR)/ECU_Abstraction/IoHwAb/IoHwAb_TorqueSensor.c \
    $(BSW_DIR)/MCAL/Adc.c \
    $(BSW_DIR)/MCAL/Can.c \
    $(BSW_DIR)/MCAL/Dio.c \
	$(BSW_DIR)/MCAL/Mcal_Config.c \
	$(BSW_DIR)/MCAL/Pwm.c \
    $(BSW_DIR)/Services/Dcm.c \
    $(BSW_DIR)/Services/Dem.c \
    $(BSW_DIR)/Services/Mem.c \
    $(BSW_DIR)/Services/Os.c \
    $(BSW_DIR)/Services/Pdu_Router.c \
    $(RTE_DIR)/Rte_TorqueControl.c \
    $(SWC_DIR)/Torque_Control.c \
    main.c

# chuyển danh sách trong soucre từ *.c qua *.o để có danh sách tên file object
OBJS = $(SRCS:.c=.o)

# rule mặc định khi chạy make
all: $(TARGET)

# rule build file target
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

# Quy tắc bulid file source thàn file object
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# rule clean file build
clean:
	rm -f $(OBJS) $(TARGET)

# rule compile và chạy chương trình
run: $(TARGET)
	./$(TARGET)