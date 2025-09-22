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

void menu(){
	cout << " ¿Como quieres ordenar el ranking ? " << endl;
	cout << " 1. Por Puntaje " << endl;
	cout << " 2. Por nivel " << endl;
	cout << " 3. Salir " << endl; 

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
		std::cout << "Ingresa la ruta del archivo CSV: ";
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
	std::vector<vector<std::string>> jugadores;
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
		jugadores.push_back(campos); //Vector de jugador se almacena con los demas

	}
	archivo.close();

	cout << "Bienvendio a la Tabla de Rankin de Jugadores" << endl;

	while(true)
	{
	menu();
	//sorteamos
	int option;
	cin >> option;
		if(option < jugadores[0].size() && option > 0){
			std::string label = jugadores[0][option];
			cout << "Sorting by " << label << "....." << endl;
		QuickSort(jugadores,1,jugadores.size()-1,option);
		imprimir_matriz(jugadores);
		}

		else if( option == 3)
		{
			break;
		}


		else
		{
			cout << "Opción no valida" << endl;
			continue;
		}
	
	}
	cout << "Saliendo... " << endl;
	return 0;
}

/*
0 = nombre 
1 = puntaje
2 = nivel
*/

