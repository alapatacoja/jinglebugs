#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <string>

using namespace std;

// Direcciones: arriba, derecha, abajo, izquierda
vector<pair<int, int>> direcciones = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

// Función que simula el movimiento de la guardia
bool movGuardia(vector<string>& mapa, int filaIni, int colIni) {
    int fila = filaIni, col = colIni;
    int direccion = 0; // 0: Arriba, 1: Derecha, 2: Abajo, 3: Izquierda
    set<pair<int, int>> visitadas; // Rastrea las posiciones visitadas

    while (true) {
        // Verificar si hay un obstáculo en la dirección del movimiento
        int nuevaFila = fila + direcciones[direccion].first;
        int nuevaCol = col + direcciones[direccion].second;

        // Verificar si la nueva posición está fuera del mapa o tiene un obstáculo
        if (nuevaFila < 0 || nuevaFila >= mapa.size() || nuevaCol < 0 || nuevaCol >= mapa[0].size() || mapa[nuevaFila][nuevaCol] == '#') {
            // Si hay un obstáculo, gira 90 grados a la derecha
            direccion = (direccion + 1) % 4;
        } else {
            // Si no hay obstáculo, avanza a la nueva posición
            fila = nuevaFila;
            col = nuevaCol;

            // Verificar si ya visitó esta posición, lo que indicaría un ciclo
            if (visitadas.find({fila, col}) != visitadas.end()) {
                return true; // Si la posición ya fue visitada, es un ciclo
            }

            visitadas.insert({fila, col});
        }
    }
    return false; // Si no entra en un ciclo, retorna false
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

    // Leer el mapa y localizar la posición inicial del guardia (^)
    while (getline(archivo, linea)) {
        mapa.push_back(linea);
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

    // Verificar todas las posiciones vacías para colocar un obstáculo
    int posiblesObstaculos = 0;
    for (int i = 0; i < mapa.size(); i++) {
        for (int j = 0; j < mapa[i].size(); j++) {
            // Ignorar la posición de la guardia y las posiciones con obstáculos
            if ((i == filaIni && j == colIni) || mapa[i][j] == '#' || mapa[i][j] == '^' || mapa[i][j] == 'O') {
                continue;
            }

            // Colocar un nuevo obstáculo en la posición (i, j)
            vector<string> mapaConObstaculo = mapa;
            mapaConObstaculo[i][j] = 'O';

            // Simular el movimiento de la guardia con el nuevo obstáculo
            if (movGuardia(mapaConObstaculo, filaIni, colIni)) {
                posiblesObstaculos++;
            }
        }
    }

    cout << "La cantidad de posiciones donde colocar un obstáculo que atrape a la guardia en un ciclo es: " << posiblesObstaculos << endl;

    return 0;
}
