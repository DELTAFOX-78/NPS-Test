#include <stdio.h>  
int cost[10][10], dist[10], parent[10], n; 
void bellmanFord(int src) { 
    for(int i = 0; i < n; i++) { 
        dist[i] = 999; 
        parent[i] = -1; 
    } 
    dist[src] = 0; 
    for(int i = 0; i < n - 1; i++) { 
        for(int u = 0; u < n; u++) { 
            for(int v = 0; v < n; v++) { 
                if(dist[u] + cost[u][v] < dist[v]) { 
                    dist[v] = dist[u] + cost[u][v]; 
                    parent[v] = u; 
                } 
            } 
        } 
    } 
} 
int main() { 
    printf("Enter the no. of vertices: "); 
    scanf("%d", &n); 
    printf("Enter the adjacency matrix (Use 999 for infinity):\n"); 
    for(int i = 0; i < n; i++) { 
        for(int j = 0; j < n; j++) { 
            scanf("%d", &cost[i][j]); 
        } 
    }
    for(int src = 0; src < n; src++) { 
        bellmanFord(src); 
        printf("\nRouter %d\n", src); 
        for(int i = 0; i < n; i++) { 
            if(i != src) { 
                int j = i; 
                while(parent[j] != -1) { 
                    printf("%d <- ", j); 
                    j = parent[j]; 
                } 
                printf("%d \t Cost: %d\n", src, dist[i]); 
            } 
        } 
    } 
    return 0; 
}
