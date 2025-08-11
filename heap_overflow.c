#include <stdio.h>

int main() {
    char 名字[10] = "名字";
    printf("输入你的名字：");
    scanf("%10s", 名字);
    printf("你好，%s\n", 名字);
    return 0;
}