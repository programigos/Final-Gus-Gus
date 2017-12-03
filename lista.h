#include <iostream>
#include <string>
using namespace std;
template <class T >
struct nodo {
	T valor;
	nodo<T>* next=nullptr;
	
	nodo();
	nodo(T v, nodo<T>* next);
	~nodo();
};
template <class T>
nodo<T>::nodo(){}

template <class T>
nodo<T>::nodo(T v,nodo<T>* n_next)
{
	this->valor = v;
	this->next = n_next;
}
template <class T>
nodo<T>::~nodo() {}

template <class T,class C>
struct list {
	nodo<T>* head;
	string name;
	list(string);
	C c;
	~list();
	bool find(T x, nodo<T>**& p);
	bool insert(T x);
	bool erase(T x);
	void print(void);
	T operator [](unsigned int i){
		nodo<T> *t = head;
		unsigned int x=0;
		while (t) {
			if(x==i)
				return t->valor;
			t = t->next;
		}
	}
};
template <class T,class C>
list<T,C>::list(string a)
{
	head = nullptr;
	name = a;
}
template <class T,class C>
list<T,C>::~list()
{
	nodo<T>*temp = head;
	while (head->next)
	{
		head = head->next;
		delete temp;
		temp = head;		
	}
}
template <class T,class C>
bool list<T,C>::find(T x, nodo<T>**&p)
{
	p = &head;
	while (*p && c((*p)->valor,x))
		p = &((*p)->next);
	return (*p) && (*p)->valor == x;
}
template <class T,class C>
bool list<T,C>::insert(T x)
{
	nodo<T>** p;
	if (find(x, p)) return 0;
	*p = new nodo<T>(x,*p);
	/*nodo<T>* t = new nodo<T>(x);
	t->next = *p;
	*p = t;*/
	return 1;
}
template <class T,class C>
bool list<T,C>::erase(T x)
{
	nodo<T>**p;
	if (!find(x, p)) return 0;
	nodo<T>* t = *p;
	*p = (*p)->next;
	delete t;
	return 1;
}
template <class T,class C>
void list<T,C>::print(void)
{
	cout << "- ";
	nodo<T> *t = head;
	while (t) {
		cout << t->valor << " - ";
		t = t->next;
	}
	cout << endl;
}
//-----------------------------------------------------------//
