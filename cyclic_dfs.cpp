#include <iostream>
#include <vector>
#include <stack>
#include <iomanip>

using namespace std;

void printMatrix(const vector<vector<int>>& matrix) {
    int n = matrix.size();
    
    cout << "   ";
    for (int j = 0; j < n; ++j) cout << setw(3) << j << " ";
    cout << "\n  |" << string(4*n + 1, '-') << "|" << endl;
    
    for (int i = 0; i < n; ++i) {
        cout << setw(2) << i << "│";
        
        for (int j = 0; j < n; ++j) {
            cout << " " << matrix[i][j] << " │";
        }
        cout << endl;
        
        if (i < n - 1) {
            cout << "  |" << string(4*n + 1, '-') << "|" << endl;
        }
    }
    
    cout << "  |" << string(4*n + 1, '-') << "|" << endl;
}

bool isCyclicDFS(const vector<vector<int>>& adjMatrix, int start, vector<int>& cycle) {
    int n = adjMatrix.size();
    vector<bool> visited(n, false);
    vector<int> parent(n, -1);
    stack<int> s;
    
    s.push(start);
    visited[start] = true;

    while (!s.empty()) {
        int current = s.top();
        s.pop();

        for (int neighbor = 0; neighbor < n; ++neighbor) {
            if (adjMatrix[current][neighbor]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    parent[neighbor] = current;
                    s.push(neighbor);
                } else if (parent[current] != neighbor) {
                    cycle.push_back(neighbor);
                    int node = current;
                    while (node != neighbor && node != -1) {
                        cycle.push_back(node);
                        node = parent[node];
                    }
                    cycle.push_back(neighbor);
                    return true;
                }
            }
        }
    }
    return false;
}

void checkCyclicDFS(const vector<vector<int>>& adjMatrix) {
    cout << "\nAdjacency Matrix:\n";
    printMatrix(adjMatrix);
    
    vector<int> cycle;
    for (int i = 0; i < adjMatrix.size(); ++i) {
        if (isCyclicDFS(adjMatrix, i, cycle)) {
            cout << "\nGraph contains cycle: ";
            for (int j = cycle.size() - 1; j >= 0; --j) {
                cout << cycle[j];
                if (j > 0) cout << " → ";
            }
            cout << endl;
            return;
        }
    }
    cout << "\nGraph doesn't contain any cycle." << endl;
}

int main() {
    // Hardcoded adjacency matrix (example cyclic graph)
    vector<vector<int>> adjMatrix = {
        {0, 1, 1, 0},
        {1, 0, 1, 0},
        {1, 1, 0, 1},
        {0, 0, 1, 0}
    };

    checkCyclicDFS(adjMatrix);
    return 0;
}