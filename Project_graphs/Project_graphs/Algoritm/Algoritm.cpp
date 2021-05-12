#include <iostream>
#include <stdio.h>
#include <vector>
#include <queue>
#include <ctime>

using namespace std;

const int inf = 1e9;

int n, m, s, t;       //Количество вершин и ребер, исток и сток
int c[1000][1000];    //Матрица пропускных способностей
int e[1000], h[1000]; //Переполнение и высота
int MaxFlow = 0;      //Максимальный поток


int push(int from, int to) {/* Протолкнуть по ребру */
    int pushed = min(e[from], c[from][to]);//Проталкиваем настолько, на сколько переполнен from, но не более, чем позволит протолкнуть ребро
    if (to == t)                           //Если протолкнули в сток, добавляем в ответ
        MaxFlow += pushed;
    e[from] -= pushed;
    e[to] += pushed;
    c[from][to] -= pushed;
    c[to][from] += pushed;
    return pushed;
}


void lift(int v) {/* Поднять вершину */
    /* Ищем вершину с минимальной высотой и устанавливаем высоту на единицу больше, если таковая есть */
    int New = inf;
    for (int i = 0;i < m;i++) {
        if (c[v][i] > 0) {
            New = min(New, h[i]);
        }
    }
    if (New != inf)
        h[v] = New + 1;
}


void discharge(int v) {/* Разрядить */
    /* Пока вершина переполнена, проталкиваем во все вершины, затем поднимаем */
    while (e[v] > 0) {
        for (int i = 0;i < m;i++) {
            if (c[v][i] > 0 && h[v] == h[i] + 1) {
                push(v, i);
            }
        }
        lift(v);
    }
}


int main()
{
    setlocale(LC_ALL, "RUS");
    printf("================Ввод исходных данных=============\n");
    printf("Введите количество вершин:");
    scanf_s("%d", &n);
    printf("Введите количество ребер:");
    scanf_s("%d", &m);
    printf("Выберите исток:");
    scanf_s("%d", &s);
    printf("Выберите сток:");
    scanf_s("%d", &t);

    for (int i = 0;i < m;i++) {
        int a, b, cap;
        printf("Введите начало %d-ого ребра:", i + 1);
        scanf_s("%d", &a);
        printf("Введите конец %d-ого ребра:", i + 1);
        scanf_s("%d", &b);
        printf("Введите пропускную способность %d-ого ребра:", i + 1);
        scanf_s("%d", &cap);
        c[a][b] = cap;
    }
    int beg = time(NULL);
    /* Начальная инициализация */
    e[s] = inf;
    h[s] = n;
    for (int i = 0;i < m;i++) {
        if (c[s][i] > 0) {
            push(s, i);
        }
    }

    while (true) { //Пока есть вершины, которые нужно разрядить
        bool good = false; 
        for (int i = 0;i < m;i++) {
            if (i != s && i != t && e[i] > 0) {
                discharge(i);
                good = true;
            }
        }
        if (!good) //Все вершины разряжены - предпоток - есть максимальный поток
            break;
    }

    printf("================Результаты работы=============\n");

    printf("Максимальный поток=%d\n", MaxFlow);

    for (int i = 0;i < m;i++) {
        for (int j = 0;j < m;j++) {
            printf("%3d ", c[i][j]);
        }
        printf("\n");
    }

    int en = time(NULL);
    printf("Время выполнения=%d\n", en - beg);
    return 0;
}

