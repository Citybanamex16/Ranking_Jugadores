#Ranking de Jugadores - Consola C++

##Author
**Carlos Delgado Contreras**  
Fecha: 28 de noviembre de 2025

-------------------
Ranking de Jugadores es un programa en consola de ordenamiento y estructura de jugadores de un videojuego. Basado en un archivo CSV, Ranking de jugadores ordena y almacena los puntajes y niveles de los jugadores de forma eficaz. Pensado para ejecutarse directamente en la terminal sin interfaz gráfica, utilizamos el algoritmo de ordenamiento QuickSort para ordenar de forma descendente a los jugadores tanto por nivel como por puntaje. A través de una Hashtable, el usuario puede consultar, agregar, modificar o eliminar jugadores al Ranking. De esta forma, el programa simula un sistema de Ranking real de un videojuego. 

-------------------

##Funcionalidad e Instructivo
* Lee un archivo CSV con la información de los jugadores en formato nombre, puntaje, categorías.
* Cuenta con búsqueda automática del archivo CSV entre tus carpetas. En caso de no poder encontrarla, permite al usuario insertar la ruta del CSV de manera manual. 
* La funcion “Consultar jugador” devuelve la ficha del jugador a traves del hashtable. Esta funcion acepta mayusculas y minusculas pues “limpia” el input pudiendo procesar typos de formato asi como espacios accidentales. 
* La funcion “Agregar jugador” permite crear el perfil de un nuevo jugador agregando el nombre, puntaje (solo números) y nivel (solo numeros) al hashtable. La función procesa los espacios eliminando los. Además convierte el nombre a minusculas reduciendo la probabilidad de errores.
* La funcion “Modificar jugador” permite cambiar los valores de nivel y puntaje del jugador en el hashtable. Es importante solo ingresar numeros sin espacios en los campos. 
* La función “Eliminar Jugador” permite eliminar un jugador y vaciar una casilla del Hashtable. 
* La función “Visualizar Ranking de jugadores” abre un menu donde se interactua con el algoritmo de ordenamiento QuickSort. En este menu se puede ordenar el Ranking tanto por nivel como por puntaje
* La función “Guardar Datos” escribe y guarda los ultimos cambios en los datos en el archivo CSV. ¡Cuidado! esta funcion escribe directamente en el archivo CSV sin opcion de regreso. Utilizarla con precaución

###Resolución de bugs

#### El programa no encuentra el CSV
1. Verifica que `Ranking_CSV.csv` esté en el directorio del ejecutable
2. Usa la opción manual para ingresar la ruta completa
3. Revisa permisos de lectura del archivo

#### Error al agregar jugador
- **"Límite lleno"**: La tabla está al 70% de capacidad
  - Solución: Elimina jugadores o aumenta el tamaño

#### El ordenamiento no funciona
- Verifica que haya jugadores en el sistema
- Asegúrate de que los puntajes/niveles sean numéricos
- Revisa el formato del CSV original

-------------------

##Lectura y Guardado de Datos
Utilizamos archivos CSV para la lectura y escritura de datos de la tabla de jugadores.El archivo CSV debe contener los jugadores con los campos separados por comas, por ejemplo: Juan,1500,3 Maria,2000,5 Luis,1800,1. Implementamos un sistema de búsqueda con base en la biblioteca <filesystem> de c + + para una obtención del archivo CSV desde el sistema de archivos del usuario. Este sistema navega y gestiona rutas para encontrar el archivo CSV correctamente de entre los archivos del usuario. 

Para guardar los datos del usuario, generamos una copia temporal del csv original durante el tiempo de ejecución del programa. Al ejecutar la función de guardado lo renombramos como el archivo principal sobreescribiendo los últimos cambios y guardando las acciones del usuario en el CSV. Utilizamos las siguientes librerías para lograr esto:
- <fstream> para abrir archivos en modo escritura 
- <sstream> para formatear strings 
- <iomanip> para formatear numeros

-------------------

##Selección de Estructura no lineal
La clave central detrás de un sistema de Ranking de jugadores es el enlace Id-Datos. Se necesitaba de una estructura que conectará de manera central un identificador con una serie de datos de manera rápida y eficiente. Consultas, modificaciones, eliminaciones, etc se hacen a través de este enlace. Las Hashtable son, por excelencia, las mejores y más rápidas estructuras de datos conexión id-dato. Su velocidad de Consulta, inserción ,eliminación en el caso promedio son de O(1). Una rapidez que hace de este programa escalable hasta con miles de jugadores. En el peor de los casos Hashtable llega a tener una complejidad temporal lineal O(n) en la inserción, consulta y eliminación. Por otro lado, los HashTable hacen de este ranking de jugadores uno dinámico debido a su escalabilidad en la conexión id-dato. Los datos asociados a una llave pueden ser muchos, variados y fácilmente modificados. Pudiendo climatizar este sistema a cualquier juego con diferentes mecánicas y valores. 

La Hashtable tiene puntos negativos en contra. La eficacia de la Inserción y las colisiones depende directamente del tamaño de la estructura. Si el tamaño no es un número primo, se tiene alta probabilidad de un error directo en la inserción. No es una complejidad temporal, es un error de inserción directo. Existen varias estrategias para evitar esto como limitar el espacio al 70% del Hashtable (Aplicado en este programa) pero limita la escalabilidad del programa. Las estrategias que hacen que la Hashtable sea dinámica como el “ReHashing” son generalmente más complejas y requieren de más estructura. Una consideración a tomar en cuenta. 

