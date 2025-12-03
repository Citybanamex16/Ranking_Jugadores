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
#include <filesystem> //librería para la gestion de archivos
#include <chrono> //Librería para referenciar la hora en tiempo de ejecución :)
#include "Proyecto_hash.h"

using namespace std;
namespace fs = std::filesystem;

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
             << setw(20) << "Nombre"   
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
	cout << " 6. Guardar Datos " << endl;
	cout << " 7. Salir de Programa " << endl;
}

void jugadores_totales(const std::vector<std::vector<std::string>>& matriz_jugadores, Hash_table<string,int>& myhash) {
    std::cout << "=== LISTA DE JUGADORES REGISTRADOS ===" << std::endl;
    //std::cout << "────────────────────────────────────" << std::endl;
    std::cout << "====================================" << std::endl;

    for (size_t i = 1; i < matriz_jugadores.size(); ++i) {
        if (!matriz_jugadores[i].empty()) {
            std::cout << "* " << matriz_jugadores[i][0] << std::endl;
        }
    }

    std::cout << "====================================" << std::endl;

    if(matriz_jugadores.size()-1 != (unsigned int) myhash.get_count()){
    	cout << "¡ALERTA! numero de jugadores no sincronizado entre matriz y hash table" << endl;
    	cout << "Size en matriz: " + to_string(matriz_jugadores.size()-1);
    	cout << "Size en Hash: " + to_string(myhash.get_count());
    }

    std::cout << "Total de jugadores: " << myhash.get_count() << std::endl;
}


//Funciones de carga y guardado de archivos
fs::path obtener_ruta_ejecutable() {
    return fs::current_path();  
}


fs::path buscar_csv(const fs::path& root ,const std::string& nombre){
	//Función que busca recursivamente el archivo
	
	std::cout << "Buscando CSV desde: " << root << "\n";
	std::error_code ec; //Objeto que ayuda a almacenar y gestionar codigos de errores 
	fs::recursive_directory_iterator it(root,fs::directory_options::skip_permission_denied);
	/* Lo que el objeto it hace es:
	Por cada archivo o carpeta dentro de root, incluyendo subcarpetas, checa lo siguiente */
	//El segundo paremtro del iterador evita buscar en carpetas protegidas -> evitando asi crasheos

	fs::recursive_directory_iterator end;

	while(it != end){
		if(ec){
			//Hubo un error, lo saltamos y seguimos buscando
			ec.clear();
			it++;
			continue;
		}

		const auto& entry = *it;

		if(entry.is_regular_file(ec)){
			if(entry.path().filename() == nombre){
				return entry.path();
			}
		}
		it.increment(ec); //Avanza sin excepciones
	}

	return ""; // no encontrado
}


void escribir_csv(const std::string& ruta,const std::vector<std::vector<std::string>>& matriz) {

    std::ofstream archivo(ruta);

    if (!archivo.is_open()) {
        std::cerr << "Error: No se pudo abrir archivo para escritura.\n";
        return;
    }

    for (const auto& fila : matriz) {
    	//For loop tipo range-based que por cada fila en la matriz hace lo siguiente
        bool primero = true; //Es el primer elemento del jugador -> No empezar con coma
        for (const auto& elemento : fila) {
        	//For loop que por cada elemento del jugador hace lo siguiente

            if (!primero) archivo << ","; //¿No es el primer? agregamos coma
            archivo << elemento; //Escribimos el elemento en el archivo

            primero = false;
        }
        archivo << "\n"; //Salto que marca el fin de un jugador -> empezamos con uno nuevo
    }

    archivo.close();
}


bool guardar_seguro(const std::string& ruta_csv,
                    const std::vector<std::vector<std::string>>& matriz) {

    std::string ruta_tmp = ruta_csv + ".tmp"; //Hacemos un archivo temporar.

    escribir_csv(ruta_tmp, matriz); //Llamamos a la escritura del archivo

    // Renombrar (sobrescribir)
    std::error_code ec; //Objeto de gestion de errores 
    std::filesystem::rename(ruta_tmp, ruta_csv, ec);

    if (ec) {
        std::cerr << "Error renombrando archivo: " << ec.message() << "\n";
        return false;
    }

    return true;
}

