#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define V 5

struct Node {
    int vertex;
    int weight;
    struct Node* next;
};

struct HeapNode {
    int vertex;
    int dist;
};

struct MinHeap {
    int size;
    struct HeapNode* arr[V];
};

struct Node* createNode(int v, int w) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->vertex = v;
    newNode->weight = w;
    newNode->next = NULL;
    return newNode;
}

void addEdge(struct Node* adj[], int u, int v, int w) {
    struct Node* newNode = createNode(v, w);
    newNode->next = adj[u];
    adj[u] = newNode;
}

void swap(struct HeapNode** a, struct HeapNode** b) {
    struct HeapNode* temp = *a;
    *a = *b;
    *b = temp;
}

void heapifyUp(struct MinHeap* heap, int idx) {
    while (idx && heap->arr[(idx - 1) / 2]->dist > heap->arr[idx]->dist) {
        swap(&heap->arr[(idx - 1) / 2], &heap->arr[idx]);
        idx = (idx - 1) / 2;
    }
}

void heapifyDown(struct MinHeap* heap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < heap->size && heap->arr[left]->dist < heap->arr[smallest]->dist)
        smallest = left;

    if (right < heap->size && heap->arr[right]->dist < heap->arr[smallest]->dist)
        smallest = right;

    if (smallest != idx) {
        swap(&heap->arr[idx], &heap->arr[smallest]);
        heapifyDown(heap, smallest);
    }
}

void push(struct MinHeap* heap, int v, int dist) {
    struct HeapNode* node = (struct HeapNode*)malloc(sizeof(struct HeapNode));
    node->vertex = v;
    node->dist = dist;

    heap->arr[heap->size] = node;
    heap->size++;
    heapifyUp(heap, heap->size - 1);
}

struct HeapNode* pop(struct MinHeap* heap) {
    if (heap->size == 0) return NULL;

    struct HeapNode* root = heap->arr[0];
    heap->arr[0] = heap->arr[heap->size - 1];
    heap->size--;
    heapifyDown(heap, 0);

    return root;
}

void dijkstra(struct Node* adj[], int src) {
    int dist[V];

    for (int i = 0; i < V; i++)
        dist[i] = INT_MAX;

    dist[src] = 0;

    struct MinHeap heap;
    heap.size = 0;

    push(&heap, src, 0);

    while (heap.size > 0) {
        struct HeapNode* temp = pop(&heap);
        int u = temp->vertex;

        struct Node* crawl = adj[u];
        while (crawl != NULL) {
            int v = crawl->vertex;
            int weight = crawl->weight;

            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                push(&heap, v, dist[v]);
            }

            crawl = crawl->next;
        }
    }

    printf("Vertex\tDistance from Source\n");
    for (int i = 0; i < V; i++) {
        printf("%d\t%d\n", i, dist[i]);
    }
}

int main() {
    struct Node* adj[V];

    for (int i = 0; i < V; i++)
        adj[i] = NULL;

    addEdge(adj, 0, 1, 10);
    addEdge(adj, 0, 4, 5);
    addEdge(adj, 1, 2, 1);
    addEdge(adj, 4, 1, 3);
    addEdge(adj, 4, 2, 9);
    addEdge(adj, 4, 3, 2);
    addEdge(adj, 2, 3, 4);
    addEdge(adj, 3, 0, 7);
    addEdge(adj, 3, 2, 6);

    dijkstra(adj, 0);

    return 0;
}