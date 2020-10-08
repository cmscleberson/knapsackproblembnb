

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    int peso;
    int valor;
    double densidade;
} item;

//Compara itens pela densidade
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






// Função de bounding
double bound(item *items, int n, int capac, int pesoAtual, int valorAtual, int nivel)
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

        //Caso base, nova mochila
        *maxValor = *valorAtual;
        memcpy(maxMochila, mochilaAtual, n * sizeof(int));
        return;
    }


    if (*pesoAtual + items[nivel].peso <= capac && bound(items, n, capac, *pesoAtual, *valorAtual, nivel + 1) > *maxValor)
    {


        //Tenta adicionar novos items a mochila
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




void ordPorDens (item *items, int n) {
    int k, j;
    item aux;

    for (k = 1; k < n; k++)
        {
            for (j = 0; j < n - k; j++)
            {
                if (items[j].densidade < items[j + 1].densidade) {
                    aux          = items[j];
                    items[j]     = items[j + 1];
                    items[j + 1] = aux;
            }
        }
    }
}




int mochilaUtil(int *pesos, int *valores,int n, int capac, int **maxMochila)
{
    int pesoAtual = 0;
    int valorAtual = 0;
    int benefMax = 0;
    int i, k;
    item *items  = (item*) malloc(n * sizeof(item));
    int *mochilaAtual = (int*) malloc(n*sizeof(int));
    *maxMochila = (int*) malloc(n * sizeof(int));

    //Verifica a alocação de memória
    if (!(items && mochilaAtual && *maxMochila)) {
        free(items);
        free(mochilaAtual);
        free(*maxMochila);
        *maxMochila = NULL;
        return 0;
    }


    for (i = 0; i < n; i++) {
        items[i].id = i;
        items[i].peso = pesos[i];
        items[i].valor = valores[i];
        items[i].densidade = valores[i] / pesos[i];
    }




    ordPorDens(items, n);





    //qsort(items, n, sizeof(item), (int (*)(const void *, const void *))comparaItems);



    for(k=0; k<n; k++)
    {

        printf("\nOrdenando por densidade :: %.2f", items[k].densidade);
    }


    mochilaRec(items, n, capac, mochilaAtual, &pesoAtual,&valorAtual, *maxMochila, &benefMax, 0);
    free(items);
    free(mochilaAtual);
    return benefMax;
}












int main(void)
{
    int pesos[] =   {5,  1,  4,  2, 6, 8,  10, 9};
    int valores[] = {20, 10, 12, 8, 9, 12, 35, 36};
    int n = sizeof(valores) / sizeof(valores[0]);

    int m = 4;
    int confl[m][2];





    int capac = 28;
    int *maxMochila;
    int maxBenef = mochilaUtil(pesos, valores, n, capac, &maxMochila);
    int i;
    printf("\nBeneficio: %d\n", maxBenef);
    printf("\nMochila possui\n");
    for (i = 0; i < n; i++) {
        if (maxMochila[i] == 1) {
            printf("Item %u com peso %d e beneficio %d\n", i, pesos[i], valores[i]);
        }
    }
    free(maxMochila);
    return 0;
}
