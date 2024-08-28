**[Trình bày bài học trên Notion web](https://ritzy-tray-c64.notion.site/Advance-C-CPP-1340b8981c614ba29eb68631e6479064)**

# Bài 1: Compiler - Macro
<details>
<summary>nội dung</summary>

<h2>Compiler</h2>

**Compiler là trình biên dịch, có nhiệm vụ biên dịch source code sang ngôn ngữ máy để vi xử lí có thể thực thi được chương trình đó.**

<p align="center">
  <img src="https://github.com/user-attachments/assets/418ae9af-78e6-4ba5-a352-9193f6056b5c" width="50%">
</p>

* Preprocessing: là quá trình tiền xử lí, tạo ra file preprocessed. Trong qua trình này:

    * Preprocessor sẽ copy nội dung của file được include vào file tiền xử lí.
    * Xóa bỏ các comment trong source file.
    * Chèn nội dung được định nghĩa của macro tại vị trí gọi macro đó.

* Compilation: từ preprocessed source compiler sẽ biên dịch sang assembly code.

* Assemble: assembler tạo ra object file từ assembly code.

* Linking: Linker sẽ gộp các file object đã tạo ra từ lại thành một excutable file.
    * Vì khi include một header thì file header đó chỉ chứa tên của hàm không có nội dung thực thi của hàm đó. Tức là sau tiền xử lí cũng chỉ chứa tên hàm mà không có nội dung hàm trong file đó.
    * File source của header đó cũng được biên dịch thành file object và linker sẽ gộp nội dung của hàm đó vào executable file.

<h2>Macro</h2>

**Macro gồm một label và nội dung là đoạn code sẽ được thay thế cho label đó trong quá trình tền xử lí (preprocessing).**

**Chỉ thị tiền xử lí là chỉ thị báo cho preprocesor xử lí những nội dung có trong source code.**

Các chỉ thị tiền xử lí:

* #include: là chỉ thị chèn tất cả nội dung của file được include vào source file.
    
    ⇒ Giúp quản lí và tái sử dụng source code hiệu quả.
    
* #define: dùng để định nghĩa một macro.

* #undef: để hủy định nghĩa một macro đã định nghĩa trước đó.
    
    ⇒ Sử dụng trong trường hợp cần định nghĩa lại macro.
    
* #if, #elif, #else: là những chỉ thị điều kiện để quyết định xem có chèn những nội dung bên trong điều kiện vào source file hay không. Kết thúc chỉ thị điều kiện này là #endif.
    
    ⇒ Dùng để linh hoạt khai báo macro có nội dung khác nhau phù hợp với yêu cầu và đối tượng thực thi chương trình.
    
- #ifdef và #ifndef: là chỉ thị kiểm tra xem đã định nghĩa macro đó hay chưa. Nếu điều kiện đúng thì nội dung bên trong điều kiện sẽ được chèn vào source file. Kết thúc chỉ thị điều kiện là #endif.
    
    ⇒ Để tránh chèn lặp lại những nội dung đã được định nghĩa và chèn vào trước đó.

Các toán tử trong macro:
* Stringize: định nghĩa nội dung của label phía sau # là một chuỗi trong dấu “”.
    
    ```c
    #define _PRINTF(cmd) printf(#cmd)
    ```
    
* Concatenation: nối nội dung của label phía sau ## vào chuỗi phía trước.
    
    ```c
    #define PIN_DEF(number)    int pin_##number
    ```
    
* Variadic: tạo ra macro có thể nhận số lượng tham số truyền vào không cố định và có thể thay đổi.

    ```c
    #define NUM_LIST(...)                       \
    int sum_list[] = {__VA_ARGS__}

    NUM_LIST(1, 4, 5, 6);

    // kết quả sau tiền xử lí
    int sum_list[] = {1, 4, 5, 6};
    ```

Ví dụ định nghĩa macro:

* Định nghĩa macro có chứa giá trị của số pi.

* Định nghĩa macro khai báo nhiều biến có cùng format tên.

* Định nghĩa macro khai báo function.

    ```c
    #define PI_NUMBER               (double)3.14159

    #define NEW_VAR(name)           \
    int         int_##name;         \
    double      double_##name;      \
    char        char_##name;

    #define     _PRINTF(func_name, cmd)         \
    void func_name() {                          \
        printf(#cmd);                           \
        printf("\n");                           \
    }

    _PRINTF(print_hello, hello!);
    _PRINTF(print_goodbye, good bye!);

    int main() {

        printf("%.3f\n", PI_NUMBER); 

        NEW_VAR(test);
        int_test = 5;
        double_test = 5.0;
        char_test = 'a';

        print_hello();
        print_goodbye();
        return 0;
    }
    ```

Ví dụ #ifdef và #ifndef:

* Dùng #ifndef để kiểm tra xem label BOARD_H đã được địa nghĩa trước đó hay chưa. Và định nghĩa label đó nếu chưa.

* Dùng điều kiện #if, #elif để định nghĩa chân Led builtin  phù hợp với board cần biên dịch.

    ```c
    #ifndef BOARD_H
    #define BOARD_H

    #define MCU     UNO
    //#define MCU     MEGA

    #if MCU == UNO
        #define     LED_BULTIN      2
    #elif MCU == MEGA
        #define     LED_BULTIN      7
    #endif

    #endif
    ```

**Macro và function khác nhau như thế nào mặc dù có thể cho ra kết quả như nhau.**

* Function chiếm một vùng nhớ cố định trong main memory. Vì function chỉ được định nghĩa một lần. Mỗi khi gọi function thì program counter sẽ nhảy tới vùng nhớ lưu function đó để thực thi.
* Còn khi định nghĩa macro thì khi biên dịch preprocessor sẽ thay thế đoạn macro được định nghĩa tại vị trí gọi macro đó. Khi gọi nhiều lần sẽ có nhiều đoạn giống nhau trong main memory.
    
⇒ Dùng function sẽ tối ưu hơn về mặt bộ nhớ nhưng sẽ không tối ưu về mặt tốc độ khi so với macro.

</details>

# Bài 2: STDARG - ASSERT
<details>
<summary>nội dung</summary>

<h2>STDARG</h2>

**Stdarg là thư viện chuẩn của C, hỗ trợ viết function với số lượng tham số và kiểu dữ liệu không xác định trước.**

Kiểu dữ liệu và macro của thư viện stdarg:

* va_list: là kiểu dự liệu để chứa các tham số truyền vào.

* void va_start(va_list *ap*, *argN*): xác định địa chỉ bắt đầu trong danh sách tham số truyền vào. Địa chỉ bắt đầu là địa chỉ của tham số tiếp theo phía sau  label argN. Cần gọi trước va_start trước khi gọi va_arg.

* type va_arg(va_list *ap*, *type*): trả về giá trị của địa chỉ hiện tại đang trỏ tới trong danh sách tham số với kiểu dữ liệu xác định tại type. Và chuyển con trỏ đến vị trí tiếp theo trong danh sách tham số.

* void va_end(): giải phóng vùng nhớ đã tạo ra của biến va_list. Cần gọi khi không còn sử dụng va_list đó nữa.

Ví dụ viết một function tính tổng các số truyền vào kiểu int có số lượng tham số có thể thay đổi:

```c
int sum(int count, ...){
    va_list num_list;
    // khởi tạo va_list để lưu địa chỉ các tham số truyền vào
    va_start(num_list, count);
    // lấy ra giá trị của tham số hiện tại đang trỏ đến (địa chỉ đầu tiên là địa chỉ của tham số phía sau count)
    int result = va_arg(num_list, int);
    for(int index=1;index<count;index++) {
            // cộng dồn lần lượt các giá trị còn lại trong danh sách tham số
        result += va_arg(num_list, int);
    }
    // giải phóng vùng nhớ đã khởi tạo num_list
    va_end(num_list);
    return result;
}

int main(void) {
    printf("%d\n", sum(5, 1, 3, 5, 6, 7));
    return 0;
}
```

⇒ Ứng dụng để viết những function xử lí những trường hợp tham số truyền vào có thể thay đổi được.

<h2>ASSERT</h2>

**Assert là thư viện chuẩn của C, hỗ trợ debug và báo lỗi cho chương trình.**

**void assert(_Expression):** có tham số truyền vào là điều kiện báo lỗi và chuỗi kí tự thông báo khi có lỗi xảy ra.

* Nếu điều kiện đúng chương trình sẽ chạy tiếp mà không báo lỗi.
* Nếu điều kiện sai chương trình sẽ báo lỗi với chuỗi kí tự đã định nghĩa trước và dừng chương trình ngay lập tức.

⇒ Quan trọng trong quá trình debug và xử lí lỗi và assert sẽ báo chính xác vị trí lỗi trong source code là line nào.

Ví dụ sử dụng assert để báo lỗi:
```c
#define LOG(condition, cmd)     assert((condition) && #cmd)

double divide(double number_a, double number_b) {
    // assert( (number_b!=0) && "Divide for zero");
    LOG(number_b!=0, "Divide for zero");
    return number_a / number_b;
}

int main() {
	printf("%f\n", divide(4.0, 1.0));
	printf("%f\n", divide(4.0, 0.0));
}
```

</details>

# Bài 3: Pointer
<details>
<summary>nội dung</summary>

<h2>Pointer</h2>

**Pointer là biến có giá trị là địa chỉ của một biến khác. Thông qua con trỏ có thể truy cập đến để đọc hoặc thay đổi giá trị tại địa chỉ đó.**

* Mọi biến đều được lưu trên RAM trong quá trình thực thi chương trình và có địa chỉ riêng.

* Có thể dùng pointer để truy cập nhiều biến khác nhau giúp quá trình xử lí chương trình linh hoạt hơn.

**Kích thước của con trỏ phụ thuộc vào kiến trúc của vi xử lí.**

Ví dụ khai báo và sử dụng con trỏ:
```c
int number = 10;
int *ptr = &number;   // lấy địa chỉ của biến number gán cho con trỏ
*ptr = 100;           // thay đổi giá trị tại biến number = 100
```

<h2>Void Pointer</h2>

**Void Pointer là con trỏ có thể trỏ đến bất kì biến nào mà không cần biết trước kiểu dữ liệu của nó.**

* Tuy nhiên trước khi đọc hoặc thay đổi giá trị của biến được trỏ tới thì cần ép kiểu cho đúng với kiểu dữ liệu của biến đó.

Ví dụ khai báo Void pointer:
```c
int a = 100;
void *ptr = &a;
printf("%d\n", *(int *)a);
*(int *)ptr = 10;
```

<h2>NULL Pointer</h2>

**NULL Pointer là con trỏ có giá trị (địa chỉ trỏ tới) là 0x00.**

Khi khai báo một biến mới chương trình sẽ lấy một vùng nhớ chưa được sử dụng trên RAM để lưu biến. Nếu không gán giá trị khi khai báo thì giá trị của biến sẽ là một giá trị ngẫu nhiên đã được lưu tại địa chỉ này trước đó. 

⇒ Do đó khi khai báo con trỏ mà chưa gán địa chỉ cho nó thì gán NULL để tránh lỗi chương trình khi trỏ nhầm địa chỉ. (Khi không dùng nữa cũng gán NULL)

* Dùng con trỏ NULL có thể kiểm tra được con trỏ đã được khai báo địa chỉ hợp lệ hay chưa.

```c
void *ptr = NULL;
```

<h2>Pointer to Constant</h2>

**Pointer to constant là con trỏ chỉ cho phép đọc giá trị tại tại địa chỉ được trỏ đến mà không được phép thay đổi giá trị tại địa chỉ đó. Tuy nhiên có thể gán lại giá trị (địa chỉ trỏ đến) cho con trỏ.**

Ví dụ sử dụng pointer to constant:
```c
int number_a = 10;
int number_b = 5;
// có thể khai báo con trỏ theo một trong hai cách sau.
int const *ptr_const = &number_a;
// const int *ptr_const = &number_a;

// không thể thay đổi giá trị của biến được trỏ đến.
// *ptr_const = 5; => Lỗi
// tuy nhiên có thể thay đổi giá trị của con trỏ.
ptr_const = &number_b;
```

<h2>Constant Pointer</h2>

**Constant pointer là con trỏ được khởi tạo với giá trị (địa chỉ trỏ đến) không được phép thay đổi. Chỉ có thể đọc và thay đổi giá trị tại địa chỉ được trỏ đến.**

Ví dụ sử dụng constant pointer:
```c
int number_a = 10;
int number_b = 5;
int *const ptr_const = &number_a;

// có thể thay đổi giá trị tại number_a
*const_ptr = 7;

// tuy nhiên đã khởi tạo con trỏ trỏ đến địa chỉ của number_a thì không thể trỏ đến một biến khác nữa.
// ptr_const = &number_b; => chương trình báo lỗi
```

<h2>Pointer to Function</h2>

**Function pointer là con trỏ có giá trị là địa chỉ của một function.**

    ⇒ Trỏ đến vùng nhớ chứa function.

Ví dụ sử dụng pointer to function:

```c
/*
	khai báo ptr là con trỏ hàm có tham số truyền vào là (int, int)
và kiểu trả về là int.
	sử dụng con trỏ hàm để gọi hàm phù hợp theo điều kiện
*/

#define OPERATOR    SUM
// #define OPERATOR    MULTIPLE

int multiple(int number_a, int number_b) {
    return number_a * number_b;
}

int sum(int number_a, int number_b) {
    return number_a + number_b;
}

int main() {
    int (*ptr)(int, int) = NULL;

    #if OPERATOR == SUM
        ptr = &sum;
    #elif OPERATOR == MULTIPLE
        ptr = &multiple;
    #endif
    
    printf("%d\n", ptr(5, 10));
}
```
* Function pointer còn có thể dùng làm tham số truyền vào cho một function khác. 

    Ví dụ:
    ```c
    /*
        Tạo một function có tham số truyền vào là một con trỏ hàm và các tham số phụ.
        Sử dụng con trỏ để gọi hàm tính toán.
    */


    int multiple(int number_a, int number_b) {
        return number_a * number_b;
    }

    int sum(int number_a, int number_b) {
        return number_a + number_b;
    }

    int CalcAndShow(int (*ptr)(int, int), int number_a, int number_b) {
        int result = ptr(number_a, number_b);
        printf("%d\n", result);
        return result;
    }

    int main() {
        int a = 10, b = 4;
        int (*ptr)(int, int) = NULL;
        CalcAndShow(&multiple, a, b);
        CalcAndShow(&sum, a, b);
    }
    ```

Ép kiểu một con trỏ hàm:
```c
int sum(int number_a, int number_b) {
    return number_a + number_b;
}
...
void *ptr = &sum;
int result = ((int (*)(int, int))ptr)(5, 3);
```

<h2>Pointer to Pointer</h2>

**Pointer to Pointer là con trỏ có giá trị là địa chỉ của con trỏ khác (trỏ đến con trỏ khác).**

```c
/*
	Khai báo con trỏ ptr_1 trỏ tới biến point.
	Khai báo con trỏ ptr_2 trỏ tới ptr_1.
	In ra giá trị và địa chỉ của ptr_1 và ptr_2.
*/

double point = 9.2;
double *ptr_1 = &point;
double **ptr_2 = &ptr_1;

printf("&point : %lu\t- point = %.3f\n", &point, point);
printf("&ptr_1 : %lu\t- *ptr_1 = %.3f\n", &ptr_1, *ptr_1);

// con trỏ ptr_2 có giá trị là địa chỉ của ptr_1.
// ta cũng có thể trỏ với point qua ptr_2
printf("ptr_2 : %lu\t- *ptr_2 : %lu\t- **ptr_2 = %.3f\n", ptr_2, *ptr_2, **ptr_2);

/*
	Kết quả in ra
&point : 144701488      - point = 9.200
&ptr_1 : 144701480      - *ptr_1 = 9.200
ptr_2 : 144701480       - *ptr_2 : 144701488    - **ptr_2 = 9.200
*/
```

</details>

# Bài 4: Extern - Static - Volatile
<details>
<summary>nội dung</summary>

<h2>Extern</h2>

**Từ khóa extern dùng để khai báo một biến toàn cục hoặc hàm đã được định nghĩa (khai báo và cấp phát bộ nhớ) ở một file khác. Tức là có thể sử dụng biến toàn cục hoặc hàm của một file khác.**

- Khai báo một biến và gán giá trị cho nó thì nó phải nằm ở file source (.c).

Ví dụ khai báo và sử dụng một hàm và biến toàn cục ở một file source khác:

```c
/* scale.c */

#include "scale.h"

double scale_factor = 0.5;

double calcLength(double len) {
    return len*scale_factor;
}

```

```c
/* main.c */

#include <stdio.h>
// #include "sum.h" => ví dụ này không dùng include

// dùng từ khóa extern để báo đây là một biến toàn cục và một function đã được định nghĩa ở một file kkhác.
extern double scale_factor;
extern double calcLength(double len);

int main(void) {

    double obj_len = 10.0;
    // gọi hàm tính độ dài với scale factor được định nghĩa ở một file khác với.
    printf("Length: %.3f.\n", calcLength(obj_len));
    // do đã dùng từ khóa extern để khai báo scale_factor
	  // thay đổi giá trị scale_factor được định nghĩa file scale.c
	  // và tính lại độ dài một lần nữa với scale_factor vừa thay đổi.
    scale_factor = 2;
    printf("Length: %.3f.\n", calcLength(obj_len));

    return 0;
}

/* Kết quả in trên terminal
Length: 5.000.
Length: 20.000.
*/
```

## Static

### Biến static cục bộ

**Static local variables là những biến cục bộ được khai báo và cấp phát địa chỉ một lần duy nhất và chỉ thu hồi vùng nhớ của biến khi kết thúc chương trình.**

Local variables: biến cục bộ là biến được khai báo bên trong hàm chỉ có phạm vi sử dụng bên trong hàm.

Ứng dụng: 

- Sử dụng trong trường hợp cần giữ lại giá trị của biến trong các lần gọi hàm.
- Thực hiện khởi tạo cho hàm một lần duy nhất.

    Ví dụ sử dụng biến static cục bộ:
    
    ```c
    #include <stdio.h>
    
    void countObject() {
    		// biến counter sẽ được khai báo ở lần đầu tiên gọi hàm
    		// khi gọi những lần tiếp theo chương trình sẽ không khai báo lại 
    		// mà dùng sửa dụng lại vùng nhớ đã cấp phát trước đó.
    		// nên giá trị của biến counter sẽ được cộng lên ở mỗi lên gọi hàm
        static int counter = 0;
        printf("Add object %d.\n", ++counter);
    }
    
    int main(void) {
        countObject();
        countObject();
        countObject();
        countObject();
        countObject();
    }
    
    /* Kết quả in ra màn hình
    Add object 1.
    Add object 2.
    Add object 3.
    Add object 4.
    Add object 5.
    */
    ```
    
    ```c
    
    #include <stdio.h>
    #include <time.h>
    
    #define TIMER_INIT      0
    #define TIMER_RUN       1
    #define TIME_OUT        0
    
    /*
    function timer sửa dụng hai biến static cục bộ:
    state để kiểm tra trạng thái của timer, khởi tạo giá trị cho time_stamp khi timer bắt đầu chạy.
    time_stamp lưu giá trị clock để so sánh cho những lần gọi sau. Tính xem timer đã time out hay chưa.
    */
    int timer(int interval) {
        static clock_t time_stamp;
        static int state = TIMER_INIT;
    
        if (state == TIMER_INIT) {
            time_stamp = clock();
            state = TIMER_RUN;
        } else {
            if ((clock() - time_stamp) >= interval) {
                state = TIMER_INIT;
                return TIME_OUT;
            }
        }
        
        return TIMER_RUN;
    }
    
    int main(void) {
    
        int counter = 1;
        while (1) {
            if (timer(1000) == TIME_OUT) {
                printf("Time out.\n");
                if (counter == 5) {
                    break;
                }
                counter++;
            }
        }
    
        return 0;
    }
    ```
    

### Biến static toàn cục

**Static global variables là những biến toàn cục chỉ có thể sử dụng trong phạm vi của file chứa nó và không cho phép extern để file khác sử dụng.**

Global variables: 

- Biến toàn cục là biến được khai báo không nằm trong hàm nào.
- Không thể extern biến static toàn cục để sử dụng ở một file khác. (Tương tự với hàm static)
    
    ⇒ Có thể sử dụng biến hoặc hàm static ở một file khác thông qua function được định nghĩa ở chính file đó.
    

Ứng dụng: để hạn chế gọi hàm hoặc biến ở ngoài file chứa nó (Trong trường hợp thiết kế thư viện sẽ dùng với mục đích không cho phép người sử dụng gọi hàm hoặc biến không được phép truy cập làm ảnh hưởng kết quả của chương trình).

- Ví dụ sử dụng biến static toàn cục:
    - Khi viết một thư viện nhưng không muốn người sử dụng sử dụng các hàm tính toán trong đó hay thay đổi những biến trong đó ta sẽ định nghĩa nó ở dạng static.
    - Trong ví dụ này chỉ khai báo biến scale_factor và hàm calcLength trong file sum.c, ngoài file này ra không có file nào có thể sử dụng được biến và hàm này.
    - Người dùng chỉ có thể gọi được function showLength khi include file  sum.h
    
    ```c
    /* file name: sum.h */
    #ifndef SUM_H
    #define SUM_H
    
    #define OBJECT_1
    // #define OBJECT_2
    // #define OBJECT_3
    
    void showLength(double len);
    
    #endif
    ```
    
    ```c
    /* file name: sum.c */
    
    #include "sum.h"
    #include <stdio.h>
    
    #ifdef OBJECT_1
        #define _SCALE_FACTOR   0.5
    #elif OBJECT_2
        #define _SCALE_FACTOR   1.2
    #elif OBJECT_3
        #define _SCALE_FACTOR   0.8
    #else
        #define _SCALE_FACTOR   1.0
    #endif
    
    static double scale_factor = _SCALE_FACTOR;
    
    static double calcLength(double len) {
        return len*scale_factor;
    }
    
    void showLength(double len) {
        printf("Length: %.3f.\n", calcLength(len));
    }
    ```
    
    ```c
    /* file name: main.c */
    
    #include <stdio.h>
    #include "sum.h"
    
    int main(void) {
        double obj_len = 10.0;
        showLength(obj_len);
        return 0;
    }
    ```
    

Thắc mắc: Biến và hàm static toàn cục khi khai báo ở file header (.h) thì chỉ có thể sử dụng trong phạm vi file header. Nên thông thường người ta sẽ khai báo biến và hàm static toàn cục trong file source (.c) để có ghể gọi từ các hàm khác như trong ví dụ ở phía trên.

### Từ khóa register

<p align="center">
  <img src="https://github.com/user-attachments/assets/dcfa0002-01e9-4c82-9096-6b11ef19e123" width="90%">
</p>


ALU (Arithmetic Logic Unit) có nhiệm vụ các phép toán trong chương trình. Và ALU chỉ làm việc với thanh ghi.

Khi một biến được khai báo chương trình sẽ cấp phát bộ nhớ của biến đó tại một địa chỉ trên RAM.

Các bước vi xử lí thực hiện một phép toán:

- Chuyển giá trị tại vùng nhớ cần tính trên RAM vào register.
- ALU lấy giá trị trên register tính toán sau đó trả giá trị vào register.
- Register chuyển kết quả nhận được từ ALU vào lại RAM.

⇒ Tốc độ thực thi của chương trình phụ thuộc nhiều vào tốc độ truyền dự liệu của RAM.

**Từ khóa register sẽ báo cho compiler khai báo và cấp phát bộ nhớ của biến đó trên thanh ghi. Giúp giảm bước truyền nhận dữ liệu giữa RAM và Register nên chương trình thực sẽ thi nhanh hơn. Chỉ có thể sử dụng từ khóa register với những biến cục bộ.**

**Bộ nhớ của register ít và không thể mở rộng giới hạn được như RAM.**

Ứng dụng: khai báo các biến dùng thường xuyên và xử lí tính toán với những biến đó ưu tiên tốc độ.

Ví dụ sử dụng hai biến được định với từ khóa register và không có từ khóa register:
    
- Với từ khóa register biến index sẽ được khai báo và cấp phát bộ nhớ trong thanh ghi thay vì trên RAM.
        
    ⇒ Tốc độ thực thi hàm khi sử dụng register để khai báo biến index sẽ nhanh hơn.
        

    ```c
    #include <stdio.h>
    #include <time.h>
    
    void showTime() {
        clock_t time_start;
        time_start = clock();
    
        register unsigned long index;
        // unsigned long index;
        
        unsigned long number = 100000000;
    
        for(index=0;index<number;index++) {
    
        }
    
        printf("Execution time: %.5f\n", (double)((clock() - time_start)/1000.0));
    }
    
    int main(void) {
    
        showTime();
        
        return 0;
    }
    
    /* Output:
    Execution time: 0.22800 (without register)
    Execution time: 0.03500 (with register)
    */
    ```
    

Thắc mắc: Nếu biến được khai báo và cấp phát bộ nhớ trên thanh ghi của vi xử lí thì có thể dùng con trỏ để trỏ đến biến đó hay lấy địa chỉ như một biến thông thường được cấp phát bộ nhớ trên RAM hay không?

## Từ khóa Volatile

Vi điều khiển có bộ nhớ giới hạn, nên khi build chương trình compiler sẽ tối ưu bộ nhớ bằng các bỏ qua các biến không thay đổi giá trị trong quá trình chạy chương trình.

```c
int main() {
	while(1) {
		int number_a = 10;
		int number_b = read_number();
        number_a;
        number_b;
	}
}
```

Trong đoạn code phía trên khi compiler thấy biến cục bộ number_a không thay đổi giá trị phía bên trong while nên compiler sẽ tối ưu biến này. Tương tự với number_b, tuy được khai báo và gán giá trị là giá trị trả về của một hàm nhưng compiler vẫn sẽ tối ưu number_b.

**Từ khóa Volatile sẽ báo cho compiler không tối ưu biến đó.**

```c
volatile number_a = 10;
```

Ứng dụng:

- Khai báo volatile để tránh những lỗi chạy chương trình khi compiler tối ưu biến đó.
- Thường được sửa dụng nhiều trong RTOS. (Khi một biến toàn cục được thay đổi giá trị ở nhiều task khác nhau, dùng votatile để tránh compiler tối ưu biến đó bên trong một task)

</details>

# 5. Goto - Setjmp
<details>
<summary>nội dung</summary>

## Goto

**Từ khóa goto sẽ cho phép nhảy đến một label được đặt trong phạm vi của hàm gọi từ khóa goto.**

Các trường hợp ứng dụng goto:

- Thoát khỏi nhiều vòng lặp chồng lên nhau.
- Finite State Machines.
- Lập trình các ứng dụng menu, quét lét,…

    Ví dụ sử dụng goto để thoát ra khỏi 3 cấp vòng lặp, thay vì sử dụng break để thoát ra khỏi từng vòng lặp:
    
    ```c
    #include <stdio.h>
    
    int main(void) {
    
        while(1) {
            for(int col=0;col<10;col++) {
                for(int row=0;row<10;row++) {
                    if((col==5)&&(row==8)) {
                        goto exit_loops;
                    }
                    printf("Col: %d, Row: %d\n", col, row);
                }
            }
        }
    
        exit_loops:
    
        return 0;
    }
    ```
    

## Setjmp

**setjump là thư viện chuẩn của C, hỗ trợ macro setjmp và function longjmp.**

- Macro setjmp(BUF): thiết lập một vị trí trong chương trình mà khi gọi longjmp chương trình sẽ nhảy lệnh đó và trả về một giá trị.
    - BUF là tham số truyền vào có kiểu dữ liệu là jmp_buf.
    - Ở lần đầu tiên thực thi setjmp sẽ trả về giá trị 0.
    - Ở những lần thực thi tiếp theo setjmp sẽ trả về giá trị tương ứng với tham số thứ 2 của longjmp.
- Function longjmp(jmp_buf _Buf,int _Value): nhảy đến vị trị đã set của tham số đầu tiên và trả về giá trị của tham số thứ hai.

⇒ setjump thường được sử dụng cho xử lí ngoại lệ trong C.

- Ví dụ sử dụng setjmp và longjmp:
    - Ví dụ xử lí những ngoại lệ như truyền vào mảng không hợp lệ (size = 0) hoặc không nằm trong range.
    - Gọi marco setjmp trong main để thiết lập điểm nhảy tới khi gọi longjmp (xảy ra ngoại lệ).
    - Ở lần đầu tiên setjmp sẽ trả về 0, tức là exception_code có giá trị là 0, tương ứng với case ERR_NONE ⇒ Chạy function xử lí mảng.
    - Nếu những điều kiện đặt ra không thỏa mãn như mảng có độ dài = 0, hoặc giá trị phần tử vượt ngoài range thì longjump sẽ được gọi và truyền vào giá trị lỗi tương tứng ở tham số thứ 2. ⇒ chương trình sẽ qua lại chỗ setjump và lúc này exception_code mang một giá trị khác.
    - Những case lỗi (ERR_ARRAY_SIZE, ERR_OUT_RANGE) là nơi sẽ thực hiện xử lí khi có ngoại lệ xảy ra.
    - Trong trường hợp phát hiện ra lỗi, ngoại lệ vẫn có thể chạy tiếp các lệnh khác ở phía dưới.
    
    ```c
    #include <stdio.h>
    #include <setjmp.h>
    
    #define ERR_NONE            0
    #define ERR_ARRAY_SIZE      1
    #define ERR_OUT_RANGE       2
    
    #define VAL_MIN             0
    #define VAL_MAX             10
    
    jmp_buf buf;
    int exception_code;
    
    void checkOutRange(int value) {
        if ((value < VAL_MIN)  || (value > VAL_MAX)) {
            longjmp(buf, ERR_OUT_RANGE);
        }
    }
    
    void arrayProcess(int *const arr, int size) {
        if (size <= 0 ) {
            longjmp(buf, ERR_ARRAY_SIZE);
        }
    
        for(int index=0;index<size;index++) {
            checkOutRange(*(arr+index));
            printf("Number at <index>: %d.\n", *(arr+index));
        }
    }
    
    int main(void) {
    
        int num_list[] = { 0, 2, 4, 5, 6, 3, 12};
        int list_size = sizeof(num_list)/sizeof(int);
    
        exception_code = setjmp(buf);
    
        switch (exception_code) {
            case ERR_NONE:
                arrayProcess(num_list, list_size);
    		        // arrayProcess(num_list, 0);
                break;
            case ERR_ARRAY_SIZE:
                printf("Input Array invalid...\n");
                break;
            case ERR_OUT_RANGE:
                printf("Value out of range...\n");
                break;
        }
    
    		printf("Handle another features...\n");
        return 0;
    }
    ```

</details>

# Bài 6: Bitmask
<details>
<summary>nội dung</summary>

**Bitmask là một kỹ thuật lập trình, sử dụng các toán tử bitwise để thao tác hoặc lưu trữ thông tin với đơn vị bit.**

Ứng dụng: Tối ưu hóa bộ nhớ sử dụng, quản lí thuộc tính của đối tượng,…

## Các toán tử bitwise:

### AND

**Toán tử AND ( & ) sẽ thực hiện phép AND Logic cho từng cặp bit của hai giá trị cần thực hiện phép toán.**

| Input 1 | Input 2 | Output |
| --- | --- | --- |
| 0 | 0 | 0 |
| 0 | 1 | 0 |
| 1 | 0 | 0 |
| 1 | 1 | 1 |

⇒ Chỉ khi bit input 1 và bit input 2 đều là 1 thì kết quả mới là 1.

Ví dụ:

```c
uint8_t input_1 = 0b01001100;
uint8_t input_2 = 0b00101100;
uint8_t output  = input_1 & input_2;
/*   => output  = 0b00001100  */
```

### OR

**Toán tử OR ( | ) sẽ thực hiện phép OR Logic cho từng cặp bit của hai giá trị cần thực hiện phép toán.**

| Input 1 | Input 2 | Output |
| --- | --- | --- |
| 0 | 0 | 0 |
| 0 | 1 | 1 |
| 1 | 0 | 1 |
| 1 | 1 | 1 |

⇒ Chỉ cần tối thiểu 1 trong hai bit input là 1 thì kết quả là 1.

Ví dụ: 

```c
uint8_t input_1 = 0b01001100;
uint8_t input_2 = 0b00101100;
uint8_t output  = input_1 | input_2;
/*   => output  = 0b01101100  */
```

### XOR

**Toán tử XOR ( ^ ) sẽ thực hiện phép XOR Logic cho từng cặp bit của hai giá trị cần thực hiện phép toán.**

| Input 1 | Input 2 | Output |
| --- | --- | --- |
| 0 | 0 | 0 |
| 0 | 1 | 1 |
| 1 | 0 | 1 |
| 1 | 1 | 0 |

⇒ Nếu một cả hai bit input cùng là 0 hoặc cùng là 1 thì kết quả sẽ là 0. Ngược lại chỉ có 1 trong hai input là 1 là kết quả là 1.

```c
uint8_t input_1 = 0b01001100;
uint8_t input_2 = 0b00101100;
uint8_t output  = input_1 ^ input_2;
/*   => output  = 0b01100000  */
```

### NOT

**Toán tử NOT ( ~ )  sẽ thực hiện phép NOT Logic, đảo ngược giá trị của bit.**

```c
uint8_t input  = 0b01001100;
uint8_t output = ~input;
/*   => output = 0b10110011  */
```

### Shift left - Shift right

**Shift left ( << ) là toán tử dịch bit sang trái, các bit được chèn vào phía bên phải sẽ là 0.**

```c
uint8_t input  = 0b00000001;
uint8_t output = input << 2;
/*   => output = 0b00000100  */
output = input << 5;
/*   => output = 0b00100000  */
```

**Shift right ( >> ) là toán tử dịch bit sang phải, các bit được chèn vào phía bên trái sẽ là 0.**

```c
uint8_t input  = 0b10000001;
uint8_t output = input >> 2;
/*   => output = 0b00100000  */
output = input >> 5;
/*   => output = 0b00000100  */
```

- Ví dụ sử dụng bitmask:
    - Sử dụng bitmask để thay đổi giá trị tại một bit chỉ định mà vẫn giữ nguyên giá trị cho các bit còn lại.
    - Sử dụng bitmask để đọc ra giá trị của từng bit.
    
    ```c
    #include <stdio.h>
    #include <stdint.h>
    
    uint8_t port_State = 0;
    
    void portWrite(uint8_t pin_number, uint8_t value) {
        if(value == 0) {
            port_State &= ~(1 << pin_number);
        } else if (value == 1) {
            port_State |= (1 << pin_number);
        }
    }
    
    char *const showBinary(uint8_t value) {
        static char bin[9];
    
        for(int index=0;index<8;index++) {
            uint8_t single_bit = (value >> index) & 1;
            bin[7-index] = ((single_bit == 0) ? '0' : '1');
        }
    
        return bin;
    }
    
    int main(void) {
        // printf("0b%s", showBinary(0b00100));
    
        printf("%s\n", showBinary(port_State));
        portWrite(0, 1);
        printf("%s\n", showBinary(port_State));
        portWrite(2, 1);
        printf("%s\n", showBinary(port_State));
        portWrite(7, 1);
        printf("%s\n", showBinary(port_State));
        portWrite(0, 0);
        printf("%s\n", showBinary(port_State));
        portWrite(7, 0);
        printf("%s\n", showBinary(port_State));
        
        return 0;
    }
    ```
    

### Bit fields

**Bit fields trong struct giúp tối ưu bộ nhớ khi khai báo và sử dụng một struct bằng cách xác định số bit sẽ dùng để lưu một phần tử trong struct.**

- Ví dụ sử dụng Bit fields 1:
    
    ```c
    typedef struct {
        uint8_t bit_0 : 1;
        uint8_t bit_1 : 1;
        uint8_t bit_2 : 1;
        uint8_t bit_3 : 1;
        uint8_t bit_4 : 1;
        uint8_t bit_5 : 1;
        uint8_t bit_6 : 1;
        uint8_t bit_7 : 1;
    } GPIO_PORT;
    ```
    
    Như ví dụ ở trên, struct có tên GPIO_PORT có 8 phần tử kiểu uint8_t, tuy nhiên mỗi phần tử chỉ sử dụng 1 bit để lưu giá trị thay vì 1 byte. Nên struct này chỉ chiếm 1 byte bộ nhớ.
    
- Ví dụ sử dụng Bit fields 2:
    
    ```c
    typedef struct {
        uint8_t feature_1 : 4;
        uint8_t feature_2 : 4;
        uint8_t feature_3 : 1;
    } Features;
    ```
    
    Như ví dụ ở trên feature_3 sử dụng 1 bit, nhưng hai phần tử trước đó đã đủ 8 bit, nên lúc này struct Features sẽ chiếm 2 byte bộ nhớ.
    
    Với feature_3 chỉ chiếm 1 bit để lưu trữ lên khi chỉ có thể gán 0b1 hoặc 0b0 nếu gán giá trị lớn hơn (ví dụ: 0b10) sẽ làm mất dữ liệu do 1 bit không thể lưu hết.

</details>

# Bài 7. Struct - Union

<details> 
<summary>nội dung</summary>

# 7. Struct - Union

## Struct

**Struct là cấu trúc dữ liệu chứa nhiều biến member do người lập trình định nghĩa, mỗi member có một vùng nhớ riêng.**

Sử dụng struct:

```c
struct Car{
    char name[50];
    double maxSpeed;
    double maxAccel;
    int seats;
};

// Khai báo một struct và dữ liệu
struct Car myCar = {.name = "Honda", .maxSpeed = 200.0, .maxAccel = 500.0, .seats = 4};
// truy cập đến struct member
myCar.maxSpeed = 150.0;
struct Car* ptr = &myCar;
// con trỏ truy cập đến struct member
ptr->seats = 6;
```

Sử dụng từ khóa typedef thêm tên cho struct để rút gọn cú pháp khai báo biến:

```c
typedef struct {
    char name[50];
    double maxSpeed;
    double maxAccel;
    int seats;
} Car;

Car myCar = {.name = "Honda", .maxSpeed = 200.0, .maxAccel = 500.0, .seats = 4};
```

### Padding của Struct:

Cách sắp xếp vùng nhớ của struct:

```c
typedef struct {
    uint8_t member_1;
    uint32_t member_2;
    uint16_t member_3;
} struct_1;
```

![struct_padding.svg](https://prod-files-secure.s3.us-west-2.amazonaws.com/12f85233-d251-4641-9068-58727ed3c3fb/73b908d7-c020-462c-be40-dcf7e300baf5/struct_padding.svg)

struct_1 mặc dùng tổng size của ba phần tử là 7 byte tuy nhiên struct_1 có kích thước là 12 byte:

- compiler sẽ chọn kích thước của phần tử lớn nhất để làm tham chiếu sắp xếp vị trí cho các phần tử còn lại.
- struct_1 sẽ chọn kích thước 4 làm bội số và một phần tử sẽ hoàn toàn đặt trong một vùng nhớ 4 byte.
- member_1 là phần tử đầu tiên, có kích thước là 1 byte, giả sử địa chỉ bắt đầu của biến struct này là 0xF0. member 1 sẽ đặt ở 0xF0.
- member_2 có kích thước là 4 byte và nếu đặt vào địa chỉ 0xF1 sẽ thừa ra 1 byte (tại 0xF4) vào vùng nhớ 4 byte kế tiếp. Nên member_2 sẽ bắt đầu từ 0xF4 và 3 byte không được sử dụng trong vùng nhớ 4 byte đầu tiên gọi là padding.
- Tương tự member_3 sẽ bắt đầu từ địa chỉ 0xF8 và 2 byte còn lại là padding.
    
    ⇒ Kích thước của struct sẽ là 7 byte + 5 byte padding = 12 byte.
    

```c
typedef struct {
    uint8_t member_1;
    uint16_t member_2;
    uint32_t member_3;
} struct_2;
```

![struct_padding_2.svg](https://prod-files-secure.s3.us-west-2.amazonaws.com/12f85233-d251-4641-9068-58727ed3c3fb/98857ad8-b0b1-40de-949b-a68be412e382/struct_padding_2.svg)

struct_2 có kích thước là 8 byte trong đó có 1 byte padding.

Ứng dụng nhiều trong xử lí json và list.

### Union

**Union là cấu trúc dữ liệu mà tất cả member đều sử dụng chung 1 vùng nhớ và có địa chỉ bắt đầu giống nhau.**

Ví dụ:

```c
typedef union {
    uint8_t member_1;
    uint16_t member_2;
    uint32_t member_3;
} union_1;

union_1 myUnion;
myUnion.member_3 = 1048574;
/*
member_3 = 1048574
member_2 = 65534
member_1 = 254
*/
```

![union_memory.svg](https://prod-files-secure.s3.us-west-2.amazonaws.com/12f85233-d251-4641-9068-58727ed3c3fb/9506489f-5187-4daa-91e9-e216d11f8d05/union_memory.svg)

Do tất cả member của union đều dùng chung vùng nhớ và có cùng địa chỉ bắt đầu nên khi gán giá trị cho member_3 như ví dụ ở trên thì thực chất cũng là thay đổi giá trị của member_1 và member _2.

member_1 chỉ chiếm 1 byte tính từ địa chỉ bắt đầu nên giá trị member_1 là giá trị tại byte đầu tiên của member_3. Tương tụ với member_2.

Kích thước của Union:
    
- Kích thước của một union là kích thước của member lớn nhất cộng với tổng số padding.
    
    ```c
    typedef union {
        uint8_t member_1[1];
        uint16_t member_2[5];
        uint32_t member_3[2];
    } union_1;
    
    /*
    	Kích thước của union_1 là 12
    	Do uint32_t là kiểu dự liệu có size lớn nhất trong union, nên 4 byte sẽ được tính là bội số.
    	member_2 là phần tử có kích thước lớn nhất, 10 byte, tuy nhiên với bội số 4 thì vùng nhớ 4 byte cuối cùng sẽ gồm 2 byte của member_2 và 2 byte padding.
    */
    
    typedef union {
        uint8_t member_1[13];
        uint16_t member_2[5];
        uint32_t member_3[2];
    } union_2;
    
    /*
    	Kích thước của union_2 là 16
    	member 1 có kích thước lớn nhất 13 byte, tuy nhiên với bội số 4 thì vùng nhớ 4 byte cuối cùng sẽ gồm 1 byte của member_1 và 3 byte padding.
    */
    ```
    
Ứng dụng của Union và Struct trong embedded:
    
```c
typedef union {
    struct {
        uint8_t id[2];
        uint8_t data[4];
        uint8_t check_sum[2];
    } data;
    
    uint8_t frame[8];
} DataFrame;

int main(void) {
    DataFrame transmitter_data;
    DataFrame receiver_data;

    strcpy(transmitter_data.data.id, "10");
    strcpy(transmitter_data.data.data, "1234");
    strcpy(transmitter_data.data.check_sum, "70");
    
    strcpy(receiver_data.frame, transmitter_data.frame);

    return 0;
}
```
    
- data và frame dùng chung vùng nhớ.
- Khi muốn thay đổi thành phần của frame truyền đi sẽ thay đổi giá trị các member của data.
- Khi truyền từng byte dữ liệu đi sẽ dùng member frame.

⇒ Khi sử dụng struct và union thường sẽ thiết kế các member để không có padding.

</details>
