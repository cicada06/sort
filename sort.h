#ifndef __SORT_H__
#define __SORT_H__

#ifdef __cplusplus
extern "C" {
#endif

// 冒泡排序
void bubble_sort(int *d, int n);
// 鸡尾酒排序 
void shaker_sort(int *d, int n);

void select_sort(int *d, int n);
void insertion_sort(int *d, int n);
void quick_sort(int *d, int n);
void quick_sort2(int *d, int n);
void quick_sort3(int *d, int n);
void heap_sort(int *d, int n);
void merge_sort(int *d, int n);
void counting_sort(int *d, int n);
void bucket_sort(int *d, int n);
void radix_sort(int *d, int n);


#ifdef __cplusplus
}
#endif

#endif
