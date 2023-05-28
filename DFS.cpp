#include <iostream>
#include <stack>
#include <vector>
#include <omp.h>
// Define the number of threads to use
#define NUM_THREADS 4

// Define the graph as an adjacency list
typedef std::vector<std::vector<int>> Graph;

void parallelDFS(const Graph& graph, int startNode) {
    int numNodes = graph.size();
    std::vector<bool> visited(numNodes, false);
    std::stack<int> dfsStack;

    dfsStack.push(startNode);
    visited[startNode] = true;

    {
        while (!dfsStack.empty()) {
            int currentNode;
            #pragma omp critical
            {
                currentNode = dfsStack.top();
                dfsStack.pop();
            }
            #pragma omp for
            for (int i = 0; i < graph[currentNode].size(); ++i) {
                int neighbor = graph[currentNode][i];
                
                if (!visited[neighbor]) {
                    visited[neighbor] = true;

                    #pragma omp critical
                    {
                        dfsStack.push(neighbor);
                    }
                }
            }
        }
    }

    // Output the visited nodes
    std::cout << "Visited nodes: ";
    for (int i = 0; i < numNodes; ++i) {
        if (visited[i]) {
            std::cout << i << " ";
        }
    }
    std::cout << std::endl;
}

int main() {
    // Define the graph
    Graph graph = {
        {1, 2},        // Node 0 is connected to nodes 1 and 2
        {0, 2, 3},     // Node 1 is connected to nodes 0, 2, and 3
        {0, 1, 3},     // Node 2 is connected to nodes 0, 1, and 3
        {1, 2, 4},     // Node 3 is connected to nodes 1, 2, and 4
        {3, 5},        // Node 4 is connected to nodes 3 and 5
        {4, 6},        // Node 5 is connected to nodes 4 and 6
        {5}            // Node 6 is connected to node 5
    };

    // Perform parallel DFS starting from node 0
    parallelDFS(graph, 0);

    return 0;
}
