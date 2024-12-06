#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <string>

using namespace std;

// Direcciones: arriba, derecha, abajo, izquierda
vector<pair<int, int>> direcciones = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

// Función que simula el movimiento de la guardia
int movGuardia(vector<string>& mapa, int filaIni, int colIni, set<pair<int, int>>& visitadas, char obstaculo = ' ') {
    int fila = filaIni, col = colIni;
    int direccion = 0; // 0: Arriba, 1: Derecha, 2: Abajo, 3: Izquierda
    visitadas.insert({fila, col}); // La guardia comienza en esta posición

    while (true) {
        // Verificar si el guardia se sale del mapa
        if (fila < 0 || fila >= mapa.size() || col < 0 || col >= mapa[0].size()) {
            break;
        }

        // Verificar si hay un obstáculo en la dirección del movimiento
        int nuevaFila = fila + direcciones[direccion].first;
        int nuevaCol = col + direcciones[direccion].second;

        // Verificar si la nueva posición está fuera del mapa
        if (nuevaFila < 0 || nuevaFila >= mapa.size() || nuevaCol < 0 || nuevaCol >= mapa[0].size()) {
            break;
        }

        if (mapa[nuevaFila][nuevaCol] == '#') {
            // Si hay un obstáculo, gira 90 grados a la derecha
            direccion = (direccion + 1) % 4;
        } else {
            // Si no hay obstáculo, avanza a la nueva posición
            fila = nuevaFila;
            col = nuevaCol;

            // Verificar si ya visitó esta posición, lo que indicaría un ciclo
            if (visitadas.find({fila, col}) != visitadas.end()) {
                break; // Si la posición ya fue visitada, es un ciclo, terminamos
            }

            visitadas.insert({fila, col});
        }
    }

    return visitadas.size(); // Retorna la cantidad de posiciones visitadas
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

    // Simulación del movimiento de la guardia desde su posición inicial
    set<pair<int, int>> visitadas;
    movGuardia(mapa, filaIni, colIni, visitadas);

    // Verificar todas las posiciones vacías para colocar un obstáculo
    int posiblesObstaculos = 0;
    for (int i = 0; i < mapa.size(); i++) {
        for (int j = 0; j < mapa[i].size(); j++) {
            // Ignorar la posición de la guardia y las posiciones con obstáculos
            if ((i == filaIni && j == colIni) || mapa[i][j] == '#' || mapa[i][j] == '^') {
                continue;
            }

            // Colocar un nuevo obstáculo en la posición (i, j)
            vector<string> mapaConObstaculo = mapa;
            mapaConObstaculo[i][j] = 'O';

            // Simular el movimiento de la guardia con el nuevo obstáculo
            set<pair<int, int>> nuevasVisitadas;
            movGuardia(mapaConObstaculo, filaIni, colIni, nuevasVisitadas, 'O');

            // Verificar si el número de posiciones visitadas con el nuevo obstáculo es mayor
            if (nuevasVisitadas.size() > visitadas.size()) {
                posiblesObstaculos++;
            }
        }
    }

    cout << "La cantidad de posiciones donde colocar un obstáculo que atrape a la guardia en un ciclo es: " << posiblesObstaculos << endl;

    return 0;
}
