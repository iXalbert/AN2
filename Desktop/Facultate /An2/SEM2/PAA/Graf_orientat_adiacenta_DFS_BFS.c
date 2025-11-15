#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VERTICES 100

// Nod din lista de adiacență
typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

// Structură graf
typedef struct Graph {
    int numVertices;
    Node* adjLists[MAX_VERTICES];
    bool visited[MAX_VERTICES];
} Graph;

// Nod nou în listă
Node* createNode(int v) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

// Inițializare graf
Graph* createGraph(int vertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices = vertices;

    for (int i = 0; i < vertices; i++) {
        graph->adjLists[i] = NULL;
        graph->visited[i] = false;
    }
    return graph;
}

// Adaugă muchie orientată
void addEdge(Graph* graph, int src, int dest) {
    Node* newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;
}

// BFS
void BFS(Graph* graph, int startVertex) {
    int queue[MAX_VERTICES], front = 0, rear = 0;
    graph->visited[startVertex] = true;
    queue[rear++] = startVertex;

    while (front < rear) {
        int current = queue[front++];
        printf("%d ", current);

        Node* temp = graph->adjLists[current];
        while (temp) {
            int adj = temp->vertex;
            if (!graph->visited[adj]) {
                graph->visited[adj] = true;
                queue[rear++] = adj;
            }
            temp = temp->next;
        }
    }
}

// DFS
void DFS(Graph* graph, int vertex) {
    graph->visited[vertex] = true;
    printf("%d ", vertex);

    Node* temp = graph->adjLists[vertex];
    while (temp) {
        int adj = temp->vertex;
        if (!graph->visited[adj])
            DFS(graph, adj);
        temp = temp->next;
    }
}

// Resetare vizite
void resetVisited(Graph* graph) {
    for (int i = 0; i < graph->numVertices; i++)
        graph->visited[i] = false;
}

int main() {
    Graph* graph = createGraph(6);
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 1, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 2, 4);
    addEdge(graph, 3, 5);
    addEdge(graph, 4, 5);

    printf("Parcurgere BFS: ");
    BFS(graph, 0);
    printf("\n");

    resetVisited(graph);
    printf("Parcurgere DFS: ");
    DFS(graph, 0);
    printf("\n");

    return 0;
}
