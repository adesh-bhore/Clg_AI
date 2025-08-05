# Simple Uninformed Search (BFS) with Packet Sending

A very simple implementation of Breadth-First Search (BFS) - an uninformed search algorithm for finding the shortest path in a network, with added packet sending simulation.

## 🎯 What This Does

This program demonstrates **uninformed search** using BFS to find the shortest path between nodes in a simple network, and includes a **packet sending simulation** that shows how data travels through the network.

## 🚀 Key Features

- **Pure BFS Algorithm**: Simple breadth-first search implementation
- **No Complex Data Structures**: Just arrays and simple functions
- **Visual Output**: Shows the search process step by step
- **Shortest Path Finding**: Finds optimal paths between nodes
- **Packet Sending Simulation**: Shows packets traveling through the network

## 📁 Files

- **`simple_search.c`** - The main program with BFS and packet sending
- **`SIMPLE_SEARCH_README.md`** - This documentation

## 🎮 How to Use

### Compile and Run
```bash
gcc -o simple_search simple_search.c
./simple_search
```

## 📊 Sample Network

The program creates this simple network:
```
A -- B -- D
|    |    |
|    |    |
C -- E
```

### Network Structure:
- **Nodes**: A, B, C, D, E
- **Connections**: A-B, A-C, B-C, B-D, C-E, D-E

## 🔍 How BFS Works (Uninformed Search)

### What is Uninformed Search?
- **No domain knowledge**: Algorithm doesn't know about the goal location
- **Systematic exploration**: Explores all possibilities level by level
- **Guaranteed optimal**: Finds shortest path (in terms of number of steps)

### BFS Algorithm Steps:
1. **Start**: Begin at the starting node
2. **Explore neighbors**: Visit all direct neighbors first
3. **Level by level**: Move to next level of neighbors
4. **Continue**: Until goal is found or all nodes visited

### Example BFS Traversal:
```
Starting from A:
Level 0: A
Level 1: B, C  
Level 2: D, E
```

## 📦 Packet Sending Feature

### What is Packet Sending?
- **Simulates data transmission**: Shows how packets travel through the network
- **Uses shortest path**: Packets follow the optimal route found by BFS
- **Visual simulation**: Shows packet movement step by step

### How Packet Sending Works:
1. **Find shortest path**: Uses BFS to determine optimal route
2. **Simulate travel**: Shows packet at each node along the path
3. **Display progress**: Shows hops and final delivery

## 🏗️ Code Structure

### Simple Data Structures:
```c
int network[10][10];        // Adjacency matrix
int visited[10];            // Track visited nodes
int distance[10];           // Shortest distances
int parent[10];             // Path reconstruction
char node_names[10][20];    // Node names
```

### Key Functions:
1. **`bfs(start)`** - Main BFS algorithm
2. **`enqueue(node)`** - Add to queue
3. **`dequeue()`** - Remove from queue
4. **`print_path(start, end)`** - Show shortest path
5. **`send_packet(start, end)`** - Simulate packet sending

## 🔍 Sample Output

```
=== SIMPLE UNINFORMED SEARCH (BFS) WITH PACKET SENDING ===

Added node: A
Added node: B
Added node: C
Added node: D
Added node: E
Connected A to B
Connected A to C
Connected B to C
Connected B to D
Connected C to E
Connected D to E

Network connections:
A: B C 
B: A C D 
C: A B E 
D: B E 
E: C D 

=== BFS SEARCH FROM NODE A ===

BFS traversal from A:
Visiting: A
  Found neighbor: B (distance: 1)
  Found neighbor: C (distance: 1)
Visiting: B
  Found neighbor: D (distance: 2)
Visiting: C
  Found neighbor: E (distance: 2)
Visiting: D
Visiting: E

=== SHORTEST DISTANCES ===
A: 0 steps
B: 1 steps
C: 1 steps
D: 2 steps
E: 2 steps

=== SHORTEST PATH EXAMPLE ===
Shortest path from A to E (distance: 2):
A -> C -> E

=== PACKET SENDING FEATURE ===

=== PACKET SENDING SIMULATION ===
Sending packet from A to E...

Packet at: A (SOURCE)
  Traveling to next node...

Packet at: C (HOP 1)
  Traveling to next node...

Packet at: E (DESTINATION)

=== PACKET DELIVERED SUCCESSFULLY ===
Packet reached E via shortest path!
Total hops: 2
```

## 🎯 Why This is Uninformed Search

### Characteristics:
1. **No Heuristics**: Doesn't use any domain-specific knowledge
2. **Systematic**: Explores all possibilities in order
3. **Complete**: Will find solution if it exists
4. **Optimal**: Finds shortest path (in terms of steps)

### Comparison with Informed Search:
- **Uninformed (BFS)**: Explores level by level, no knowledge of goal
- **Informed (A*)**: Uses heuristics to guide search toward goal

## 🎓 Learning Points

This simple implementation teaches:
- **Graph Traversal**: How to explore connected nodes
- **Queue Data Structure**: FIFO (First In, First Out) principle
- **Shortest Path**: Finding optimal routes
- **Uninformed Search**: Systematic exploration without domain knowledge
- **Network Simulation**: How data travels through networks

## 🔧 Key Algorithm Steps

### BFS Pseudocode:
```
1. Initialize: Mark start node as visited, distance = 0
2. Enqueue start node
3. While queue not empty:
   a. Dequeue current node
   b. For each unvisited neighbor:
      - Mark as visited
      - Set distance = current_distance + 1
      - Set parent = current_node
      - Enqueue neighbor
4. Path reconstruction using parent array
```

### Packet Sending Pseudocode:
```
1. Find shortest path using BFS
2. Reconstruct path from destination to source
3. For each node in path (source to destination):
   a. Display packet location
   b. Show travel progress
   c. Move to next node
4. Confirm successful delivery
```

## 🚀 Advantages

1. **Simple**: Easy to understand and implement
2. **Guaranteed**: Always finds shortest path
3. **Complete**: Will find solution if it exists
4. **No Heuristics**: Pure systematic search
5. **Visual**: Shows packet movement clearly

## 🎯 Real-World Applications

This type of uninformed search is used in:
- **Network Routing**: Finding shortest paths in computer networks
- **Web Crawling**: Exploring web pages systematically
- **Social Networks**: Finding connections between people
- **Game AI**: Pathfinding in games
- **GPS Navigation**: Route planning
- **Data Transmission**: Packet routing in networks

## 📦 Packet Sending Applications

The packet sending feature demonstrates:
- **Network Protocols**: How data travels through networks
- **Routing**: Finding optimal paths for data transmission
- **Network Simulation**: Understanding network behavior
- **Data Flow**: Visualizing information transfer

---

**Note**: This is a basic educational implementation. Real-world applications use more sophisticated algorithms and data structures, but this demonstrates the core concept of uninformed search and network packet transmission! 