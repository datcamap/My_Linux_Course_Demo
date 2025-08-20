- Trong bài này ta có Channel là wrapper có chức năng gói các decorator 
- Các decorator sẽ chứa con trỏ type Channel
- Khi khởi tạo các decorator, cần truyền vào con trỏ Channel, các hàm send và receive sẽ được gán cho từng decorator
- Các decorator lưu lại inner, đây là decorator đã được gói trước đó

```C
    struct Channel {
        int  (*send)(Channel* self, const uint8_t* data, size_t len);
        int  (*receive)(Channel* self, uint8_t* buffer, size_t bufferLength, size_t* out_len);
        void*             impl;
    };
```