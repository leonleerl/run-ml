#include <ctype.h>

// 函数去除字符串两边的空格
void trim(char *str)
{
    char *start = str; // 指向字符串的起始位置
    char *end;

    // 移动start指针，跳过前导空格
    while (isspace((unsigned char)*start))
    {
        start++;
    }

    // 如果字符串全是空格
    if (*start == 0)
    {
        str[0] = '\0';
        return;
    }

    // 找到字符串的末尾
    end = start + strlen(start) - 1;

    // 移动end指针，跳过末尾空格
    while (end > start && isspace((unsigned char)*end))
    {
        end--;
    }

    // 将末尾空格后的字符置为字符串结束符
    *(end + 1) = '\0';

    // 如果start移动过，则将start后的内容复制到str开始处
    if (start != str)
    {
        memmove(str, start, end - start + 2);
    }
}
