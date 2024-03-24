/*
    选择排序: [选择一个]数据中最大/小的元素排到前面
        - 口诀：
            1、将数组分成『已排序区』和『待排序区』
            2、每⼀轮从『待排序区』中选择⼀个最小的元素放到『已排序区』的尾部
            3、直到『待排序区』没有元素为⽌
        - 时间复杂度：O(n^2) 稳定
*/

#include "0.sort_test.h"

void selection_sort(int *arr, int l, int r) {
    //因为.h文件里的fun(temp, 0 ,n)，此时l = 0，r = n共(n+1)
    //所以外层循环循环i[l,n-1),左闭右开的区间共n-1-l次
    //外层循环的i++可以将已排序区和待选区分开
    for (int i = l, I = r-1; i < I; i++)
    {
        int ind = i;
        //内层循环是从待选区中找到最小的元素，用ind做标记
        for (int j = i + 1; j < r; j++)
        {
            if(arr[j] < arr[ind]) ind = j;
        }
        swap(arr[i], arr[ind]); //由内层循环找到的待排序区的最小值放到已排序区的后面
    }
    return ;
}

int main(void) {
    int *arr = getRandData(SMALL_DATA_N);
    TEST(selection_sort, arr, SMALL_DATA_N);
    free(arr);
    return 0;
}
