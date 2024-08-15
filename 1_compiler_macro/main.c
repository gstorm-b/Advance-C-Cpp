/* Viết macro tính tổng nhiều số */

#include <stdio.h>

#define SUM_INT(...)                                \
    int num_list[] = {__VA_ARGS__};                 \
    int args_len = sizeof(num_list)/sizeof(int);    \
    int result = num_list[0];                       \
    for(int index=1;index<args_len;index++) {       \
        result += num_list[index];                  \
    }                                               \
    printf("Sum [%s] = %d", #__VA_ARGS__, result);

int main() {

    SUM_INT(1, 2, 54, 5, 6, 6, 7);

    return 0;
}