#include <iostream>
#include <math.h>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include "day7.h"

using namespace std;

int main(){

	vector <string> entrada;
	long resultado = 0;
	
	abrir_archivo(entrada);
	for (const string& linea : entrada) {
		resultado+=crear_combinaciones(linea);
	}

	cout<< "Resultado: " << resultado << endl; 
 
	return 0;
}
