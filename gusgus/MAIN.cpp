#include <iostream>
#include <cstdlib>
#include <fstream>
#include "aveliano.h"
#include "lista.h"
#include "player.h"
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

struct pushBack{
	inline bool operator()(Player &A,Player &B){
		return 1;
	}
};
struct pNro{
	inline bool operator()(Player &A,Player &B){
		unsigned int a=A.dorsal,b=B.dorsal;
		return a<=b;
	}
};
void insertarJugador(list<Player,pushBack> &jug){
	string n,ap;
	char pos;
	unsigned int no,ed;
	cout<<"Nacionalidad    : ";cin>>n;
	cout<<"Apellido        : ";cin>>ap;
	cout<<"Edad            : ";cin>>ed;
	cout<<"Posicion        : ";cin>>pos;
	cout<<"Nro de camiseta : ";cin>>no;
	Player *newPlayer = new Player(no,ap,ed,n,pos);
	jug.insert(*newPlayer);
}
void eliminarJugador(){}

void lpe(AvelianTree<Node<Player*>,Mayor<int>> &t){
	cout<<"por edad"<<endl;
}
void lpP(AvelianTree<Node<Player*>,Mayor<int>> &t){
	cout<<"por posicion"<<endl;
}
void lps(AvelianTree<Node<Player*>,Mayor<int>> &t){
	cout<<"por seleccion"<<endl;
}
void printPlayers(list<Player,pushBack> &p){
	nodo<Player> *t = p.head;
	while (t) {
		t->valor.imprimir();
		t = t->next;
	}
}
int main(){
	list<Player,pushBack> AllPick("");
	AvelianTree<Node<Player*>,Mayor<int>> porEdad , porPos , RUSSIA;

	
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
			cout<<"1 -> añadir jugador"<<endl;
			cout<<"2 -> eliminar jugador"<<endl;
			cout<<"3 -> LISTA DE JUGADORES"<<endl;
			cout<<endl;
			cout<<"0 -> atras"<<endl;
			cin>>opcion;
			system("cls");
			if(opcion=='1'||opcion=='2'||opcion=='3'){
				switch(opcion){
				case '2':
					break;//borrar jugador
				case '1':
					insertarJugador(AllPick);
					break;//añadir jugador
				case '3':
					printPlayers(AllPick);
					cin>>op;
					break;//lista de jugadores
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
