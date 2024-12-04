/**
 * @author Alexandra Zapata Rincón
 */


#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

/*Se comprueba que la diferencia entre niveles no salga del rango*/
int diferencia(vector<int> v){
    int temp;
    for(int i=0; i<v.size()-1; i++){
        temp = abs(v[i]-v[i+1]);
        //cout << temp << endl;
        if(temp<1 || temp>3){
            return -1;
        }
    }
    return 0;
}


/*Se comprueba si el vector sigue un patrón de subida, bajada, hay dos
números iguales seguidos o si no se sigue ningún patrón*/
int subibaja(vector<int> v){
    int sube;
    if(v[0]>v[1]){
        sube = 0;
    } else if (v[0]<v[1]){
         sube = 1;
    } else {
        return -1;
    }
    
    for(int i=1; i<v.size()-1; i++){
        if(v[i]>v[i+1]){
            if(sube==1){
                return -1;
            }
        } else if (v[i]<v[i+1]){
            if(sube==0){
                return -1;
            }
        }
    }

    return 0;
}

/*Se rellena los reports con los levels (números)*/
void fillreport(vector<vector<int>> &reports){
    ifstream file("input.txt");
    string line, data;
    while(getline(file, line)){
        vector<int> v;
        stringstream iss(line);
        while(iss>>data){
            v.push_back(stoi(data));
        }
        reports.push_back(v);
    }
}

int main(){
    int safes=0, err1, err2;
    vector<vector<int>> reports;

    fillreport(reports);
    for(int i=0; i<reports.size();i++){
        err1 = diferencia(reports[i]);
        err2 = subibaja(reports[i]);
        //cout << err1 << " y " << err2 << endl;
        if(err1==0 && err2==0)
            safes+=1;
    }
    cout << "Numero de informes seguros: " << safes << endl;
}