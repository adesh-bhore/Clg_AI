#include <stdio.h>
#include <string.h> // Required for strcpy

#define MAX_NODES 10
#define INF 999

// Simple network representation
int network[MAX_NODES][MAX_NODES];
int visited[MAX_NODES];
int distance[MAX_NODES];
int parent[MAX_NODES];
char node_names[MAX_NODES][20];
int num_nodes = 0;

// Queue for BFS
int queue[MAX_NODES];
int front = 0, rear = 0;

// Simple queue operations
void enqueue(int node) {
    queue[rear] = node;
    rear++;
}

int dequeue() {
    if (front == rear) return -1;
    int node = queue[front];
    front++;
    return node;
}

int is_empty() {
    return front == rear;
}

// Add node to network
void add_node(char name[]) {
    if (num_nodes < MAX_NODES) {
        strcpy(node_names[num_nodes], name);
        num_nodes++;
        printf("Added node: %s\n", name);
    }
}

// Add connection between nodes
void add_connection(int from, int to) {
    if (from >= 0 && from < num_nodes && to >= 0 && to < num_nodes) {
        network[from][to] = 1;
        network[to][from] = 1;  // Undirected graph
        printf("Connected %s to %s\n", node_names[from], node_names[to]);
    }
}

// BFS algorithm (uninformed search)
void bfs(int start) {
    // Initialize
    for (int i = 0; i < num_nodes; i++) {
        visited[i] = 0;
        distance[i] = INF;
        parent[i] = -1;
    }
    
    // Start BFS
    visited[start] = 1;
    distance[start] = 0;
    enqueue(start);
    
    printf("\nBFS traversal from %s:\n", node_names[start]);
    
    while (!is_empty()) {
        int current = dequeue();
        printf("Visiting: %s\n", node_names[current]);
        
        // Check all neighbors
        for (int i = 0; i < num_nodes; i++) {
            if (network[current][i] == 1 && visited[i] == 0) {
                visited[i] = 1;
                distance[i] = distance[current] + 1;
                parent[i] = current;
                enqueue(i);
                printf("  Found neighbor: %s (distance: %d)\n", node_names[i], distance[i]);
            }
        }
    }
}

// Print shortest path
void print_path(int start, int end) {
    if (distance[end] == INF) {
        printf("No path exists from %s to %s\n", node_names[start], node_names[end]);
        return;
    }
    
    // Reconstruct path
    int path[MAX_NODES];
    int path_length = 0;
    int current = end;
    
    while (current != -1) {
        path[path_length] = current;
        path_length++;
        current = parent[current];
    }
    
    // Print path
    printf("Shortest path from %s to %s (distance: %d):\n", 
           node_names[start], node_names[end], distance[end]);
    
    for (int i = path_length - 1; i >= 0; i--) {
        printf("%s", node_names[path[i]]);
        if (i > 0) printf(" -> ");
    }
    printf("\n");
}

// Simple packet sending simulation
void send_packet(int start, int end) {
    if (distance[end] == INF) {
        printf("Cannot send packet: No path exists from %s to %s\n", 
               node_names[start], node_names[end]);
        return;
    }
    
    // Reconstruct path
    int path[MAX_NODES];
    int path_length = 0;
    int current = end;
    
    while (current != -1) {
        path[path_length] = current;
        path_length++;
        current = parent[current];
    }
    
    printf("\n=== PACKET SENDING SIMULATION ===\n");
    printf("Sending packet from %s to %s...\n\n", node_names[start], node_names[end]);
    
    // Simulate packet traveling through the path
    for (int i = path_length - 1; i >= 0; i--) {
        printf("Packet at: %s", node_names[path[i]]);
        
        if (i == path_length - 1) {
            printf(" (SOURCE)");
        } else if (i == 0) {
            printf(" (DESTINATION)");
        } else {
            printf(" (HOP %d)", path_length - i - 1);
        }
        
        printf("\n");
        
        // Add a small delay effect (just print dots)
        if (i > 0) {
            printf("  Traveling to next node");
            for (int j = 0; j < 3; j++) {
                printf(".");
                // In a real program, you might use sleep(1) here
            }
            printf("\n\n");
        }
    }
    
    printf("=== PACKET DELIVERED SUCCESSFULLY ===\n");
    printf("Packet reached %s via shortest path!\n", node_names[end]);
    printf("Total hops: %d\n", distance[end]);
}

// Display network
void show_network() {
    printf("\nNetwork connections:\n");
    for (int i = 0; i < num_nodes; i++) {
        printf("%s: ", node_names[i]);
        for (int j = 0; j < num_nodes; j++) {
            if (network[i][j] == 1) {
                printf("%s ", node_names[j]);
            }
        }
        printf("\n");
    }
}

int main() {
    printf("=== SIMPLE UNINFORMED SEARCH (BFS) WITH PACKET SENDING ===\n\n");
    
    // Initialize network
    for (int i = 0; i < MAX_NODES; i++) {
        for (int j = 0; j < MAX_NODES; j++) {
            network[i][j] = 0;
        }
    }
    
    // Add nodes
    add_node("A");
    add_node("B");
    add_node("C");
    add_node("D");
    add_node("E");
    
    // Add connections
    add_connection(0, 1);  // A to B
    add_connection(0, 2);  // A to C
    add_connection(1, 2);  // B to C
    add_connection(1, 3);  // B to D
    add_connection(2, 4);  // C to E
    add_connection(3, 4);  // D to E
    
    // Show network
    show_network();
    
    // Run BFS from node A (index 0)
    printf("\n=== BFS SEARCH FROM NODE A ===\n");
    bfs(0);
    
    // Show results
    printf("\n=== SHORTEST DISTANCES ===\n");
    for (int i = 0; i < num_nodes; i++) {
        if (distance[i] == INF) {
            printf("%s: Not reachable\n", node_names[i]);
        } else {
            printf("%s: %d steps\n", node_names[i], distance[i]);
        }
    }
    
  /*   // Find shortest path to E
    printf("\n=== SHORTEST PATH EXAMPLE ===\n");
    print_path(0, 4);  // From A to E */
    
    // Prompt user for start and end node for packet sending
    int start_idx = -1, end_idx = -1;
    char start_name[20], end_name[20];

    printf("\nEnter START node name for packet sending: ");
    scanf("%19s", start_name);
    printf("Enter END node name for packet sending: ");
    scanf("%19s", end_name);

    // Find indices for the entered node names
    for (int i = 0; i < num_nodes; i++) {
        if (strcmp(node_names[i], start_name) == 0) {
            start_idx = i;
        }
        if (strcmp(node_names[i], end_name) == 0) {
            end_idx = i;
        }
    }

    if (start_idx == -1 || end_idx == -1) {
        printf("Invalid node name(s) entered. Using default: A to E.\n");
        start_idx = 0;
        end_idx = 4;
    }

    // Packet sending simulation
    printf("\n=== PACKET SENDING FEATURE ===\n");
    send_packet(start_idx, end_idx);  // Send packet from user-specified nodes
    
    
    
    return 0;
} 