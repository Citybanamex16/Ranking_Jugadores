//RankingJugadores.cpp

/*
Author: Carlos Delgado Contreras 
Matrícula


*/

#include <iostream>
#include <vector>
#include <string>
#include <fstream> //Librería para lectura de Archivos .CSV
#include <sstream>
#include <iomanip>
#include "Proyect_dlist.h"
using namespace std; 



//Quick Sort
void swap(std::vector<vector<string>>& v, int i, int j){
	//cout << "indices: "<< i << j << endl;
	//cout << "Valores de los indices " << v[i] << v[j] << endl;
	auto auxiliar = v[j];
	v[j] = v[i]; // Mi vecino adelante vale lo mismo que yo 
	v[i] = auxiliar; //Valgo lo que valía el vecino 
}


template <typename T>
int partition(std::vector<T>& v, int low, int high, int parametro){
	int pivote = stoi(v[high][parametro]); //ultimo jugador LOMUTO
	//cout << "Nuevo Pivote " << pivote << endl;
	// Indice de ultimo valor minimo e indice para recorrer el arreglo
	int i = low-1; //Indice de pequeñin
	int j = low; // Indice de recorrido 
	while(j < high){
		if(stoi(v[j][parametro]) >= pivote){
			i++; //Nuevo posición para el nuevo pequeñin despues del anterior.
			swap(v,i,j); //intercambimos el nuevo pequeñin. 
		}
	j += 1;
	}
	//cout << "Acabamos el while :)" << endl;
	//Hemos acabado 
	swap(v,i+1,high);
	return i+1;
}


template <typename T>
void QuickSort(std::vector<T>& v, int low, int high, int parametro){
	if(low >= high){
		return;
	}
	int p = partition(v, low, high, parametro);
	QuickSort(v,low,p-1,parametro); //Izquierda
	QuickSort(v,p+1,high,parametro); //Derecha
	}

template <typename T>
void imprimir_matriz(std::vector<T>& _jugadores) {
    if (!_jugadores.empty()) {
        cout << "===== Ranking de Jugadores =====" << endl;
        cout << left;

        // Encabezado
        cout << setw(5)  << "Pos"
             << setw(20) << "Nombre"   // <-- más ancho por nicks largos
             << setw(10) << "Puntos"
             << setw(12) << "Nivel"
             << endl;

        cout << string(50, '-') << endl;

        // Recorrer jugadores
        for (int i = 1; i < _jugadores.size(); i++) {
            cout << setw(5) << i
                 << setw(20) << _jugadores[i][0]   // Nombre
                 << setw(10) << _jugadores[i][1]   // Puntos
                 << setw(12) << _jugadores[i][2];  // Categoria
            cout << endl;
        }

        cout << "===============================" << endl;
    }
    else {
        cout << "Vector vacío" << endl;
        return;
    }
}

void menu_sort(){
	//Menu de opciones de Sorting
	cout << " ¿Como quieres ordenar el ranking ? " << endl;
	cout << " 1. Por Puntaje " << endl;
	cout << " 2. Por nivel " << endl;
	cout << " 3. Regresar " << endl; 

}

void menu(){
	//Menu General
	cout << " ¿Que vamos a hacer? " << endl;
	cout << " 1. Consultar Jugador " << endl;
	cout << " 2. Agregar Jugador  " << endl;
	cout << " 3. Modificar Jugador " << endl; 
	cout << " 4. Eliminar Jugador " << endl;
	cout << " 5. Visualizar Ranking de jugadores " << endl;
	cout << " 6. Salir de Programa " << endl;
}

void jugadores_totales(const std::vector<std::vector<std::string>>& matriz_jugadores) {
    std::cout << "🎮 LISTA DE JUGADORES REGISTRADOS 🎮" << std::endl;
    std::cout << "────────────────────────────────────" << std::endl;

    for (size_t i = 1; i < matriz_jugadores.size(); ++i) {
        if (!matriz_jugadores[i].empty()) {
            std::cout << "• " << matriz_jugadores[i][0] << std::endl;
        }
    }

    std::cout << "────────────────────────────────────" << std::endl;
    std::cout << "Total de jugadores: " << matriz_jugadores.size() << std::endl;
}



