
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



>
    uint8_t outbuffer[5] = {};
    sprintf(outbuffer,"This_is_a_very_long_text \n\r");
    printf("%s", outbuffer);

### va_list



### I/O bufferring



### Stack canary

## **Bài 8: Toán tử và câu lệnh điều kiện**

### Kỹ thuật Epsilon

### Jump table

### Polling & Interrupt