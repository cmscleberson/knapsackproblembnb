/* Variable Description….

n   – Total no. of items available

w[] – Weight of each item

p[] – Profit of each item

m   – Maximum Capacity of the Sack

unit[] – Profit of each item per Unit p[]/w[]

x[] – Final list of items put into the Sack

y[] – Intermediate list of selected items

fp  – Final Profit

fw  – Final Weight

cp  – Current Profit

cw  – Current Weight

*/


#include <stdio.h>

#include <conio.h>

#define max 10


int w[max],i,j,p[max];

int n,m;

float unit[max];

int y[max],x[max],fp=-1,fw;


void get()

{

printf("\n Enter total number of items: ");

scanf("%d",&n);

printf("\n Enter the Maximum capacity of the Sack: ");

scanf("%d",&m);

for(i=0;i<n;i++)

{

printf("\n Enter the weight of the item # %d : ",i+1);

scanf("%d",&w[i]);

printf("\n Enter the profit of the item # %d : ", i+1);

scanf("%d", &p[i]);

}

}


void show()

{

float s=0.0;

printf("\n\tItem\tWeight\tCost\tUnit Profit\tSelected ");

for(i=0;i<n;i++)

printf("\n\t%d\t%d\t%d\t%f\t%d",i+1,w[i],p[i],unit[i],x[i]);

printf("\n\n The Sack now holds following items : ");

for(i=0;i<n;i++)

if(x[i]==1)

{

printf("%d\t",i+1);

s += (float) p[i] * (float) x[i];

}

printf("\n Maximum Profit: %f ",s);

}


/*Arrange the item based on high profit per Unit*/

void sort()

{

int t,t1;

float t2;

for(i=0;i<n;i++)

unit[i] = (float) p[i] / (float) w[i];


for(i=0;i<n-1;i++)

{

for(j=i+1;j<n;j++)

{

if(unit[i]  < unit[j])

{

t2 = unit[i];

unit[i] = unit[j];

unit[j] = t2;


t = p[i];

p[i] = p[j];

p[j] = t;


t1 = w[i];

w[i] = w[j];

w[j] =t1;

}

}

}

}


float boundFunction(float cp,float cw,int k)

{

float b = cp;

float c = cw;

for(i=k;i<=n;i++)

{

c = c+w[i];

if( c < m)

b = b +p[i];

else

return (b+(1-(c-m)/ (float)w[i])*p[i]);

}

return b;

}


void knapsack01(int k,float cp,float cw)

{

if(cw+w[k] <= m)

{

y[k] = 1;

if(k <= n)

knapsack01(k+1,cp+p[k],cw+w[k]);

if(((cp+p[k]) > fp) && ( k == n))

{

fp = cp+p[k];

fw = cw+w[k];

for(j=0;j<=k;j++)

x[j] = y[j];

}

}

if(boundFunction(cp,cw,k) >= fp)

{

y[k] = 0;

if( k <= n)

knapsack01(k+1,cp,cw);

if((cp > fp) && (k == n))

{

fp = cp;

fw = cw;

for(j=0;j<=k;j++)

x[j] = y[j];

}

}

}


void main()

{


printf("\n\n\n\t\t    ******** KNAPSACK PROBLEM ********");

printf("\n\t\t —————————————–");

get();

printf("\n The Sack is arranged in the order…\n");

sort();

knapsack01(0,0.0,0.0);

show();

getch();

}
