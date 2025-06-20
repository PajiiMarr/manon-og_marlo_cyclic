#include <iostream>
#include <vector>
#include <queue>
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

bool isCyclicBFS(const vector<vector<int>>& adjMatrix, int start, vector<int>& cycle) {
    int n = adjMatrix.size();
    vector<bool> visited(n, false);
    vector<int> parent(n, -1);
    queue<int> q;

    q.push(start);
    visited[start] = true;

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        for (int neighbor = 0; neighbor < n; ++neighbor) {
            if (adjMatrix[current][neighbor]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    parent[neighbor] = current;
                    q.push(neighbor);
                } else if (parent[current] != neighbor) {
                    vector<int> path1, path2;
                    int node = current;
                    while (node != -1) {
                        path1.push_back(node);
                        node = parent[node];
                    }
                    node = neighbor;
                    while (node != -1) {
                        path2.push_back(node);
                        node = parent[node];
                    }

                    int i = path1.size() - 1, j = path2.size() - 1;
                    while (i >= 0 && j >= 0 && path1[i] == path2[j]) {
                        i--;
                        j--;
                    }

                    for (int k = 0; k <= i + 1; ++k) {
                        cycle.push_back(path1[k]);
                    }
                    for (int k = j; k >= 0; --k) {
                        cycle.push_back(path2[k]);
                    }
                    return true;
                }
            }
        }
    }
    return false;
}

void checkCyclicBFS(const vector<vector<int>>& adjMatrix) {
    cout << "\nAdjacency Matrix:\n";
    printMatrix(adjMatrix);
    
    vector<int> cycle;
    for (int i = 0; i < adjMatrix.size(); ++i) {
        if (isCyclicBFS(adjMatrix, i, cycle)) {
            cout << "\nGraph contains cycle: ";
            for (size_t j = 0; j < cycle.size(); ++j) {
                cout << cycle[j];
                if (j < cycle.size() - 1) cout << " → ";
            }
            cout << endl;
            return;
        }
    }
    cout << "\nGraph doesn't contain any cycle." << endl;
}

int main() {
    vector<vector<int>> adjMatrix = {
        {0, 1, 0, 0, 1},
        {1, 0, 1, 0, 1},
        {0, 1, 0, 1, 1},
        {0, 0, 1, 0, 1},
        {0, 0, 1, 0, 1},
    };

    checkCyclicBFS(adjMatrix);
    return 0;
}