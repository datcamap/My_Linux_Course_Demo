- Trong bài này ta có Channel là wrapper có chức năng gói các decorator 
- Các decorator sẽ chứa con trỏ type Channel
- Khi khởi tạo các decorator, cần truyền vào con trỏ Channel

```C
    typedef struct {
        int  (*send)(Channel* self, const uint8_t* data, size_t len);
        int  (*receive)(Channel* self, uint8_t* buffer, size_t bufferLength, size_t* out_len);
    } ChannelOps;

    struct Channel {
        const ChannelOps* ops;
        void*             impl;
    };
```