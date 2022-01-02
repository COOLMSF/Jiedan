#include "headers.h"

int builtin_pwd()
{
    char cwd[PATH_MAX];

    // 获取当前目录
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("%s\n", cwd);
    } else {
        perror("getcwd() error");
        return 1;
   }
   return 0;
}
