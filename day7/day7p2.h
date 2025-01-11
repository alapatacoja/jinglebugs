#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>

using namespace std;

// Función para abrir el archivo y leer sus líneas
void abrir_archivo(string arch, vector<string>& entrada) {
    string linea;
    ifstream archivo(arch);
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

long long comprobar_siguientes(long long i, const vector<string>& combinacion){
        //caso base encontramos un operado diferente, o , caso base es el ultimo, cuando compruebe el siguiente se saldrá del bucle
        if(i+2 > combinacion.size()) return i; //significa que || es el ultimo operando del vector
	else{
		i = i+ 2;
		for(long long j = i; j<combinacion.size(); j+=2){
		if(combinacion[j]!="||") return j-2; //el siguiente operando no es ||, j es la última posicion del operando ||
		}
	}	
	return combinacion.size()-2; //hemos llegado al final del vector y el último operando también es "||"
	
	/*if(i+2>= combinacion.size()|| combinacion[i+2] !="||"){
		return i;
	}

	i+=2;
        return comprobar_siguientes(i, combinacion);*/
}

// Función para verificar si una combinación específica de operadores produce el valor objetivo
bool comprobar_combinacion(long long valor_prueba, const vector<string>& combinacion) {
    long long resultado = stoll(combinacion[0]);
    for (size_t i = 1; i < combinacion.size(); i += 2) {
        string operador = combinacion[i];
        long long numero = stoll(combinacion[i + 1]);
	long long n = 0;
	//if((i+2<combinacion.size()&&combinacion[i+2]=="||") || (i==1 && combinacion[i]=="||")) {  
	   if(i+2<combinacion.size() && operador!="||" && combinacion[i+2]=="||"){
        	cout<<"Hay un || en: " << i+2 <<endl;
                long long r = stoll(combinacion[i+1]);//primer numero que hay que juntar
		n = comprobar_siguientes(i+2, combinacion);//comrobamos si hay que juntar varios seguidos y guardamos en n la posicion del ultimo
  		cout<<"i: "<<i<<"N: "<<n<<endl;
		for(long long k = i+2; k <= n; k += 2){
                	r = stoll(to_string(r)+combinacion[k+1]);
                }
                numero = r;
		cout<<"Resultado de juntar: "<<numero<< endl;
		if (combinacion[i] == "+") {
                	resultado += numero;
        	} else if (combinacion[i] == "*") {
                	resultado *= numero;
        	}
		i = n; //posición del último || ya que el for hará i+=2 para apuntar al siguiente operando
	} else if(operador =="||"){
	   	cout<<"Hay un || en: " << i <<endl;
                long long r = stoll(combinacion[i-1]);//primer numero que hay que juntar
		n = comprobar_siguientes(i, combinacion);//comrobamos si hay que juntar varios seguidos y guardamos en n la posicion del ultimo || seguidos
                for(long long k = i; k <= n; k += 2){
                        r = stoll(to_string(r) + combinacion[k+1]);
                }
		if(i==1) resultado =0;
                resultado += r; // y saltar el resto de números
		i = n;//posición del último || ya que el for hará i+=2 para apuntar al siguiente operando
                cout<<"Resultado de juntar: "<<resultado<< endl;
	} else{	
     		if (operador == "+") {
			resultado += numero;
		} else if (operador == "*") {
			resultado *= numero;
        	}
     	}
    }
    cout<<"Resultado: "<<resultado<<endl;
    return resultado == valor_prueba;
}
			
// Función para generar combinaciones y verificar cuál cumple con el valor objetivo
bool crear_combinaciones(const string& linea, long long& resultado) {
    vector<long long> numeros;
    long long valor_prueba;
    leer_linea(&valor_prueba, numeros, linea);
    
    cout << valor_prueba<< endl;

    vector<string> operadores = {"+", "*", "||"};
    int posiciones = numeros.size() - 1;
    long long total_combinaciones = pow(3, posiciones);

    for (long long i = 0; i < total_combinaciones; ++i) {
        vector<string> combinacion;
        for (int j = 0; j < posiciones; ++j) {
            combinacion.push_back(to_string(numeros[j]));
            combinacion.push_back(operadores[(i / static_cast<int>(pow(3, j))) % 3]);
        }

	cout<<"Combinación: ";
	for(int i=0; i<combinacion.size(); i++){
		cout<<combinacion[i];
	} cout<<endl;


        combinacion.push_back(to_string(numeros[posiciones]));
        if (comprobar_combinacion(valor_prueba, combinacion)) {
            resultado = valor_prueba;


		cout<<"Sí: "<<resultado<< " = " <<valor_prueba<<endl;

            return true;
        }


	cout<<"NO"<<endl;


    }
    return false;
}

