# **Toán tử và câu lệnh điều kiện**

### Kỹ thuật Epsilon

- Khi so sánh 2 số thực , do sai số làm tròn nên nếu so sánh chính xác là việc rất rủi ro
- Giải pháp: Luôn so sánh trong một khoảng sai số rất nhỏ

```C
    fagb(a-b) < EPSILON
```

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

- Polling: always blocking
- Interrupt: block only when some conditions are met 