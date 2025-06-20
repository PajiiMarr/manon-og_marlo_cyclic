#include <iostream>
#include <vector>
#include <stack>
#include <iomanip>

using namespace std;

void printMatrix(const vector<vector<int>>& matrix) {
    int n = matrix.size();
    
    cout << "   ";
    for (int j = 0; j < n; ++j) cout << setw(3) << j << " ";
    cout << "\n  ┌" << string(4*n + 1, '-') << "┐" << endl;
    
    for (int i = 0; i < n; ++i) {
        cout << setw(2) << i << "│";
        for (int j = 0; j < n; ++j) {
            cout << " " << matrix[i][j] << " │";
        }
        cout << endl;
        if (i < n - 1) {
            cout << "  ├" << string(4*n + 1, '-') << "┤" << endl;
        }
    }
    cout << "  └" << string(4*n + 1, '-') << "┘" << endl;
}

bool isCyclicDFS(const vector<vector<int>>& adjMatrix, int node, vector<bool>& visited, 
                vector<bool>& recStack, vector<int>& cycle) {
    if (!visited[node]) {
        visited[node] = true;
        recStack[node] = true;
        
        for (int neighbor = 0; neighbor < adjMatrix.size(); ++neighbor) {
            if (adjMatrix[node][neighbor]) {
                if (!visited[neighbor] && isCyclicDFS(adjMatrix, neighbor, visited, recStack, cycle)) {
                    if (cycle.empty() || cycle.back() != node) {
                        cycle.push_back(node);
                        if (cycle.front() == node) return true;
                    }
                    return true;
                } else if (recStack[neighbor]) {
                    cycle.push_back(neighbor);
                    cycle.push_back(node);
                    return true;
                }
            }
        }
    }
    recStack[node] = false;
    return false;
}

void checkCyclicDFS(const vector<vector<int>>& adjMatrix) {
    cout << "\nAdjacency Matrix (Directed Graph):\n";
    printMatrix(adjMatrix);
    
    int n = adjMatrix.size();
    vector<bool> visited(n, false);
    vector<bool> recStack(n, false);
    vector<int> cycle;
    
    for (int i = 0; i < n; ++i) {
        if (!visited[i] && isCyclicDFS(adjMatrix, i, visited, recStack, cycle)) {
            cout << "\nGraph contains directed cycle: ";
            for (int j = cycle.size() - 1; j >= 0; --j) {
                cout << cycle[j];
                if (j > 0) cout << " → ";
            }
            cout << endl;
            return;
        }
    }
    cout << "\nGraph doesn't contain any directed cycle." << endl;
}

int main() {
    // Hardcoded adjacency matrix for directed graph
    vector<vector<int>> adjMatrix = {
        {0, 1, 0, 0, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 1, 0},
        {0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0}  // Creates a cycle 0→1→2→3→4→0
    };

    checkCyclicDFS(adjMatrix);
    return 0;
}