Builder pattern chia nhỏ việc khởi tạo object thành việc khởi tạo từng thuộc tính
Trong trường hợp object có rất nhiều thuộc tính, chia nhỏ như vậy cho phép tạo ra nhiều biến thể của object một cách dễ dàng mà không phải truyền nhiều tham số cho một hàm khởi tạo duy nhất
Mỗi biến thể khác nhau được tạo ra bằng cách khởi tạo các thuộc tính khác nhau của object
Nhưng số lượng hàm khởi tạo sẽ nhiều lên vì mỗi thuộc tính cần 1 hàm khởi tạo riêng