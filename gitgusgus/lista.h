#include <iostream>
#include <string>
using namespace std;

template <class T >
struct nodo{
	T valor;
	nodo<T>* next=NULL;
	
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
	list();
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
	bool encontrar(T x, nodo<T>**&p);
	bool erase2(T x);
	bool insert2(T x);
};
template <class T,class C>
list<T,C>::list()
{
	head = NULL;
}
template <class T,class C>
list<T,C>::~list()
{
	nodo<T>*temp = head;
	while (head)
	{
		head = head->next;
		delete temp;
		temp = head;
	}
	delete temp;
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
bool list<T,C>::encontrar(T x, nodo<T>**&p)
{
	p = &head;
	while (*p && !(*((*p)->valor) == *x))
		p = &((*p)->next);
	return (*p) && (*((*p)->valor) == *x);
}

template <class T,class C>
bool list<T,C>::insert(T x)
{
	nodo<T>** p;
	if (find(x, p)) return 0;
	*p = new nodo<T>(x,*p);

	return 1;
}
template <class T,class C>
bool list<T,C>::erase(T x)
{
	nodo<T>**p;
	if (!find(x, p)) return 0;
	nodo<T> *t = *p;
	*p = (*p)->next;
	delete t;
	return 1;
}
template <class T,class C>
bool list<T,C>::insert2(T x)
{
	nodo<T>** p;
	if(encontrar(x, p)) return 0;
	find(x,p);
	*p = new nodo<T>(x,*p);
	return 1;
}
template <class T,class C>
bool list<T,C>::erase2(T x)
{
	nodo<T>**p;
	if (!encontrar(x, p)) return 0;
	nodo<T> *t = *p;
	*p = (*p)->next;
	delete t;
	return 1;
}

template <class T,class C>
void list<T,C>::print(void)
{
	nodo<T> *t = head;
	while (t) {
		t->valor->imprimir();
		cout  << endl;
		t = t->next;
	}
}
