# ПРАКТИЧНА РОБОТА 1

## ЗАВДАННЯ 1 (ВАРІАНТ 13)

## Умова
Напишіть програму, яка читає число та створює динамічний масив цього розміру.
Заповніть масив цим числом.
Додайте функцію зміни розміру масиву (realloc) та реалізуйте можливість збільшення чи зменшення розміру масиву під час виконання програми.
Введіть обмеження на мінімальний та максимальний розмір масиву.
Реалізуйте функцію перевірки використання пам’яті, яка виводить поточний стан виділеної пам’яті (malloc, realloc, free).

## Код до завдання
```c
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
```

## Опис програми
Я написав програму, яка працює з динамічними масивами. Спочатку вона запитує в мене розмір масиву, і я маю ввести число в межах від 1 до 1000. Якщо я ввожу неправильне значення, програма знову запитує розмір до тих пір, поки не введу правильне число.
Після того як я ввів розмір, програма створює динамічний масив цього розміру, використовуючи функцію malloc, яка виділяє пам’ять під масив. Програма також перевіряє, чи вдалося виділити пам’ять. Якщо пам’ять не була виділена, програма виведе повідомлення про помилку і завершить роботу.
Далі я маю ввести значення, яким буде заповнений масив. Програма заповнює масив цим числом. Потім вона виводить вміст масиву на екран.
Програма дозволяє мені змінювати розмір масиву після того, як він уже створений. Для цього я можу ввести новий розмір. Програма перевіряє, чи новий розмір знаходиться в допустимих межах. Якщо розмір правильний, програма змінює розмір масиву за допомогою функції realloc. Якщо новий розмір більший за попередній, програма додає нові елементи, заповнюючи їх тим же значенням, яким був заповнений старий масив. Після кожної зміни розміру масиву програма виводить новий вміст масиву.
Програма також стежить за використанням пам’яті. Після кожної операції виділення або звільнення пам'яті вона виводить інформацію про кількість використаної пам'яті та загальний обсяг пам'яті, що була виділена. Коли я закінчую роботу з масивом, програма звільняє виділену пам'ять і виводить повідомлення про це.
В результаті, програма дає мені можливість динамічно керувати розміром масиву, заповнювати його значеннями і контролювати використану пам'ять.

## Результати виконання програми
![image](https://github.com/user-attachments/assets/4c81d757-bb4d-4014-a84b-301adaec3f99)
![image](https://github.com/user-attachments/assets/16d4c716-6a2f-484a-9c99-b6960eb7b3de)
![image](https://github.com/user-attachments/assets/3e7c08e5-e423-421f-97a1-6aa47c3c769f)
![image](https://github.com/user-attachments/assets/940afcee-a4cc-4247-8fcc-5ae8d46cba22)
![image](https://github.com/user-attachments/assets/58eb47a8-b143-4fab-bb97-1e865306dfc2)




