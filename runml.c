#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "tools.h"

int main()
{
    FILE *mlFile;
    FILE *cFile;
    char line[2048];

    // 打开ml文件进行读取
    mlFile = fopen("program.ml", "r");
    if (mlFile == NULL)
    {
        printf("无法打开ml文件\n");
        return EXIT_FAILURE;
    }

    // 创建新的C文件进行写入
    cFile = fopen("run.c", "w");
    if (cFile == NULL)
    {
        printf("无法创建C文件\n");
        fclose(mlFile);
        return EXIT_FAILURE;
    }

    // 写入标准的C文件头
    fprintf(cFile, "#include <stdio.h>\n\n");
    fprintf(cFile, "int main(int argc, char *argv[]) {\n");

    const char *operator= "<-";
    char *x;
    char *value;
    // 逐行读取ml文件并解析
    while (fgets(line, sizeof(line), mlFile))
    {
        // 这句是否为普通的赋值 有"->"
        char *res = strstr(line, operator);
        if (res != NULL)
        {
            // 拆分字符串，获取 "<-" 左边的部分
            *res = '\0';                    // 将 "<-" 替换为字符串结束符
            x = line;                       // 左边部分是变量名
            value = res + strlen(operator); // 右边部分是值

            // 去除两边的空格
            trim(x);
            trim(value);

            // 输出结果
            // printf("变量名: '%s', 值: '%s'\n", x, value);
            fprintf(cFile, "\tdouble %s;\n", x);
            fprintf(cFile, "\t%s = %s;\n", x, value);
        }
    }

    // 写入C文件的结尾
    fprintf(cFile, "\treturn 0;\n");
    fprintf(cFile, "}\n");

    // 关闭文件
    fclose(mlFile);
    fclose(cFile);

    // 编译生成的C代码文件
    system("gcc run.c -o main");

    // 运行生成的可执行文件
    system("./main");

    // 删除临时文件
    // system("rm -rf main");
    // system("rm -rf run");
    // system("rm -rf run.c");
    return EXIT_SUCCESS;
}
