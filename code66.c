#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool dfs(int node, int** graph, int* graphColSize, int* visited, int* recStack) {
    visited[node] = 1;
    recStack[node] = 1;

    for (int i = 0; i < graphColSize[node]; i++) {
        int neighbor = graph[node][i];

        if (!visited[neighbor]) {
            if (dfs(neighbor, graph, graphColSize, visited, recStack))
                return true;
        }
        else if (recStack[neighbor]) {
            return true;
        }
    }

    recStack[node] = 0;
    return false;
}

bool hasCycle(int** graph, int graphSize, int* graphColSize) {
    int* visited = (int*)calloc(graphSize, sizeof(int));
    int* recStack = (int*)calloc(graphSize, sizeof(int));

    for (int i = 0; i < graphSize; i++) {
        if (!visited[i]) {
            if (dfs(i, graph, graphColSize, visited, recStack)) {
                free(visited);
                free(recStack);
                return true;
            }
        }
    }

    free(visited);
    free(recStack);
    return false;
}

int main() {
    int V = 4;

    int* graph[4];
    int graphColSize[4];

    graphColSize[0] = 1;
    graph[0] = (int*)malloc(sizeof(int) * 1);
    graph[0][0] = 1;

    graphColSize[1] = 1;
    graph[1] = (int*)malloc(sizeof(int) * 1);
    graph[1][0] = 2;

    graphColSize[2] = 1;
    graph[2] = (int*)malloc(sizeof(int) * 1);
    graph[2][0] = 0;

    graphColSize[3] = 0;
    graph[3] = NULL;

    if (hasCycle(graph, V, graphColSize))
        printf("YES\n");
    else
        printf("NO\n");

    return 0;
}