
#ifndef _SORT_TEST_H
#define _SORT_TEST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SMALL_DATA_N 5000
#define BIG_DATA_N 1000000

__attribute__((constructor))
void __init__Rand__() {
    printf("init rand\n");
    srand(time(0));
}


//获得一个长n的随机数组
int *getRandData(int n){
    int *arr = (int *)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++)
    {
        arr[i] = rand() % 10000;
    }
    return arr;
}

//检测是否是升序 数组arr，左边界l，有边界r
int check(int *arr, int l, int r) {
    for (int i = l + 1; i < r; i++)
    {
        if(arr[i] < arr[i-1]) return false; //后一位小于前一位
    }
    return true;
}

// 交换的宏
#define swap(a, b)           \
    {                        \
        __typeof(a) __c = a; \
        a = b;               \
        b = __c;             \
    }

//测试宏 传入函数func，数组arr，测试数据的个数n
#define TEST(func, arr, n) { \
    printf("Test %s : ", #func); \
    int *temp = (int *)malloc(sizeof(int) * n); \
    memcpy(temp, arr, sizeof(int) * n); \
    long long b = clock(); \
    func(temp, 0, n); \
    long long e = clock(); \
    if(check(temp, 0, n)) { \
        printf("\tOK"); \
    } else { \
        printf("FAIL "); \
    }  \
    printf(" %d items %lldms\n", n, (e-b) * 1000 / CLOCKS_PER_SEC); \
    free(temp); \
}

#endif
