#include "book_management.h"

extern int connfd;

int book_save_list_to_file(const char *filename, SListEntry *list)
{
    FILE *fp = NULL;
    char buff[MAXBUF] = { 0 };
    SListEntry *p = list;

    fp = fopen(filename, "w");
    if (!fp) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    // 跳过第一样标题，不然每次都要把它覆盖了
    // 获取数据但并不使用，只是更新fp
    // 这种方法有问题，只能手动打印标题
    // fgets(buff, MAXBUF, fp);
    fprintf(fp, "图书编号 图书名称 图书价格 图书总数 现存数量\n");

    while (p) {
        struct _BookInfo *book_ptr = p->data;

        // 写入数据到文件
        fprintf(fp, "%s %s %lf %d %d\n", book_ptr->id, book_ptr->name,
        book_ptr->price, book_ptr->total_num, book_ptr->left_num);

        // 指向下一个节点
        p = p->next;
    }

    fclose(fp);
}

int book_read_file_to_list(const char *filename, SListEntry **list)
{
    FILE *fp = NULL;
    char buff[MAXBUF] = { 0 };

    fp = fopen(filename, "r");
    if (!fp) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    // 跳过第一行，第一行是标题
    fgets(buff, MAXBUF, fp);

    SListEntry *p;
    // 开始读取所有数据
    while (fgets(buff, MAXBUF, fp) > 0) {
        // 分配新内存
        struct _BookInfo *book_ptr = malloc(sizeof (struct _BookInfo));
        if (!book_ptr) {
            perror("malloc");
            exit(EXIT_FAILURE);
        }

        memset(book_ptr, 0, sizeof(struct _BookInfo));

        // 从缓冲区读取数据到结构体
        sscanf(buff, "%s %s %lf %d %d", book_ptr->id,
        book_ptr->name, &book_ptr->price, 
        &book_ptr->total_num, &book_ptr->left_num);

        if (book_ptr == NULL) {
            perror("malloc");
            exit(EXIT_FAILURE);
        }

        // 查找数据
        p = slist_find_data(*list, callback_check_str_id, (SListValue *)&book_ptr->id);
        // 仅当p为空的时候，也就是说该书籍不存在
        if (p == NULL) {
            if (slist_append(list, (SListValue *)book_ptr) != NULL) {
                puts("[+] 插入成功\n\n");
            } else {
                puts("[-] 插入失败\n\n");
            }
        } else {
            puts("[-] 书籍已存在\n\n");
            return -1;
        }

    }

    fclose(fp);
}

int user_save_list_to_file(const char *filename, SListEntry *list)
{
    FILE *fp = NULL;
    char buff[MAXBUF] = { 0 };
    SListEntry *p = list;

    fp = fopen(filename, "w");
    if (!fp) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    fprintf(fp, "图书证号 姓名 性别 借书数量 最大借书数量 密码\n");
    while (p) {
        struct _User *user_ptr = ((struct _User *)p->data);

        // 写入数据到文件
        fprintf(fp, "%s %s %s %d %d %s\n", user_ptr->id, user_ptr->username,
        user_ptr->gender, user_ptr->num_borrow, user_ptr->max_num_borrow, user_ptr->passwd);

        // 指向下一个节点
        p = p->next;
    }

    fclose(fp);
}

int user_read_file_to_list(const char *filename, SListEntry **list)
{
    FILE *fp = NULL;
    char buff[MAXBUF] = { 0 };

    fp = fopen(filename, "r");
    if (!fp) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    // 跳过第一行，第一行是标题
    fgets(buff, MAXBUF, fp);

    SListEntry *p;
    // 开始读取所有数据
    while (fgets(buff, MAXBUF, fp) > 0) {
        // 分配新内存
        struct _User *user_ptr = malloc(sizeof (struct _User));
        if (!user_ptr) {
            perror("malloc");
            exit(EXIT_FAILURE);
        }

        memset(user_ptr, 0, sizeof(struct _User));

        // 从缓冲区读取数据到结构体
        sscanf(buff, "%s %s %s %d %d %s", user_ptr->id,
        user_ptr->username, user_ptr->gender, 
        &user_ptr->num_borrow, &user_ptr->max_num_borrow, user_ptr->passwd);

        if (user_ptr == NULL) {
            perror("malloc");
            exit(EXIT_FAILURE);
        }

        // 查找数据
        p = slist_find_data(*list, callback_check_str_id, (SListValue *)&user_ptr->id);
        // 仅当p为空的时候，也就是说该用户不存在
        if (p == NULL) {
            if (slist_append(list, (SListValue *)user_ptr) != NULL) {
                puts("[+] 插入成功\n\n");
            } else {
                puts("[-] 插入失败\n\n");
            }
        } else {
            puts("[-] 用户已存在\n\n");
            return -1;
        }

    }

    fclose(fp);
}

