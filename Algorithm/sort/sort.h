#ifndef _SORT_H_
#define _SORT_H_

typedef int Item;

#define SWAP(A, B) {Item t = A; A = B; B = t;}
#define SELECTION_SORT 1
#define INSERTION_SORT 2
#define BUBBLE_SORT    3
#define SHELL_SORT     4
#define QUICK_SORT     5
#define MERGE_SORT     6
#define HEAP_SORT      7
#define RADIX_SORT     8

void selection_sort(int *array, int sz);
void insertion_sort(int *array, int low, int hight);
void bubble_sort(int *array, int sz);
void shell_sort(int *array, int sz);

int  partition(int *array, int low, int high);
void quick_sort(int *, int low, int high);

void merge(int *array, int low, int mid, int high);
void merge_sort(int *, int low, int last);

void max_heapify(int *array, int root, int sz);
void heap_sort(int *array, int hsz);

void radix_sort_LSD(int *array, int sz);

#endif //_SORT_H_
