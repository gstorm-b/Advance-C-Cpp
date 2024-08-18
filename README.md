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

# Bài 3: POINTER
### Pointer

**Mọi biến đều được lưu trên RAM trong quá trình thực thi chương trình và có địa chỉ riêng.**

**Pointer là biến có giá trị là địa chỉ của một biến khác. Thông qua con trỏ có thể truy cập đến để đọc hoặc thay đổi giá trị tại địa chỉ đó.**

Cú pháp khai báo con trỏ:
* Dùng toán tử * để khai báo con trỏ.
* Toán tử & đứng trước tên biến để lấy địa chỉ của biến đó.
```
int number = 10;
int *ptr = &number;
*ptr = 100; // Number = 100
```
**Con trỏ NULL: là con trỏ có giá trị là 0 (Trỏ đến địa chỉ 0).**
* Khi khai báo một biến mới chương trình sẽ lấy một vùng nhớ chưa được sử dụng trên RAM để lưu biến. Nếu không gán giá trị khi khai báo thì giá trị của biến sẽ là một giá trị ngẫu nhiên đã được lưu tại địa chỉ này trước đó. Do đó khi khai báo con trỏ mà chưa gán địa chỉ cho nó thì gán NULL để tránh truy cập đến một ô nhớ khác làm ảnh hưởng chương trình.

**Kích thước của con trỏ phụ thuộc vào kiến trúc của vi xử lí.**

**Con trỏ VOID: là con trỏ có thể trỏ tới một địa chỉ bất kì mà không cần biết trước kiểu dữ liệu của biến được trỏ tới. Tuy nhiên khi đọc hoặc thay đổi giá trị của biến đó phải ép kiểu con trỏ đúng với kiểu dữ liệu của biến.**
```
int a = 100;
void *ptr = &a;
printf("%d\n", *(int *)a);
*(int *)ptr = 10;
```

### POINTER TO CONSTANT

**Pointer to constant là con trỏ chỉ cho phép đọc giá trị tại tại địa chỉ được trỏ đến mà không được phép thay đổi giá trị tại địa chỉ đó. Tuy nhiên có thể gán lại giá trị(địa chỉ trỏ đến) cho con trỏ.**
```
int const *ptr_const;
const int *ptr_const;
```

### CONSTANT POINTER:
**Constant pointer là con trỏ được khởi tạo với giá trị(địa chỉ trỏ đến) không được phép thay đổi. Chỉ có thể đọc và thay đổi giá trị tại địa chỉ được trỏ đến.**
```
int *const const_ptr = &a;
```

### FUNCTION POINTER
**Function pointer là con trỏ có giá trị là địa chỉ của một function.**

Ví dụ khai báo function pointer:
```
int multiple(int number_a, int number_b) {
    return number_a * number_b;
}
...
int (*ptr)(int, int);
ptr = &multiple;
int result = ptr(5, 3);
printf("%d\n", ptr(5, 3));
```
Ép kiểu cho con trỏ:
```
int sum(int number_a, int number_b) {
    return number_a + number_b;
}
...
void *ptr = &sum;
int result = ((int (*)(int, int))ptr)(5, 3);
```
