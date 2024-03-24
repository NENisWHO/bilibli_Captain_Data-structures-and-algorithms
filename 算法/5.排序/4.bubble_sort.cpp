/*
    冒泡排序：
    - ⼝诀：
        1、将数组分成『已排序区』和『待排序区』
        2、从头到尾扫描『待排序区』，若前面元素比后面元素⼤，则交换
        3、每⼀轮都会将『待排序区』中最⼤的放到『已排序区』的开头
        4、直到『待排序区』没有元素为⽌
    - 时间复杂度：O(n^2)
*/

#include "0.sort_test.h"

// void bubble_sort(int *arr, int l, int r) {
//     for (int i = r - 1, I = l + 1; i >= I; i--)
//     {
//         for (int j = l; j < i; j++)
//         {
//             if(arr[j] > arr[j + 1]) {
//                 swap(arr[j], arr[j + 1]);
//             }
//         }
//     }
//     return;
// }

void bubble_sort(int *arr, int l, int r)
{
    for (int i = r - 1, I = l + 1, cnt; i >= I; i--)
    {
        cnt = 0;
        for (int j = l; j < i; j++)
        {
            if(arr[j] <= arr[j + 1]) continue;//优化：若排序区已经有序了就不用交换顺序了
            swap(arr[j], arr[j + 1]);
            cnt += 1;
        }
        if (cnt == 0) break;    //这一句说明数据本身就有序不用冒泡了
    }
    return;
}

int main(void) {
    int *arr = getRandData(SMALL_DATA_N);
    TEST(bubble_sort, arr, SMALL_DATA_N);
    free(arr);
    return 0;
}