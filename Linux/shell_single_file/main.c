// 文件操作头文件
#include <fcntl.h>

// 目录操作头文件
#include<dirent.h>

// 标准输入头文件
#include<stdio.h>
// 标准库
#include<stdlib.h>
// 字符串
#include<string.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
// 提供readline函数
#include <readline/readline.h>

#define MAX_DATA 1024
#define TURE 1
#define FALSE 0

int FileDescriptor;
char *Arguments[MAX_DATA];
char Prompt[MAX_DATA];
char *InputBuffer;
char *CommandToExecute[MAX_DATA];
int TestFlag, len;
char cwd[MAX_DATA];
pid_t pid;
int OfLines;
int EnvoFlag;
int PipeFlagLess,  RedirectionToOutput, RedirectionFromInput;
int status;
char *InputRedirectionFile;
char *OutPutRedirectionFile;

// 跳过空格符号
char *SkiptWhiteSpace(char* str) {
    int i = 0, j = 0;
    char *temp;
    // 分配内存
    if (NULL == (temp = (char *) malloc(sizeof(str)*sizeof(char)))) {
        fprintf(stderr, "malllc");
        exit(EXIT_FAILURE);
        // 判断空格符号
    } while(str[i++]) {
        if (str[i-1] != ' ')
            temp[j++] = str[i-1];
    }
    temp[j] = '\0';
    return temp;
}

void DoFilter()
{

}

// 改变目录内置命令
void ChangeDirectory() {
    // 默认路径
    char *home_dir = "/home";

    if ((Arguments[1]==NULL) 
    || (!(strcmp(Arguments[1], "~") 
    && strcmp(Arguments[1], "~/"))))
    // 系统调用，切换目录
        chdir(home_dir);
        // 切换目录出错
    else if (chdir(Arguments[1]) < 0)
        perror("No such file or directory: ");
}

// 处理重定向
void RedirectionOutput(char *cmd_exec){
    char *NewCommandExecStr,*s1;
    char *val[128];
    int m = 1;
    // 复制字符串
    NewCommandExecStr=strdup(cmd_exec);
    // 分割字符串
    val[0] = strtok(NewCommandExecStr, ">");
    while ((val[m] = strtok(NULL,">")) != NULL) m++;
    s1 = strdup(val[1]);
    // 跳过空白符
    OutPutRedirectionFile = SkiptWhiteSpace(s1);
    TokenizeBySpace(val[0]);
}

// 处理输入输出重定向
void TokenizeRedirectionInputOutput(char *cmd_exec) {
    int m = 1;
    char *val[128];
    char *NewCommandExecStr, *s1, *s2;
    // 复制字符串
    NewCommandExecStr = strdup(cmd_exec);
    // 同上，分割字符串
    val[0] = strtok(NewCommandExecStr, "<");
    // while循环
    while ((val[m] 
    = strtok(NULL,">")) != NULL) m++;
    s1 = strdup(val[1]);
    s2 = strdup(val[2]);
    // 跳过空白符
    InputRedirectionFile = SkiptWhiteSpace(s1);
    OutPutRedirectionFile = SkiptWhiteSpace(s2);
    // 跳过空白符
    TokenizeBySpace(val[0]);
}

// 处理输入重定向
void TokenizeRedirectionInput(char *cmd_exec) {
    char *val[128];
    int m = 1;
    char *NewCommandExecStr, *s1;
    NewCommandExecStr = strdup(cmd_exec);
    val[0] = strtok(NewCommandExecStr, "<");
    while ((val[m] = strtok(NULL,"<")) != NULL) m++; s1 = strdup(val[1]);
    InputRedirectionFile = SkiptWhiteSpace(s1);
    TokenizeBySpace (val[0]);
    return;
}

// 处理空白符
void TokenizeBySpace(char *str) {
    int m = 1;
    Arguments[0] = strtok(str, " ");
    // strtok分割
    while ((Arguments[m] = strtok(NULL," ")) != NULL) m++;
    Arguments[m] = NULL;
}

