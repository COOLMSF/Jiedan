#include <iostream>
#include <stdio.h>

using namespace std;

void sort(int *arr, int size);
void swap(int *a, int *b);

int main(int argc, char const *argv[])
{

    int n = 100;
    int arr[n];
    FILE *fp;

    // open file
    fp = fopen("result.txt", "w");
    if (fp == NULL) {
        perror("cannot open file");
        exit(EXIT_FAILURE);
    }


    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 100;
    }

    sort(arr, n);

    for (int i = 0; i < n; i++) {
        fprintf(fp, "%d\n", arr[i]);
    }

    return 0;
}

void sort(int *arr, int size) 
{
    for (int i = 0; i < size; i++) { 
        for (int j = 0; j < size; j++) {
            if (arr[i] < arr[j])
                swap(arr+i, arr+j);
        }
    }
}

void swap(int *a, int *b)
{
    int tmp;

    tmp = *a;
    *a = *b;
    *b = tmp;
}