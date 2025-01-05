#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <utility>
#include <queue>
using namespace std;

//rellenar el mapa
void leer(vector<vector<int>> &mapa)
{
    ifstream file("input.txt");
    string line;
    while (getline(file, line))
    {
        vector<int> fila;
        for (int i = 0; i < line.length(); ++i) {
            char c = line[i];
                fila.push_back(c - '0'); 
            }
            mapa.push_back(fila);
    }
}


int shortestpath(vector<vector<int>> &mapa, int x, int y){
    int filas = mapa.size();
    int columnas = mapa[0].size();
    vector<vector<bool>> visitado(filas, vector<bool>(columnas, false));
    queue<pair<int,int>> q;

    q.push({x,y});
    visitado[x][y] = true;
    int c9 = 0;

    while(!q.empty()){
        pair<int, int> n = q.front();
        q.pop();
        int x2 = n.first;
        int y2 = n.second;

        if(mapa[x2][y2] == 9)
            c9++;

        //comprobar que la celda no salga del mapa, que no se haya visitado y que la altura sea 1 mayor
        //arriba
        if (x2 - 1 >= 0 && !visitado[x2 - 1][y2] && mapa[x2 - 1][y2] == mapa[x2][y2] + 1) {
            q.push(make_pair(x2 - 1, y2));
            visitado[x2 - 1][y2] = true;
        }
        //abajo
        if (x2 + 1 < filas && !visitado[x2 + 1][y2] && mapa[x2 + 1][y2] == mapa[x2][y2] + 1) {
            q.push(make_pair(x2 + 1, y2));
            visitado[x2 + 1][y2] = true;
        }
        //izquierda
        if (y2 - 1 >= 0 && !visitado[x2][y2 - 1] && mapa[x2][y2 - 1] == mapa[x2][y2] + 1) {
            q.push(make_pair(x2, y2 - 1));
            visitado[x2][y2 - 1] = true;
        }
        //derecha
        if (y2 + 1 < columnas && !visitado[x2][y2 + 1] && mapa[x2][y2 + 1] == mapa[x2][y2] + 1) {
            q.push(make_pair(x2, y2 + 1));
            visitado[x2][y2 + 1] = true;
        }

    }

    return c9;
}

int main() {
    vector<vector<int>> mapa;
    leer(mapa);

    int sum = 0;

    for (int i = 0; i < mapa.size(); ++i) {
        for (int j = 0; j < mapa[i].size(); ++j) {
            if (mapa[i][j] == 0) {  
                sum += shortestpath(mapa, i, j);
            }
        }
    }

    cout << sum << endl;
    return 0;
}