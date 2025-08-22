- Cần thống nhất 1 interface chung giữa các Concreate Creator với Factory, trong bài này là cấu trúc dữ liệu SensorDriver

```C
    typedef struct {
        const char* kind;
        Sensor*   (*create)(void);
    } SensorDriver;
```

- Tuỳ vào loại sensor mà các thư viện sẽ implement hàm create một cách khác nhau
- Factory sẽ có hàm register để các thư viện đăng kí kind of sensor (tên của sensor), hoặc là có thể khai báo 1 enum SensorType trong factory nhưng sẽ cần sửa enum mỗi khi thêm sensor mới
- Phía người dùng chỉ cần gọi ra hàm sensor_create() cùng với tham số kind thích hợp, là có thể khởi tạo được mọi loại sensor mà đã được đăng kí