// 处理管道符
void TokenlizeByPipe()
{
    int i, n = 1, input = 0, first = 1;
    // strtok分割
    CommandToExecute[0] = strtok(InputBuffer, "|");
    // strtok分割
    while ((CommandToExecute[n] = strtok(NULL, "|")) != NULL) n++;
    CommandToExecute[n] = NULL;
    for (i = 0; i < n-1; i++) {
        // 执行内置命令
        input = ExecuteBuiltinCommand(CommandToExecute[i], input, first, 0);
        first = 0;
    }
    input = ExecuteBuiltinCommand(CommandToExecute[i], input, first, 1);
}

// 跳过双引号
char *SkipDoubleQuote(char *str) {
    int i = 0, j = 0; char *temp;
    // 内存分配
    if (NULL == (temp = (char *) malloc(sizeof(str)*sizeof(char)))) {
        perror("Memory Error: ");
        return NULL;
    }
    // 循环字符串查找双引号
    while(str[i++]) {
        if (str[i-1] != '"')
            temp[j++] = str[i-1];
    }
    temp[j] = '\0';
    return temp;
}

// 输出提示信息
void PrintBanner() {
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        strcpy(Prompt, "MyShell# ");
        // strcat(prompt, cwd);
        strcat(Prompt, ">");
    }
    else {
        perror("getcwd");
    }
}

// 执行命令
int ExecuteCommand(int input, int first, int last, char *cmd_exec) {
    int PipeFileDe[2] ,ret,input_fd, output_fd;
    // 创建管道
    if (-1 == (ret = pipe(PipeFileDe))) {
        perror("pipe error: ");
        return 1;
    }

    // 创建子进程
    pid = fork();
    // 子进程
    if (pid == 0) 
    {
        if (first == 1 && last == 0 && input == 0) 
        {
            dup2 (PipeFileDe[1], 1);
        }
        else if (first == 0 && last == 0 && input != 0) 
        {
            dup2 (input, 0);
            dup2 (PipeFileDe[1], 1);
        }
        else 
        {
            dup2 (input, 0);
        }
        // 需要重定向
        if (strchr(cmd_exec, '<') && strchr(cmd_exec, '>')) 
        {
            RedirectionFromInput = 1;
            RedirectionToOutput = 1;
            TokenizeRedirectionInputOutput (cmd_exec);
        }
        // 需要重定向
        else if (strchr(cmd_exec, '<')) 
        {
            RedirectionFromInput = 1;
            TokenizeRedirectionInput (cmd_exec);
        }
        // 需要重定向
        else if (strchr(cmd_exec, '>')) 
        {
            RedirectionToOutput = 1;
            RedirectionOutput (cmd_exec);
        }
        if (RedirectionToOutput) 
        {
            if ((output_fd = creat(OutPutRedirectionFile, 0644)) < 0) 
            {
                fprintf(stderr, "writing\n", OutPutRedirectionFile);
                return (EXIT_FAILURE);
            }
            dup2(output_fd, 1);
            close(output_fd);
            RedirectionToOutput = 0;
        }
        if (RedirectionFromInput) {
            if ((input_fd = open(InputRedirectionFile, O_RDONLY, 0)) < 0) {
                fprintf(stderr, "reading\n", InputRedirectionFile);
                return (EXIT_FAILURE);
            }
            dup2(input_fd, 0);
            close(input_fd);
            RedirectionFromInput = 0;
        }
        // 内置命令
        if (!strcmp (Arguments[0], "echo")) {
            //echo_calling(cmd_exec);
        }
        // 使用execvp执行命令
        else if (execvp(Arguments[0], Arguments) < 0) {
		printf("execvp:%s\n", Arguments[0]);
            fprintf(stderr, "%s: Command not found\n",Arguments[0]);
        }
        exit(0);
    }
    if (last==1)
    // 关闭管道
        close(PipeFileDe[0]);
    if (input!= 0)
        close(input);

    // 关闭管道
    close(PipeFileDe[1]);
    return (PipeFileDe[0]);
}


