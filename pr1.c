#include <stdio.h>
#include <stdlib.h>

#define MIN_SIZE 1
#define MAX_SIZE 1000

size_t totalMemoryAllocated = 0;

void checkMemoryUsage(size_t size, const char* operation) {
    printf("Операція: %s, виділено: %zu байт пам'яті.\n", operation, size);
    totalMemoryAllocated += size;
    printf("Загальна використана пам'ять: %zu байт.\n", totalMemoryAllocated);
}

int changeArraySize(int **arr, int *size, int new_size, int fill_value) {
    if (new_size < MIN_SIZE || new_size > MAX_SIZE) {
        printf("Розмір масиву повинен бути між %d і %d.\n", MIN_SIZE, MAX_SIZE);
        return 0;
    }

    int old_size = *size;
    int *temp = realloc(*arr, new_size * sizeof(int));

    if (temp == NULL) {
        printf("Не вдалося змінити розмір масиву.\n");
        return 0;
    }

    *arr = temp;
    *size = new_size;

    checkMemoryUsage(new_size * sizeof(int), "realloc");

    if (new_size > old_size) {
        for (int i = old_size; i < new_size; i++) {
            (*arr)[i] = fill_value;
        }
    }

    return 1;
}

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main() {
    int *array = NULL;
    int size, new_size, fill_value;
    char choice;

    printf("Введіть розмір масиву (від %d до %d): ", MIN_SIZE, MAX_SIZE);
    while (scanf("%d", &size) != 1 || size < MIN_SIZE || size > MAX_SIZE) {
        printf("Помилка! Введіть коректне число від %d до %d: ", MIN_SIZE, MAX_SIZE);
        clearInputBuffer();
    }

    array = (int *)malloc(size * sizeof(int));

    if (array == NULL) {
        printf("Не вдалося виділити пам'ять для масиву розміру %d.\n", size);
        return 1;
    }

    checkMemoryUsage(size * sizeof(int), "malloc");

    printf("Введіть значення для заповнення масиву: ");
    while (scanf("%d", &fill_value) != 1) {
        printf("Помилка! Введіть число: ");
        clearInputBuffer();
    }

    for (int i = 0; i < size; i++) {
        array[i] = fill_value;
    }

    printf("Масив створено:\n");
    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");

    while (1) {
        printf("Бажаєте змінити розмір масиву? (y/n): ");
        clearInputBuffer();
        choice = getchar();

        if (choice == 'n' || choice == 'N') {
            break;
        }

        printf("Введіть новий розмір масиву: ");
        while (scanf("%d", &new_size) != 1 || new_size < MIN_SIZE || new_size > MAX_SIZE) {
            printf("Помилка! Введіть число від %d до %d: ", MIN_SIZE, MAX_SIZE);
            clearInputBuffer();
        }

        if (changeArraySize(&array, &size, new_size, fill_value)) {
            printf("Масив змінено:\n");
            for (int i = 0; i < size; i++) {
                printf("%d ", array[i]);
            }

            printf("\n");
        }
    }

    free(array);
    printf("Пам'ять звільнена.\n");
    checkMemoryUsage(0, "free");

    return 0;
}
