#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>
#include <fstream>

using namespace std;

// Función para leer el archivo de entrada
void leer_archivo(const string& archivo, vector<string>& lineas) {
    ifstream input(archivo);
    string linea;
    if (!input) {
        cerr << "No se pudo abrir el archivo " << archivo << endl;
        return;
    }
    while (getline(input, linea)) {
        lineas.push_back(linea);
    }
    input.close();
}

// Función para procesar una línea de entrada
void procesar_linea(const string& linea, long long *objetivo, vector<long long>& numeros) {
    stringstream ss(linea);
    string objetivo_str;
    getline(ss, objetivo_str, ':');
    *objetivo = stoll(objetivo_str);

    string numeros_str = linea.substr(linea.find(":") + 1);
    stringstream numeros_stream(numeros_str);
    long long numero;
    while (numeros_stream >> numero) {
        numeros.push_back(numero);
    }
}

// Función para evaluar una combinación de operadores
bool evaluar_combinacion(const vector<long long>& numeros, const vector<string>& operadores, long long objetivo) {
    long long resultado = numeros[0];
    for (size_t i = 0; i < operadores.size(); ++i) {
        if (operadores[i] == "+") {
            resultado += numeros[i + 1];
        } else if (operadores[i] == "*") {
            resultado *= numeros[i + 1];
        } else if (operadores[i] == "||") {
            resultado = stoll(to_string(resultado) + to_string(numeros[i + 1]));
        }
    }
    return resultado == objetivo;
}

// Función para generar todas las combinaciones de operadores y verificar cada una
bool validar_ecuacion(long long objetivo, const vector<long long>& numeros) {
    int n = numeros.size() - 1;
    long long total_combinaciones = pow(3, n); // 3 operadores: +, *, ||
    vector<string> operadores = {"+", "*", "||"};

    for (long long i = 0; i < total_combinaciones; ++i) {
        vector<string> combinacion;
        for (int j = 0; j < n; ++j) {
            combinacion.push_back(operadores[(i / static_cast<int>(pow(3, j))) % 3]);
        }
        if (evaluar_combinacion(numeros, combinacion, objetivo)) {
            return true;
        }
    }
    return false;
}

int main() {
    vector<string> lineas;
    leer_archivo("input.txt", lineas);

    long long suma_calibracion = 0;

    for (const string& linea : lineas) {
        long long objetivo;
        vector<long long> numeros;
        procesar_linea(&linea, &objetivo, &numeros);

        if (validar_ecuacion(objetivo, numeros)) {
            suma_calibracion += objetivo;
        }
    }

    cout << "Resultado de calibración total: " << suma_calibracion << endl;
    return 0;
}

