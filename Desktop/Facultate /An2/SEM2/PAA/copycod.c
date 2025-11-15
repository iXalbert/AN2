//copeierecod

#include <stdio.h>

#define N 100
#define INF 1000000

int graf[N][N];
int cost[N][N];
int dist[N];
int dist2[N][N];
int reach[N][N];
int viz[N];
int n;

void dfs(int nod){

    viz[nod] = 1;
    printf("%d",nod);
    for(int i=0;i<n;i++){
        if(graf[nod][i] && !viz[i]){
            dfs(i);
        }
    }
}

void bfs(int start){

    int coada[N];
    int st=0,dr=0;
    coada[dr++] = start;
    viz[start] = 1;

    while(st < dr){
        int nod = coada[st++];
        printf("%d", nod);

        for(int i=0;i<n;i++){
            if(graf[nod][i] && !viz[i]){
                viz[i] = 1;
                coada[dr++] = i;
            }
        }
    } 
}

void componente_conexe(){

    for(int i=0;i<n;i++){
        if(!viz[i]){
            printf("Compoentente conexe :");
            dfs(i);
            printf("\n");
        }
    }
}

void dijkstra(int start){

    for(int i=0;i<n;i++){
        dist[i] = INF;
        viz[i] = 0;
        }

    dist[start] = 1;

    for(int k=0;k<n;k++){
        int min_pos = -1;
        int min = INF;
        for(int i=0;i<n;i++){
            if(!viz[i] && dist[i]<min){
                min = dist[i];
                min_pos = i;
            }

            if(min_pos == -1){
                break;
            }

            viz[min_pos] = 1;

            for(int v=0;v<n;v++){
                if(cost[min_pos][v] != INF && dist[min_pos] + cost[min_pos][v] < dist[v])
                    dist[v] = dist[min_pos] + cost[min_pos][v];
            }
        }
    }

    printf("Distanta minima de la %d " , start);

    for(int i=0;i<n;i++)
        printf(" %d : %d\n", i , dist[i]);
}

void prim(int graf[N][N], int n, int start){

    for(int i=0;i<n;i++)
        viz[i] = 0;

    viz[start] = 1;

    int cost_minim = 0;

    for(int pas = 0; pas < n-1;pas++){

        int min_pondere = INF;
        int min_nod1 = -1;
        int min_nod2 = -1;

        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                if(graf[i][j] && !viz[j] && !viz[i] && graf[i][j] < min_pondere){
                    min_pondere = graf[i][j];
                    min_nod1 = i;
                    min_nod2 = j;
                } 
            }
        }

        viz[min_nod2] = 1;
        printf("Muchie %d - %d (cost %d) \n", min_nod1,min_nod2, graf[min_nod1][min_nod2]);
        cost_minim = cost_minim + graf[min_nod1][min_nod2];
    }

     printf("Cost minim: %d\n", cost_minim);
}

typedef struct {

    int u,v,cost;
}Muchie;

int t[N];

int gaseste(int x){

    if(t[x] != x)
        t[x] = gaseste(t[x]);
    return t[x];
}

void uneste(int x, int y){
    t[gaseste(x)] = gaseste(y);
}

int comp(const void *a, const void *b){
    return ((Muchie*)a)->cost - ((Muchie*)b)->cost;
}

void kruskal(Muchie muchii[], int n, int m){

    for(int i=0;i<n;i++){
        t[i]=i;
    }

    qsort(muchii,m,sizeof(Muchie),comp);

    int total;

    printf("Muchii in arborele de acoperire minim : \n");

    for(int i=0;i<m;i++){
        int u = muchii[i].u;
        int v = muchii[i].v;

        if(gaseste(u) != gaseste(v)){
            uneste(u,v);
            total = total + muchii[i].cost;
            printf("%d - %d (cost %d) \n ", u,v,muchii[i].cost);
        }
    }

    printf("Cost total : %d", total);

}

void flowyd_warshall(){

    for(int k=0;k<n;k++){
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                if(dist2[i][k] + dist2[k][j] < dist2[i][j])
                    dist2[i][j] = dist2[i][k] + dist2[k][j];
            }
        }
    }
}

void print_dist(){

    printf("MAtrocea distantelor minime \n");
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(dist2[i][j] == INF){
                printf("INF\n");
            }else{
                printf("3%d", dist2[i][j]);
            }
        }

        printf("\n");
    }
}

void warshall(){

    for(int k=0;k<n;k++){
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                reach[i][j] = reach[i][j] || (reach[i][k] && reach[k][j]);
            }
        }
    }
}

void print_warshall(){

    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            printf("%d ", reach[i][j]);
        }
        printf("\n");
    }
}

//articulatii

int tin[N],low[N];
int timer;
int is_articulation[N];

void dfs2(int u, int parent) {
    viz[u] = 1;
    tin[u] = low[u] = timer++;
    int children = 0;

    for (int v = 0; v < n; v++) {
        if (graf[u][v]) {
            if (v == parent) continue;
            if (viz[v]) {
                // muchie de întoarcere
                if (low[u] > tin[v])
                    low[u] = tin[v];
            } else {
                dfs2(v, u);
                if (low[u] > low[v])
                    low[u] = low[v];

                if (low[v] >= tin[u] && parent != -1)
                    is_articulation[u] = 1;

                children++;
            }
        }
    }

    if (parent == -1 && children > 1)
        is_articulation[u] = 1;
}

void find_articulation_points() {
    memset(viz, 0, sizeof(viz));
    memset(is_articulation, 0, sizeof(is_articulation));
    timer = 0;

    for (int i = 0; i < n; i++) {
        if (!viz[i])
            dfs2(i, -1);
    }

    printf("Puncte de articulatie:\n");
    for (int i = 0; i < n; i++) {
        if (is_articulation[i])
            printf(" - Nodul %d\n", i);
    }
} 