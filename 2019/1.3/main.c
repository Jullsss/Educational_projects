#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int size;
    scanf("%d", &size);
    int array[size];
    for (int k = 0; k < size; k++) {
        scanf("%d", &array[k]);
	}
    int step, i, j, tmp;
	// Выбор шага
	for (step = size / 2; step > 0; step /= 2) {
	    // Перечисление элементов, которые сортируются на определённом шаге
		for (i = step; i < size; i++) {
		    // Перестановка элементов внутри подсписка, пока i-тый не будет отсортирован
			for (j = i - step; j >= 0 && array[j] > array[j + step]; j -= step)
			{
				tmp = array[j];
				array[j] = array[j + step];
				array[j + step] = tmp;
			}
		}
	}
	for (int k = 0; k < size; k++) {
        printf("%d ", array[k]);
	}
    return 0;
}
