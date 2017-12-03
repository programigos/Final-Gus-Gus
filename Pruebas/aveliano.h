#include <iostream>
#include <stack>
#include <vector>
#include <string.h>
#include "lista.h"
#include "player.h"

using namespace std;

bool compString(string a, string b){
	for(int i=0;i<a.length();i++){
		if(a[0]>b[0])
			return 0;
		if(a[0]<b[0])
			return 1;
	}
	return 1;
}
int abs(int a){
	if(a<0)return (a * -1);
	return a;
}
struct pushBack{
	inline bool operator()(Player &A,Player &B){
		return 1;
	}
};
struct pNro{
	inline bool operator()(Player *A,Player *B){
		return A->dorsal<=B->dorsal;
	}
};
struct pEdad{
	inline unsigned int operator()(Player *A){
		return A->edad;
	}
};
struct pPos{
	inline char operator()(Player *A){
		return A->posicion;
	}
};
struct pSeleccion{
	inline string operator()(Player *A){
		return A->seleccion;
	}
};

template <class T>
void PrintVector(vector<T> a){
	int sizz = a.size();
	cout<<"- ";
	for(int i = 0;i < sizz;i++){
		a[i]->print();
		cout<<" - ";
	}
	cout<<endl;
}
template <class T>
struct Node
{
	T my_x;
	Node<T> * my_nodes[2];
	list<Player*,pNro> hash;
	
	int h=0;
	
	Node(T x, Player *P) {
		my_x = x;
		my_nodes[0] = my_nodes[1] = NULL;
		hash.insert(P);
	}
	~Node(){}
	void print(){
		T l,r;
		l= (my_nodes[0] == NULL)? 0 :my_nodes[0]->my_x;
		r= (my_nodes[1] == NULL)? 0 :my_nodes[1]->my_x;
		cout<<my_x<<"->{ L:";
		if(my_nodes[0] == NULL)cout<<"_";
		else
			cout<<l;
		cout<<" R:";
		if(my_nodes[1] == NULL)cout<<"_";
		else
			cout<<r;
		cout<<" }";
		cout<<" H :"<<h;
	}
};
void printStack(stack<Node<int>**> a){
	cout<<"| ";
	while(!a.empty()){
		cout<<(*(a.top()))->my_x<<" | ";
		a.pop();
	}
	cout<<endl;
}
template <class T,class G>
struct AvelianTree
{
	Node<T> *root;
	G my_g;
	stack<Node<T>**> way;
	
	AvelianTree();
	~AvelianTree();
	
	bool find(T x, Node<T> **&p);
	bool insert(Player *x);
	bool remove(T x);
	bool remove_player(Player *x);
	Node<T>** remplazo(Node<T>**& ptr);
	void Niveles(void);
	
	void chekeo();
	void rechekeo();
	void direc(Node<T>**& x,Node<T>**& i);
	void direc2(Node<T>**& x);
	
	void dezSimpleR(Node<T>**& abuelo);
	void dezSimpleL(Node<T>**& abuelo);
	void dezDobleR(Node<T>**& abuelo);
	void dezDobleL(Node<T>**& abuelo);
	
	void inOrden(Node<T>* r);
};

template <class T, class G>
AvelianTree<T,G>::AvelianTree(){
	root = 0;
}
template <class T, class G>
AvelianTree<T,G>::~AvelianTree(){}
template <class T, class G>
bool AvelianTree<T,G>::find(T x, Node<T> **&p){
	p=&root ;
	while(*p && (*p)->my_x != x ){
		way.push(p);
		p=&((*p)->my_nodes[(*p)->my_x<x]);
	}
	way.push(p);
	return !!(*p);
}
template <class T, class G>
bool AvelianTree<T,G>::insert(Player *x){
	Node<T>**p;
	if(find(my_g(x), p)){ 
		return (*p)->hash.insert(x);
	}
	*p = new Node<T>(my_g(x),x);
	chekeo();
	return 1;
}
template <class T, class G>
bool AvelianTree<T,G>::remove(T x){
	Node<T>**p;
	if (!find(x, p))
		return 0;
	if ((*p)->my_nodes[0] &&
		(*p)->my_nodes[1]) {
		int hh=(*p)->h;
		Node<T>**q = remplazo(p);
		(*p)->my_x = (*q)->my_x;
		(*p)->h = (*q)->h;
		(*p)->h=hh;
		p = q;
	}
		Node<T>*temp = *p;
		*p = (*p)->my_nodes[(*p)->my_nodes[1] != 0];
		delete temp;
		rechekeo();
		return 1;
}
template <class T, class G>
bool AvelianTree<T,G>::remove_player(Player *x){
	Node<T>**p;
	if (!find(my_g(x), p))
		return 0;
	p->hash.erase(x);
	if(p->hash->head==nullptr)
		remove(my_g(x));
	return 1;
}
template<class T, class G>
Node<T>** AvelianTree<T,G>::remplazo(Node<T>**& ptr)
{
	Node<T>** t = ptr;
	t = &(*t)->my_nodes[0];
	way.push(t);
	while((*t)->my_nodes[1]){
		t = &(*t)->my_nodes[1];
		way.push(t);
	}
	return t;
}

