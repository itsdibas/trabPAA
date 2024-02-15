#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int projeto;
    int tempo;
} Projeto;

typedef struct node {
    int destino;
    struct node *next;
} Node;

typedef struct {
    Node *head;
} Lista;

int max(int a, int b) {
    return (a > b) ? a : b;
}

Node* novoNode(int destino) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->destino = destino;
    newNode->next = NULL;
    return newNode;
}

void addEdge(Lista* lista, int src, int dest) {
    Node* newNode = novoNode(dest);
    newNode->next = lista[src].head;
    lista[src].head = newNode;
}

int dfs(int node, int visited[], int *stack, int *top, int *recursion_stack, Lista lista[], int nProjetos) {
    visited[node] = 1;
    recursion_stack[node] = 1;
    Node* temp = lista[node].head;
    while(temp) {
        int dest = temp->destino;
        if (!visited[dest]) {
            if (dfs(dest, visited, stack, top, recursion_stack, lista, nProjetos) == -1) {
                return -1; // ciclo detectado
            }
        } else if (recursion_stack[dest]) {
            return -1; // ciclo detectado
        }
        temp = temp->next;
    }
    recursion_stack[node] = 0;
    stack[(*top)++] = node;
    return 0;
}

int calculaTempoMinimo(Projeto projetos[], Lista lista[], int nProjetos) {
    int i;
    int* tempoTotal = (int*)calloc(nProjetos, sizeof(int));
    int* visited = (int*)calloc(nProjetos, sizeof(int));
    int* recursion_stack = (int*)calloc(nProjetos, sizeof(int));
    int* stack = (int*)malloc(nProjetos * sizeof(int));
    int top = 0;

    // Perform a DFS to find a topological sort
    for (i = 0; i < nProjetos; i++) {
        if (!visited[i]) {
            if (dfs(i, visited, stack, &top, recursion_stack, lista, nProjetos) == -1) {
                return -1; // ciclo detectado
            }
        }
    }

    // Initialize tempoTotal array with the time of each project
    for (i = 0; i < nProjetos; i++) {
        tempoTotal[i] = projetos[i].tempo;
    }

    // Calculate the total time for each project considering the dependencies
    while (top > 0) {
        int node = stack[--top];
        Node* temp = lista[node].head;
        while(temp) {
            int dest = temp->destino;
            tempoTotal[dest] = max(tempoTotal[dest], tempoTotal[node] + projetos[dest].tempo);
            temp = temp->next;
        }
    }

    // Find the maximum time among all projects
    int tempoMinimo = 0;
    for (i = 0; i < nProjetos; i++) {
        tempoMinimo = max(tempoMinimo, tempoTotal[i]);
    }

    free(tempoTotal);
    free(visited);
    free(stack);
    free(recursion_stack);

    return tempoMinimo;
}

int main() {
    int N, M;

    // Lê o número de projetos e relações de dependência
    scanf("%d %d", &N, &M);

    Projeto* projetos = (Projeto*)malloc(N * sizeof(Projeto));
    Lista* lista = (Lista*)malloc(N * sizeof(Lista));

    // Initialize adjacency list
    for (int i = 0; i < N; i++) {
        lista[i].head = NULL;
    }

    // Lê os tempos estimados de conclusão de cada projeto
    for (int i = 0; i < N; i++) {
        scanf("%d", &projetos[i].tempo);
        projetos[i].projeto = i;
    }

    // Lê as relações de dependência
    for (int i = 0; i < M; i++) {
        int origem, destino;
        scanf("%d %d", &origem, &destino);
        addEdge(lista, origem, destino);
    }

    // Calcula e imprime o tempo mínimo
    int tempoMinimo = calculaTempoMinimo(projetos, lista, N);
    if (tempoMinimo == -1) {
        printf("Ciclo detectado\n");
    } else {
        printf("%d\n", tempoMinimo);
    }

    free(projetos);
    free(lista);    

    return 0;
}