string obtenerHoraActual(){
	// Obtener la hora actual del sistema
	auto now = std::chrono::system_clock::now();
	//El identificador auto dice al compilador que deduzca el tipo de variable a partir de un tipo inicial
	// Convertir a time_t para usar funciones de ctime :)
	std::time_t t = std::chrono::system_clock::to_time_t(now);

	std::tm tm = {};
	//Portabilidad Windows/Mac
	#ifdef _WIN32 //Si estamos en windows
    localtime_s(&tm, &t);
	#else //Nos encontramos en otro entorno
    localtime_r(&t, &tm);
    //Estas son instrucciones del procesador (Preprocesado). 
	#endif


	// Formatear la hora y fecha en una cadena
    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S"); // Formato personalizable
    return oss.str();


}


unsigned int function_hash(const string s){
	//Funcion del profe
	unsigned int acum = 0;
	for (size_t i = 0; i < s.size(); i++) {
		acum += (int) s[i];
	}
	return acum;
}

string limpiar_nombres(const string nombre){
	string nombre_limpio = nombre;

	for (char &c : nombre_limpio) {
        c = std::tolower(static_cast<unsigned char>(c));
        /*Static_cast lo que hace es conversióndel valor de una expresión a un tipo de dato  en este caso
        un unsigned char. Esto hace que el tamaño en bits del string sea consistente lo cual puede 
        mejorar la portabilidad del programa en general. En especial en esta función que se llama constantemente
        El programa sin importar si es Windows/Linux interpeta estos datos de manera uniforme.*/

        //Eliminar ls espaciooooos 
        nombre_limpio.erase(std::remove(nombre_limpio.begin(), nombre_limpio.end(), ' '),nombre_limpio.end());

    }

	return nombre_limpio;
}


int main(){
	/* Recibimos un archivo .CSV y lo leemos a traves de una 
	instancia(objeto) de ifstream pasando la ruta del archivo al constructor */
	fs::path root = fs::current_path();
	fs::path ruta_csv = buscar_csv(root,"Ranking_CSV.csv");
	std::ifstream archivo;

	if(ruta_csv != "" ){
		//Se encontro :)
		archivo.open(ruta_csv);
		std::cout << "Archivo encontrado en: " << ruta_csv << "\n";
	}

	else{
		std::cout << "CSV no encontrado en la carpeta.\n";
	}

	
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
	//CREACION DE ESTRUCTURAS DE DATOS
	std::vector<vector<std::string>> jugadores; //MATRIZ principal para el Sorting
	cout << "Creando Hash" << endl;
	Hash_table <string,int> myhash(31,string("no_player"),function_hash);//Aqui creamos nuestro Hash de Jugadores
	cout << "Hash Creado correctamente" << endl;
	string debug_hash = myhash.toString();
	//cout << debug_hash << endl;

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

		if(!campos.empty()){
        campos[0] = limpiar_nombres(campos[0]);
    }


		jugadores.push_back(campos); //Vector de jugador se almacena con los demas en Matriz

		//Nos saltamos los titulos
		if(i != 0){

		// 0 -> nombre (key) 1 -> valor1 2 -> valor2
		myhash.put(campos[0],std::stoi(campos[1]),std::stoi(campos[2])); //Insertamos datos en Hash_Table
		}
		i++;
	}
	archivo.close();
	//// FIN DE LECTURA 


