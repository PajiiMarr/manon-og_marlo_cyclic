#include <iostream>
#include <vector>
#include <queue>
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

bool isCyclicBFS(const vector<vector<int>>& adjMatrix) {
    int n = adjMatrix.size();
    vector<int> inDegree(n, 0);
    
    // Calculate in-degree for each node
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (adjMatrix[i][j]) {
                inDegree[j]++;
            }
        }
    }
    
    queue<int> q;
    for (int i = 0; i < n; ++i) {
        if (inDegree[i] == 0) {
            q.push(i);
        }
    }
    
    int cnt = 0;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        cnt++;
        
        for (int v = 0; v < n; ++v) {
            if (adjMatrix[u][v]) {
                if (--inDegree[v] == 0) {
                    q.push(v);
                }
            }
        }
    }
    
    return cnt != n;
}

void checkCyclicBFS(const vector<vector<int>>& adjMatrix) {
    cout << "\nAdjacency Matrix (Directed Graph):\n";
    printMatrix(adjMatrix);
    
    if (isCyclicBFS(adjMatrix)) {
        cout << "\nGraph contains at least one directed cycle." << endl;
    } else {
        cout << "\nGraph doesn't contain any directed cycle." << endl;
    }
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

    checkCyclicBFS(adjMatrix);
    return 0;
}