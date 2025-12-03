/*Proyecto_hash.h
Author: Carlos Delgado Contreras 
A01712819
28 de novimebre de 2025
*/


#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <cctype> //para convertir un string en minusculas
#include <iomanip>  // mejorar prints


using namespace std;

template <class Key, class Value>
class Hash_table{
private:
	int size;
	int count;
	vector<vector<Value>> tabla_valores; //Un arreglo fijo con el valor de los datos
	Key *tabla_llaves; //Un arreglo fijo con el status de los lugares en la tabla -> false/true
	Key llaves_iniciales;
	int DELETE = -999;
	unsigned int (*func)(const string);


public:
	Hash_table(string);
	Hash_table(int,Key, unsigned int (*f) (const string));
	 ~Hash_table();  // DESTRUCTOR >:)
	//int hash_function(int); //recibe una llave y devuelve un indice
	bool put(Key,Value,Value); //recibe una llave y la inserta dependiendo de lo que Hash_function dicte -> si ya existe lo modifica.
	bool eliminar(Key); //Recibimos la llave a eliminar, la buscamos y la eliminamos
	int collision(int,int);
	//string c_str(); 
	string toString() const;
	bool get(Key);// consulta de jugador
	int get_count(); // devuelve la cantidad de jugadores actuales
	long HashIndex(const Key);
	bool modificar(const Key,const Value, const Value); //Modificar a un jugador existente
	bool full();
};


template <class Key, class Value>
Hash_table<Key,Value>::Hash_table(int sze, Key init_key, unsigned int (*f) (const string)):size(sze),tabla_valores(size,vector<int>(2,-1)){
	count = 0;
	llaves_iniciales = init_key;
	//Inicializamos nuestras estructuras 
	tabla_llaves = new Key[size];
	

	for(int i = 0; i < size;i++){
		vector<int> datos;
		//datos[0] = -1; //Todos los valores en -1
		//datos[1] = -1; //Todos los valores en -1
		//tabla_valores.push_back(datos); //Metemos nuevo vector de jugador.
		tabla_llaves[i] = llaves_iniciales; //Todos los indices en un valor inicial
	}

	this -> func = f;

}

// Implementación
template <class Key, class Value>
Hash_table<Key,Value>::~Hash_table(){
    delete[] tabla_llaves;  // Liberar memoria
}



template<class Key, class Value>
long Hash_table<Key,Value>::HashIndex(const Key key){
	int i;
	int start;
	int paso = 0;

	start = i = func(key) % size; //Evitamos iterar infinitamente
	do {
		if (tabla_llaves[i] == key) {
			//Checamos si la llave que buscamos esta en este locker
			return i; //Regresamos el indice hash de nuestra llave llave -> abre locker a valores mediante indice
		}
		paso++;
		i = (i + paso*paso) % size; //Nos movemos cuadraticamente
	} while (start != i);
	return -1; //Nuestra llave a buscar no existe, no esta registrada
}


template <class Key, class Value>
bool Hash_table<Key,Value>::put(Key key, Value value1, Value value2){

	if(!full()){

		int indice = func(key) % size; //Creamos indice hash
	//cout << "indice de: " + key + " es " + to_string(indice) << endl;
	int start = indice;
	int i = 0;
	
	//Mientras el locker en el que estemos no esta vacío
	while(tabla_llaves[indice] != llaves_iniciales){
		//Caso 1: Misma llave, debemos actualizas
		if(tabla_llaves[indice] == key){
			tabla_valores[indice][0] = value1; //Actualizamos llave.
			tabla_valores[indice][1] = value2; //Actualizamos llave.
			return true;
		}

		//Caso 2: No es la misma llave ->colisión
		i++;
		//cout << key + "Tuve su colisión numero " + to_string(i)<< endl;
		indice = collision(indice,i);
		

		//Checamos para no iterar infinitamente
		if(start == indice){
			cout << "Tabla Llena" << endl;
			return false;
		}
	}

	//No entramos al loop pues el indice arrojó un locker vacío :) -> añadimos
	tabla_llaves[indice] = key; //Añadimos la llave en el cajon disponible
	tabla_valores[indice][0] = value1; //Añadimos el valor en el cajon disponible
	tabla_valores[indice][1] = value2;
	count++;
	//cout << "Añadimos llave y valor " << key << value1 << " " << value2 << " en indice " + to_string(indice)<<endl;
	return true;

	}
	else{
		cout << "Limite lleno ";
		return false;
	}

	
	
}

