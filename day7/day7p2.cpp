#include <iostream>
#include <math.h>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include "day7p2.h"

using namespace std;

// Función principal
int main() {
    vector<string> entrada;
    string archivo = "input2.txt";
    abrir_archivo(archivo, entrada);

    long long suma_resultados = 0;

    for (const string& linea : entrada) {
        long long resultado = 0;
        if (crear_combinaciones(linea, resultado)) {
            suma_resultados += resultado;
        }
    }

    cout << "La suma total de los valores de calibración es: " << suma_resultados << endl;
    return 0;
}
