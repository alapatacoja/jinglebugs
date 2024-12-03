// @author Claudia Iborra Hurtado


/*
--- Day 3: Mull It Over ---

"Our computers are having issues, so I have no idea if we have any Chief Historians in stock! 
You're welcome to check the warehouse, though," says the mildly flustered shopkeeper at the North Pole 
Toboggan Rental Shop. The Historians head out to take a look.

The shopkeeper turns to you. "Any chance you can see why our computers are having issues again?"

The computer appears to be trying to run a program, but its memory (your puzzle input) is corrupted. 
All of the instructions have been jumbled up!

It seems like the goal of the program is just to multiply some numbers. It does that with instructions 
like mul(X,Y), where X and Y are each 1-3 digit numbers. For instance, mul(44,46) multiplies 44 by 46 
to get a result of 2024. Similarly, mul(123,4) would multiply 123 by 4.

However, because the program's memory has been corrupted, there are also many invalid characters 
that should be ignored, even if they look like part of a mul instruction. Sequences like 
mul(4*, mul(6,9!, ?(12,34), or mul ( 2 , 4 ) do nothing.

For example, consider the following section of corrupted memory:

xmul(2,4)%&mul[3,7]!@^do_not_mul(5,5)+mul(32,64]then(mul(11,8)mul(8,5))

Only the four highlighted sections are real mul instructions. Adding up the result of each instruction 
produces 161 (2*4 + 5*5 + 11*8 + 8*5).

Scan the corrupted memory for uncorrupted mul instructions. What do you get if you add up all of the results 
of the multiplications?

*/
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
