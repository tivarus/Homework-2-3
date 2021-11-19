#include <stdio.h>
#include <stdbool.h>

int main(){
    FILE* file_graph;
    FILE* result;
    char s, f;
    int n, u, v, m, g, k = 0, z = 0, q = 0;

    //подсчет количества ребер
    file_graph = fopen("graph.txt", "r");
    while ((s = getc(file_graph)) != EOF) {
        putc(s, stdin);
        if (s == '\n')
            n ++;
    }
    ++n;
    fclose(file_graph);

    //запись графа в двумерный массив
    int edges[n][2];
    file_graph = fopen("graph.txt", "r");
    for (int i = 0; i < n; i++) {
        fscanf(file_graph, "%d%c%d;", &u, &f, &v);
        if (f == ';')
            k = 1;
        edges[i][0] = u;
        edges[i][1] = v;
    }
    fclose(file_graph);
    m = n * 2;//кол-во записанных цифр в файле
    int a[m];
    int i, b;

    //проверка на петли
    for(int i = 0; i < n; i++) {
        if(edges[i][0] == edges[i][1])
            z = 1;
    }

    //проверка на кратность
    for(int i = 0; i < n; i++) {
        for( int b = i + 1; b < n; b++){
            if((edges[i][0] == edges[b][0] && edges[i][1] == edges[b][1]) || (edges[i][1] == edges[b][0] && edges[i][0] == edges[b][1]))
                q = 1;
        }
    }

    //подсчет количества вершин
    while(i != n + 1){//запись графа в одномерный массив
        a[b]=edges[i][0];
        ++b;
        a[b]=edges[i][1];
        ++b;
        ++i;
    }

    bool p;
    for (int i = m - 1; i >= 0; i--) {//сортировка массива
        p = 1;
        for (int j = 0; j < i; j++) {
            if (a[j] > a[j + 1]) {
                g = a[j];
                a[j] = a[j + 1];
                a[j + 1] = g;
                p = 0;
            }
        }
        if (p == 1)
            break;
    }
    int c = 0;
    for (int i = 1; i < m; i++) {//кол-во повтор€ющихс€ цифр
        if (a[i] == a[i-1])
            ++c;
    }
    int d = m - c - n; //всего цифр минус кол-во повтор€ющихс€ цифр минус число ребер, если !=1 то граф не дерево

    //вывод результата
    if (z == 0 && q == 0 && k == 0 && d == 1){
        puts("Graph is a tree\n");
        result = fopen("result.txt", "w");
        fprintf(result, "graph {\n");
        for(int i = 0; i < n; i++) //запись графа в файл result на €зыке dot, если он €вл€етс€ деревом
            fprintf(result, "   %d -- %d;\n",edges[i][0], edges[i][1]);
        fprintf(result, "}");
        fclose(result);
    } else {
        puts("graph is NOT a tree\n");
        result = fopen("result.txt", "w");
        fprintf(result, "Graph is NOT a tree\n");
        fclose(result);
    }
    return 0;
}
