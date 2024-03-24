/*
插入排序：我默认有一个顺序队列，新加入的元素到末尾，新加入的和前面的依顺序比较，直到符合排序顺序终止交换
    - ⼝诀：
        1、将数组分成『已排序区』和『待排序区』
        2、将『已排序区』后面⼀个元素，向前插⼊到『待排序区』中
        3、直到『待排序区』没有元素为⽌
    - 时间复杂度：平均O(n^2) 最差O(n^2) 最好O(n)
*/

#include "0.sort_test.h"

void insert_sort(int *arr, int l, int r) {
    //外层循环：让已排序区的下一位(待选区的首位)作为插入元素
    for (int i = l + 1; i < r; i++)
    {
        int j = i;  // j 作为一个标记
        while (j > l && arr[j] < arr[j -1])
        {
            swap(arr[j], arr[j-1]);
            j -= 1; //交换完一次后j标记到前一位，为下一次交换准备
        }
    }
    return;
}
//无人坚守的插入排序
void unguarded_insert_sort(int *arr, int l, int r) {
    //先找的全局的最小值移到首位
    int ind = l;
    for (int i = l + 1; i < r; i++)
    {
        if(arr[i] < arr[ind]) ind = i;
    }
    while (ind > l)
    {
        swap(arr[ind], arr[ind-1]);
        ind -= 1;
    }
    //
    for (int i = l + 2; i < r; i++)
    {
        int j = i;
        while (arr[j] < arr[j-1])
        {
            swap(arr[j], arr[j-1]);
            j -= 1;
        }
    }
    return;
}

int main(void) {
    int *arr = getRandData(SMALL_DATA_N);
    TEST(insert_sort, arr, SMALL_DATA_N);
    TEST(unguarded_insert_sort, arr, SMALL_DATA_N);
    free(arr);
    return 0;
}