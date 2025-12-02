# Ranking de Jugadores - Consola C++

Este proyecto implementa un **ranking de jugadores** basado en un archivo CSV con sus nombres, puntajes y niveles. Está pensado para ejecutarse directamente en la **terminal** sin interfaz gráfica. Además, aplica **algoritmos de ordenamiento** como QuickSort organizar la tabla en base a diferentes parametros como el **Puntaje** o el **Nivel** del jugador.

---

## Funcionalidad

- Lee un archivo CSV con la información de los jugadores.
- Permite ordenar el ranking según:
  1. Puntaje
  2. Nivel
- Muestra la tabla de manera organizada con posiciones, nombres, puntajes y categorías.

---

## Formato del CSV

El archivo CSV debe contener los jugadores con los campos separados por comas, por ejemplo:
Juan,1500,3
Maria,2000,5
Luis,1800,1

## Ejecución

1. Coloca el archivo CSV en la misma carpeta que el ejecutable **opcionalmente** con nombre `Ranking_CSV.csv`.  
2. Si el programa **no encuentra el CSV en la ruta relativa**, pedirá al usuario que ingrese la **ruta completa** del archivo.
3. Posteriormente, podrás interactuar con el programa para ordenar y visualizar el ranking.


# Instrucciones de compilacion.

## Requisitos
- C++17 o superior
- GCC 8+, Clang 7+, MSVC 2019+

## Compilación

### Windows (MSVC)
```cmd
cl /EHsc /std:c++17 RankingJugadores.cpp
```

### Linux/Mac (GCC)
```bash
g++ -std=c++17 RankingJugadores.cpp -o RankingJugadores
```

### Linux/Mac (GCC < 9.0)
```bash
g++ -std=c++17 RankingJugadores.cpp -lstdc++fs -o RankingJugadores
```

### Con CMake (Recomendado)
```bash
mkdir build
cd build
cmake ..
make
```
