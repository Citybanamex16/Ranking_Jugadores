//Proyect_dlist.h
/*
Autor: Carlos Delgado Contreras
Matricula: A01712819
Fecha: 16 de Septiembre de 2025
*/

#ifndef PROYECT_DLIST_H
#define PROYECT_DLIST_H

#include <iostream>

template <class T> class DList;
template <class T>
class Nodo{
private:
	std::string nombre;
	T puntaje;
	T nivel;

	Nodo* next;
	Nodo* prev;
public:
	Nodo(std::string nombre,T,T);
	Nodo(std::string nombre,T,T, Nodo<T>*,Nodo<T>*);
	Nodo(const Nodo<T>&);

	friend class DList<T>;
};

template < class T>
Nodo<T>::Nodo(std::string name,T val,T num): nombre(name), puntaje(val), nivel(num),next(nullptr),prev(nullptr){}
template < class T>
Nodo<T>::Nodo(std::string name,T val,T num ,Nodo* _next,Nodo* _prev): nombre(name),puntaje(val),nivel(num),next(_next),prev(_prev){}
template < class T>
Nodo<T>::Nodo(const Nodo<T> &n): nombre(n.nombre),puntaje(n.puntaje),nivel(n.nivel),next(n.next),prev(n.prev){}
//En este caso n No es un apuntador sino que es un objeto Nodo. Por lo que usamos el "." para llamar a sus atributos.

template <class T>
class DList{
private:
	Nodo<T>* head;
	Nodo<T>* tail;
	int size;
public:
	DList();
	DList(Nodo<T>* ptr);
	~DList();

	std::string toStringForward() const;
	std::string toStringBackward() const;

	//Funciones de Lista 
	void insertion(std::string nombre_jugador,int val,int num); //Añade a un jugador nuevo
	void update(std::string nombre, T val, T nivel ); // Modifica los valores de un jugador.
	void deleteAt(std::string nombre_a_eliminar); //Borra un jugador.
	Nodo<T>* search(std::string nombre_a_buscar); //Buscar a un jugador por nombre
	void consultar(std::string nombre); //Consultar los datos de un nodo en especifico
	bool empty() const;
	int index(std::string nombre);
	int get_size();
};

//Constructores 
template <class T>
DList<T>::DList():head(nullptr),size(0){}
template <class T>
DList<T>::DList(Nodo<T>* ptr):head(ptr),size(1){}
//Destructor
template <class T>
DList<T>::~DList(){
	{
    Nodo<T>* actual = head;
    while (actual != nullptr) {
        Nodo<T>* tmp = actual;
        actual = actual->next;
        delete tmp;
    }
}
}

//Funciones
template <class T>
std::string DList<T>::toStringForward() const {
	std::stringstream aux;
	Nodo<T> *p;

	if(size == 0){
		return "[]";
	}
	p = head;
	aux << "[";
	while (p != 0) {
		aux << p->nombre;
		if (p->next != 0) {
			aux << ", ";
		}
		p = p->next;
	}
	aux << "]";
	return aux.str();
}

template <class T>
std::string DList<T>::toStringBackward() const {
	std::stringstream aux;
	Nodo<T> *p;

	if(size == 0){
		return "[]";
	}

	p = tail;
	aux << "[";
	while (p != 0) {
		aux << p->nombre;
		if (p->prev != 0) {
			aux << ", ";
		}
		p = p->prev;
	}
	aux << "]";
	return aux.str();
}

template <class T>
bool DList<T>::empty() const {
	if(size == 0){
		return true;
	}
	return false;
}


std::string toLower(const std::string& texto) {
    std::string resultado = texto;
    std::transform(resultado.begin(), resultado.end(), resultado.begin(),
                   [](unsigned char c){ return std::tolower(c); });
    return resultado;
}


template <class T>
void DList<T>::insertion(std::string nom,int puntos, int nivel)  {
	//Agregar al final. 
	Nodo<T> *p = tail;
	Nodo<T> *new_node = new Nodo<T>(nom, puntos, nivel); //ambos ptr en null

	if(empty()){
		tail = new_node;
		head = new_node;
		size++;
		return;
	}
	p->next = new_node;
	new_node->prev = p;
	tail = new_node;
	size++;
}

