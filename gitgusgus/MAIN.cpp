#include <iostream>
#include <cstdlib>
#include <fstream>
#include "aveliano.h"
#include <vector>
#include <string>
#include <locale>

using namespace std;

void sleep(){
	long i=0,o;
	while(i<100000000){
		o=2*2+2*2+2*2+2*2+2*2+2*2+2*2+2*2+2*2+2*2+2*2+2*2+2*2+2*2+2*2+2*2+2*2+2*2+2*2+2*2+2*2+2*2+2*2+2*2+2*2+2*2+2*2+2*2+2*2+2*2+2*2+2;
		o=0;
		i++;
	}
}

list<Player,pushBack> AllPick;
AvelianTree<unsigned int,pEdad> porEdad;
AvelianTree<char,pPos> porPos;
AvelianTree<string,pSeleccion> RUSSIA;

void insertarJugador(){
	string n,ap;
	char pos;
	unsigned int no,ed;
	cout<<"Nacionalidad    : ";cin>>n;
	cout<<"Apellido        : ";cin>>ap;
	cout<<"Edad            : ";cin>>ed;
	cout<<"Posicion        : ";cin>>pos;
	cout<<"Nro de camiseta : ";cin>>no;
	Player *newPlayer = new Player(no,ap,ed,n,pos);
	AllPick.insert(*newPlayer);
	porEdad.insert(newPlayer);
	porPos.insert(newPlayer);
	RUSSIA.insert(newPlayer);
}
void eliminarJugador(){
	string n,ap;
	char pos;
	unsigned int no,ed;
	cout<<"Nacionalidad    : ";cin>>n;
	cout<<"Apellido        : ";cin>>ap;
	cout<<"Edad            : ";cin>>ed;
	cout<<"Posicion        : ";cin>>pos;
	cout<<"Nro de camiseta : ";cin>>no;
	Player *newPlayer = new Player(no,ap,ed,n,pos);
	AllPick.erase(*newPlayer);
	porEdad.remove_player(newPlayer);
	porPos.remove_player(newPlayer);
	RUSSIA.remove_player(newPlayer);
}

void lpe(){
	cout<<"por edad"<<endl;
	int a,b;
	cout << "Ingrese la edad mínima: ";
	cin >> a;
	cout << "Ingrese la edad máxima: ";
	cin >> b;
	sleep();cout<<" . ";sleep();cout<<" . ";sleep();cout<<" . "<<endl;
	porEdad.rango(porEdad.root,a,b);
	cout<<"0 -> continuar";
	char s;cin>>s;
}
void lpP(){
	cout<<"por posicion"<<endl;
	cout << "Ingrese una posicion: ";
	char pos;
	cin >> pos;
	sleep();cout<<" . ";sleep();cout<<" . ";sleep();cout<<" . "<<endl;
	porPos.print(pos);
	cout<<"0 -> continuar";
	char s;cin>>s;
}
void lps(){
	cout<<"por seleccion"<<endl;
	cout << "Ingrese una seleccion: ";
	string sel;
	cin >> sel;
	sleep();cout<<" . ";sleep();cout<<" . ";sleep();cout<<" . "<<endl;
	RUSSIA.print(sel);
	cout<<"0 -> continuar";
	char s;cin>>s;
}
void printPlayers(list<Player,pushBack> &p){
	nodo<Player> *t = p.head;
	while (t) {
		t->valor.imprimir();
		t = t->next;
	}
	cout<<"0 -> continuar";
	char s;cin>>s;
}
void generar_mundial(list<Player,pushBack> &AllPick){
	ifstream entrada;
	string num;
	string ape;
	string pos;
	string ed;
	string equi;
	string completo;
	entrada.open("teams.txt");
	while(!entrada.eof()){
		getline(entrada,completo);
		num = completo.substr(0,completo.find('-'));
		ape = completo.substr(completo.find('-')+1);
		pos = ape.substr(ape.find('-')+1);
		ed = pos.substr(pos.find('-')+1);
		equi = ed.substr(ed.find('-')+1);
		
		ape = ape.substr(0,ape.find('-'));
		pos = pos.substr(0,pos.find('-'));
		ed = ed.substr(0,pos.find('-'));
		
		Player *temp = new Player((unsigned int)atoi(num.c_str()),ape,(unsigned int)atoi(ed.c_str()),equi,pos[0]);
		AllPick.insert(*temp);
		porEdad.insert(temp);
		porPos.insert(temp);
		RUSSIA.insert(temp);
	}
	entrada.close();
}
int main(){
	
	generar_mundial(AllPick);
	setlocale(LC_ALL,"spanish");

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

			cout<<endl;
			cout<<"0 -> atras"<<endl;
			cin>>opcion;
			system("cls");
			if(opcion=='1'||opcion=='2'||opcion=='3'){
				switch(opcion){
				case '2':
					eliminarJugador();
					break;//borrar jugador
				case '1':
					insertarJugador();
					break;//añadir jugador
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
			cout<<"4 -> LISTA COMPLETA DE JUGADORES"<<endl;
			cout<<endl;
			cout<<"0 -> atras"<<endl;
			cin>>opcion;
			system("cls");
			if(opcion=='1'||opcion=='2'||opcion=='3'||opcion=='4'){
				switch(opcion){
				case '1':
					lpe();
					break;//lista por edad
				case '2':
					lpP();
					break;//lista por posicion
				case '3':
					lps();
					break;//lista de selecciones
				case '4':
					printPlayers(AllPick);
					break;//lista de jugadores
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
