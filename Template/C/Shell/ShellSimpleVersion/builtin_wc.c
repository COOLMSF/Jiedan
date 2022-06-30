#include "headers.h"

int count_word(char *buf)
{
    char *p = buf;
    int cnt = 0;

    while (*p != '\0') {
        // assume a word
        if (*p == ' ') {
            cnt++;
        }
        p++;
    }
    return cnt;
}

int builtin_wc(char *cmd)
{
	char **args = alloc_args();

	int arg_num = get_args(cmd, args);

    if (arg_num < 2) {
        printf("usage: wc file_to_count\n");
        return -1;
    }

    FILE *fin = NULL;
    char buf[MAX_BUF] = { 0 };
    int words_cnt = 0;

    fin = fopen(args[1], "r");
    while (fgets(buf, MAX_BUF, fin) > 0) {
        words_cnt += count_word(buf);
    }

    printf("Total words: %d\n", words_cnt);
	free_args();
}