template <class T>
void DList<T>::update(std::string nombre_a_buscar, T nuevo_puntaje, T nuevo_nivel){
	Nodo<T>* ptr = head; //Apuntador temporal para recorrer la lista
	if(!empty()){
	// No esta vacío entonces procedemos a buscar
		std::string nombre_modificar_lower = toLower(nombre_a_buscar);

	for(int i = 0; i < size;i++){
		//buscamos de entre el rango de nodos.
		//std::cout << "Este es mi nombre " << ptr -> nombre << std::endl;
		std::string nombre_actual_lower = toLower(ptr->nombre);
		if(nombre_modificar_lower == nombre_actual_lower){
			//encontramos al jugador
			//std::cout << "modificado PIUM"<< std::endl;
			ptr -> puntaje = nuevo_puntaje;
			ptr -> nivel = nuevo_nivel;
			return;
		}
		else{
			ptr = ptr -> next; //Avanzamos
		}
	}
	// Acabo el for y no lograos encontrar el nombre 
	std::cout<<"Jugador no encontrado " << std::endl;

	}
	//Esta vacío :(
	else{
		std::cout<< "Lista Vacía: No hay jugadores" << std::endl;
	}
}


template <class T>
Nodo<T>* DList<T>::search(std::string nombre_a_buscar){
	Nodo<T>* ptr = head; //Apuntador temporal para recorrer la lista

	if(!empty()){// No esta vacio podemos buscar.
		std::string nombre_busqueda_lower = toLower(nombre_a_buscar);

	for( int i = 0; i < size; i++){
		std::string nombre_actual_lower = toLower(ptr->nombre);

		if(nombre_busqueda_lower == nombre_actual_lower)
		{
			//lo encontramos y devolvemos el indice
			return ptr;
		}
		else{
			ptr = ptr -> next;
		}
	}
	//No fue encontrado
	return nullptr;
	}
	else{
		std::cout << "Lista vacía: No hay jugadores" << std::endl;
	}
	return nullptr;

}


template <class T>
void DList<T>::consultar(std::string nombre) {
    Nodo<T>* consulta = search(nombre);

    if (consulta != nullptr) {
        std::cout << "┌────────────────────────────┐" << std::endl;
        std::cout << "│      CONSULTA DE JUGADOR   │" << std::endl;
        std::cout << "├────────────────────────────┤" << std::endl;
        std::cout << "│ Nombre : " << consulta->nombre << std::endl;
        std::cout << "│ Puntaje: " << consulta->puntaje << std::endl;
        std::cout << "│ Nivel  : " << consulta->nivel << std::endl;
        std::cout << "└────────────────────────────┘" << std::endl;
    } 
    else {
        std::cout << "⚠️  No se encontró al jugador \"" << nombre << "\" en la lista." << std::endl;
    }
}

template <class T>
int DList<T>::index(std::string nombre){
	Nodo<T>* ptr = head; //Apuntador temporal para recorred la lista
	int i;
	std::string nombre_busqueda_lower = toLower(nombre);
	for( i = 0; i < size; i++){
		std::string nombre_actual_lower = toLower(ptr->nombre);
		if(nombre_busqueda_lower == nombre_actual_lower)
		{
			return i;
		}
		else{
			ptr = ptr -> next;
		}
	}
	//No fue encontrado
	return -1;

}



template <class T>
void DList<T>::deleteAt(std::string nombre_a_eliminar){
	Nodo<T>* ptr = head; //Apuntador temporal para recorrer la lista
	Nodo<T>* eliminar; //alamacenar el apuntador vecino
	int pos = index(nombre_a_eliminar);
	
	if (pos >= size or pos < 0) { 
		std::cout << "Jugador no encontrado" << std::endl;
		return; }

	else if(pos == 0){
		//ELiminar el primero
		head = ptr -> next; //Head vale el vecino
		head ->prev = nullptr;// desconectamos prev del vecino del valor a eliminar. 
		eliminar = ptr; //ELiminar apuntal al valor a eliminar
		eliminar -> next = nullptr; //desconectamos next.
		eliminar -> nivel = 0;
		eliminar -> puntaje = 0;
		delete eliminar;
	}

	// Caso 2: eliminar el último
    else if (pos == size - 1) {
        eliminar = tail;
        tail = tail->prev;
        tail->next = nullptr;

        eliminar->prev = nullptr;
        delete eliminar;
    }

    else{ //Caso 3: Eliminar en Medio 
	for(int i = 0; i < pos;i++){
		// Recorremos hasta la pos indicada
		//A <-> B <-> C
		ptr = ptr -> next;
	}
	//Llegamos al nodo a eliminar. Ptr vale B
	eliminar = ptr; //guardamos el apuntador al nodo a eliminar.
	eliminar->prev->next = eliminar->next; // A->next = C
	eliminar->next->prev = eliminar->prev; // C->prev = A

	

	//En este momento Tanto A como C estan enlazados. Podemos desconctar C.
	eliminar -> next = nullptr; //desconectamos el next de B
	eliminar -> prev = nullptr; //desconectamos el prev de B
	delete eliminar;

    }
	size -= 1;

}
template <class T>
int DList<T>::get_size(){
	return size;
}

#endif