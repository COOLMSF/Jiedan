#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "Common/cJSON.h"
#include "Service/Connect.h"
#include "Persistence/MySQL.h"

int main()
{
    char buf[1024];
    char host[50] ,user[30],pass[50],database[50];
    int fd = open("config.json" ,O_RDONLY);

    if(fd == -1) {
        printf("配置文件打开失败!");
        getchar();
        exit(0);
    }

    // 读取配置文件
    read(fd ,buf ,1024);

    // 解析配置文件
    cJSON* root = cJSON_Parse(buf);

    // 解析主机名
    cJSON* item = cJSON_GetObjectItem(root ,"host");
    // 复制json host对象到，host数组
    strcpy(host, item->valuestring);

    // 解析用户名
    item = cJSON_GetObjectItem(root ,"user");
    // 复制json user对象到user数组
    strcpy(user, item->valuestring);

    // 解析
    item = cJSON_GetObjectItem(root, "pass");
    strcpy(pass, item->valuestring);

    // 解析数据库
    item = cJSON_GetObjectItem(root, "database");
    strcpy(database ,item -> valuestring);

    // 解析端口
    item = cJSON_GetObjectItem(root, "port");
    int port = item -> valueint;

    // 释放对象
    close(fd);
    cJSON_Delete(root);

    if(MySQL_Connect(host ,user ,pass ,database) == 0) {
        printf("数据库连接失败\n");
        exit(0);
    }

    Connect(port);
}
