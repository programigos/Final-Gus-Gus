#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class jugador{
public:
    int camiseta;
    int edad;
    string apellido;
    string posicion;
    string equipo;
    void imprimir(){
        cout << camiseta << " " << apellido << " " << posicion << " " << edad << endl;
    }
};

int main(){                             //Podemos meter todo esto en una funcion de crear jugadores
    ifstream entrada;         
    vector<jugador> players;
    string num;
    string ape;
    string pos;
    string ed;
    string completo;
    jugador hola;
    entrada.open("teams.txt");
    while(!entrada.eof()){
        getline(entrada,completo);
        num = completo.substr(0,completo.find('-'));
        ape = completo.substr(completo.find('-')+1);
        pos = ape.substr(ape.find('-')+1);
        ed = pos.substr(pos.find('-')+1);

        ape = ape.substr(0,ape.find('-'));
        pos = pos.substr(0,pos.find('-'));

        hola.apellido = ape;
        hola.camiseta = atoi(num.c_str());
        hola.edad = atoi(ed.c_str());
        hola.posicion = pos;
        players.push_back(hola);
    }
    for(int i = 0; i < players.size(); i++){
        players[i].imprimir();
    }
    entrada.close();
    return 0;
}
