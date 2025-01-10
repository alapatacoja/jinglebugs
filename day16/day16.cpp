#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <queue>
#include <cmath>
#include <climits>
using namespace std;

struct Node
{
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

bool valido(int x, int y, vector<vector<char>> &mapa)
{
    if (x >= 0 && x < mapa.size() && y >= 0 && y < mapa[0].size() && mapa[x][y] != '#')
        return true;
    else
        return false;
}

int recalculardir(Node* n, int &x, int &y, int sentido){
    int dir = n->direccion;

    if(sentido==0){
        if(dir==3) dir=0;
        else dir+=1;
    } else if(sentido==1){
        if(dir==0) dir=3;
        else dir-=1;
    }

    switch(dir){
            case 0:
                x = n->x-1;
                y = n->y;
                
                break;
            case 1:
                x = n->x;
                y = n->y+1;
                
                break;
            case 2:
                x = n->x+1;
                y = n->y;
                
                break;
            case 3:
                x = n->x;
                y = n->y-1;
                
                break;
        }

        return dir;
}

int shortestpath(vector<vector<char>> &mapa, int xini, int yini, int xfin, int yfin)
{
    Node *root = new Node(xini, yini, 0, 1);
    queue<Node *> q;
    q.push(root);

    vector<vector<vector<bool>>> visitado(mapa.size(), vector<vector<bool>>(mapa[0].size(), vector<bool>(4, false)));
    visitado[xini][yini][1] = true;

    int minpuntos = INT_MAX;

    while (!q.empty())
    {
        Node *n = q.front();
        q.pop();
        //cout << "("<<n->x<<","<<n->y<<") "<<n->puntos<<endl;
        if (n->x == xfin && n->y == yfin)
        {
            minpuntos = min(minpuntos, n->puntos);
            cout << "ueu" << endl;
            delete n;
            continue;
        }

        int tempx;
        int tempy;
        int dir;
        //0 norte, 1 este, 2 sur, 3 oeste
        dir = recalculardir(n, tempx, tempy, -1);
        
        if(valido(tempx, tempy, mapa) && !visitado[tempx][tempy][n->direccion]){
            Node* sig = new Node(tempx, tempy, (n->puntos)+1, n->direccion, n);
            q.push(sig);
            visitado[tempx][tempy][n->direccion] = true;
            //cout << "palante ("<<tempx<<","<<tempy<<") "<<sig->puntos<<endl;
        }

        dir = recalculardir(n, tempx, tempy, 0);
        if (valido(tempx, tempy, mapa) && !visitado[tempx][tempy][dir]) {
            Node* sig = new Node(tempx, tempy, (n->puntos) + 1001, dir, n);
            q.push(sig);
            visitado[tempx][tempy][dir] = true;
            //cout << "horario ("<<tempx<<","<<tempy<<") "<<sig->puntos<<endl;
        }

        dir = recalculardir(n, tempx, tempy, 1);
        if (valido(tempx, tempy, mapa) && !visitado[tempx][tempy][dir]) {
            Node* sig = new Node(tempx, tempy, n->puntos + 1001, dir, n);
            q.push(sig);
            visitado[tempx][tempy][dir] = true;
            //cout << "antihorario ("<<tempx<<","<<tempy<<") "<<sig->puntos<<endl;
        }
        delete n;
    }

    return minpuntos;
}

int main()
{
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
    cout << xfin<<" " <<yfin << endl;
    cout << result << endl;

}