**[Trình bày bài học trên Notion](https://ritzy-tray-c64.notion.site/Advance-C-CPP-1340b8981c614ba29eb68631e6479064)**

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
    * Chèn nội dung được định nghĩa cua macro tại vị trí gọi macro đó.

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
* Còn khi định nghĩa macro thì khi biên dịch compiler sẽ thay thế đoạn macro được định nghĩa tại vị trí gọi macro đó. Khi gọi nhiều lần sẽ có nhiều đoạn giống nhau trong main memory.
    
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