void pre_welcome()
{
    // puts("1:) 登陆");
    // puts("2:) 注册");
    // puts("3:) 忘记密码");
    // puts("4:) 退出");

    char buf[MAXBUF] = "1:) 登陆\n"
                       "2:) 注册\n"
                       "3:) 忘记密码\n"
                        "4:) 退出\n"
                        ;


    // kill(0, SIGSTOP);
    // send(connfd, "1:) 登陆\n", MAXBUF, 0);
    // send(connfd, "2:) 注册\n", MAXBUF, 0);
    // send(connfd, "3:) 忘记密码\n", MAXBUF, 0);
    // send(connfd, "4:) 退出\n", MAXBUF, 0);
    send(connfd, buf, strlen(buf), 0);

}

int book_management()
{
    int input;
    char temp_buf[MAXBUF] = { 0 };
    // 图书链表，用于存储图书
    SListEntry *book_list = NULL;
    // 用户链表，用于存储用户
    SListEntry *user_list = NULL;
    struct _User *user;
    struct _User *current_user;

    user_read_file_to_list("A.txt", &user_list);
    book_read_file_to_list("B.txt", &book_list);

    while (1) {
        pre_welcome();
        // puts("输入你的选择:");
        send(connfd, "输入你的选择:", MAXBUF, 0);
        // scanf("%d", &input);
        recv(connfd, temp_buf, MAXBUF, 0);

        // 网络传输数据为char *，需要转化为int
        input = atoi(temp_buf);

        switch (input) 
        {
            if (input > 10) {
                break;
            }
            case 1:
                if ((current_user = login(&user_list)) != NULL) {
                    // puts("[+] 登陆成功\n\n");
                    send(connfd, "[+] 登陆成功\n\n", MAXBUF, 0);
                    goto login_succeed;
                } else {
                    // puts("[-] 登陆失败\n\n");
                    send(connfd, "[+] 登录失败\n\n", MAXBUF, 0);
                    break;
                }
            case 2:
                if (regist(&user_list)) {
                    puts("[+] 注册成功]\n\n");
                    break;
                } else {
                    puts("[-] 注册失败\n\n");
                    break;
                }
            case 3:
                ;
                // if (forget_passwd(&user_list)) {
                //     puts("找回密码成功");
                //     break;
                // } else {
                //     puts("找回密码失败");
                //     break;
                // }
            case 4:
                exit(EXIT_SUCCESS);
            default:
                puts("输入错误");
        }

    }

login_succeed:
    while (1) {
        welcome();
        puts("");
        puts("输入你的选择:");
        scanf("%d", &input);

        switch (input) {
            case 1:
                // if (!is_in_sll(user, user_list, callback)) {
                //     insert_user()
                // }
                if (current_user->type != TEACHER) {
                    printf("[-] 学生不能添加图书\n\n\n");
                    break;
                }
                // 添加图书
                insert_book(&book_list);
                break;
            case 2:
                if (current_user->type != TEACHER) {
                    printf("[-] 学生不能删除图书\n\n\n");
                    break;
                }
                // 删除图书
                delete_book(&book_list);
                break;
            case 3:
                if (current_user->type != TEACHER) {
                    printf("[-] 学生不能修改图书\n\n\n");
                    break;
                }
                // 修改图书
                modify_book(&book_list);
                break;
            case 4:
                // 不用检查身份
                query_book(&book_list);
                break;
            case 5:
                // 借书还书，会修改book_list链表，所以这里要取地址
                borrow_book(current_user, &book_list);
                break;
            case 6:
                // 还书
                return_book(current_user, &book_list);
                break;
            case 7:
                show_userinfo(current_user);
                break;
            case 8:
                // statistic(book_list);
                break;
            case 9:
                show_books(book_list);
                break;
            case 10:
                user_save_list_to_file("A.txt", user_list);
                book_save_list_to_file("B.txt", book_list);
                exit(EXIT_SUCCESS);
            default:
                puts("[-] 输入错误\n\n");
                break;
        }
    }

    slist_free(book_list);
    return 0;
}

