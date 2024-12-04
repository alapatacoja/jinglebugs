#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

// Función para verificar si hay un patrón X-MAS en una posición dada
bool X_MAS(const vector<string>& grid, int x, int y) {
    int n = grid.size();
    int m = grid[0].size();
    if (x - 1 >= 0 && x + 1 < n && y - 1 >= 0 && y + 1 < m) {
        // Verificar las posiciones alrededor de (x, y) para "MAS" y "SAM"
        bool dd = (grid[x][y] == 'A' &&
                        grid[x-1][y-1] == 'M' && grid[x+1][y+1] == 'S' &&
                        grid[x-1][y+1] == 'M' && grid[x+1][y-1] == 'S');
        
        bool dr = (grid[x][y] == 'A' &&
                        grid[x-1][y-1] == 'M' && grid[x+1][y+1] == 'S' &&
                        grid[x-1][y+1] == 'S' && grid[x+1][y-1] == 'M');
        
	bool rd = (grid[x][y] == 'A' &&
                        grid[x-1][y-1] == 'S' && grid[x+1][y+1] == 'M' &&
                        grid[x-1][y+1] == 'M' && grid[x+1][y-1] == 'S');

        bool rr = (grid[x][y] == 'A' &&
                      grid[x-1][y-1] == 'S' && grid[x+1][y+1] == 'M' &&
                      grid[x-1][y+1] == 'S' && grid[x+1][y-1] == 'M');
        
        return (dd || rr || rd || dr);
    }
    return false;
}

// Función para contar todas las instancias de X-MAS en la grilla
int contarX_MAS(const vector<string>& grid) {
    int n = grid.size();
    int m = grid[0].size();
    int count = 0;
    for (int i = 1; i < n - 1; ++i) {
        for (int j = 1; j < m - 1; ++j) {
            if (X_MAS(grid, i, j)) {
                count++;
            }
        }
    }
    return count;
}
