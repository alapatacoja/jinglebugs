#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "xmas.h"

using namespace std;

int main() {
    	ifstream inputFile("input.txt");
	vector<string> grid;
	string line;

	if (inputFile.is_open()) {
    		while (getline(inputFile, line)) {
        		grid.push_back(line);
    		}
    		inputFile.close();
	} else {
    		cerr << "No se pudo abrir el archivo input.txt" << endl;
    		return 1;
	}

    	int n = grid.size();
    	int m = grid[0].size();
    	cout << "La palabra XMAS aparece " << contarXMASRecursivo(grid, 0, 0, n, m) << " veces." << endl;
    	
	return 0;
}