void welcome()
{
    puts("");
    puts("-------------------");
    puts("欢迎使用图书管理系统");
    puts("1:) 添加一本图书");
    puts("2:) 删除一本图书");
    puts("3:) 修改一本图书");
    puts("4:) 查询一本图书");
    puts("5:) 借书");
    puts("6:) 还书");
    puts("7:) 查看用户借还信息");
    puts("8:) 统计");
    puts("9:) 查看剩余图书");
    puts("10:) 退出");
    puts("-------------------");
    puts("");
}


struct _User *login(SListEntry **entry) 
{
    struct _User *new_user;
    SListEntry *p;
    SListValue *data;
    char passwd[MAXBUF] = { 0 };
    char temp_buf[MAXBUF] = { 0 };

    new_user = (struct _User *) malloc(sizeof(struct _User));

    // puts("请输入用户名");
    send(connfd, "请输入用户名\n", MAXBUF, 0);
    // scanf("%s", new_user->username);
    // 获取客户端的用户名
    recv(connfd, temp_buf, sizeof(temp_buf), 0);

    // puts("请输入密码");
    send(connfd, "请输入密码\n", MAXBUF, 0);
    // scanf("%s", new_user->passwd);
    // 获取客户端密码
    recv(connfd, temp_buf, MAXBUF, 0);

    p = slist_find_data(*entry, callback_check_username, (SListValue *)new_user);
    if (p == NULL) {
        puts("[-] 用户未注册");
        return NULL;
    } else {
        if (strncmp(((struct _User *)p->data)->passwd, new_user->passwd, 
        strlen(((struct _User *)p->data)->passwd)) == 0)
            return (struct _User *)p->data;
    }
    return NULL;
}

int regist(SListEntry **entry)
{
    struct _User *new_user;
    SListEntry *p;
    SListValue *data;
    char passwd[MAXBUF], passwd_repeat[MAXBUF];

    new_user = (struct _User *)malloc(sizeof(struct _User));
    puts("请输入id:");
    scanf("%s", new_user->id);
    puts("请输入你的姓名:");
    scanf("%s", new_user->name);
    puts("请输入你的性别:");
    scanf("%s", new_user->gender);
    puts("请输入你的职位 0:老师, 1学生:");
    scanf("%d", &new_user->type);
    puts("请输入用户名");
    scanf("%s", new_user->username);

    while (1) 
    {
        puts("请输入密码:");
        scanf("%s", passwd);
        puts("请输再次入密码:");
        scanf("%s", passwd_repeat);

        if (strncmp(passwd, passwd_repeat, strlen(passwd)) == 0) {
            break;
        } else {
            puts("密码不一致，请重新输入:");
        }
    }

    // 密码设置成功，复制密码
    strcpy(new_user->passwd, passwd);
    // 找到用户名是否存在
    p = slist_find_data(*entry, callback_check_username, (SListValue *)new_user->username);
    if (p == NULL) {
        if (slist_append(entry, (SListValue *)new_user)) {
            puts("[+] 注册成功\n\n");
            return 1;
        }
    } else {
        puts("[-] 用户已注册\n\n");
        return -1;
    }
    puts("[-] 用户注册失败\n\n");
    return -1;
}

