#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"

int hashcode(char *);

void freenode(struct node *);

struct node * add(hashtable *h, char *key, int freq) {
    struct node *newnode;
    int index = hashcode(key) % h->tablesize;
    struct node *current = h->table[index];

    /* Search for duplicate value */
    // hash collision?
    while(current != NULL) {
        if(strcmp(key, current->key) == 0)
            // should be linked based hash table, rather than just return
            return current;
        current = current->next;
    }
    /* Create new node if no duplicate is found */
    newnode = nalloc(key, freq);
    newnode->next = h->table[index];
    h->table[index] = newnode;
    h->currentsize = h->currentsize + 1;
    return newnode;
}

bool contains(hashtable *h, char *key) {
    int index = hashcode(key) % h->tablesize;
    struct node *current = h->table[index];

    while(current != NULL) {
        if(strcmp(key, current->key) == 0)
            return true;
        current = current->next;
    }
    return false;
}

struct node * getnode(hashtable *h, char *key) {
    int index = hashcode(key) % h->tablesize;
    struct node *current = h->table[index];

    while(current != NULL) {
        if(strcmp(key, current->key) == 0)
            return current;
        current = current->next;
    }
    return NULL;
}

void deletenode(hashtable *h, char *key) {
    int index = hashcode(key) % h->tablesize;
    struct node *current = h->table[index];
    struct node *previous = NULL;

    if(current == NULL)
        return;
    /* Scan the linked list until  match is found or the end is reached */
    while(current != NULL && strcmp(key, current->key) != 0) {
        previous = current;
        current = current->next;
    }
    /* Item not found */
    if(current == NULL)
        return;
    /* Item is in the first position */
    else if(current == h->table[index])
        h->table[index] = current->next;
    /* Item is in the last position */
    else if(current->next == NULL)
        previous->next = NULL;
    /* Item is in the middle of the list */
    else
        previous->next = current->next;
    /* Deallocate memory for the deleted node */
    freenode(current);
}

/* Prints values that have a value higher than the integer parameter */
void mostfrequent(hashtable *h, int freq) {
    struct node *current = NULL;
    int i;
    printf("\n  Word       Frequency\n");
    printf("  --------------------\n");
    for(i = 0; i < h->tablesize; i++) {
        current = h->table[i];
        while(current != NULL) {
            if(current->frequency > freq)
                printf("  %-14s %d\n", current->key, current->frequency);
            current = current->next;
        }
    }
}

void freq_top_n_sorted(hashtable *h, int n) {
    struct node *current = NULL;
    struct node *tmp = NULL;
    int i, j;
    int cnt = 0;
    int size = h->tablesize;
    int node_array_size = h->currentsize;

    struct node *node_array[node_array_size];

    // store hash table to array
    for (int i = 0; i < size; i++) {
        // make sure not NULL
        if (h->table[i] != NULL) {
            node_array[cnt] = h->table[i];
            // calulate length
            cnt++;
        }
    }

    // bubble sort
    for (int i = 0; i < cnt; i++) {
        for (int j = 0; j < cnt - 1; j++) {
            if (node_array[i]->frequency > node_array[j]->frequency) {
                struct node *t;

                t = node_array[i];
                node_array[i] = node_array[j];
                node_array[j] = t;
            }
        }
    }

    printf("\n  Word       Frequency\n");
    printf("  --------------------\n");

    // print hashtable
    for (int i = 0; i < cnt; i++) {
        if (i == n) {
            break;
        }
        printf("  %-14s %d\n", node_array[i]->key, node_array[i]->frequency);
    }
}

/* Returns a positive integer hash value generated from a string value */
int hashcode(char *key) {
    int i, hash = 7;
    int length = strlen(key);

    for(i = 0; i < length; i++)
        hash = (hash * 31) + *(key + i);
    return hash & 0x7FFFFFFF;  /* Make value positive */
}

/* Returns a pointer to a newly allocated hash table */
struct hashtable * createtable(int size) {
    int i;
    if(size < 1)
        return NULL;
    hashtable *table = (hashtable *) malloc(sizeof(hashtable));
    table->table = (struct node **) malloc(sizeof(struct node *) * size);

    if(table != NULL) {
        table->currentsize = 0;
        table->tablesize = size;
    }
    /* Set all pointers to NULL */
    for(i = 0; i < size; i++)
        table->table[i] = NULL;
    return table;
}

/* Allocates memory for a new node. Initializes the new node's members */
struct node * nalloc(char *key, int freq) {
    struct node *p = (struct node *) malloc(sizeof(struct node));

    if(p != NULL) {
        p->key = strdup(key);
        p->frequency = freq;
        p->next = NULL;
    }
    return p;
}

/* Deallocates memory of the string stored in the node and the
   node itself */
void freenode(struct node *node) {
    free(node->key);
    free(node);
}

/* Deallocates all of the memory associated with the hash table */
void freetable(hashtable *h) {
    struct node *current = NULL;
    int i;

    for(i = 0; i < h->tablesize; i++) {
        current = h->table[i];
        if(current == NULL)
            continue;
        /* Deallocate memory of every node in the table */
        while(current->next != NULL) {
            h->table[i] = h->table[i]->next ;
            freenode(current);
            current = h->table[i];
        }
        freenode(current);
    }
    /* Free the hash table */
    free(h->table);
    free(h);
}


