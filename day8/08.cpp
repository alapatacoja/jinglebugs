#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <set>
#include <string>

using namespace std;

// Punto en los límites del mapa
bool limit(int x, int y, int fil, int col) {
    return x >= 0 && x < fil && y >= 0 && y < col;
}

// Calcular antinodos únicos
int antinodos(const vector<string>& map) {
    int fil = map.size();
    int col = map[0].size();

    // Tabla hash --> almacenar coord de antenas agrupadas por frecuencia
    unordered_map<char, vector<pair<int, int>>> antenas;

    // Recopilar coord de antenas
    for (int i = 0; i < fil; ++i) {
        for (int j = 0; j < col; ++j) {
            char frec = map[i][j];
            if (frec != '.') {
                antenas[frec].emplace_back(i, j);
            }
        }
    }

    // Almacenar antinodos únicos
    set<pair<int, int>> antinodos;

    // Procesar frecuencias --> tabla hash
    for (const auto& [frec, pos] : antenas) {
        int n = pos.size();
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                // Coord de antenas y calcular dif
                int x1 = pos[i].first, y1 = pos[i].second;
                int x2 = pos[j].first, y2 = pos[j].second;

                int dx = x2 - x1;
                int dy = y2 - y1;

                // Generar antinodos (ambas direcc)
                int ax = x2 + dx, ay = y2 + dy;
                if (limit(ax, ay, fil, col)) {
                    antinodos.emplace(ax, ay);
                }

                int bx = x1 - dx, by = y1 - dy;
                if (limit(bx, by, fil, col)) {
                    antinodos.emplace(bx, by);
                }
            }
        }
    }

    return antinodos.size();
}

int main() {
    // Abrir input
    ifstream input("input");
    if (!input) {
        cerr << "No se pudo abrir el archivo" << endl;
        return 1;
    }

    // Leer el mapa
    vector<string> mapa;
    string l;
    while (getline(input, l)) {
        mapa.push_back(l);
    }
    input.close();

    
    int result = antinodos(mapa);
    cout << "Número de antinodos únicos: " << result << endl;

    return 0;
}
