#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "hashtable.h"

int filter_word(char *str)
{
    int len = strlen(str);

    // not a string
    if (str == NULL || strcmp(str, " ") == 0 || strlen(str) <= 1) {
        return 0;
    }

    // if last element ispunct, remove it
    // for example, word. , should be changed to word

    // scan str[0] - str[len - 2], check if it has punc, which is not a word
    for (int i = 0; i < len - 2; i++) {
        if (ispunct(str[i])) {
            return 0;
        }
    }

    // check last element 
    if (ispunct(str[len - 1])) {
        str[len - 1] = '\0';
    }

    // this is a word, to upper
    for (int i = 0; i < strlen(str); i++) {
        str[i] = toupper(str[i]);
    }

    return 1;
}

int main(int argc, char *argv[]) 
{
    int total_word = 0;

    if (argc != 2) {
        fprintf(stderr, "usage: %s textfile", argv[0]);
        exit(EXIT_FAILURE);
    }

    FILE *in = fopen(argv[1], "r");
    if (!in) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    hashtable *hash = createtable(500000);
    struct node *node = NULL;
    char word[100];
    int length = 0;

    /* Load data from txt file to the hash table */
    while(1) {
        if (fscanf(in, "%s", word) != 1) {
            break;
        }

        if(ispunct(word[length]))
	        *(word + length) = '\0';

        // for (int i = 0; i < strlen(word); i++) {
        //     word[i] = toupper(word[i]);
        // }
        
        if (!filter_word(word)) {
            continue;
        }

	    // if(strlen(word) > 0) {
     //        node = add(hash, word, 1);
     //        node->frequency++;
     //    }


        total_word++;
        node = add(hash, word, 0);
        node->frequency++;
    }

    fclose(in);
    // mostfrequent(hash, 100);
    printf("Total number of words = %d\n", total_word);
    printf("Number of different words = %d\n", hash->currentsize);
    printf("The 100 most common words:\n");
    freq_top_n_sorted(hash, 100);
    freetable(hash);
    return 0;
}

