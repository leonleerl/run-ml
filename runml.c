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
        // 如果第一行为注释符号#，则忽略该行
        if (line[0] == '#')
            continue;
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

            // 是浮点数
            if (strchr(value, '.') || strchr(value, 'e') || strchr(value, 'E'))
            {
                fprintf(cFile, "\tdouble %s = 0.0;\n", x);
                fprintf(cFile, "\t%s = %s;\n", x, value);
            }
            // 是整数
            else
            {
                fprintf(cFile, "\tint %s = 0;\n", x);
                fprintf(cFile, "\t%s = %s;\n", x, value);
            }
        }

        // print
        else if (strncmp(line, "print", 5) == 0)
        {
            char *command;
            char *expression;

            // 使用strtok分割字符串，第一次调用获取命令部分
            command = strtok(line, " ");

            // 第二次调用获取表达式部分
            expression = strtok(NULL, ""); // 获取剩余部分
                                           // fprintf(cFile, "\tprintf(\"%%.6f\\n\", %s);", expression);
            fprintf(cFile,
                    "\tif ((%s) == (int)(%s)) {\n"
                    "\t\tprintf(\"%%d\\n\", (int)%s);\n"
                    "\t} else {\n"
                    "\t\tprintf(\"%%.6f\\n\", (double)%s);\n"
                    "\t}\n",
                    expression, expression, expression, expression);
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