// 初始化
void ClearVariables() {
    FileDescriptor = 0;
    TestFlag = 0;
    len = 0;
    cwd[0] = '\0';
    Prompt[0] = '\0';
    pid = 0;
    PipeFlagLess = 0;
    Prompt[0] = '\0';
    pid = 0;
    OfLines = 0;
    RedirectionToOutput = 0;
    RedirectionFromInput = 0;
    EnvoFlag = 0;
}

// 实现grep命令
int MyGrep(char *FileName, char *str)
{
	char *buf = NULL;
	size_t n;
	FILE *fp;
    // 打开文件
	if ((fp = fopen(FileName, "r")) == NULL) 
    {
		perror("fopen");exit(EXIT_FAILURE);
	}

    // 查找关键字
	while (getline(&buf, &n, fp) > 0) 
    {
		if (strstr(buf, str))
			printf("%s", buf);
	}
}


// 执行内置命令
int ExecuteBuiltinCommand(char *cmd_exec, 
int input, int isfirst, int islast) {
    char *NewCommandExecStr;
    NewCommandExecStr = strdup(cmd_exec);
    TokenizeBySpace (cmd_exec);
    if (Arguments[0] != NULL) {
        if (!(strcmp(Arguments[0], "exit") && strcmp(Arguments[0], "quit")))
            exit(0);
        if (!strcmp(Arguments[0], "echo")) {
            cmd_exec = SkipDoubleQuote(NewCommandExecStr);
            TokenizeBySpace(cmd_exec);
            char **args_ptr = &Arguments[1];
            while(*args_ptr)
                puts(*args_ptr++);
        }

        // 内置cd命令
        if (!strcmp("cd", Arguments[0])) {
            ChangeDirectory();
            return 1;
        }
        // 内置mygrep命令
	if (!strcmp("mygrep", Arguments[0])) {
		MyGrep(Arguments[2], Arguments[1]);
		return 1;
	}
    // 内置info命令
	if (!strcmp("info", Arguments[0])) {
		puts("COMP2211 Simplified Shell by 2019110033");
		return 1;
	}
    }
    return (ExecuteCommand(input, isfirst, islast, NewCommandExecStr));
}

// 删除字符串字串
char *strremove(char *str, const char *sub) {
    size_t len = strlen(sub);
    if (len > 0) {
        char *p = str;
        while ((p = strstr(p, sub)) != NULL) {
            memmove(p, p + len, strlen(p + len) + 1);
        }
    }
    return str;
}

// 主函数
int
main()
{
    int DebugStatus = FALSE;
    // 状态栏
    int status;
    char StrInput = 0;
    // 调试信息
    char *DebugMessage = "This is debug output";
    do {
	char temp[MAX_DATA] = { 0 };
	char *p_input_buffer;
	char *p_temp;
	char *p_ex;
	int index = 0;
    ClearVariables();
    PrintBanner();

    // 过滤ex字符串
    InputBuffer=readline(Prompt);
	p_ex = strstr(InputBuffer, "ex");
	p_temp = InputBuffer;
	if (p_ex != NULL)
	strremove(InputBuffer, "ex");
    if (!(strcmp(InputBuffer, "\n") && strcmp(InputBuffer,"")))
    continue;
    if (!(strncmp(InputBuffer,"exit", 4) && strncmp(InputBuffer, "quit", 4))) {
        TestFlag = 1;
        break;
    }
    TokenlizeByPipe();
    } while(!WIFEXITED(status) || !WIFSIGNALED(status));
    if (TestFlag == 1) {
        printf("\nClosing Shell\n");
        exit(0);
    }
    return 0;
}
