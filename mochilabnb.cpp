
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* A knapsack item */
typedef struct {
    int id;
    int peso;
    int valor;
    double densidade;
} item;

/* Compare items by lesser profit density */
int comparaItems(item *item1, item *item2)
{
    if (item1->densidade > item2->densidade) {
        return -1;
    }
    if (item1->densidade < item2->densidade) {
        return 1;
    }
    return 0;
}

/* Bounding function */
double bound(item *items, int n, double capac, double pesoAtual, double valorAtual, int nivel)
{
    double capacRestante = capac - pesoAtual;
    double bound = valorAtual;
    int lvl = nivel;
    /* Fill in order of decreasing profit density */
    while (lvl < n &&
        items[lvl].peso <= capacRestante)
    {
        capacRestante -= items[lvl].peso;
        bound += items[lvl].valor;
        lvl++;
    }
    /* Pretend we can take a fraction of the next object */
    if (lvl < n) {
        bound += items[lvl].densidade
            * capacRestante;
    }
    return bound;
}

void mochilaRec(item *items, int n, int capac,int *mochilaAtual, int *pesoAtual, int *valorAtual, int *maxMochila, int *maxValor, int nivel)
{
    if (nivel == n) {

        /* Found a new max knapsack */
        *maxValor = *valorAtual;
        memcpy(maxMochila, mochilaAtual, n * sizeof(int));
        return;
    }
    if (*pesoAtual + items[nivel].peso <= capac)
    {   /* Try adding this item */
        *pesoAtual += items[nivel].peso;
        *valorAtual += items[nivel].valor;
        mochilaAtual[items[nivel].id] = 1;
        mochilaRec(items, n, capac, mochilaAtual, pesoAtual,valorAtual, maxMochila, maxValor, nivel + 1);
        *pesoAtual -= items[nivel].peso;
        *valorAtual -= items[nivel].valor;
        mochilaAtual[items[nivel].id] = 0;
    }
    if (bound(items, n, capac, *pesoAtual, *valorAtual, nivel + 1) > *maxValor) {
        /* Still promising */
        mochilaRec(items, n, capac, mochilaAtual, pesoAtual,valorAtual, maxMochila, maxValor, nivel + 1);
    }
}

int mochilaUtil(int *pesos, int *valores,int n, int capac, int **maxMochila)
{
    int pesoAtual = 0.0;
    int valorAtual = 0.0;
    int benefMax = 0.0;
    int i;
    item *items  = (item*) malloc(n * sizeof(item));
    int *mochilaAtual = (int*) calloc(n, sizeof(int));
    *maxMochila = (int*) malloc(n * sizeof(int));
    if (!(items && mochilaAtual && *maxMochila)) {
        free(items);
        free(mochilaAtual);
        free(*maxMochila);
        *maxMochila = NULL;
        return 0;
    }



    /* Populate the array of items */
    for (i = 0; i < n; i++) {
        items[i].id = i;
        items[i].peso = pesos[i];
        items[i].valor = valores[i];
        items[i].densidade = valores[i] / pesos[i];
    }




    /* Sort into decreasing density order */
    qsort(items, n, sizeof(item), (int (*)(const void *, const void *))comparaItems);
    mochilaRec(items, n, capac, mochilaAtual, &pesoAtual,&valorAtual, *maxMochila, &benefMax, 0);
    free(items);
    free(mochilaAtual);
    return benefMax;
}



int main(void)
{
    int pesos[] = {3, 5, 2, 1};
    int valores[] = {9, 10, 7, 4};
    int n = sizeof(valores) / sizeof(valores[0]);
    int capac = 7;
    int *maxMochila;
    int maxBenef = mochilaUtil(pesos, valores, n, capac, &maxMochila);
    int i;
    printf("Beneficio: %d\n", maxBenef);
    printf("Mochila possui:\n");
    for (i = 0; i < n; i++) {
        if (maxMochila[i] == 1) {
            printf("Item %u com peso %d e beneficio %d\n", i, pesos[i], valores[i]);
        }
    }
    free(maxMochila);
    return 0;
}
