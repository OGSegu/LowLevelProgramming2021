# 1 "bSort.c"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "bSort.c"
# 1 "bSort.h" 1


void bSort(int *num, int size);
# 2 "bSort.c" 2
void bSort(int *num, int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = (size - 1); j > i; j--) {
            if (num[j - 1] > num[j]) {
                int temp = num[j - 1];
                num[j - 1] = num[j];
                num[j] = temp;
            }
        }
    }
}