int insert_book(SListEntry **list)
{
    BookInfo *book_info;
    SListEntry *p;

    book_info = malloc(sizeof (struct _BookInfo));
    if (book_info == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    puts("输入书本id:");
    scanf("%s", book_info->id);
    puts("输入书本名字:");
    scanf("%s", book_info->name);
    puts("输入书本作者:");
    scanf("%s", book_info->author_name);
    puts("请输入书的种类: 1)Novel 2)Classic 3)Tech");
    scanf("%d", &book_info->type);
    puts("");

    p = slist_find_data(*list, callback_check_str_id, (SListValue *)&book_info->id);
    if (p == NULL) {
        if (slist_append(list, (SListValue *)book_info) != NULL) {
            puts("[+] 插入成功\n\n");
            return 1;
        } else {
            puts("[-] 插入失败\n\n");
            return 0;
        }
    } else {
        puts("[-] 此书已存在\n\n");
        return -1;
    }
    return 1;
}

int delete_book(SListEntry **entry)
{
    int id;

    puts("输入要删除书本的id:");
    scanf("%d", &id);
    delete_book_by_id(entry, id);

    return 1;
}

int delete_book_by_id(SListEntry **entry, int id)
{
    SListEntry *p;
    SListValue *value;
    struct _BookInfo *book_info;

    // 删书有三种情况, 第一 图书馆没有此书, 第二 图书馆有多本此书(只需num_left--)，
    // 第三 图书馆只有一本书(需要删除节点)
    p = slist_find_data(*entry, callback_check_str_id, (SListValue *)&id);
    if (p == NULL) {
        puts("-------------------");
        puts("此书不存在");
        puts("-------------------");
        return -1;
    } else {
        value = slist_data(p);
        book_info = (struct _BookInfo *) value;
        if (slist_remove_entry(entry, p) == 0) {
            puts("[-] 删除数据失败\n\n");
            return -1;
        } else {
            puts("[+] 删除成功\n\n");
            return 1;
        }
    }
    puts("");
}

int callback_check_id(SListValue a, SListValue b)
{
    // if (((struct _BookInfo *)a)->id == *(int *)b)
    //     return 1;
    // else
    //     return 0;
}

int callback_check_str_id(SListValue a, SListValue b)
{
    if (strcmp(((struct _BookInfo *)a)->id, b) == 0)
        return 1;
    else
        return 0;
}

int callback_check_username(SListValue a, SListValue b)
{
    if (strcmp(((struct _User *)a)->username, ((struct _User *)b)->username) == 0)
        return 1;
    else
        return 0;
}

int query_book(SListEntry **entry)
{
    char id[4] = { 0 };

    puts("请输入要查询的id:");
    scanf("%s", id);
    query_book_by_id(entry, id);

    return 1;
}

int query_book_by_id(SListEntry **entry, char *id)
{
    SListEntry *p;
	SListEntry *rover;
    SListValue *data;

    p = slist_find_data(*entry, callback_check_str_id, (SListValue *)id);
    if (p == NULL) {
        puts("[-] 未查询到数据\n\n");
        return -1;
    } else {
        data = slist_data(p);

        puts("----------------------");
        printf("查询结果如下\n");
        // 这里需要强制转换
        printf("id:%s\n", ((struct _BookInfo *)data)->id);
        printf("书名:%s\n", ((struct _BookInfo *)data)->name);
        printf("作者:%s\n", ((struct _BookInfo *)data)->author_name);
        puts("----------------------");
    }
    return 1;
}

int modify_book(SListEntry **entry)
{
    return 0;
}

int borrow_book(struct _User *user, SListEntry **book_list)
{
    char id[MAXBUF] = { 0 };
    SListEntry *book;
    SListEntry *user_book;

    puts("输入你要借的书的id:");
    scanf("%s", id);

    // 要借的书不存在，直接返回错误
    book = slist_find_data(*book_list, callback_check_str_id, (SListValue *)&id);
    if (book == NULL) {
        puts("[-] 此书不存在");
        return -1;
    }

    // puts("输入借书时间:");
    // scanf("%d", &p->time_borrow);
    // // 检查最大借书数量
    // if (p->num_borrow > p->max_num_borrow) {
    //     puts("超过最大借书数量");
    //     return -1;
    // }

    // 在用户链表中查找次书，有的话直接num_left++,没有的话再创建节点
    user_book = slist_find_data(user->borrowed_book, callback_check_str_id, (SListValue *)&id);
    if (!user_book) {
        // 没找到
        if (!slist_append(&user->borrowed_book, book->data)) {
            puts("[-] 添加图书至用至用户借书链表失败\n\n");
            return -1;
        }
    } else {
        ((struct _BookInfo *)user_book->data)->left_num++;
    }

    // 用户要借书需要判断图书馆的书是否够，图书馆的书数量会发生变化
    // 如果图书馆原来书本数量 == 1, 则删掉该节点，否则只需要将数量-1
    if (((struct _BookInfo *)book->data)->left_num == 1) {
        // 将原有的图书链表删掉数据
        if (!slist_remove_entry(book_list, book)) {
            puts("[-] 删除图书失败");
            return -1;
        }
    } else {
        ((struct _BookInfo *)book->data)->left_num--;
    }


    user->num_borrow++;

    puts("[+] 借书成功\n\n");
    return 1;
}

int return_book(struct _User *user, SListEntry **book_list)
{
    char id[MAXBUF] = { 0 };
    SListEntry *user_entry;
    SListEntry *book_entry;

    puts("输入你要还的书的id:");
    scanf("%s", id);

    // 在用户链表中找到此书
    user_entry = slist_find_data(user->borrowed_book, callback_check_str_id, (SListValue *)&id);
    if (user_entry == NULL) {
        puts("[-] 用户未借此书\n\n");
        return -1;
    }

    // 在图书链表中找到此书
    book_entry = slist_find_data(*book_list, callback_check_str_id, 
    (SListValue *)((struct _BookInfo *)user_entry->data)->id);
    // 这里也要考虑还书的情况，如果原来图书馆里面没有此书则创建节点，否则只需要将数量+1就行
    if (!book_entry) {
        // 在图书链表中未找到该节点，添加
        if (!slist_append(book_list, user_entry)) {
            puts("[-] 将用户书归还时出错\n\n\n");
            return -1;
        }
    } else {
        ((struct _BookInfo *)book_entry->data)->left_num++;
    }

    // 同时借几本同样的书的情况
    // 如果用户所借图书链表中数量==1，则从用户借书链表中删除，否则数量-1
    if (((struct _BookInfo *)user_entry->data)->left_num == 1) {
        if (!slist_remove_entry(&user->borrowed_book, user_entry)) {
            puts("[-] 从用户借书链表中删除出错\n\n");
            return -1;
        }
    } else {
        // 否则, 只需要将图书数量-1就行
        ((struct _BookInfo *)user->borrowed_book->data)->left_num--;
    }

    user->num_borrow--;


    puts("[+] 还书成功\n\n");
    return 1;
}

// 初始化学生和老师的限制量
void teacher_borrow(struct _BookInfo *p)
{
    // p->max_num_borrow = 15;
    // p->max_time_borrow = 180;
}

void student_borrow(struct _BookInfo *p)
{
    // p->max_time_borrow = 10;
    // p->max_time_borrow = 120;
}

struct _User *ask_user_info(struct _User *p)
{
    struct _User *user;

    user = malloc(sizeof(struct _User));
    if (user == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    p = malloc(sizeof(struct _User));
    if (p == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    // 复制内存
    memcpy(user, p, sizeof(struct _User));

    puts("您的名字是:");
    scanf("%s", user->name);
    puts("您的学号是:");
    scanf("%s", user->id);
    puts("您的身份是 0:)老师, 1:)学生:");
    scanf("%d", &user->type);

    return user;
}

int insert_user(SListEntry **list, SListValue *user)
{
    SListEntry *p;

    if (slist_append(list, (SListValue *)user) != NULL) {
        puts("[+] 插入用户成功\n\n");
        return 1;
    } else {
        puts("[-] 插入用户失败\n\n");
        return 0;
    }
}

void show_userinfo(struct _User *p)
{
    SListEntry *temp;

    puts("-------------------");
    printf("用户名:%s\n", p->username);
    // printf("所借数量:%d\n", t->num_borrow);
    printf("所借数量:%d\n", p->num_borrow);

    if (!p->borrowed_book) {
        puts("用户未借任何书籍");
        return;
    }

    temp = p->borrowed_book;
    while (temp) {
        printf("书名: %s\n", ((struct _BookInfo *)temp->data)->name);
        temp = temp->next;
    }
}

void show_books(SListEntry *book_list)
{
    SListValue *value;
    SListEntry *p = book_list;

    int n = 0;
    puts("-------------------");
    while (p != NULL) {
        value = p->data;

        if (!value)
            break;

        printf("ID:%s\t", ((struct _BookInfo *) value)->id);
        printf("书名:%s\t", ((struct _BookInfo *) value)->name);
        printf("作者:%s\t", ((struct _BookInfo *) value)->author_name);
        puts("");

        p = p->next;
        n++;
    }
    puts("-------------------");

    if (n == 0) {
        puts("[-] 未查询到任何数据\n\n");
    }
}

// int statistic(SListEntry *book_list)
// {
//     int id;
//     int n = 0;
//     SListEntry *p;
//     int num_borrowed, num_left;
// 
//     puts("-------------------");
//     puts("图书统计如下:");
// 
//     p = book_list;
//     while (p != NULL) {
//         id = ((struct _BookInfo *)p->data)->id;
//         num_left = ((struct _BookInfo *)p->data)->num_left;
//         num_borrowed = ((struct _BookInfo *)p->data)->num_borrowed;
// 
//         printf("书本id:%d 剩余数量:%d 借书数量:%d\n", id, num_left, num_borrowed);
//         // printf("书本id:%d 借书率:%lf\n", id, ((double) num_left) / num_borrowed);
//         n++;
//         p = p->next;
//     }
//     puts("-------------------");
// 
//     if (n == 0) {
//         puts("没有任何数据");
//     }
// }
// 
