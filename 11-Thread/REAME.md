- Một chương trình có nhiều process
- Một process có nhiều thread
- Thread light-weight hơn so với prcess

### **Giải thích các tham số của hàm pthread_create()**

```C
    int pthread_create(pthread_t *__restrict__ __newthread, const pthread_attr_t *__restrict__ __attr, void *(*__start_routine)(void *), void *__restrict__ __arg)
Create a new thread, starting with execution of START-ROUTINE
getting passed ARG. Creation attributed come from ATTR. The new
handle is stored in *NEWTHREAD.
```

- Thread sẽ kết thúc khi handler return hoặc gọi ra hàm pthread_exit()
- Thread cũng sẽ kết thúc nếu process chứa thread kết thúc, vì điều này nên cần có hàm thread join ở main để chờ thread hoàn thành công việc và giải phóng tài nguyên của thread
- Nếu như không muốn block thread main để chờ thì có thể gọi pthread_detach() nhưng sẽ không nhận được giá trị trả về của thread (thực ra giá trị trả về có thể lấy ra bẳng cách khác nên thường sẽ ưu tiên dùng pthread_detach())

### **Race condition**

- Cần sử dụng mutex (mutual exclusion) để khoá truy cập vào biến global dùng chung giữa các thread, nếu không khoá mutex thì các thread chạy song song có thể sẽ ghi đè giá trị lên biến dùng chung, khiến cho kết quả cuối cùng không chính xác

