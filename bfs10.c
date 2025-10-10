#include <stdio.h>

#define MAX 10

int queue[MAX];
int front = -1, rear = -1;
int visited[MAX];

// Function to enqueue a vertex
void enqueue(int vertex) {
    if (rear == MAX - 1) {
        printf("Queue Overflow!\n");
        return;
    }
    if (front == -1)
        front = 0;
    queue[++rear] = vertex;
}

// Function to dequeue a vertex
int dequeue() {
    if (front == -1 || front > rear)
        return -1;
    return queue[front++];
}

// BFS Function
void bfs(int adj[MAX][MAX], int n, int start) {
    int i, current;

    // Reset visited array
    for (i = 0; i < n; i++)
        visited[i] = 0;

    // Start BFS
    enqueue(start);
    visited[start] = 1;

    printf("\nBFS Traversal starting from vertex %c:\n", 'A' + start);

    while ((current = dequeue()) != -1) {
        printf("%c ", 'A' + current);

        // Visit all unvisited adjacent vertices
        for (i = 0; i < n; i++) {
            if (adj[current][i] == 1 && !visited[i]) {
                enqueue(i);
                visited[i] = 1;
            }
        }
    }

    printf("\n");
}

int main() {
    int n, adj[MAX][MAX];
    char startChar;
    int start;

    printf("Enter the number of vertices (max %d): ", MAX);
    scanf("%d", &n);

    printf("\nLabeling vertices as: ");
    for (int i = 0; i < n; i++)
        printf("%c ", 'A' + i);
    printf("\n");

    printf("\nEnter the adjacency matrix (1 for edge, 0 for no edge):\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &adj[i][j]);
        }
    }

    printf("\nEnter the starting vertex (A - %c): ", 'A' + n - 1);
    scanf(" %c", &startChar);

    start = startChar - 'A';  // Convert char label to index

    bfs(adj, n, start);

    return 0;
}

