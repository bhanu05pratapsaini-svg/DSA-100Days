#include <stdio.h>
#include <stdlib.h>

struct Node {
    int vertex;
    struct Node* next;
};

struct Node* createNode(int v) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

void addEdge(struct Node* adj[], int u, int v) {
    struct Node* newNode = createNode(v);
    newNode->next = adj[u];
    adj[u] = newNode;
}

void topoSort(int V, struct Node* adj[]) {
    int* inDegree = (int*)calloc(V, sizeof(int));

    for (int i = 0; i < V; i++) {
        struct Node* temp = adj[i];
        while (temp != NULL) {
            inDegree[temp->vertex]++;
            temp = temp->next;
        }
    }

    int* queue = (int*)malloc(V * sizeof(int));
    int front = 0, rear = 0;

    for (int i = 0; i < V; i++) {
        if (inDegree[i] == 0) {
            queue[rear++] = i;
        }
    }

    int count = 0;

    printf("Topological Order: ");

    while (front < rear) {
        int node = queue[front++];
        printf("%d ", node);
        count++;

        struct Node* temp = adj[node];
        while (temp != NULL) {
            inDegree[temp->vertex]--;
            if (inDegree[temp->vertex] == 0) {
                queue[rear++] = temp->vertex;
            }
            temp = temp->next;
        }
    }

    if (count != V) {
        printf("\nGraph has a cycle! Topological sort not possible.\n");
    }

    free(inDegree);
    free(queue);
}

int main() {
    int V = 6;

    struct Node* adj[V];
    for (int i = 0; i < V; i++) {
        adj[i] = NULL;
    }

    addEdge(adj, 5, 2);
    addEdge(adj, 5, 0);
    addEdge(adj, 4, 0);
    addEdge(adj, 4, 1);
    addEdge(adj, 2, 3);
    addEdge(adj, 3, 1);

    topoSort(V, adj);

    return 0;
}