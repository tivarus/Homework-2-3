#include <stdio.h>
#include <stdbool.h>

int Sort(int* array, int numbers, int ribs) {

    int i, n, j, temp[numbers];
    for (int i = 0; i < numbers; i++) {
        temp[i] = array[i];
    }
    for (i = 0; i < numbers - 1; i++) {
       for (j = 0; j < numbers - i - 1; j++) {
           if(temp[j] > temp[j+1]) {
              int n = temp[j];
              temp[j] = temp[j+1];
              temp[j+1] = n;
           }
       }
    }

    int duplicates = 0;
    for (int i = 1; i < numbers; i++) {
        if (temp[i] == temp[i-1]) {
            ++duplicates;
        }
    }
    int count = numbers - duplicates - ribs;
    return count;
}

int SearchCycle (int numbers, int* array, int a, int x, int size, int* check, int start, int h){
    int error;
    for(int a = 0; a < numbers; ++a) {
        if (start == array[a] && a != h) {

            if (a % 2 != 0) {
                --a;
            } else {
                ++a;
            }
            x = array[a];

            for (int i = 0; i < size+1; i++) {
                if(x == check[i]) {
                    error = 1;
                }
            }

            if (error != 1) {
                ++size;
                check[size] = x;
                h = a;
                SearchCycle(numbers, array, 0, x, size, check, check[size], h);
                if (SearchCycle(numbers, array, 0, x, size, check, check[size] , h) == 1) {
                    return 1;
                }
                ++a;
            } else {
                return 1;
            }
        }
    }
    return 0;
}

int main() {
    FILE* file_graph;
    FILE* result;
    char symbol;
    int ribs = 0, numbers = 0, first, second, Loop = 0, Multiple = 0, x, size = 0, a = 0, start;

    file_graph = fopen("graph.txt", "r");
    while ((symbol = getc(file_graph)) != EOF) {
        if (symbol == '\n') {
            ribs ++;
        }
    }
    ++ribs;
    fclose(file_graph);

    numbers = ribs * 2;
    int array[numbers];
    file_graph = fopen("graph.txt", "r");
    for (int i = 0; i < numbers; i += 2) {
        fscanf(file_graph, "%d-%d", &first, &second);
        array[i] = first;
        array[i+1] = second;
    }
    fclose(file_graph);

    for(int i = 0; i < numbers; i += 2) {
        if(array[i] == array[i+1]) {
            Loop = 1;
        }
    }

    for (int i = 0; i < numbers; i += 2) {
        for ( int j = i + 2; j < numbers; j += 2){
            if ((array[i] == array[j] && array[i+1] == array[j+1]) || (array[i] == array[j+1] && array[i+1] == array[j])){
                Multiple = 1;
            }
        }
    }

    int check[numbers];
    check[size] = start = array[0];
    int h = array[1];
    int Cycle = SearchCycle(numbers, array, a, x, size, check, start, h);

    int Count = Sort(array, numbers, ribs);

    printf("Count is %d\n", Count);
    printf("Cycle is %d\n", Cycle);
    printf("Loop is %d\n", Loop);
    printf("Multiple is %d\n", Multiple);
    result = fopen("result.txt", "w");
    if (Loop == 0 && Multiple == 0 && Cycle != 1 && Count == 1){
        printf("Graph is a tree\n");

        fprintf(result, "graph {\n");
        for (int i = 0; i < numbers; i=i+2) {
            fprintf(result, "   %d -- %d;\n",array[i], array[i+1]);
        }
        fprintf(result, "}");
    } else {
    printf("Graph is NOT a tree\n");

    fprintf(result, "The last graph was NOT a tree\n");
    }
    fclose(result);
    return 0;
}
