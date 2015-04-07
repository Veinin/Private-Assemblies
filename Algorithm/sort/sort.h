#ifndef _SORT_H_
#define _SORT_H_

typedef int Item;

#define SWAP(A, B) {Item t = A; A = B; B = t;}
#define SELECTION_SORT 1
#define INSERTION_SORT 2
#define BUBBLE_SORT    3
#define SHELL_SORT     4

void selection_sort(int *, int);
void insertion_sort(int *, int, int);
void bubble_sort(int *, int);
void shell_sort(int *, int);

#endif //_SORT_H_
