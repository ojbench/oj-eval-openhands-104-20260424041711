
#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>
using namespace std;

// Structure to represent a state in the BFS
struct State {
    int row, col, umbrella_found;
    int distance;
    
    State(int r, int c, int u, int d) : row(r), col(c), umbrella_found(u), distance(d) {}
};

// Directions for moving: up, down, left, right
const int dr[] = {-1, 1, 0, 0};
const int dc[] = {0, 0, -1, 1};

int main() {
    int n, m;
    cin >> n >> m;
    
    vector<vector<int>> grid(m, vector<int>(n));
    int start_r = -1, start_c = -1;
    
    // Read the grid and find the starting position
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cin >> grid[i][j];
            if (grid[i][j] == 2) {
                start_r = i;
                start_c = j;
            }
        }
    }
    
    // 3D array to store the minimum distance to each state
    // dist[r][c][u] = minimum distance to reach (r,c) with u umbrella status (0 = not found, 1 = found)
    vector<vector<vector<int>>> dist(m, vector<vector<int>>(n, vector<int>(2, INT_MAX)));
    
    // Queue for BFS
    queue<State> q;
    
    // Start from the initial position with no umbrella
    q.push(State(start_r, start_c, 0, 0));
    dist[start_r][start_c][0] = 0;
    
    int min_distance = INT_MAX;
    
    while (!q.empty()) {
        State curr = q.front();
        q.pop();
        
        int r = curr.row;
        int c = curr.col;
        int umbrella = curr.umbrella_found;
        int d = curr.distance;
        
        // If we reached home with an umbrella, update the minimum distance
        if (grid[r][c] == 3 && umbrella == 1) {
            min_distance = min(min_distance, d);
            continue;
        }
        
        // Explore all four directions
        for (int i = 0; i < 4; i++) {
            int nr = r + dr[i];
            int nc = c + dc[i];
            
            // Check if the new position is within bounds
            if (nr < 0 || nr >= m || nc < 0 || nc >= n) {
                continue;
            }
            
            // Check if the new position is not a construction site (1)
            if (grid[nr][nc] == 1) {
                continue;
            }
            
            // Determine the new umbrella status
            int new_umbrella = umbrella;
            if (grid[nr][nc] == 4) {
                new_umbrella = 1;
            }
            
            // If we found a shorter path to this state, update it
            if (d + 1 < dist[nr][nc][new_umbrella]) {
                dist[nr][nc][new_umbrella] = d + 1;
                q.push(State(nr, nc, new_umbrella, d + 1));
            }
        }
    }
    
    cout << min_distance << endl;
    
    return 0;
}
