#include <iostream>
#include <cstdlib>
#include <fstream>
#include "aveliano.h"
#include "lista.h"
#include <vector>
#include <string>

using namespace std;

void sleep(){
	long i=0,o;
	while(i<100000000){
		o=2*2+2*2+2*2+2*2+2*2+2*2+2*2+2*2+2*2+2*2+2*2+2*2+2*2+2*2+2*2+2*2+2*2+2*2+2*2+2*2+2*2+2*2+2*2+2*2+2*2+2*2+2*2+2*2+2*2+2*2+2*2+2;
		o=0;
		i++;
	}
}
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
};
struct pushBack{
	bool operator()(Player &A,Player &B){
		return 1;
	}
};
struct pNro{
	bool operator()(Player &A,Player &B){
		unsigned int a=A.dorsal,b=B.dorsal;
		return a<b;
	}
};
void insertarJugador(vector<list<Player,pushBack>> &paises){
	string n,ap;
	char pos;
	unsigned int no,ed;
	cout<<"Nacionalidad    : ";cin>>n;
	cout<<"Apellido        : ";cin>>ap;
	cout<<"Edad            : ";cin>>ed;
	cout<<"Posicion        : ";cin>>pos;
	cout<<"Nro de camiseta : ";cin>>no;
	Player *newPlayer = new Player(no,ap,ed,n,pos);
	paises[0].insert(newPlayer);
	cout<<paises[0][0]->apellido<<"sssws"<<endl;
}
void eliminarSeleccion(){}
void eliminarJugador(){}

void lpe(AvelianTree<list<Player*,pNro>,Mayor<int>> &t){
	cout<<"por edad"<<endl;
}
void lpP(AvelianTree<list<Player*,pNro>,Mayor<int>> &t){
	cout<<"por posicion"<<endl;
}
void lps(AvelianTree<list<Player*,pNro>,Mayor<int>> &t){
	cout<<"por seleccion"<<endl;
}
int main(){
	vector<list<Player,pushBack>> Naciones;
	AvelianTree<list<Player*,pNro>,Mayor<int>> porEdad , porPos , RUSSIA;
	
	///first menu
	cout<<"  ______________________________________  "<<endl;
	cout<<"||--------------------------------------||"<<endl;
	cout<<"||        - - - Russia 2018 - - -       ||"<<endl;
	cout<<"||______________________________________||"<<endl;
	cout<<"  --------------------------------------  "<<endl;
	
	char opcion,op;
	while(true){
		cout<<"  --------------------------------------  "<<endl;
		cout<<"0 -> Salir"<<endl;
		cout<<"1 -> Modificar"<<endl;
		cout<<"2 -> Visualizar"<<endl;
		cout<<endl;
		cout<<"Ingrese una opcion:"<<endl;
		cin>>opcion;
		system("cls");
		if(opcion == '0'){
			cout<<"-CERRADO-"<<endl;
			break;
		}
		else if(opcion == '1'){
			cout<<"--------------MODIFICAR---------------"<<endl;
			cout<<"1 -> añadir seleccion"<<endl;
			cout<<"2 -> añadir jugador"<<endl;
			cout<<"3 -> eliminar seleccion"<<endl;
			cout<<"4 -> eliminar jugador"<<endl;
			cout<<endl;
			cout<<"0 -> atras"<<endl;
			cin>>opcion;
			system("cls");
			if(opcion=='1'||opcion=='2'||opcion=='3'||opcion=='4'){
				switch(opcion){
				case '1':
//					insertarSeleccion("mexico",Naciones);
					break;//insertar seleccion
				case '2':
					insertarJugador(Naciones);
					break;//insertar jugador
				case '3':
					break;//borrar seleccion
				case '4':
					break;//borrar jugador
				}
			}
			else{
				;
			}
		}
		else if(opcion == '2'){
			cout<<"-------------VISUALIZAR--------------"<<endl;
			cout<<"1 -> Listado por Edad"<<endl;
			cout<<"2 -> Listado por Posicion"<<endl;
			cout<<"3 -> Listado por Selecciones"<<endl;
			cout<<endl;
			cout<<"0 -> atras"<<endl;
			cin>>opcion;
			system("cls");
			if(opcion=='1'||opcion=='2'||opcion=='3'){
				switch(opcion){
				case '1':
					sleep();cout<<" . ";sleep();cout<<" . ";sleep();cout<<" . "<<endl;
					lpe(porEdad);
					cin>>op;
					break;//lista por edad
				case '2':
					sleep();cout<<" . ";sleep();cout<<" . ";sleep();cout<<" . "<<endl;
					lpP(porPos);
					cin>>op;
					break;//lista por posicion
				case '3':
					sleep();cout<<" . ";sleep();cout<<" . ";sleep();cout<<" . "<<endl;
					lps(RUSSIA);
					cin>>op;
					break;//lista de selecciones
				}
			}
			else{
				;
			}
		}
		system("cls");
	}
	return 0;
}
