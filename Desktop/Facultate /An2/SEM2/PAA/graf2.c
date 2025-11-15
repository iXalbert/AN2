#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int graf[MAX][MAX];
int vizitat[MAX];
int ciclic = 0;
int m,n;

void dfs(int nod, int parinte){
    vizitat[nod] = 1;
    for(int i = 1; i <= n; i++){
        if(graf[nod][i]){
            if(!vizitat[i]){
                dfs(i, nod);
            } else if(i != parinte){
                ciclic = 1;
            }
        }
    }
}

int main(){
    /*
    scanf("%d %d", &n, &m);

    for(int i = 0; i < m; i++){
        int a, b;
        scanf("%d %d", &a, &b);
        graf[a][b] = graf[b][a] = 1;
    }

    int componente = 0;

    for(int i = 1; i <= n; i++){
        if(!vizitat[i]){
            dfs(i, -1);
            componente++;
        }
    }

    */
   
    FILE *f = fopen("grafuri3.txt", "r");

    if(!f){
        perror("eroare la deschidera fisierului\n");
        return 1;
    }

    fscanf(f,"%d", &n);

    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++){
            fscanf(f,"%d", &graf[i][j]);
        }
    }

    int componente = 0;

    for(int i = 1; i <= n; i++){
        if(!vizitat[i]){
            dfs(i, -1);
            componente++;
        }
    }

    printf("%d %d\n", componente, ciclic); 

    return 0;
}
