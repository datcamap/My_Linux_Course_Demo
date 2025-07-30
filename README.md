
# **Linux Embedded Notebook**

## **Bài 4: Memory layout & static keyword**

![Memory layout of C/C++ program!](./Memory%20layout.png "Memory layout of C/C++ program")

### Text Segment:

- Chứa các chỉ thị để CPU thực thi
- Read-only
- Kích thước cố định tại thời điểm compile
- Có thể chia sẻ: Nếu chạy nhiều bản sao của 1 chương trình thì hệ điều hành chỉ cần nạp 1 lần vào vùng .text trên RAM

### Intialized data Segment:

- Chứa các biến global và các biến static được khởi tạo khác 0
- Read-Write
- Life time: trong suốt vòng đời của chương trình
- Giá trị khởi tạo được lưu trong file thực thi, khi chương trình chạy thì giá trị được OS load vào vùng .data trên RAM

### Unintialized data Segment:

- Chứa các biến global và các biến static được khởi tạo = 0 hoặc là không được khởi tạo
- Read-Write
- Life time: trong suốt vòng đời của chương trình
- Tác dụng  là tối ưu kích thước của file thực thi. Thay vì lưu một lượng lớn các số 0 trong file thực thi, linker chỉ ghi lại kích thước mà vùng nhớ này sẽ chiếm dụng và khi chương trình chạy thì OS sẽ khởi tạo vùng nhớ này bằng 0.

### Heap Segment:

- Dùng để cấp phát bộ nhớ động bằng các hàm như malloc(),...
- Vùng heap có thể thay đổi kích thước khi chương trình đang chạy, mở rộng từ địa chỉ thấp lên cao, giới hạn là program break
- Khi lập trình cần phải quản lý việc cấp phát và xoá vùng nhớ bằng cách thủ công, nếu không có thể gây ra hiện tượng Memory leak (mất thông tin về phần bộ nhớ được cấp phát)

### Stack Segment:

- Gồm các stack frame được tạo ra khi gọi hàm
- LIFO (Last in, First out)
- Cấp phát và giải phóng bộ nhớ trên Stack chỉ đơn giản là thay đổi giá trị của con trỏ Stack pointer nên truy cập vào stack rất nhanh
- Khi có stack frame mới được thêm vào thì giá trị của stack pointer sẽ giảm xuống, sau khi hàm kết thúc thì stack pointer lại trở về vị trí trước khi thêm stack frame
- Kích thước cố định và giới hạn, nếu có quá nhiều stack frame sẽ gây ra hiện tượng Stack overflow

## **Bài 5: Biến và kiểu dữ liệu tự định nghĩa**

- Declaration (khai báo): Thông báo cho compiler về sự tồn tại của biến hoặc hàm (function prototype)
- Definition (định nghĩa): Cấp phát bộ nhớ cho biến bằng việc khởi tạo giá trị, hoặc là cung cấp mã thực thi cho hàm (phần thân hàm)

### Extern keyword:

- Khai báo rằng biến hoặc hàm đã được định nghĩa ở một nơi khác
- Hàm được khai báo thì sẽ mặc định được coi như có từ khoá extern

> int Add (int a, int b);

và

> extern int Add (int a, int b); 

đều có nghĩa như nhau đối với compiler

### Volatile keyword:

- Đây là type qualifier có tác dụng thông báo cho compiler rằng biến được khai báo có thể thay đổi giá trị bởi tác nhân nằm ngoài đoạn code đang thực thi
- Thêm keyword này nhằm tránh việc compiler có thể tối ưu hoá code khiến cho logic bị sai

*Một số trường hợp cần sử dụng volatile:*

- Truy cập thanh ghi phần cứng: giá trị của thanh ghi có thể bị thay đổi bởi phần cứng bất kỳ lúc nào
- Giá trị biến bị thay đổi khi xuất hiện interrupt: ISR có thể được gọi bất kỳ lúc nào
- Biến được chia sẻ giữa các luồng (Thread)

### Register keyword:
- Gợi ý cho compiler rằng 1 biến được sử dụng lặp lại nhiều lần để compiler lưu biến vào thanh ghi của CPU thay vì lưu vào RAM giúp tăng tốc độ truy cập biến

### Bytes order

