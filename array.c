#include "array.h"
#include <stdlib.h>
#include <stdio.h>
const  int BLOCK_SIZE = 20;
/*#ifndef _ARRAY_H_
#define _ARRAY_H_
typedef struct{
    int *array;
    int size;
}Array;
void array_creat(int init_size);
void array_free(Array *a);
void array_size(const Array *a);
int *array_at(Array *a,int index);
void array_inflate(Array *a,int more_size);
#endif */
Array array_creat(int init_size){
    Array a;
    a.size = init_size;
    a.array = (int*)malloc(sizeof(int)*a.size);
    return a;
}
void array_free(Array *a){
    free(a->array);
    a->size = 0;
    a->array = NULL;
}
//封装
int array_size(const Array *a){
    return a->size;
}
int* array_at(Array *a,int index){
    if(index<=a->size){
        array_inflate(a,index/(BLOCK_SIZE+1)*sizeof(BLOCK_SIZE));
    }
    return &(a->array[index]);
}
int array_get(const Array *a,int index){
    return a->array[index];
}
void array_set(Array *a ,int index,int value){
    a->array[index] = value; 
}
void array_inflate(Array *a,int more_size){
    int *p = (int*)malloc(sizeof(int)*(a->size+more_size));
    int i;
    for(i=0;i<a->size;i++){
        p[i] = a->array[i];
        free (a->array);
        a->array = p;
        a->size+=more_size;
    }

}
int main(int argc,const char *argv[]){
    Array a = array_creat(100);
    printf("size is %d\n",array_size(&a));
    *array_at(&a,0) = 10;
    printf("the at is %d\n",*array_at(&a,0));
    printf("the value is %d\n",array_get(&a,0));
    array_set(&a,0,100);
    printf("the value si %d\n",array_get(&a,0));
    int cnt = 0;
    int number = 0;
    while(number != -1){
        scanf("%d",&number);
        if(number==-1){
            break;
        }
        *array_at(&a,cnt++) = number;
        
    }
    array_free(&a);
    return 0;
}