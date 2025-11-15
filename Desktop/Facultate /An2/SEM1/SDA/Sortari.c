#include <stdio.h>

typedef struct{
    int cheie;
}Ap;

Ap a[5001],b[5001];
Ap c[8];

int n=8;

#define mm 8
#define T 3
int h[T];

#define MAX 1500

void generare(Ap a[],int n)
{
    for(int i=0;i<n;i++)
    a[i].cheie=n-1-i;
}

void inseration_sort(Ap a[],int n)
{
    Ap temp;
    int j;
    for(int i=0;i<n;i++)
    {
        temp = a[i];
        for(j=i; (j>0) && (temp.cheie)<(a[j-1].cheie) ; j--)
            a[j]=a[j-1];
        a[j] = temp;
    }
}

int comparare(Ap el1, Ap el2)
{
    return el1.cheie-el2.cheie;
}

void swap(Ap* el1, Ap* el2)
{
    Ap temp;
    temp = *el1;
    *el1 = *el2;
    *el2 = temp;
}

void selection_Sort(Ap a[], int n)
{
    int min;
    for(int i=0;i<n-1;i++)
    {
        min = i ;
        for(int j=i+1;j<n;j++)
        {
            if(a[j].cheie < a[min].cheie)
                min = j;
        }

        swap(&a[i],&a[min]);
    }
}

void bubble_sort(Ap a[],int n)
{
    for(int i=0;i<n;i++)
    {
        for(int j = n-1;j>i;j--)
            if(a[j].cheie < a[j-1].cheie)
            swap(&a[j],&a[j-1]);
        }
}

void generare_incrementare(int h[],int t)
{
    h[T-1] = 1;
    for(int i=T-2;i>=0;i--)
    {
        h[i] = 3 * h[i+1] - 1;
    }
}

void shell_sort(Ap a[],int n)
{
    Ap temp;
    generare_incrementare(h,T);
    int l;
    for(int i=0;i<T;i++)
    {
        int H = h[i];
        for(int j=0;j<H;j++)
        {
            for(int k=H+j;k<n;k=k+H)
            {
                temp = a[k];
                for(l=k;(l-H >=0) && (temp.cheie<a[l-H].cheie);l=l-H)
                {
                    a[l]=a[l-H];
                }
                a[l]=temp;
            }
        }
    }
}

void quicksort(Ap a[], int prim, int ultim)
{
    int st = prim+1;
    int dt = ultim;

    swap(&a[st],&a[(dt+st)/2]);
    Ap temp = a[prim];
    while(st<=dt)
    {
        while(a[st].cheie<temp.cheie)
        st++;
        while(temp.cheie<a[dt].cheie)
        dt--;
        if(st<dt)
        swap(&a[st++],&a[dt--]);
        else
        st++;
    }

    swap(&a[dt],&a[prim]);
    if(prim<dt-1)
    quicksort(a,prim,dt-1);
    if(dt+1<ultim)
    quicksort(a,dt+1,ultim);
}

void deplasare(Ap a[], int st, int dt)
{
	int fiu = 2 * st + 1;
	while (fiu <= dt)
	{
		if (fiu < dt && a[fiu].cheie < a[fiu + 1].cheie)
			fiu++;								
		if (a[st].cheie < a[fiu].cheie)  
		{										
			swap(&a[st], &a[fiu]);			
			st = fiu;
			fiu = 2 * st + 1;
		}
		else
			fiu = dt + 1;
	}
}

void mergesort(Ap A[],Ap temp[],int left,int right)
{
   	if (left == right) 
    return; 
	int mid = (left + right) / 2;
	mergesort(A, temp, left, mid);
	mergesort(A, temp, mid + 1, right);
	for (int i = left; i <= right; i++) 
    temp[i] = A[i]; 
	int i1 = left; int i2 = mid + 1; 
	for (int index = left; index <= right; index++) 
    {
		if (i1 == mid + 1)
         A[index] = temp[i2++];  
		else if (i2 > right) 
        A[index] = temp[i1++];
		else if (temp[i1].cheie < temp[i2].cheie) 
        A[index] = temp[i1++];
		else A[index] = temp[i2++];
	}
}


void heapsort(Ap a[], int n)
{
    for(int i=n/2-1;i>=0;i--)
    {
        deplasare(a,i,n-1);      
    }

    for(int i = n-1;i>=1;i--)
    {
        swap(&a[0],&a[i]);
        deplasare(a,0,i-1);
    }
}


void sortare_liniara(Ap a[], Ap b[], int n)
{
	int i;
	for (i = 0; i < n; i++)
		b[a[i].cheie] = a[i];
}
void afisare(Ap a[], int n)
{
	int i;
	for (i = 0; i < n; ++i)
		printf("%d ", a[i].cheie);
	printf("\n");
}
void binsort(Ap a[], int n)
{
	int i;
	for (i = 0; i < n; i++)
		while (a[i].cheie != i)
			swap(&a[i], &a[a[i].cheie]);
}


#define M 10
typedef int Ap2;


Ap2 numar[M];

void countingsort(Ap a[], Ap b[], int n)
{
	for (int j = 1; j <= M - 1; j++) 
    numar[j] = 0;
	for (int i = 1; i <= n; i++) 
    numar[a[i - 1].cheie] = numar[a[i - 1].cheie] + 1; 
	for (int j = 1; j <= M - 1; j++)
    numar[j] = numar[j - 1] + numar[j]; 
	for (int i = n; i >= 1; i--)
	{
		b[numar[a[i - 1].cheie] - 1] = a[i - 1];
		numar[a[i - 1].cheie] = numar[a[i - 1].cheie] - 1;
    }
	for (int i = 1; i <= n; i++) 
    a[i - 1] = b[i - 1];
}

unsigned biti(unsigned x,int k, int j)
{
    return (x>>k) & ~(~0 << j);
}

void radinters(int st,int dt,int b,int a[])
{
    int temp;
    if((dt>st) && (b>=0))
    {
        int i = st;
        int j = dt;
        do{
            while ((biti(a[i],b,1) == 0) && (i<j)) 
            i++;
            while ((biti(a[j],b,1) == 1) && (i<j))
            j--;
        }while(!(i==j));

        if(biti(a[dt],b,1) == 0)
        {
            j++;
        }

        radinters(st,j-1,b-1,a);
        radinters(j,dt,b-1,a);
    }
}

#define m 2
#define m1 m*m
int t[m1];

void radixdirect(int a[], int n, int b)
{
	int trecere;
	int numar[m1]; 
	int aux;
	for (trecere = 0; trecere <= (b / m) - 1; trecere++)
	{
		for (int j = 0; j <= m1 - 1; j++)
			numar[j] = 0;
		for (int i = 0; i <= n - 1; i++)
		{
			aux = biti(a[i], trecere * m, m);
			numar[aux] = numar[aux] + 1;
		}
		for (int j = 1; j <= m1 - 1; j++)      
			numar[j] = numar[j - 1] + numar[j];
		for (int i = n - 1; i >= 0; i--)
		{
			aux = biti(a[i], trecere * m, m);
			t[numar[aux] - 1] = a[i];           
			numar[aux] = numar[aux] - 1;
		}
		for (int i = 0; i < n; i++) 
        a[i] = t[i];
	}
} 

int main()
{
    return 0;
}