template <class Key, class Value>
int Hash_table<Key,Value>::collision(int collide_index, int step){
	//metodo lineal
	int nuevo_index = (collide_index + step*step) % size;
	//cout << "Nuevo indice es: " << nuevo_index;
	return nuevo_index;
}

template <class Key, class Value>
bool Hash_table<Key,Value>::get(Key key){

	int indice = HashIndex(key); //Buscamos la llave.
	
	//Caso 1: No existe la llave 
	if(indice == -1){
		cout << "Llave inexistente en tabla " << endl;
		return false;
	}

	// FORMATO DE IMPRESIÓN UNIVERSAL
	//Se cambio pues en el Powershell de Windows sale HORRIBLE la implementación anterior.
	// Define el ancho total del marco
	const int ANCHO_CONTENIDO = 30; 
    //const int ANCHO_TOTAL = ANCHO_CONTENIDO + 2;

	// Línea superior del marco
    cout << "\n+" << string(ANCHO_CONTENIDO, '-') << "+" << endl;
    
	// Título centrado
    cout << "| " << left << setw(ANCHO_CONTENIDO) << "STATS DEL JUGADOR" << " |" << endl;
    
	// Separador
    cout << "+" << string(ANCHO_CONTENIDO, '-') << "+" << endl;
    
	// Datos del jugador
    cout << "| Player:" << left << setw(ANCHO_CONTENIDO - 8) << key << " |" << endl;
    cout << "| Score: " << left << setw(ANCHO_CONTENIDO - 8) << tabla_valores[indice][0] << " |" << endl;
    cout << "| Level: " << left << setw(ANCHO_CONTENIDO - 8) << tabla_valores[indice][1] << " |" << endl;
    
	// Línea inferior del marco
    cout << "+" << string(ANCHO_CONTENIDO, '-') << "+\n" << endl;
	// ----------------------------------------------

    return true;
}


// impresion clase quadratic
template <class Key, class Value>
std::string Hash_table<Key, Value>::toString() const {
	std::stringstream aux;
	for (int i = 0; i < size; i++){
			if (tabla_llaves[i] != llaves_iniciales){
				aux << "(" << i << " ";
			  aux << tabla_llaves[i] << " : " << tabla_valores[i][0] << " , " << tabla_valores[i][1] << ") ";
			}
	}
	return aux.str();
}



//Función de eliminación
template <class Key, class Value>
bool Hash_table<Key,Value>::eliminar(Key key_a_eliminar){
	//1. primero se calcula el indice hash
	int  indice_hash = HashIndex(key_a_eliminar);

	//Caso 1 -> No existe la key a eliminar
	if(indice_hash == -1){
		cout << "Jugador '" << key_a_eliminar << "' no existe" << endl;
		return false;
	}
	else{
		//Caso 2: Si lo encontramos, lo eliminamos.
		tabla_llaves[indice_hash] = llaves_iniciales;
		tabla_valores[indice_hash][0] = DELETE;
		tabla_valores[indice_hash][1] = DELETE;
		count--;
		 cout << "Jugador " << key_a_eliminar << " eliminado con exito" << endl;
		return true;
		}

	
}


template <class Key, class Value>
int Hash_table<Key,Value>::get_count(){
	return count;
}

template <class Key, class Value>
bool Hash_table<Key,Value>::modificar(Key llave_a_modificar, Value nuevo_valor1, Value nuevo_valor2){
	//Buscar nuestra indice hash a modificar mediante llave 
	int indice_a_modificar = HashIndex(llave_a_modificar); //Buscamos la llave.

	//Caso 1: No existe mi llave 
	if(indice_a_modificar == -1){
		cout << "Llave a modificar no existe ;(";
		return false;
	}
	else{
		//Caso 2: SI existe vamos a modificarlo
		tabla_valores[indice_a_modificar][0] = nuevo_valor1;
		tabla_valores[indice_a_modificar][1] = nuevo_valor2;
		return true;

	}

	return false;
}

template<class Key, class Value>
bool Hash_table<Key,Value>::full(){
	if(count >= size*0.7){
		return true;
	}
	else{
		return false;
	}
	return false;
}



#endif