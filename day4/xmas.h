#include <iostream>
#include <vector>
#include <string>

using namespace std;

int buscarXMAS(const vector<string>& grid, int x, int y, int dx, int dy) {
	string palabra = "XMAS";
    	int n = grid.size();
    	int m = grid[0].size();
    	for (int i = 0; i < 4; ++i) {
        	int nx = x + i * dx;
        	int ny = y + i * dy;
        	if (nx < 0 || nx >= n || ny < 0 || ny >= m || grid[nx][ny] != palabra[i]) {
            		return 0;
        	}
    	}

    	return 1;
}

int contarXMASRecursivo(const vector<string>& grid, int startX, int startY, int endX, int endY) {
    	if (endX - startX < 4 && endY - startY < 4) {// Caso base: subgrilla pequeña, buscar directamente
        	int count = 0;
        	vector<pair<int, int>> direcciones = {{1, 0}, {0, 1}, {1, 1}, {1, -1}, {-1, 0}, {0, -1}, {-1, -1}, {-1, 1}};
        	for (int i = startX; i < endX; ++i) {
            		for (int j = startY; j < endY; ++j) {
                		for (auto [dx, dy] : direcciones) {
                    			count += buscarXMAS(grid, i, j, dx, dy);
                		}		
            		}
        	}
        	return count;
	} else {
        // Dividir la grilla en cuatro subgrillas
        	int midX = (startX + endX) / 2;
        	int midY = (startY + endY) / 2;
       		return contarXMASRecursivo(grid, startX, startY, midX, midY) +
			contarXMASRecursivo(grid, startX, midY, midX, endY) +
               		contarXMASRecursivo(grid, midX, startY, endX, midY) +
               		contarXMASRecursivo(grid, midX, midY, endX, endY);
    }
}
