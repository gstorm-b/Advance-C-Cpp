**[Trình bày bài học trên Notion](https://ritzy-tray-c64.notion.site/Advance-C-CPP-1340b8981c614ba29eb68631e6479064)**

# Bài 1: Compiler - Macro
## Compiler
**Compiler là trình biên dịch chuyển từ source code sang mã máy.**

Các bước trong quá trình biên dịch:
1. Preprocessing: quá trình tiền xử lí tạo ra file source có định dạng ‘*.i”. Nếu có include thì copy nội dung từ file được include sang. Xóa bỏ comment nếu có. Copy nội dung của macro được định nghĩa vào chỗ gọi.
2. Compilation: từ file được tạo ra sau tiền xử lí Compiler sẽ chuyển tất cả nội dung đó sang code assembly. (định dạng “*.s”)
3. Assemble: tạo ra object file  (định dạng *.o). File object chứa địa chỉ và giá trị tại địa chỉ đó.
4. Linking: Link các file object lại với nhau và tạo ra file mã máy. Nếu include header thì trong quá tiền xử lí chỉ có các tên hàm trong source do đó cần link các file object chứa nội dung của các header đó.
## Macro
**Macro là một đoạn code để chỉ thị compiler thay thế nội dung được định nghĩa trước tại vị trí gọi macro đó trong quá trình tiền xử lí (preprocessing).**

Các chỉ thị tiền xử lí:
* #include: toàn bộ nội dung của file được include sẽ được copy vào file tiền xử lí (định dạng *.i).
    
* #define: dùng để định nghĩa một macro. Có thể định nghĩa một hằng số, một function, hoặc biến.
    
* #undef: dùng để hủy label đã được định nghĩa là macro trước đó. Sau đó có thể định nghĩa lại để sử dụng cho mục đích khác nếu cần.
    
* #if, #elif, #else: là những chỉ thị điều kiện để quyết định xem có thêm những nội dung bên trong điều kiện vào file tiền xử lí hay không. Kết thúc chỉ thị điều kiện này là #endif.
    
* #ifdef và ifndef: là chỉ thị điều kiện đã định nghĩa label đó hay chưa. Nếu điều kiện đúng thì nội dung bên trong điều kiện được thêm vào file tiền xử lí. Kết thúc chỉ thị điều kiện là #endif.

Một số toán tử của Macro:
* #: để định nghĩa đó là một chuỗi (stringize).
```
#define MSG(msg)            #msg
...
printf("%s", MSG(Hello world));
```
* ##: để định nghĩa tên biến.
```
#define DEC_VAR(number)     int var_##number
DEC_VAR(2);
```
* Variadic macro: tạo ra Macro có thể nhận số lượng tham số truyền vào và kiểu dữ liệu không xác định.
```
#define NUM_LIST(...)                       \
int sum_list[] = {__VA_ARGS__}
// khai báo trong file main.c
NUM_LIST(1, 4, 5, 6);
// kết quả sau tiền xử lí
int sum_list[] = {1, 4, 5, 6};
```

Ví dụ tạo Macro định nghĩa một function.
```
#define CREATE_FUNC(func, cmd)              \
void func() {                               \
    printf(#cmd);                           \
    printf("\n");                           \
}
```
Ví dụ tạo Macro định nghĩa nhiều biến.
```
#define CREATE_VAR(name)                    \
int int_##name;                             \
double double_##name;                       \
char char_##name;                           
```

# Bài 2: STDARG - ASSERT
## STDARG
**STDARG là thư viện chuẩn của C hỗ trợ tạo function với số lượng tham số và kiểu dữ liệu không xác định trước.**

Các Macro được định nghĩa trong thư viện:
- va_list: là kiểu dự liệu sử dụng cho 3 macro còn lại (Cấp phát một vùng nhớ để sử dụng cho va_start và va_arg).
- va_start: khởi tạo điểm bắt đầu của list tham số. Điểm bắt đầu là label phía sau label được khởi tạo. Gọi trước va_start trước khi gọi va_arg.
- va_arg: trả về giá trị của label hiện tại trong list tham số. Ở lần gọi kế tiếp thì giá trị nhận được là của tham số tiếp theo phía sau nó.
- va_end: giải phóng vùng nhớ đã tạo ra từ va_list. Cần gọi khi không còn sử dụng va_list đó nữa.
## ASSERT
 
**ASSERT là thư viên chuẩn của C hỗ trợ báo lỗi chương trình.**

**Macro assert(_Expression) có tham số truyền vào là điều kiện báo lỗi và chuỗi kí tự thông báo khi có lỗi xảy ra.**
* Nếu điều kiện đúng chương trình sẽ chạy tiếp mà không báo lỗi.
* Nếu điều kiện sai chương trình sẽ báo lỗi với chuỗi kí tự đã định nghĩa trước và dừng chương trình ngay lập tức.

Ví dụ dùng assert để kiểm tra điều kiện:
```
#define MAX_RANGE       20
#define MIN_RANGE       0
#define ASSERT_RANGE(val, msg)      \
assert(((val >= MIN_RANGE) && (val <= MAX_RANGE)) && #msg)
```
Ngoài ra cũng có thể định nghĩa một macro tiện cho tiên debug:
```
#define LOG(condition, msg)         \
assert(condition && #msg)
```

# Bài 3: Pointer
<details>
<summary>nội dung</summary>

<h2>Pointer</h2>

**Pointer là biến có giá trị là địa chỉ của một biến khác. Thông qua con trỏ có thể truy cập đến để đọc hoặc thay đổi giá trị tại địa chỉ đó.**

* Mọi biến đều được lưu trên RAM trong quá trình thực thi chương trình và có địa chỉ riêng.

* Có thể dùng pointer để truy cập nhiều biến khác nhau giúp quá trình xử lí chương trình linh hoạt hơn.

**Kích thước của con trỏ phụ thuộc vào kiến trúc của vi xử lí.**

Ví dụ khai báo và sử dụng con trỏ:
```
int number = 10;
int *ptr = &number;   // lấy địa chỉ của biến number gán cho con trỏ
*ptr = 100;           // thay đổi giá trị tại biến number = 100
```

<h2>Void Pointer</h2>

**Void Pointer là con trỏ có thể trỏ đến bất kì biến nào mà không cần biết trước kiểu dữ liệu của nó.**

* Tuy nhiên trước khi đọc hoặc thay đổi giá trị của biến được trỏ tới thì cần ép kiểu cho đúng với kiểu dữ liệu của biến đó.

Ví dụ khai báo Void pointer:
```
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

```
void *ptr = NULL;
```

<h2>Pointer to Constant</h2>

**Pointer to constant là con trỏ chỉ cho phép đọc giá trị tại tại địa chỉ được trỏ đến mà không được phép thay đổi giá trị tại địa chỉ đó. Tuy nhiên có thể gán lại giá trị (địa chỉ trỏ đến) cho con trỏ.**

Ví dụ sử dụng pointer to constant:
```
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
```
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

```
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
    ```
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
```
int sum(int number_a, int number_b) {
    return number_a + number_b;
}
...
void *ptr = &sum;
int result = ((int (*)(int, int))ptr)(5, 3);
```

<h2>Pointer to Pointer</h2>

**Pointer to Pointer là con trỏ có giá trị là địa chỉ của con trỏ khác (trỏ đến con trỏ khác).**

```
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
