# **Mảng và con trỏ**

- Con trỏ là 1 biến đặc biệt có kích thước 4 bytes trên hệ điều hành 32 bit
- Con trỏ có thể lưu lại giá trị của 1 ô nhớ trên bộ nhớ

### Con trỏ NULL
NULL là một hằng số đặc biệt cho biết rằng một con trỏ đang không trỏ tới 1 địa chỉ cụ thể trong bộ nhớ

```C
    int *pointer;
```

Nếu khi khởi tạo con trỏ mà không gán giá trị thì con trỏ sẽ mang 1 giá trị bất kì (con trỏ lúc này được gọi là wild pointer), việc tham chiếu ngược vào con trỏ này sẽ khiến chương trình có thể bị crash
Cho nên con trỏ thường được khởi tạo với giá trị NULL nếu chưa được gán cho địa chỉ ô nhớ

```C
    int *pointer = NULL;
```

### Mảng
- Tên mảng là 1 hằng con trỏ, constant pointer
- Việc truy cập phần tử x trong mảng arr chính là offset con trỏ 1 lượng = x*(kích thước 1 phần tử trong mảng arr) sau đó tham chiếu ngược vào con trỏ đã offset

```C
    arr[x] == *( arr + x*sizeof(arr[0]) )
```

### Con trỏ 2 chiều

- Một mảng 2 chiều có thể được biểu diễn trong C dưới dạng mảng 1 chiều mà các phần tử trong mảng là các con trỏ đến các mảng 1 chiều khác

```C
    arr[i][j] == *(*(arr + i) + j)
```

### Con trỏ hàm
- Lưu trữ giá trị địa chỉ của 1 hàm nằm trong Text Segment
- Tên hàm đóng vai trò như một hằng con trỏ hàm

```C
    int add(int a, int b) {
        return a + b;
    }
```

- Con trỏ hàm phải có signature giống với hàm được gán cho con trỏ

```C
    int (*func_point_to_add)(int, int) = add;
```

- Tên của các tham số khi khai báo hàm không nhất thiết phải giống với tên của tham số khi định nghĩa hàm, thậm chí khi khai báo hàm không cần có tên tham số cũng được

```C
    /* header.h */
    int add(int, int);

    /* source.c */
    int add(int a, int b);
```

### Callback Function

- Một con trỏ hàm có thể được truyền như một tham số cho function
- Ví dụ khi xảy ra ngắt timer thì hàm xử lí ngắt sẽ gọi ra hàm thực thi thông qua con trỏ hàm này, việc này giúp dễ dàng tùy biến fucntion được gọi

### Command dispatch table

- Mỗi command được gán cho 1 hàm cụ thể trong bảng, chương trình sẽ dựa vào command để gọi ra hàm tương ứng
- Triển khai theo cách này giúp dễ dàng mở rộng khi số lượng command lớn
