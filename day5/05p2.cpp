/**
 * @author Alexandra Zapata Rincón 
 */

#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <utility> 
using namespace std;

void leerdata(vector<pair<int, int>> &reglas, vector<vector<int>> &updates){
    ifstream file("input.txt");
    string line, x, y, data;
    bool rupdates=false;
    while(getline(file, line)){
        if(line.empty()){
            rupdates=true;
            continue;
        }

        if(!rupdates){
            stringstream ss(line);
            getline(ss, x, '|'); 
            getline(ss, y);
            reglas.emplace_back(stoi(x),stoi(y));
        } else {
            vector<int> v;
            stringstream ss(line);
            while(getline(ss, data, ',')){
                v.push_back(stoi(data));
            }
            updates.push_back(v);
        }
    }
}
    

        bool verificar_update(vector<pair<int, int>> &reglas, vector<int> &update){
            int x, y, xpos, ypos;
            for(int i=0; i<reglas.size(); i++){
                x=reglas[i].first;
                y=reglas[i].second;

                xpos = -1;
                ypos = -1; 

                for(int j=0;j<update.size();j++){
                    if(update[j]==x)
                        xpos=j;
                    if(update[j]==y)
                        ypos=j;
                }

                if(xpos>ypos && xpos!=-1 && ypos !=-1)
                    return false;
                }
            
            return true;
        }

        int medio(const vector<int> &update){
            //cout << update[update.size()/2] << endl;
            return update[update.size()/2];
        }

        void ordenar(vector<pair<int, int>> &reglas, vector<int> &update){
            bool ordenado = false;
            while (!ordenado) {
                ordenado = true;
                for (int i = 0; i < update.size() - 1; i++) {
                    for (int j = 0; j < reglas.size(); j++) {
                        if (update[i] == reglas[j].second && update[i + 1] == reglas[j].first) {
                            swap(update[i], update[i + 1]);
                            ordenado = false;
                            break;
                        }
                    }
                }
            }
        }

        int main(){
            vector<pair<int,int>> reglas;
            vector<vector<int>> updates;
            int suma =0;

            leerdata(reglas, updates);
            
            for(int i = 0; i<updates.size();i++){
                if(!verificar_update(reglas, updates[i])){
                    ordenar(reglas, updates[i]);
                    suma +=  medio(updates[i]);
                }
            }

            cout << suma;
            
        }