template<class T, class G>
void AvelianTree<T,G>::chekeo(){
	int hr,hl,ht,ha;
	bool b=false;
	Node<T>** aux = way.top();
	Node<T>**temp;
	temp = aux;
	(*aux)->h +=1;
	way.pop();
	while(!way.empty()){
		if(!b){
			aux=way.top();
			
			hl = ((*aux)->my_nodes[0] == NULL)? 0 :(*aux)->my_nodes[0]->h;
			hr = ((*aux)->my_nodes[1] == NULL)? 0 :(*aux)->my_nodes[1]->h;
			ht = hr-hl;
			if(hl==(*aux)->h||(*aux)->h==hr)
				(*aux)->h +=1;
		}
		if(ht == 2 || ht == -2){
			direc(aux,temp);
			b=true;
			ht=0;
		}
		way.pop();
	}
}
template <class T, class G>
void AvelianTree<T,G>::direc(Node<T>**& a,Node<T>**& i){
	Node<T>** t = a;
	T axx = (*i)->my_x;
	bool d[3];
	for(int j=0;(*t)->my_x != axx;j++){
		d[j]=(*t)->my_x<axx;
		t=&((*t)->my_nodes[d[j]]);
	}
	if(d[0]){
		if(d[1])
			dezSimpleL(a);
		else
			dezDobleL(a);
	}
	else{
		if(!d[1])
			dezSimpleR(a);
		else
			dezDobleR(a);
	}
}
///al padre le resto dos hahahahaahahah
template<class T, class G>
void AvelianTree<T,G>::dezSimpleR(Node<T>**& abuelo){
	int hr,hl,hh;
	Node<T>*temp = *abuelo;
	*abuelo = (*abuelo)->my_nodes[0];
	temp->my_nodes[0]=(*abuelo)->my_nodes[1];
	(*abuelo)->my_nodes[1] = temp;
	
	hl = (temp->my_nodes[0] == NULL)? 0 :temp->my_nodes[0]->h;
	hr = (temp->my_nodes[1] == NULL)? 0 :temp->my_nodes[1]->h;
	hh=temp->h;
	if(hh-hl!=1 || hh-hr!=1){
		temp->h=(hl > hr)? hl+1:hr+1;
	}
	hl = ((*abuelo)->my_nodes[0] == NULL)? 0 :(*abuelo)->my_nodes[0]->h;
	hr = ((*abuelo)->my_nodes[1] == NULL)? 0 :(*abuelo)->my_nodes[1]->h;
	hh=(*abuelo)->h;
	if(hh-hl!=1 || hh-hr!=1){
		(*abuelo)->h=(hl > hr)? hl+1:hr+1;
	}
}
template<class T, class G>
void AvelianTree<T,G>::dezSimpleL(Node<T>**& abuelo){
	int hl,hr,hh;
	Node<T>*temp = *abuelo;
	*abuelo = (*abuelo)->my_nodes[1];
	temp->my_nodes[1]=(*abuelo)->my_nodes[0];
	(*abuelo)->my_nodes[0] = temp;
	
	hl = (temp->my_nodes[0] == NULL)? 0 :temp->my_nodes[0]->h;
	hr = (temp->my_nodes[1] == NULL)? 0 :temp->my_nodes[1]->h;
	hh=temp->h;
	if(hh-hl!=1 || hh-hr!=1){
		temp->h=(hl > hr)? hl+1:hr+1;
	}
	hl = ((*abuelo)->my_nodes[0] == NULL)? 0 :(*abuelo)->my_nodes[0]->h;
	hr = ((*abuelo)->my_nodes[1] == NULL)? 0 :(*abuelo)->my_nodes[1]->h;
	hh=(*abuelo)->h;
	if(hh-hl!=1 || hh-hr!=1){
		(*abuelo)->h=(hl > hr)? hl+1:hr+1;
	}
}
///padre baja 1, abuelo 2 y hijo sube 1 hhahahahaaha
template<class T, class G>
void AvelianTree<T,G>::dezDobleR(Node<T>**& abuelo){
	Node<T>**temp = &((*abuelo)->my_nodes[0]);
	//l y r
	dezSimpleL(temp);
	//(*temp)->h+=1;
	//(*temp)->my_nodes[0]->h+=1;
	dezSimpleR(abuelo);
}
template<class T, class G>
void AvelianTree<T,G>::dezDobleL(Node<T>**& abuelo){
	Node<T>**temp = &((*abuelo)->my_nodes[1]);
	//r y l
	dezSimpleR(temp);
	//	(*temp)->h+=1;
	//	(*temp)->my_nodes[1]->h +=1;
	dezSimpleL(abuelo);
}
template <class T, class G>
void AvelianTree<T,G>::inOrden(Node<T>* r){
	if(!r)return;
	inOrden(r->my_nodes[0]);
	cout<<" ";
	r->hash.print();
	inOrden(r->my_nodes[1]);
}
template<class T, class G>
void AvelianTree<T,G>::Niveles(void){
	Node<T> *p=root;
	vector<Node<T>*> niveles;
	niveles.push_back(p);
	
	while(niveles.size()!=0){
		PrintVector(niveles);
		int s =niveles.size();
		for(int i=0;i < s;s--){
			if(niveles[i]->my_nodes[0]){
				niveles.push_back(niveles[i]->my_nodes[0]);
			}
			if(niveles[i]->my_nodes[1]){
				niveles.push_back(niveles[i]->my_nodes[1]);
			}
			niveles.erase(niveles.begin());
		}
	}
	cout<<endl<<"> ------------------------------------------- <"<<endl<<endl;
}
template <class T> 
vector<T> llenarV(stack<T> a){
	vector<T>s;
	//	printStack(a);
	while(!a.empty()){
		s.push_back(a.top());
		a.pop();
	}
	vector<T>q;
	for(int i=s.size()-1 ; i >= 0 ; i--){
		q.push_back(s[i]);
	}
	return q;
}
template<class T, class G>
void AvelianTree<T,G>::rechekeo(){
	Node<T>** aux;
	int hl,hr,ht,ha;
	way.pop();
	while(!way.empty()){
		aux=way.top();
		ha=(*aux)->h;
		hl = ((*aux)->my_nodes[0] == NULL)? 0 :(*aux)->my_nodes[0]->h;
		hr = ((*aux)->my_nodes[1] == NULL)? 0 :(*aux)->my_nodes[1]->h;
		ht=hr-hl;
		if(ha - hl >1 && ha - hr > 1)
			(*aux)->h =(ha-hl > 1)? hl+1 : hr+1;
		if(ht==-2 ||ht==2){
			direc2(aux);
			break;
		}
		way.pop();
	}
}
template <class T, class G>
void AvelianTree<T,G>::direc2(Node<T>**& x){
	int ht,hl,hr;
	hl = ((*x)->my_nodes[0] == NULL)? 0 :(*x)->my_nodes[0]->h;
	hr = ((*x)->my_nodes[1] == NULL)? 0 :(*x)->my_nodes[1]->h;
	ht=hr-hl;
	if(ht<0){
		//iz
		hl = ((*x)->my_nodes[0]->my_nodes[0] == NULL)? 0 :(*x)->my_nodes[0]->my_nodes[0]->h;
		hr = ((*x)->my_nodes[0]->my_nodes[1] == NULL)? 0 :(*x)->my_nodes[0]->my_nodes[1]->h;
		ht=hr-hl;
		if(ht<=0){
			dezSimpleR(x);return;}
		else{
			dezDobleR(x);return;}
	}
	if(ht>0){
		hl = ((*x)->my_nodes[1]->my_nodes[0] == NULL)? 0 :(*x)->my_nodes[1]->my_nodes[0]->h;
		hr = ((*x)->my_nodes[1]->my_nodes[1] == NULL)? 0 :(*x)->my_nodes[1]->my_nodes[1]->h;
		ht=hr-hl;
		if(ht>=0){
			dezSimpleL(x);return;}
		else{
			dezDobleL(x);return;}
	}
}
template <class T>
struct Mayor{
	bool operator()(T &a,T &b){
		return a<b;
	}
};
