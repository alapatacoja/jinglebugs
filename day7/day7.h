#include <iostream>
#include <math.h>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>

using namespace std;

void abrir_archivo(vector<string>& entrada){
	string linea;
	ifstream archivo("input2.txt");
    	if (!archivo) {
        	cerr << "No se pudo abrir el archivo input.txt" << endl;
    	}

    	while (getline(archivo, linea)) {
        	entrada.push_back(linea);
    	}

    	archivo.close();
}

void leer_linea(long *valor_prueba, vector<long>& numeros, const string& linea){
	
	string valor_prueba_str;
	string numeros_str;
        long numero;
	
	stringstream ss(linea);
        getline(ss, valor_prueba_str, ':');
        getline(ss, numeros_str);

        *valor_prueba = stol(valor_prueba_str);
        stringstream numeros_stream(numeros_str);

        while (numeros_stream >> numero) {
            numeros.push_back(numero);
        }
}

int comprobar_combinacion(long valor_prueba, vector<string>& combinacion){
	long resultado = stol(combinacion[0]);
    	for (size_t i = 1; i < combinacion.size(); i += 2) {
        	string operador = combinacion[i];
        	long numero = stol(combinacion[i + 1]);
        	if (operador == "+") {
            		resultado += numero;
        	} else if (operador == "*") {
            		resultado *= numero;
        	}
    	}
	
	if(resultado == valor_prueba){
	       cout<<"SÍ: "<<valor_prueba<<"="<<resultado<<endl;	
		return valor_prueba;
	} else{ 
		return 0;
	}
}

long crear_combinaciones(const string& linea){
	vector <long> numeros;
	long valor_prueba;
	long resultado = 0;
	leer_linea(&valor_prueba, numeros, linea);
	vector<string> operadores = {"+", "*"};
    	int posiciones = numeros.size() - 1;
    	long total_combinaciones = pow(2, posiciones);

    	for (long i = 0; i < total_combinaciones; ++i) {
        	if(resultado==0){
			vector<string> combinacion;
        		for (int j = 0; j < posiciones; ++j) {
            			combinacion.push_back(to_string(numeros[j]));
            			combinacion.push_back(operadores[(i >> j) & 1]);
        		}
        		combinacion.push_back(to_string(numeros[posiciones]));
        		resultado= comprobar_combinacion(valor_prueba, combinacion);
		} else{
			return resultado;
		}
	}

	return resultado;
}


