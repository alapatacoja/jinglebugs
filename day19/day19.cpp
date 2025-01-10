#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;

void leerdata(vector<string> &patrones, vector<string> &disenos){
    ifstream file("input.txt");
    string line;
    bool lecturaPatrones = true; 

    while(getline(file, line)){
        if(line.empty()){
            lecturaPatrones = false;
            continue;
        }

        if(lecturaPatrones){
            stringstream ss(line);
            string patron;
            while(getline(ss, patron, ',')){
                patron.erase(0, patron.find_first_not_of(" \t\n\r\f\v")); //strip
                patrones.push_back(patron);
            }
        } else {
            disenos.push_back(line);
        }
    }
}

bool comprobarPatrones(string diseno, vector<string> patrones, vector<int> &mem){
    if(diseno.empty())
        return true;
    
    int n = diseno.size();
    if(mem[n] != -1) 
        return mem[n];

    for(int i=0; i<patrones.size(); i++){
        //cout << diseno << "|" << patrones[i] << endl;
        if(diseno.find(patrones[i]) == 0) {
            if (comprobarPatrones(diseno.substr(patrones[i].length()), patrones, mem)) {
                mem[n] = 1;
                return true;
            }
        }
    }
    /* cout << "----" << endl; 
    if(diseno.length()==1)
        return false;
    else comprobarPatrones(diseno.substr(0, diseno.size()-1), patrones, disenoorginal);*/
    mem[n] = 0;
    return false;
}

int main() {
    vector<string> patrones;
    vector<string> disenos;
    int sum = 0;

    leerdata(patrones, disenos);

    for(int i=0; i<disenos.size(); i++){
        vector<int> mem(disenos[i].size()+1, -1);
        if (comprobarPatrones(disenos[i], patrones, mem)) {
            sum++;
        } 

        
    }
    cout << sum << endl;
    return 0;
}
