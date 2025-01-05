// @author Claudia Iborra Hurtado

#include <iostream>
#include <fstream>
#include <string>
#include <regex>
using namespace std;


int main() {

   ifstream file("puzzleinput.txt");

    if (!file.is_open()) {
        std::cerr << "No se pudo abrir el archivo " << std::endl;
        return 1; 
    }

    string puzzle;
    getline(file,puzzle,'\0');
     
    
    
    file.close();


    // Expresión para encontrar mul(X, Y)
    regex mul(R"(mul\((\d+),(\d+)\))");
    

    // Iterador para recorrer la cadena de entrada 
    /*
    iter: es el iterador que empieza al principio de las coincidencias.
    end: es el iterador de final que indica cuando hemos llegado al final de las coincidencias.
    */
    sregex_iterator iter(puzzle.begin(), puzzle.end(), mul);
    sregex_iterator end;

    int result = 0;

    // Recorrer coincidencias y multiplicar
    while (iter != end) {
        // Extraer los números de la coincidencia  (stoi: string to int)
        int x = stoi((*iter)[1].str());
        int y = stoi((*iter)[2].str());

        // Calcular la multiplicación y agregar al total
         result += (x*y);

        ++iter;  // Avanzar a la siguiente coincidencia
    }

    // Mostrar el resultado total
    std::cout << "El resultado es: " << result << std::endl;

    return 0;
}
