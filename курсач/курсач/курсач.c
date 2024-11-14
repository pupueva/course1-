//курсовая
#define _CRT_SECURE_NO_WARNINGS  
#include <stdio.h>  
#include <stdlib.h>  
#include <locale.h>  
#include <math.h>  
#include <time.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Функция для создания и инициализации матрицы
int** create_matrix(int rows, int cols, int randomize) {
    int** matrix = (int**)malloc(rows * sizeof(int*));
    for (int i = 0; i < rows; i++) {
        matrix[i] = (int*)malloc(cols * sizeof(int));
    }

    if (randomize) {
        srand(time(0));
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                matrix[i][j] = rand() % 21 - 10; // случайные числа от -10 до 10
            }
        }
    }
    else {
        printf("Введите элементы матрицы %dx%d:\n", rows, cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                printf("Введите элемент [%d][%d]: ", i + 1, j + 1);
                scanf_s("%d", &matrix[i][j]);
            }
        }
    }
    return matrix;
}

// Функция для вывода матрицы
void print_matrix(int** matrix, int rows, int cols) {
    printf("Матрица:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%4d ", matrix[i][j]);
        }
        printf("\n");
    }
}

// Подсчет отрицательных элементов в строках, содержащих хотя бы один ноль
void count_negatives_in_rows_with_zero(int** matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        int has_zero = 0, negative_count = 0;
        for (int j = 0; j < cols; j++) {
            if (matrix[i][j] == 0) {
                has_zero = 1;
            }
            if (matrix[i][j] < 0) {
                negative_count++;
            }
        }
        if (has_zero) {
            printf("Строка %d содержит %d отрицательных элементов.\n", i + 1, negative_count);
        }
    }
}

// Поиск и вывод седловых точек
void find_saddle_points(int** matrix, int rows, int cols) {
    printf("Седловые точки:\n");
    int found = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            int is_min_in_row = 1, is_min_in_col = 1;
            for (int k = 0; k < cols; k++) {
                if (matrix[i][k] < matrix[i][j]) {
                    is_min_in_row = 0;
                    break;
                }
            }
            for (int k = 0; k < rows; k++) {
                if (matrix[k][j] < matrix[i][j]) {
                    is_min_in_col = 0;
                    break;
                }
            }
            if (is_min_in_row && is_min_in_col) {
                printf("Седловая точка найдена на позиции [%d][%d]: %d\n", i + 1, j + 1, matrix[i][j]);
                found = 1;
            }
        }
    }
    if (!found) {
        printf("Седловых точек не найдено.\n");
    }
}

// Очистка памяти
void free_matrix(int** matrix, int rows) {
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

int main() {
    setlocale(LC_CTYPE, "RUS");
    int rows, cols;
    int choice, randomize;
    int** matrix = NULL;

    while (1) {
        printf("\nМеню:\n");
        printf("1. Инициализировать матрицу\n");
        printf("2. Показать матрицу\n");
        printf("3. Подсчитать отрицательные элементы в строках с нулями\n");
        printf("4. Найти седловые точки\n");
        printf("5. Завершить программу\n");
        printf("Выберите действие: ");
        scanf_s("%d", &choice);

        switch (choice) {
        case 1:
            if (matrix) {
                free_matrix(matrix, rows);
            }
            printf("Введите количество строк и столбцов: ");
            scanf_s("%d %d", &rows, &cols);
            printf("Выберите способ инициализации:\n1. Случайные числа\n2. Ввод с консоли\n");
            scanf_s("%d", &randomize);
            matrix = create_matrix(rows, cols, randomize == 1);
            break;

        case 2:
            if (matrix) {
                print_matrix(matrix, rows, cols);
            }
            else {
                printf("Матрица не инициализирована.\n");
            }
            break;

        case 3:
            if (matrix) {
                count_negatives_in_rows_with_zero(matrix, rows, cols);
            }
            else {
                printf("Матрица не инициализирована.\n");
            }
            break;

        case 4:
            if (matrix) {
                find_saddle_points(matrix, rows, cols);
            }
            else {
                printf("Матрица не инициализирована.\n");
            }
            break;

        case 5:
            if (matrix) {
                free_matrix(matrix, rows);
            }
            printf("Завершение программы.\n");
            return 0;

        default:
            printf("Некорректный ввод. Повторите попытку.\n");
        }
    }
}