int main()
{
	/* Recibimos un archivo .CSV y lo leemos a traves de una 
	instancia(objeto) de ifstream pasando la ruta del archivo al constructor */

	std::string ruta ="Ranking_CSV.csv";
	std::ifstream archivo(ruta);

	//DEBUG
	if(archivo.is_open()){
		cout << "Archivo CSV encontrado" << endl;
	}
	else{
		while(true)
		{
		cout << "Archivo CSV no encontrado" << endl;
		cout << "Ingresa la ruta del archivo CSV: ";
		std::string nueva_ruta;
		std::getline(std::cin, nueva_ruta); // Lee toda la línea, con espacios
		archivo.open(nueva_ruta);
			if(archivo.is_open())
			{
				cout << "Archivo CVS encontrado" << endl;
				break;
			}

			else{
				continue;
			}

		}
		
	}

	//Lectura linea por linea 
	std::string linea;
	std::vector<vector<std::string>> jugadores; //MATRIZ principal para el Sorting
	DList<int> lista_jugadores;//Lista Doblemente ligada
	int i = 0;
	while(std::getline(archivo,linea))
	{
		//valor verdadero si la lectura fue exitosa o falso si hubo un problema (Fin de archivo).
		std::stringstream contenido(linea); 
		std::string campo; //String donde almacenamos cada campo. 
		std::vector<std::string> campos; // Para almacenar los campos de la línea

		while(std::getline(contenido,campo,','))
		{
			campo.erase(0, campo.find_first_not_of(" \t\r\n"));
    		campo.erase(campo.find_last_not_of(" \t\r\n") + 1);
			campos.push_back(campo); //Agrega el contenido al final del vector.
		}
		jugadores.push_back(campos); //Vector de jugador se almacena con los demas en Matriz

		//Nos saltamos los titulos
		if(i != 0){

		lista_jugadores.insertion(campos[0],std::stoi(campos[1]),std::stoi(campos[2]));
		}
		i++;
	}
	archivo.close();
	//// FIN DE LECTURA 


////Inicio de programa/////
	//cout << "La lista tiene: " << lista_jugadores.get_size() << " jugadores creados" << endl;
	cout << "Bienvendio a la Tabla de Rankin de Jugadores" << endl;

	while(true)
{  	//Loop de menu general.
	int option; //Opcion de Menu general
	jugadores_totales(jugadores);


	//cout <<lista_jugadores.toStringForward()<< endl;
	//cout << lista_jugadores.toStringBackward() << endl;

	menu(); //Menu general
	cin >> option;
	//CONSULTAR
	if(option == 1){
		std::string jugador_a_consultar;
		cout<< "¿Que jugador quieres consultar" <<endl;
		cin >> jugador_a_consultar;
		lista_jugadores.consultar(jugador_a_consultar);

	}
	//AGREGAR
	else if(option == 2){
		std::vector<std::string> vector_temporal;
		std::string nuevo_jugador;
		int nuevo_puntaje;
		int nuevo_nivel;

		cout<<"Nombre de nuevo jugador: "<<endl;
		cin >> nuevo_jugador;
		cout<<"Puntaje de nuevo jugador: "<<endl;
		cin >> nuevo_puntaje;
		cout<<"Nivel de nuevo jugador: "<<endl;
		cin >> nuevo_nivel;
		//Agregamos a la lista
		lista_jugadores.insertion(nuevo_jugador,nuevo_puntaje,nuevo_nivel);

		//Agregamos a la matriz
		vector_temporal.push_back(nuevo_jugador);
		vector_temporal.push_back(to_string(nuevo_puntaje));
		vector_temporal.push_back(to_string(nuevo_nivel));
		jugadores.push_back(vector_temporal); 

		cout<<"Agregando jugador: " << nuevo_jugador<<endl;
		//debug 
		cout<< "Nuevo numero de jugadores: " << lista_jugadores.get_size() << endl;

	}

	//MODIFICAR
	else if(option == 3){
		std::string jugador_a_modificar;
		int nuevo_p;
		int nuevo_n;
		cout<<"¿Que jugador vamos a modificar?"<<endl;
		cin >> jugador_a_modificar;
		cout<<"¿Inserta el nuevo puntaje de " << jugador_a_modificar <<endl;
		cin >> nuevo_p;
		cout<<"¿Inserta el nuevo nivel de " << jugador_a_modificar <<endl;
		cin >> nuevo_n;

		lista_jugadores.update(jugador_a_modificar,nuevo_p,nuevo_n);

		//Modificar Matriz
		for(int i = 0; i < jugadores.size();i++){
			if(jugadores[i][0] == jugador_a_modificar){
				//Si lo encontramos lo modificamos
				jugadores[i][1] = to_string(nuevo_p);
				jugadores[i][2] = to_string(nuevo_n);
				break;
			}
		}
		cout << "Jugador: " << jugador_a_modificar << " modificado" << endl;
	}

	//ELMINAR
	else if(option == 4){
		std::string jugador_a_eliminar;
		cout<<"¿Que jugador vamos a eliminar"<<endl;
		cin >> jugador_a_eliminar;

		lista_jugadores.deleteAt(jugador_a_eliminar);
		//debug 
		

		//eliminar de Matriz 
		for(int i = 0; i < jugadores.size();i++){
			if(jugadores[i][0] == jugador_a_eliminar){
				//Si lo encontramos lo eliminamos
				jugadores.erase(jugadores.begin()+i);
				break;
			}
		}
		cout << "Jugador: " << jugador_a_eliminar << " eliminado" << endl;
		cout<< "Nuevo size: " << lista_jugadores.get_size() << endl;
	}


	//Ordenar y Visualizar Tabla 
	else if(option == 5){
		while(true){
			menu_sort();
		//sorteamos
		int option_sort; //Opcion de menu de sort
		cin >> option_sort;
			if(option_sort < jugadores[0].size() && option > 0){
				std::string label = jugadores[0][option_sort];
				cout << "Sorting by " << label << "....." << endl;
			QuickSort(jugadores,1,jugadores.size()-1,option_sort);
			imprimir_matriz(jugadores);
			}

			else if(option_sort == 3)
			{
				break;
			}


			else
			{
				cout << "Opción no valida" << endl;
				continue;
			}

			}
	}

	//SALIR
	else if(option == 6){
		break;
	}

	else{
		cout << "Selección no valida"<< endl;
		continue;
	}
	
}
	/////Fin del programa
	cout << "Saliendo... " << endl;
	return 0;
}

/*
0 = nombre 
1 = puntaje
2 = nivel
*/

