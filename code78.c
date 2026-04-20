#include <stdio.h>
#include <limits.h>

#define MAX 100

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    int graph[MAX][MAX];

    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            graph[i][j] = INT_MAX;
        }
    }

    for(int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        graph[u][v] = w;
        graph[v][u] = w;
    }

    int visited[MAX] = {0};
    int minEdge[MAX];

    for(int i = 1; i <= n; i++) {
        minEdge[i] = INT_MAX;
    }

    minEdge[1] = 0; 

    int totalWeight = 0;

    for(int i = 1; i <= n; i++) {
        int u = -1;

        for(int j = 1; j <= n; j++) {
            if(!visited[j] && (u == -1 || minEdge[j] < minEdge[u])) {
                u = j;
            }
        }

        visited[u] = 1;
        totalWeight += minEdge[u];

        for(int v = 1; v <= n; v++) {
            if(graph[u][v] != INT_MAX && !visited[v] && graph[u][v] < minEdge[v]) {
                minEdge[v] = graph[u][v];
            }
        }
    }

    printf("%d\n", totalWeight);
    return 0;
}