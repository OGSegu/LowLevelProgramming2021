#include <stdio.h>
#include "bSort.h"
int main() {
    int a[10] = {100, 1, 4, 0, 1000, 52, 26, 89, -35, 389};
    bSort(a, 10);
    for (int i = 0; i < 10; i++) {
        printf("%d ", a[i]);
    }
    return 0;
}
