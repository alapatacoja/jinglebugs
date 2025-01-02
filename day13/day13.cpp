#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <regex>
#include <cmath>
using namespace std;

//para poder guardar los valores
struct Maquina {
    int ax, ay; 
    int bx, by;
    int px, py;
};

//guardar los valores desde el archivo input.txt
void fillMaquinas(vector<Maquina> &maquinas) {
    ifstream file("input.txt");
    string line;
    Maquina maquina;

    while (getline(file, line)) {
        if (line.find("Button A:") != string::npos) { //si encontramos el boton A
            smatch match; //para guardar las coincidencias con regex
            regex pattern("X\\+(-?\\d+), Y\\+(-?\\d+)"); //el patron en X+[numero], Y+[numero]
            if (regex_search(line, match, pattern)) {
                maquina.ax = stoi(match[1]);
                maquina.ay = stoi(match[2]);
            }
        } else if (line.find("Button B:") != string::npos) {
            smatch match;
            regex pattern("X\\+(-?\\d+), Y\\+(-?\\d+)");
            if (regex_search(line, match, pattern)) {
                maquina.bx = stoi(match[1]);
                maquina.by = stoi(match[2]);
            }
        } else if (line.find("Prize:") != string::npos) {
            smatch match;
            regex pattern("X=(-?\\d+), Y=(-?\\d+)"); //aqui el patron es X=[numero], Y=[numero]
            if (regex_search(line, match, pattern)) {
                maquina.px = stoi(match[1]);
                maquina.py = stoi(match[2]);
            }
            maquinas.push_back(maquina); 
        }
    }
    file.close();
}


//para encontrar las veces que pulsas cada boton:
//se hace mediante un sistema de ecuaciones (crammer)
int ecuacion(Maquina maquina){
    int sum=0;
    float x,y;
    float det = maquina.ax * maquina.by - maquina.ay * maquina.bx;
    if(det != 0){
        x=(maquina.by*maquina.px - maquina.bx * maquina.py)/det;
        y=(maquina.ax * maquina.py - maquina.ay*maquina.px)/det;

        if((floor(x)==x && x<100) && (floor(y)==y && y<100)){
            sum = 3*x + y;
            cout << "x:" << x << " y: " << y << " det: " << det << endl;
        }
    }
    return sum;
}

int main() {
    int suma = 0;
    vector<Maquina> maquinas;
    fillMaquinas(maquinas);
    
    for (int i = 0; i<maquinas.size(); i++) {
        suma += ecuacion(maquinas[i]);
        cout << suma << endl;
    }

    return 0;
}
