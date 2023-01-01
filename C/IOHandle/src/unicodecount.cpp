#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <wchar.h>
#include <errno.h>
#include <locale.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/uio.h>

using std::cin;
using std::cout;
using std::endl;
using std::fstream;
using std::ifstream;
using std::ofstream;

#define private public
#define protected public
#include <fstream>
#undef private
#undef protected

int main(void)
{
    setlocale(LC_ALL, "en_US.utf8");

    // ifstream ifs("/dev/stdin");
    // if (ifs.bad()) {
    //     perror("open file");
    //     exit(EXIT_FAILURE);
    // }

    FILE *fp = fopen("/dev/stdin", "r");
    if(!fp) {
        perror("Can't open file for reading");
        return EXIT_FAILURE;
    }

    wint_t wc;
    int cnt = 0;
    errno = 0;
    // it's almost impossible to convert cpp's stream to c's FILE *
    // so we can't use cpp's steam
    while ((wc = fgetwc(fp)) != WEOF) {
        // putwchar(wc);
        cnt++;
    }

    int fd = open();
 
    if (ferror(fp)) {
        if (errno == EILSEQ) {
            cout << "Invalid or incomplete multibyte or wide character" << endl;
            return -1;
        }
        else {
            cout << "Invalid or incomplete multibyte or wide character" << endl;
            return -1;
        }
    }
    cout << cnt;
    fclose(fp);
}
