#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int main() {
    while (1) {
        // Cấp phát 10MB mỗi vòng lặp mà không free
        char *data = malloc(10 * 1024 * 1024);
        if (data == NULL) {
            // Khi hệ thống hết bộ nhớ, malloc sẽ trả về NULL
            perror("malloc failed");
            break;
        }

        // Giả lập xử lý để giữ vùng nhớ "bận rộn"
        memset(data, 0, 10 * 1024 * 1024);
    }
    return 0;
}
