# Bài 1: Compiler - Macro
## Compiler
**Compiler là trình biên dịch chuyển từ source code sang mã máy.**

Các bước trong quá trình biên dịch:
1. Preprocessing: quá trình tiền xử lí tạo ra file source có định dạng ‘*.i”. Nếu có include thì copy nội dung từ file được include sang. Xóa bỏ comment nếu có. Copy nội dung của macro được định nghĩa vào chỗ gọi.
2. Compilation: từ file được tạo ra sau tiền xử lí. Compiler sẽ chuyển tất cả nội dung đó sang code assembly. (định dạng “*.s”)
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
# Bài 2: STDARG - ASSERT