////Inicio de programa/////
	//cout << "Debug Tabla Hash " << endl;
	//debug_hash = myhash.toString();
	//cout << debug_hash << endl;

	cout << "¡Bienvenido a la Tabla de Rankin de Jugadores!" << endl;

	while(true){  	//Loop de menu general.

	int option; //Opcion de Menu general
	jugadores_totales(jugadores, myhash);



	menu(); //Menu general
	cin >> option;

	//Evitamos errores de usuario -> string por accidente
    if(cin.fail()) {
        cout << "Entrada inválida. Por favor ingresa un número." << endl;
        cin.clear();              // Limpiar el estado de error
        cin.ignore(10000, '\n');  // Vaciar el buffer hasta el salto de línea
        continue;                 // Volver al inicio del loop
    }


	//CONSULTAR
	if(option == 1){
		if (myhash.get_count() > 0){
			std::string jugador_a_consultar;
		cout<< "¿Que jugador quieres consultar? " <<endl;
		getline(cin >> ws, jugador_a_consultar); //Getline para que si el usuario mete espacios no explote esto
		//cout << limpiar_nombres(jugador_a_consultar) << endl;
		jugador_a_consultar = limpiar_nombres(jugador_a_consultar);
		//Consulta en Hash Table
		myhash.get(jugador_a_consultar);
		}
		else{
			cout << "No hay jugadores que consultar " << endl;
		}
		
	}
	//AGREGAR
	else if(option == 2){
		if(!myhash.full()){
			//inputs
				std::vector<std::string> vector_temporal;
				std::string nuevo_jugador;
				int nuevo_puntaje;
				int nuevo_nivel;

				cout<<"Nombre de nuevo jugador: "<<endl;
				getline(cin >> ws , nuevo_jugador);
				nuevo_jugador = limpiar_nombres(nuevo_jugador);

				//Checar que esto sean INTS que luego la gente se equivoca


				cout<<"Puntaje de nuevo jugador (solo numeros) : "<<endl;
				cin >> nuevo_puntaje;

				cout<<"Nivel de nuevo jugador (solo numeros) : "<<endl;
				cin >> nuevo_nivel;


			if(myhash.put(nuevo_jugador,nuevo_puntaje,nuevo_nivel)){
				//Agregamos a la matriz
				vector_temporal.push_back(nuevo_jugador);
				vector_temporal.push_back(to_string(nuevo_puntaje));
				vector_temporal.push_back(to_string(nuevo_nivel));
				jugadores.push_back(vector_temporal); 

				cout<<"Agregando jugador: " << nuevo_jugador<<endl;
				//debug 
				cout<< "Nuevo numero de jugadores: " << myhash.get_count() << endl;

			}
			else{
				cout << "Error en la inserción en Hash Table. Abort para evitar desincronización. Trata eliminando un jugador " << endl;
			}
		}

	else{
		cout << "Limite de jugadores, eliminar jugadores para poder agegar mas " << endl;
	}
		

	}

	//MODIFICAR
	else if(option == 3){
		if(jugadores.size() > 0) {

		std::string jugador_a_modificar;
		int nuevo_p;
		int nuevo_n;
		bool modificacion;
		cout<<"¿Que jugador vamos a modificar?"<<endl;
		getline(cin >> ws, jugador_a_modificar);
		jugador_a_modificar = limpiar_nombres(jugador_a_modificar);
		myhash.get(jugador_a_modificar);
		cout<<"Inserta el nuevo puntaje de " << jugador_a_modificar << " (Solo numeros) " <<endl;
		cin >> nuevo_p;
		cout<<"Inserta el nuevo nivel de " << jugador_a_modificar << " (Solo numeros) " <<endl;
		cin >> nuevo_n;

		modificacion = myhash.modificar(jugador_a_modificar,nuevo_p,nuevo_n);

		//Modificar Matriz
		for(size_t i = 0; i < jugadores.size();i++){
			if(jugadores[i][0] == jugador_a_modificar){
				//Si lo encontramos lo modificamos
				jugadores[i][1] = to_string(nuevo_p);
				jugadores[i][2] = to_string(nuevo_n);
				break;
			}
		}

		if(modificacion){
			cout << "Jugador: " << jugador_a_modificar << " modificado" << endl;

		}
		else{
			cout << "Error en modificación " << endl;
		}
		

		}

		else{
			cout << "Sin jugadores que modificar " << endl;
		}
		
	}

	//ELMINAR
	else if(option == 4){
		if(jugadores.size() > 0){
			std::string jugador_a_eliminar;
		cout<<"¿Que jugador vamos a eliminar"<<endl;
		getline(cin >> ws, jugador_a_eliminar);
		jugador_a_eliminar = limpiar_nombres(jugador_a_eliminar);
		myhash.eliminar(jugador_a_eliminar);

		//eliminar de Matriz 
		for(size_t i = 0; i < jugadores.size();i++){
			if(jugadores[i][0] == jugador_a_eliminar){
				//Si lo encontramos lo eliminamos
				jugadores.erase(jugadores.begin()+i);
				cout << "Jugador eliminado en Matriz " << endl;
				break;
			}
		}
		cout << "Jugador: " << jugador_a_eliminar << " eliminado" << endl;
		cout<< "Nuevo size: " << myhash.get_count() << endl;

		}
		else{
			cout << "Sin jugadores que eliminar" << endl;
		}
		
	}


	//Ordenar y Visualizar Tabla 
	else if(option == 5 and jugadores.size() > 0){
		while(true){
			menu_sort();
		//sorteamos
		size_t option_sort; //Opcion de menu de sort
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

	//Guardar datos
	else if(option == 6){
		if(guardar_seguro(ruta_csv.string(),jugadores) == true){
			cout << "Archivo Guardado el " + obtenerHoraActual() << endl;
		}
	}

	//SALIR
	else if(option == 7){
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

