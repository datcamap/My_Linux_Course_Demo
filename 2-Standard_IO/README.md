# **Standard I/O**

### Buffer Overflow 

Giới hạn số lượng ký tự nhập vào buffer

>
    char name[10];
    scanf("%s", name);

- Trong đoạn code trên, nếu nhập vào trên 10 ký tự thì chương trình sẽ báo lỗi " stack smashing detected "
- Có thể thêm giới hạn 10 cho format specifier để tránh việc nhập quá nhiều ký tự vào buffer

>
    char name[10];
    scanf("%10s", name);

- Trong ví dụ dưới đây, hàm sprintf() đang cố ghi một chuỗi dài hơn 5 vào bộ đệm outbuffer, khi chạy cũng sẽ phát sinh lỗi " stack smashing detected "

>
    uint8_t outbuffer[5] = {};
    sprintf(outbuffer,"This_is_a_very_long_text \n\r");
    printf("%s", outbuffer);

- Giải pháp ở đây là luôn sử dụng hàm snprintf() thay cho sprintf() vì snprintf() nhận vào thêm 1 tham số là kích thước tối đa được phép ghi vào bộ đệm
>
    snprintf(outbuffer, sizeof(outbuffer), "This_is_a_very_long_text \n\r");

### Thư viện <stdarg.h>

- Dùng để tạo hàm với danh sách đối số thay đổi
- va_list: là kiểu dữ liệu chứa danh sách các đối số
- va_start(va_list, [last_arg]): khởi tạo danh sách đối số, [last_arg] là tên của đổi số cuối cùng trước khi khởi tạo danh sách
- va_arg(va_list, type) : lấy ra đối số tiếp theo trong danh sách
- va_end(va_list): dọn dẹp danh sách

- các node trong va_list sẽ bị thay đổi sau khi sử dụng, vậy nên nếu muốn dùng lại va_list nhiều lần thì cần phải copy 1 bản backup bằng hàm va_copy()

### I/O bufferring

- Giảm thiểu số lần gọi các system call (các hàm tương tác trực tiếp với phần cứng hoặc hệ điều hành)
- Mỗi lần gọi system call thì hệ thống phải chuyển giữa không gian user và không gian kernel, thực hiện nhiều lần chuyển đổi này sẽ dẫn đến việc tốn kém tài nguyên
- Giảm số lần giao tiếp trực tiếp với phần cứng cũng sẽ tăng tuổi thọ cho phần cứng
- Kiểm soát kích thước của buffer trước khi gọi ra các hàm system call

>
    int setvbuf(FILE *stream,char *buffer,int mode, size_t size);

- stream: con trỏ file
- buffer: con trỏ đến bộ đệm
- mode: 
    - _IOFBF: Full Buffering
    - _IOLBF: Line Buffering
    - _IONBF: No Buffering
- size: kích thước của bộ đệm

- Ngoài ra nên sử dụng các hàm fread(), fwrite() để đọc và ghi theo block

### Stack canary

- " stack samshing detected " là một cơ chế bảo vệ quan trọng được tích hợp vào các trình biên dịch
- Cấu trúc 1 stack frame từ địa chỉ cao xuống thấp:
    - Địa chỉ trả về
    - Con trỏ Frame cũ
    - Các biến cục bộ
- Cấu trúc 1 stack frame có tích hợp Stack Canary:
    - Địa chỉ trả về
    - Stack Canary: một giá trị ngẫu nhiên bí mật
    - Con trỏ frame cũ
    - Các biến cục bộ

#### Cơ chế hoạt động
- Khởi tạo hàm: giá trị canary ngẫu nhiên được lấy từ một vùng nhớ bí mật và đặt lên stack
- Thực thi hàm
- Nếu có lỗi tràn bộ đệm, chuỗi đầu vào sẽ lấp đầy buffer, ghi đè lên các biến khác và ghi đè lên Stack Canary
- Kết thúc hàm: trước khi thực hiện lệnh ret (quay về địa chỉ trả về), một đoạn mã kiểm tra được thực thi để so sánh giá trị Cannery hiện tại với giá trị bí mật ban đầu:
    - Hai giá trị khớp nhau → Kết thúc bình thường
    - Hai giá trị không khớp → Dừng chương trình và in ra " stack smashing detected "
