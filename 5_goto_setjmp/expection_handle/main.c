#include <stdio.h>
#include <setjmp.h>
#include <time.h>

#define LED_OFF     0
#define LED_ON      1

jmp_buf buf;
int exception_code;

#define TRY                 if ((exception_code = setjmp(buf)) == 0) 
#define CATCH(x)            else if (exception_code == (x))
#define THROW(x, msg)       \
    printf(msg);            \
    printf(" => ");         \
    longjmp(buf, (x));

typedef enum {
    NO_ERROR = 0,
    FILE_ERROR = 1,
    CONNECT_ERROR = 2,
    PARSE_DATA_ERROR = 3
} ErrorCode;

void readFile(int error) {
    if (error == 1) {
        // printf("Cannot open file  => ");
        // longjmp(buf, FILE_ERROR);
        THROW(FILE_ERROR, "Cannot open file");
    }

    printf("File opened.\n");
}

void connectToClient(int error) {
    if (error == 1) {
        THROW(CONNECT_ERROR, "Not found client in network");
    }
    
    printf("Connected to client.\n");
}

void parseData(int error) {
    if (error == 1) {
        THROW(PARSE_DATA_ERROR, "Data wrong format");
    }
    
    printf("Data parsed.\n");
}

void toggleLed() {
    static int led = LED_ON;

    if (led==LED_OFF) {
        led = LED_ON;
        printf("\nLed is on.\n\n");
    } else {
        led = LED_OFF;
        printf("\nLed is off.\n\n");
    }
}

void delay(int interval) {
    clock_t time_stamp;
    time_stamp = clock();

    while ((clock() - time_stamp) < interval) {

    }
}

int main() {

    // exception_code = setjmp(buf);
    // if ((exception_code) == 0) {
    //     connectToClient(0);
    //     readFile(1);
    //     parseData(0);
    // } else if (exception_code == FILE_ERROR) {
    //     printf("Error code: 0x01 - FILE_ERROR \n");
    //     // handle
    // } else if (exception_code == CONNECT_ERROR) {
    //     printf("Error code: 0x02 - CONNECT_ERROR \n");
    // } else if (exception_code == PARSE_DATA_ERROR) {
    //     printf("Error code: 0x03 - PARSE_DATA_ERROR \n");
    // }

    // TRY {
    //     connectToClient(0);
    //     readFile(0);
    //     parseData(1);
    // } CATCH(FILE_ERROR) {
    //     printf("Error code: 0x01 - FILE_ERROR \n");
    // } CATCH(CONNECT_ERROR) {
    //     printf("Error code: 0x02 - CONNECT_ERROR \n");
    // } CATCH(PARSE_DATA_ERROR) {
    //     printf("Error code: 0x03 - PARSE_DATA_ERROR \n");
    // }

    // printf("End program!\n");

    while (1)   {
        TRY {
            int error_1, error_2, error_3 = 0;
            connectToClient(error_1);
            readFile(error_2);
            parseData(error_3);
        } CATCH(FILE_ERROR) {
            printf("Error code: FILE_ERROR (0x01) \n");
        } CATCH(CONNECT_ERROR) {
            printf("Error code: CONNECT_ERROR (0x02) \n");
        } CATCH(PARSE_DATA_ERROR) {
            printf("Error code: PARSE_DATA_ERROR (0x03) \n");
        }

        toggleLed();
        delay(1000);
    }

    return 0;
}