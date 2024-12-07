#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>

using namespace std;

// Función para abrir el archivo y leer sus líneas
void abrir_archivo(vector<string>& entrada) {
    string linea;
    ifstream archivo("input2.txt");
    if (!archivo) {
        cerr << "No se pudo abrir el archivo input2.txt" << endl;
        return;
    }
    while (getline(archivo, linea)) {
        entrada.push_back(linea);
    }
    archivo.close();
}

// Función para leer cada línea del archivo y extraer el valor objetivo y los números
void leer_linea(long long* valor_prueba, vector<long long>& numeros, const string& linea) {
    string valor_prueba_str, numeros_str;
    long long numero;
    stringstream ss(linea);
    getline(ss, valor_prueba_str, ':');
    *valor_prueba = stoll(valor_prueba_str);
    stringstream numeros_stream(ss.str().substr(ss.tellg()));
    while (numeros_stream >> numero) {
        numeros.push_back(numero);
    }
}

// Función para verificar si una combinación específica de operadores produce el valor objetivo
bool comprobar_combinacion(long long valor_prueba, const vector<string>& combinacion) {
    long long resultado = stoll(combinacion[0]);
    for (size_t i = 1; i < combinacion.size(); i += 2) {
        string operador = combinacion[i];
        long long numero = stoll(combinacion[i + 1]);
        if (operador == "+") {
            resultado += numero;
        } else if (operador == "*") {
            resultado *= numero;
        }
    }
    return resultado == valor_prueba;
}

// Función para generar combinaciones y verificar cuál cumple con el valor objetivo
bool crear_combinaciones(const string& linea, long long& resultado) {
    vector<long long> numeros;
    long long valor_prueba;
    leer_linea(&valor_prueba, numeros, linea);

    vector<string> operadores = {"+", "*"};
    int posiciones = numeros.size() - 1;
    long long total_combinaciones = pow(2, posiciones);

    for (long long i = 0; i < total_combinaciones; ++i) {
        vector<string> combinacion;
        for (int j = 0; j < posiciones; ++j) {
            combinacion.push_back(to_string(numeros[j]));
            combinacion.push_back(operadores[(i >> j) & 1]);
        }
        combinacion.push_back(to_string(numeros[posiciones]));
        if (comprobar_combinacion(valor_prueba, combinacion)) {
            resultado = valor_prueba;
            return true;
        }
    }
    return false;
}

