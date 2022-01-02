g++ -fPIC -lnsl -ldl -c jj-mod.c util.c && ld -G -o jj-mod.so jj-mod.o