- Little Endian: các bytes có trọng số nhỏ nhất nằm ở ô nhớ có địa chỉ nhỏ nhất, các bytes có trọng số lớn nhất nằm ở ô nhớ có địa chỉ lớn nhất
- Big Endian: các bytes có trọng số lớn nhất nằm ở ô nhớ có địa chỉ nhỏ nhất, các bytes có trọng số nhỏ nhất nằm ở ô nhớ có địa chỉ lớn nhất

### Struct

- Các thành viên được lưu trữ tuần tự, mỗi thành viên có một địa chỉ riêng
- Kích thước của struct là tổng kích thước của các thành viên, cộng với các byte đệm nếu có

#### Padding & Alignment

Memory alignment: Hầu hết CPU được thiết kế để truy cập dữ liệu hiệu quả nhất khi mà dữ liệu được đặt trong ô nhớ có địa chỉ là bội số kích thước của dữ liệu
 - Ví dụ: uint32_t (4 bytes) nên được đặt trong ô nhớ có địa chỉ chia hết cho 4
>
    typedef struct {
        uint32_t height;
        uint32_t width;
        uint8_t speed;
        char name[7];
    }monitor1_t;

    typedef struct {
        uint32_t height;
        uint8_t speed;
        uint32_t width;
        char name[7];
    }monitor2_t;

- monitor1_t có kích thước là 16 bytes
- monitor2_t có kích thước là 20 bytes 

![Padding!](./Memory%20padding.png "Padding")

#### Bit-fields

- Chỉ định kích thước của các thành viên trong 1 struct 
- Tiết kiệm bộ nhớ tối đa
- Biểu diễn thanh ghi thông qua struct

>
    typedef struct {
        uint8_t ODR : 4;
        uint8_t BDU : 1;
        uint8_t Zen : 1;
        uint8_t Yen : 1;
        uint8_t Xen : 1;
    } CTRL_REG4;

- CTRL_REG4 có kích thước là 1 byte
- Thứ tự các bit trên bộ nhớ còn phụ thuộc vào kiến trúc của hệ thống là Big Endian hay là Little Endian
- Little Endian: Xen-Yen-Zen-BDU-ODR
- Big Endian: ???

### Union

- Các thành viên chia sẻ chung một vùng nhớ, địa chỉ của các thành viên đều giống nhau
- Kích thước của union là kích thước của thành viên lớn nhất

#### Type-punning

- Kỹ thuật diễn giải lại các bit của kiểu dữ liệu này như một kiểu dữ liệu khác

>
    typedef union {
        uint32_t IP;
        uint8_t IPmasked[4];
    } IP_address;

- Giả sử gán giá trị 0xC0A80101 cho thành phần IP 
- Tùy vào kiến trúc của hệ thống là Big Endian hay Little Endian mà các byte sẽ được sắp xếp khác nhau
    - Little Endian: 01 - 01 - A8 - C0
    - Big Endian: C0 - A8 - 01 - 01
- Các phần tử của mảng IPmasked[4] sẽ có giá trị theo các byte của IP

#### Tagged Union

### Enum

## **Bài 7: Standard I/O**

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

## **Bài 8: Toán tử và câu lệnh điều kiện**



### Kỹ thuật Epsilon

- Khi so sánh 2 số thực , do sai số làm tròn nên nếu so sánh chính xác là việc rất rủi ro
- Giải pháp: Luôn so sánh trong một khoảng sai số rất nhỏ

>
    fagb(a-b) < EPSILON

- fabs(): hàm lấy giá trị tuyệt đối của 1 số thực
- EPSILON: hằng số rất nhỏ (ví dụ 0.00001f)

### Jump table

Một kỹ thuật tối ưu hóa được compiler sử dụng cho câu lệnh switch-case
- Compiler sẽ tạo ra 1 mảng đặc biệt trong bộ nhớ
    - Phần tử 0 của mảng chứa địa chỉ khối mã cho case 0
    - Phần tử 1 cho case 1
    - Phần tử 2 cho case 2
    ...
- Khi chạy câu lệnh switch, CPU sẽ dùng giá trị của case như 1 chỉ số mảng để truy cập thẳng tới địa chỉ của vùng code cần thực thi

### Polling & Interrupt

## **Bài 9: Mảng và con trỏ**

- Con trỏ là 1 biến đặc biệt có kích thước 4 bytes trên hệ điều hành 32 bit
- Con trỏ có thể lưu lại giá trị của 1 ô nhớ trên bộ nhớ

- Con trỏ NULL

### Mảng
- Tên mảng là 1 hằng con trỏ, constant pointer

### Con trỏ 2 chiều