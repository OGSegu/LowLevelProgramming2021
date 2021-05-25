//
// Created by Vadim on 26.05.2021.
//

#include "swap.h"

void swap(int *var1, int *var2) {
    int temp = *var1;
    *var1 = *var2;
    *var2 = temp;
}
