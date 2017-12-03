#include <iostream>
#include <string>

using namespace std;

struct Player{
	unsigned int dorsal;
	string apellido;
	unsigned int edad;
	string seleccion;
	char posicion;
	
	Player(unsigned int nro,string ap,unsigned int ed,string sl,char pos){
		dorsal=nro;
		apellido=ap;
		edad=ed;
		seleccion=sl;
		posicion=pos;
	}
	Player(){}
	~Player(){}
	bool operator ==(Player &A){
		bool a=A.apellido == this->apellido;
		bool b=A.dorsal == this->dorsal;
		bool c=A.edad == this->edad;
		bool d=A.posicion == this->posicion;
		bool e=A.seleccion == this->seleccion;
		return e && a && c && b && d;
	}
	void imprimir(){
		cout<< "< "<<seleccion<<" > : "<<dorsal<<" | "<<apellido<<"("<<edad<<" años)"<<" | "<<posicion<<" ||"<<endl;
	}
	unsigned int get_nro(){
		return dorsal;
	}
};
