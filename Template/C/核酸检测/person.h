#define MAX_STR 1024

enum Status {
    checking = 0,
    waiting
};

struct Person { 
    // id
    int id;
    char name[MAX_STR];
    // 身份证信息
    char id_num[MAX_STR];
    enum Status status;
};

// typedef struct Person Persion;
