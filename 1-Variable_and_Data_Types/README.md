# **Biến và kiểu dữ liệu tự định nghĩa**

- Declaration (khai báo): Thông báo cho compiler về sự tồn tại của biến hoặc hàm (function prototype)
- Definition (định nghĩa): Cấp phát bộ nhớ cho biến bằng việc khởi tạo giá trị, hoặc là cung cấp mã thực thi cho hàm (phần thân hàm)

### Static keyword:

- Các biến global được mặc định có từ khoá static
- Các hàm có từ khoá static thì chỉ được gọi từ các hàm ở trong cùng 1 file

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

- Các hằng số được gán cho 1 symbol, khi compiler thực hiện tiền xử lí thì giá trị của biến vẫn được gán bằng symbol, thuận tiện cho việc debug
- Enum thường được dùng trong các trường hợp kiểu dữ liệu có giá trị là một dãy số liên tiếp
- Còn khi define 1 text = 1 giá trị thì sau khi tiền xử lí, text đó sẽ bị thay bằng giá trị số, gây khó khăn cho việc debug
