// @author Claudia Iborra Hurtado


/*
--- Part Two ---

As you scan through the corrupted memory, you notice that some of the conditional statements are also still intact. If you handle some of the uncorrupted 
conditional statements in the program, you might be able to get an even more accurate result.

There are two new instructions you'll need to handle:

    The do() instruction enables future mul instructions.
    The don't() instruction disables future mul instructions.

Only the most recent do() or don't() instruction applies. At the beginning of the program, mul instructions are enabled.

For example:

xmul(2,4)&mul[3,7]!^don't()_mul(5,5)+mul(32,64](mul(11,8)undo()?mul(8,5))

This corrupted memory is similar to the example from before, but this time the mul(5,5) and mul(11,8) instructions are disabled because there is a don't() 
instruction before them. The other mul instructions function normally, including the one at the end that gets re-enabled by a do() instruction.

This time, the sum of the results is 48 (2*4 + 8*5).

Handle the new instructions; what do you get if you add up all of the results of just the enabled multiplications?

*/
#include <iostream>
#include <fstream>
#include <string>
#include <regex>
using namespace std;

string file(){
    ifstream file("puzzleinput.txt");
    string puzzle;

    if (!file.is_open()) {
        std::cerr << "No se pudo abrir el archivo " << std::endl;
        return "";
    }

    getline(file, puzzle, '\0');  // Leer todo el archivo   
    file.close(); 
    return puzzle;
}


// Función para manejar las instrucciones do() y don't() de forma incremental
void do_dont(sregex_iterator &iter, bool &activa) {
    string inst = (*iter).str();
    if (inst == "do()") {
        activa = true;  // Habilitar las multiplicaciones
    } else if (inst == "don't()") {
        activa = false;  // Deshabilitar las multiplicaciones
    }
}

int main() {
   // Expresión para encontrar mul(X, Y)
    regex mul(R"(mul\((\d+),(\d+)\))");
    // Expresión para encontrar do() y don't()
    regex d(R"(do\(\)|don't\(\))");

    // Leer el archivo
    string puzzle = file();

    // Iteradores do() y don't()
    sregex_iterator iter(puzzle.begin(), puzzle.end(), d);
    sregex_iterator end;

    // Iterador mul(x, y)
    sregex_iterator iter_m(puzzle.begin(), puzzle.end(), mul);
    sregex_iterator end_m;

    int result = 0;
    bool activa = true;  // Las multiplicaciones están habilitadas por defecto

    // Recorrer las multiplicaciones y aplicar el estado actual de activa
    while (iter_m != end_m) {
        // Primero, procesar cualquier instrucción do() o don't() que se encuentre antes de la multiplicación
    while (iter != end && iter->position(0) < iter_m->position(0)) {
            do_dont(iter, activa);
            ++iter;  // Avanzar al siguiente "do()" o "don't()"
        }

        // Extraer los números de la coincidencia de multiplicación
        int x = stoi((*iter_m)[1].str());
        int y = stoi((*iter_m)[2].str());

        // Si las multiplicaciones están habilitadas, sumamos el resultado
        if (activa) {
            result += (x * y);
        }

        ++iter_m;  // Avanzar a la siguiente coincidencia de multiplicación
    }

    // Mostrar el resultado total
    std::cout << "El resultado es: " << result << std::endl;

    return 0;
}