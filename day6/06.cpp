#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <string>

using namespace std;

// direcciones
vector<pair<int, int>> direcciones = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}}; // Arriba, Derecha, Abajo, Izquierda

// movimiento del guardia
int movGuardia(vector<string>& mapa, int filaIni, int colIni) {
    set<pair<int, int>> visitadas; // registro posiciones visitadas
    int fila = filaIni, col = colIni;
    int direccion = 0; // 0: Arriba, 1: Derecha, 2: Abajo, 3: Izquierda
    
    visitadas.insert({fila, col}); // La guardia comienza en esta posición
    
    while (true) {
        // Verificar si guardia--> fuera del mapa
        if (fila < 0 || fila >= mapa.size() || col < 0 || col >= mapa[0].size()) {
            break; 
        }

        // Verificar obstáculo enfrente 
        int nuevaFila = fila + direcciones[direccion].first;
        int nuevaCol = col + direcciones[direccion].second;

        // Verificar nueva posición está fuera del mapa
        if (nuevaFila < 0 || nuevaFila >= mapa.size() || nuevaCol < 0 || nuevaCol >= mapa[0].size()) {
            break; // Si está fuera del mapa, termina el movimiento
        }

        if (mapa[nuevaFila][nuevaCol] == '#') {
            // obstáculo: gira 90 grados a la derecha
            direccion = (direccion + 1) % 4;
        } else {
            // avanza hacia la siguiente posición
            fila = nuevaFila;
            col = nuevaCol;
            visitadas.insert({fila, col});
        }
    }

    return visitadas.size();
}

int main() {
    ifstream archivo("input.txt");
    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo." << endl;
        return 1;
    }

    vector<string> mapa;
    string linea;
    int filaIni = -1, colIni = -1;

    while (getline(archivo, linea)) {
        mapa.push_back(linea);

        // Buscar pos del guardia (^) en el mapa
        size_t pos = linea.find('^');
        if (pos != string::npos) {
            filaIni = mapa.size() - 1;
            colIni = pos;
        }
    }
    archivo.close();

    if (filaIni == -1 || colIni == -1) {
        cerr << "No se encontró la guardia en el mapa." << endl;
        return 1;
    }

    // movimiento de la guardia
    int posiciones = movGuardia(mapa, filaIni, colIni);

    cout << "La guardia visitó " << posiciones << " posiciones distintas." << endl;

    return 0;
}
