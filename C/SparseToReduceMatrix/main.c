
#include <stdio.h>
#include <stdlib.h>
#define LEN_X 6
#define LEN_Y 8

void showArr(int *arr, int row,int col){
    int num = row*col;
    int cnt = 0;
    for(int i = 0 ; i < num ; i++){

        printf("%4d",*(arr+i));
        cnt++;
        if(cnt%3==0) printf("\n");
    }
}

// get non zero number
int arrNum(int arr[][8]){
    int count = 0;
    for(int i = 0 ; i < LEN_X ; i++){
        for(int j = 0 ; j < LEN_Y ; j++){
            if(arr[i][j]!=0) count++;
        }
    }
    return count;
}
int main(){
    int i = 0,j=0,k = 0,m = 0;
    int oldArr[6][8] = {{0,1},{0,0,2},{1}};

    // get non zero number cnt
    int num = arrNum(oldArr);
    int row = num+1;
    int col = 3;

    int  *newArr;
    // malloc memory
    newArr=(int *)malloc(sizeof(int)*(num+1)*3);

    *newArr = LEN_X;
    *(newArr+1) = LEN_Y;
    *(newArr+2) = num;

    for(i = 3 ; i < row*col ; i+=3){
        for(; k < LEN_X ; ){
            for(m = 0 ; m < LEN_Y ; m++){
                if(oldArr[k][m]!=0){
                    *(newArr+i) = k;
                    *(newArr+i+1) = m;
                    *(newArr+i+2) = oldArr[k][m];
                }
            }
            k+=1;
            break;
        }
    }
    printf("稀疏矩阵：\n");
    showArr(newArr,row,col);
}