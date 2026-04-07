#include <stdio.h>
#include <stdbool.h>

#define MAX 100

int adj[MAX][MAX];   
bool visited[MAX];
int n; 

bool dfs(int node, int parent) {
    visited[node] = true;

    for (int i = 0; i < n; i++) {
        if (adj[node][i]) { 
            if (!visited[i]) {
                if (dfs(i, node))
                    return true;
            }
            else if (i != parent) {
                return true; 
            }
        }
    }
    return false;
}

bool hasCycle() {
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            if (dfs(i, -1))
                return true;
        }
    }
    return false;
}

int main() {
    printf("Enter number of vertices: ");
    scanf("%d", &n);

    printf("Enter adjacency matrix:\n");
    for (int i = 0; i < n; i++) {
        visited[i] = false;
        for (int j = 0; j < n; j++) {
            scanf("%d", &adj[i][j]);
        }
    }

    if (hasCycle())
        printf("YES\n");
    else
        printf("NO\n");

    return 0;
}