#include <iostream>
#include <fstream>


#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

using std::cout; using std::cerr;
using std::endl; using std::string;
using std::ifstream;

void cat(string filename)
{
    ifstream ifs(filename, std::ios::binary);
    // ifstream ofs("/dev/stdout", std::ios::binary);
    if (ifs.is_open()) {
        string line;
        while (getline(ifs, line)) {
            cout << line << endl;
        }
        ifs.close();
    }
}

void check_file_type(string filename)
{
    int status;
    struct stat fs;
    string tmp_name;

    // convert
    status = stat(filename.c_str(), &fs);
    if( status == -1 ) {
        fprintf(stderr,"File error\n");
        exit(1);
    }

    if (filename == "/dev/stdin")
        tmp_name = "standard input";
    else
        tmp_name = filename;

    /* file permissions are kept in the st_mode member */
    /* The S_ISREG() macro tests for regular files */

    /* should be sent to error stream */
    if (S_ISREG(fs.st_mode))
        cerr << tmp_name << " is a regular file" << endl;
    else if (S_ISFIFO(fs.st_mode))
        cerr << tmp_name << " is a pipe" << endl;
    else if (S_ISCHR(fs.st_mode))
        cerr << tmp_name << " is a character device" << endl;
    else
        cerr << tmp_name << " is something else" << endl;
}

int main(int argc, char *argv[])
{
    string filename;

    if (argc < 2) {
        filename = "/dev/stdin";
        check_file_type(filename);
        cat(filename);
    } else {
        for (int i = 1; i < argc; ++i) {
          if (strcmp(argv[i], "-") == 0)
              filename = "/dev/stdin";
          else
              filename = argv[i];

            check_file_type(filename);
            cat(filename);
        }
    }
    return(0);
}