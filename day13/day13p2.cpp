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
    long long px, py;
};

//guardar los valores desde el archivo input.txt
void fillMaquinas(vector<Maquina> &maquinas) {
    ifstream file("input.txt");
    string line;
    Maquina machine;

    while (getline(file, line)) {
        if (line.find("Button A:") != string::npos) {
            smatch match;
            regex pattern("X\\+(-?\\d+), Y\\+(-?\\d+)");
            if (regex_search(line, match, pattern)) {
                machine.ax = stoi(match[1]);
                machine.ay = stoi(match[2]);
            }
        } else if (line.find("Button B:") != string::npos) {
            smatch match;
            regex pattern("X\\+(-?\\d+), Y\\+(-?\\d+)");
            if (regex_search(line, match, pattern)) {
                machine.bx = stoi(match[1]);
                machine.by = stoi(match[2]);
            }
        } else if (line.find("Prize:") != string::npos) {
            smatch match;
            regex pattern("X=(-?\\d+), Y=(-?\\d+)");
            if (regex_search(line, match, pattern)) {
                machine.px = stoi(match[1]);
                machine.px+=10000000000000;
                machine.py = stoi(match[2]);
                machine.py+=10000000000000;
            }
            maquinas.push_back(machine); 
        }
    }
    file.close();
}



long long ecuacion(Maquina maquina){
    long long sum=0;
    long long x=0,y=0;
    long long det = maquina.ax * maquina.by - maquina.ay * maquina.bx;
    long long detx, dety;
    if(det != 0){
        detx=(maquina.by*maquina.px - maquina.bx * maquina.py);
        dety=(maquina.ax * maquina.py - maquina.ay*maquina.px);
        //cout << "x:" << detx << " y: " << dety << " det: " << det << endl;
        if((detx % det == 0) && (dety%det==0)){
            x = detx/det;
            y = dety/det;
            //cout << "x:" << x << " y: " << y << endl;
            sum = 3*x + y;
        }
    }
    return sum;
}

int main() {
    long long suma = 0;
    vector<Maquina> maquinas;
    fillMaquinas(maquinas);
    
    for (int i = 0; i<maquinas.size(); i++) {
        suma += ecuacion(maquinas[i]);
        cout << "suma: " << suma << endl;
    }

    return 0;
}
