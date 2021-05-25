#include "bSort.h"
#include "swap.h"
void bSort(int *num, int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = (size - 1); j > i; j--) {
            if (num[j - 1] > num[j]) {
                swap(&num[j - 1], &num[j]);
            }
        }
    }
}