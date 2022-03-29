#ifndef CURRENTDTO_H
#define CURRENTDTO_H

struct currentDTO       //用户状态传递，去除密码数据
{
    QString UserName;
    unsigned int Id = 0;
    unsigned int level = 0;
    unsigned int score = 0;
    int lastSignTime = 0;
    int dateOfToday = 0;
};

#endif // CURRENTDTO_H
