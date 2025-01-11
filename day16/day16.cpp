#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <climits>
using namespace std;

//nodo del arbol
struct Node {
    int x, y;
    int puntos;
    int direccion;
    Node *anterior;

    Node(int x, int y, int puntos, int direccion, Node *anterior = nullptr)
    {
        this->x = x;
        this->y = y;
        this->puntos = puntos;
        this->direccion = direccion;
        this->anterior = anterior;
    }
};

//para rellenar el mapa
void rellenarmapa(vector<vector<char>> &mapa)
{
    ifstream file("input.txt");
    string line;
    while (getline(file, line))
    {
        mapa.push_back(vector<char>(line.begin(), line.end()));
    }
    file.close();
}

//para comprobar que se puede mover
bool valido(int x, int y, vector<vector<char>> &mapa)
{
    if (x >= 0 && x < mapa.size() && y >= 0 && y < mapa[0].size() && mapa[x][y] != '#')
        return true;
    else
        return false;
}

// para calcular la direccion y los ejes x e y
int recalculardir(int direccion, int sentido, int &x, int &y) {
    if (sentido == 0) {
        if(direccion==3) direccion=0;
        else direccion+=1;
    } else if (sentido == 1) {
         if(direccion==0) direccion=3;
        else direccion-=1;
    }
    switch (direccion) {
        case 0: x--; break;
        case 1: y++; break;
        case 2: x++; break;
        case 3: y--; break;
    }
    return direccion;
}


//comprueba los tres posibles movimientos: recto, girar a la derecha o a la izquierda
void explorar(Node* n, vector<vector<char>> &mapa, int xfin, int yfin, vector<vector<vector<int>>> &visitado, int &minpuntos) {
    
    if (n->x == xfin && n->y == yfin) {
        minpuntos = min(minpuntos, n->puntos);
        return;
    }

    for (int sentido = -1; sentido <= 1; sentido++) {
        int tempx = n->x;
        int tempy = n->y;
        int dir = recalculardir(n->direccion, sentido, tempx, tempy);

        int puntos = 0;

        if(sentido == -1)
            puntos = n->puntos + 1;
        else
            puntos = n->puntos + 1001;

        if (valido(tempx, tempy, mapa) && puntos < visitado[tempx][tempy][dir]) {
            visitado[tempx][tempy][dir] = puntos;
            Node* n2 = new Node(tempx, tempy, puntos, dir, n);
            explorar(n2, mapa, xfin, yfin, visitado, minpuntos);
            delete n2; 
        }
    }
}

//para ver el camino más corto
int shortestpath(vector<vector<char>> &mapa, int xini, int yini, int xfin, int yfin) {
    vector<vector<vector<int>>> visitado(mapa.size(), vector<vector<int>>(mapa[0].size(), vector<int>(4, INT_MAX)));

    Node* root = new Node(xini, yini, 0, 1);
    visitado[xini][yini][1] = 0;

    int minpuntos = INT_MAX;

    explorar(root, mapa, xfin, yfin, visitado, minpuntos);

    delete root;
    return minpuntos;
}

int main() {
    vector<vector<char>> mapa;
    rellenarmapa(mapa);

    int xini, yini, xfin, yfin;
    for (int i = 0; i < mapa.size(); ++i) {
        for (int j = 0; j < mapa[i].size(); ++j) {
            if (mapa[i][j] == 'S') {
                xini = i;
                yini = j;
            } else if (mapa[i][j] == 'E') {
                xfin = i;
                yfin = j;
            }
        }
    }

    int result = shortestpath(mapa, xini, yini, xfin, yfin);
    cout << "Resultado: " << result << endl;
}
