# **Memory layout**

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
