#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

void Sort(int* array, int numbers, int* temp) {
    
    for (int i = 0; i < numbers; i++) {
        temp[i] = array[i];
    }
    for (int i = 0; i < numbers - 1; i++) {
        for (int j = 0; j < numbers - i - 1; j++) {
            if (temp[j] > temp[j + 1]) {
                int n = temp[j];
                temp[j] = temp[j + 1];
                temp[j + 1] = n;
            }
        }
    }
}

int SearchCycle(int numbers, int* array, int size, int* check, int start, int h) {
    int x;
    for (int a = 0; a < numbers; ++a) {
        if (start == array[a] && a != h) {
            if (a % 2 != 0) {
                x = array[a-1];
                h = a-1;
            } else {
                ++a;
                x = array[a];
                h = a;
            }

            for (int i = 0; i < size + 1; i++) {
                if (x == check[i]) {
                    return 1;
                }
            }

            ++size;
            check[size] = x;
            if (SearchCycle(numbers, array, size, check, x, h) == 1) {
                return 1;
            }
        }
    }
    return 0;
}

int main(void) {
    FILE* file_graph;
    FILE* result;
    char symbol;
    int numbers = 0, size = 0, start;

    file_graph = fopen("graph.txt", "r");
    while ((symbol = getc(file_graph)) != EOF) {
        if (symbol == '\n') {
            numbers++;
        }
    }
    ++numbers;
    fclose(file_graph);

    int Count = numbers;
    numbers *= 2;
    int *array = malloc(numbers * sizeof(int));
    int *check = malloc(numbers * sizeof(int));    
    int *temp = malloc(numbers * sizeof(int));

    file_graph = fopen("graph.txt", "r");
    for (int i = 0; i < numbers; i += 2) {
        fscanf_s(file_graph, "%d-%d", &array[i], &array[i + 1]);
    }
    fclose(file_graph);

    result = fopen("result.txt", "w");

    for (int i = 0; i < numbers; i += 2) {
        if (array[i] == array[i + 1]) {
            printf("Graph is NOT a tree\n");
            fprintf(result, "Graph is NOT a tree\n");
            return;
        }
        for (int j = i + 2; j < numbers; j += 2) {
            if ((array[i] == array[j] && array[i + 1] == array[j + 1]) 
             || (array[i] == array[j + 1] && array[i + 1] == array[j])) {
                printf("Graph is NOT a tree\n");
                fprintf(result, "Graph is NOT a tree\n");
                return;
            }
        }
    }

    check[size] = start = array[0];
    int h = array[1];
    if (SearchCycle(numbers, array, size, check, start, h) == 1) {
        printf("Graph is NOT a tree\n");
        fprintf(result, "Graph is NOT a tree\n");
        return;
    }
    
    Sort(array, numbers, temp);
    for (int i = 1; i < numbers; i++) {
        if (temp[i] == temp[i - 1]) {
            --Count;
        }
    }
    if (Count != 1) {
        printf("Graph is NOT a tree\n");
        fprintf(result, "Graph is NOT a tree\n");
        return;
    }
    result = fopen("result.txt", "w");
    fprintf(result, "Graph is NOT a tree\n");
    fclose(result);

    result = fopen("result.txt", "w");
    printf("Graph is a tree\n");

    fprintf(result, "graph {\n");
    for (int i = 0; i < numbers; i = i + 2) {
        fprintf(result, "   %d -- %d;\n", array[i], array[i + 1]);
    }
    fprintf(result, "}");

    fclose(result);
}
