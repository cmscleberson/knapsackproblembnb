

#include <stdio.h>


#define MAX 100



int i,j,n,qtdeConflitos, capacMoch;
int listaTempSelec[MAX],listaFimSelec[MAX],valorFinal=-1,pesoFinal,conflitos[MAX];
float dens[MAX];


typedef struct Item
{
    int id;
    int peso;
    int valor;
    float densidade;

} Item;


Item itens[MAX];


void get()
{

    n = 5;
    capacMoch = 40;

    printf("\n Total number of items: ");
    printf("%d",n);

    printf("\n Maximum capacity of the Sack: ");
    printf("%d",capacMoch);

    for(i=0; i<MAX; i++)
    {
        itens[i].peso = 0;
        itens[i].valor = 0;
        itens[i].densidade = 0.00;
        conflitos[i] = 0;
        dens[i] = 0.00;
        listaFimSelec[i] = 0;
        listaTempSelec[i] = 0;
    }


    itens[0].peso = 10;
    itens[1].peso = 7;
    itens[2].peso = 11;
    itens[3].peso = 15;
    itens[4].peso = 20;


    itens[0].valor = 50;
    itens[1].valor = 56;
    itens[2].valor = 44;
    itens[3].valor = 45;
    itens[4].valor = 40;


    itens[0].valor = 50;
    itens[1].valor = 56;
    itens[2].valor = 44;
    itens[3].valor = 45;
    itens[4].valor = 31;


    for(i=0;i<n;i++)
    {
        printf("\n Profit of the item # %d : ", i+1);
        printf("%d",itens[i].valor);

        itens[i].id = i;
        itens[i].densidade = (float) itens[i].valor/ (float)itens[i].peso;
        dens[i] = itens[i].densidade;
        printf("\n------ Densidade do item ::: %.2f", itens[i].densidade);
}}


void show()
{

    float s=0.0;


    printf("\n\tItem\tPeso\tCusto\tSelecionado ");

    for(i=0;i<n;i++)
    {
        printf("\n\t%d\t%d\t%d\t%d",i+1,itens[i].peso,itens[i].valor,listaFimSelec[i]);
    }


    printf("\n\n The Sack now holds following items : ");

    for(i=0;i<n;i++)
    {
        if(listaFimSelec[i]==1)
        {
            printf("%d\t",i+1);
            s += (float) itens[i].valor * (float) listaFimSelec[i];
        }
    }
    printf("\n Maximum Profit: %f ",s);
}


/*Arrange the item based on high profit per Unit*/

void sort()
{

    for(i=0;i<n;i++)

    dens[i] = (float) itens[i].valor / (float) itens[i].peso;
}

void sort2()
{
    int t,t1;
    float t2;
    for(i=0;i<n;i++)

    dens[i] = (float) itens[i].valor / (float) itens[i].peso;


    for(i=0;i<n-1;i++)
    {
        for(j=i+1;j<n;j++)
        {
            if(dens[i]  < dens[j])
            {
                t2 = dens[i];
                dens[i] = dens[j];
                dens[j] = t2;

                t = itens[i].valor;
                itens[i].valor =itens[j].valor;
                itens[j].valor = t;

                t1 = itens[i].peso;
                itens[i].peso = itens[j].peso;
                itens[j].peso =t1;
}}}}





float bound(float valorAtual,float pesoAtual,int k)
{
    float vAtual = valorAtual;
    float pAtual = pesoAtual;

    for(i=k;i<=n;i++)
    {
        pAtual = pAtual+itens[i].peso;

        if( pAtual < capacMoch)
            vAtual = vAtual +itens[i].valor;
        else return (vAtual+(1-(pAtual-capacMoch)/ (float)itens[i].peso)*itens[i].valor);
    }

    return vAtual;
}


int verConfl(int idx)
{


}


void knapsack(int k,float valorAtual,float pesoAtual)
{
    if(pesoAtual+itens[k].peso <= capacMoch && bound(valorAtual,pesoAtual,k) >= valorFinal)
    {
        if(verConfl==1) knapsack(k+1,valorAtual,pesoAtual);
        listaTempSelec[k] = 1;
        if(k <= n) knapsack(k+1,valorAtual+itens[k].valor,pesoAtual+itens[k].peso);
        if(((valorAtual+itens[k].valor) > valorFinal) && ( k == n));
        {
            valorFinal = valorAtual+itens[k].valor;
            pesoFinal = pesoAtual+itens[k].peso;
            for(j=0;j<=k;j++)
            {
               listaFimSelec[j] = listaTempSelec[j];
    }}}

     listaTempSelec[k] = 0;
    if( k <= n)
        knapsack(k+1,valorAtual,pesoAtual);

    if((valorAtual > valorFinal) && (k == n))
    {
        valorFinal = valorAtual;
        pesoFinal = pesoAtual;
        for(j=0;j<=k;j++)
        {
            listaFimSelec[j] = listaTempSelec[j];
}}}


int main()
{
    get();

    printf("\n Mochila Final\n");

    //sort();

    knapsack(0,0.0,0.0);
    show();

    return 1;
}