####Resumen
##### Ventajas
- **Complejidad O(1)** en operaciones promedio
  - Búsqueda: O(1)
  - Inserción: O(1)
  - Eliminación: O(1)
- **Escalabilidad**: Maneja miles de jugadores eficientemente
- **Flexibilidad**: Fácil extensión de atributos por jugador

##### Implementación
- **Resolución de colisiones**: cuadrático
- **Función hash**: Suma de valores ASCII
- **Factor de carga**: Limitado al 70% para eficiencia
- **Tamaño**: Número primo para mejor distribución

##### Consideraciones
- Peor caso: O(n) si hay muchas colisiones
- Requiere tamaño primo para evitar errores de inserción
- El factor de carga del 70% limita la capacidad total


-------------------

##Selección de Algoritmo de Ordenamiento.
QuickSort es de los algoritmos de ordenamiento de propósito general más rápidos con una complejidad de O(n log n). Esto permite ordenar grandes conjuntos de jugadores de manera rápida y eficaz. Una sinergia efectiva con el Hashtable frente a grandes volúmenes de jugadores. La complejidad espacial de Quicksort de O(log n) abona a escalar este programa a Rankings más complejos. Rankings con más datos por jugador. Al ser “in-place” y no generar copias en el ordenamiento, dejamos memoria para poder almacenar más datos y cada vez más complejos de los jugadores. Permitiendo escalar el proyecto aún más. 
No obstante hay algo a considerar con el QuickSort: Su alta eficacia es directamente proporcional a si el pivote es el adecuado. El algoritmo de pivote de QuickSort afecta en gran medida su rendimiento pudiendo llevarlo hasta O(n^2) en el peor de los casos. Lo más desafiante es que una buena elección de pivote puede llegar a ser trivial. Hay situaciones en las que un pivote es bueno o malo. Una desventaja a tomar en cuenta. 

###Resumen
##### Ventajas
- **Complejidad promedio**: O(n log n)
- **Complejidad espacial**: O(log n)
- **In-place**: No requiere memoria adicional
- Eficiente para grandes volúmenes de datos

##### Implementación
- **Estrategia de pivote**: último elemento
- **Ordenamiento**: Descendente
- **Parámetros**: Configurable por puntaje o nivel

##### Consideraciones
- Peor caso: O(n²) con pivotes subóptimos
- Rendimiento dependiente de la elección del pivote


-------------------

##Límites del programa.
Ranking jugadores contiene una arquitectura sólida. El Hashtable junto con el algoritmo de ordenamiento QuickSort hacen posible la consulta, eliminación, modificación y ordenamiento de miles de jugadores en tiempos cercanos a O(1) y O(n log n) en ordenamiento en el mejor de los casos/implementaciones. Efectivo como un Ranking de jugadores globales. No obstante, la arquitectura tiene puntos críticos que hacen que su peor caso sea complejo. Una mala implementación de Hashtable junto con un mal pivote en el QuickSort genera Consultas, Inserciones y eliminaciones de O(n) y un ordenamiento de O(n^2). Un rendimiento lento con miles de jugadores. La eficacia del Ranking de Jugadores depende de una correcta adaptación de los algoritmos a la situación en la que están. Un buen pivote junto con un buen algoritmo de colisiones y Has functions hacen de Ranking de Jugadores una arquitectura rapida y eficaz con grandes volúmenes de jugadores

### Resumen Análisis de Complejidad

#### Complejidad Temporal

| Operación | Caso Promedio | Peor Caso |
|-----------|---------------|-----------|
| Consulta | O(1) | O(n) |
| Inserción | O(1) | O(n) |
| Eliminación | O(1) | O(n) |
| Modificación | O(1) | O(n) |
| Ordenamiento | O(n log n) | O(n²) |

#### Complejidad Espacial
- **Hash Table**: O(n) donde n = número de jugadores
- **QuickSort**: O(log n) en recursión
- **Matriz de ordenamiento**: O(n) adicional

##Instrucciones de compilación.
El programa principal (main) se encuentra en el archivo RankingJugadores.cpp el cual utiliza el header Proyecto_hash.h para funcionar. Seleccionar uno de los siguientes comandos dependiendo del sistema operativo en el que te encuentres. 

ARCHIVOS NECESARIOS:
-------------------
- RankingJugadores.cpp  (archivo principal)
- Proyecto_hash.h       (implementación de Hash Table)
- Ranking_CSV.csv       (datos de jugadores)


###Requisitos
----------
- C++17 o superior
- Compilador compatible: GCC 8+, Clang 7+, MSVC 2019+

##COMPILACIÓN:
-----------
Linux/Mac:
  g++ -std=c++17 RankingJugadores.cpp -o RankingJugadores

Windows (MinGW):
  g++ -std=c++17 RankingJugadores.cpp -o RankingJugadores.exe

Windows (Visual Studio):
  cl /EHsc /std:c++17 RankingJugadores.cpp

EJECUCIÓN:
---------
Linux/Mac:  ./RankingJugadores
Windows:    RankingJugadores.exe

NOTAS:
------
- El archivo CSV debe estar en el mismo directorio
- El programa creará un archivo .tmp temporal al guardar



