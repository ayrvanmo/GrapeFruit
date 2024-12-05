/**
 * @file utilities.c
 * @author Pendiente
 * @brief Definiciones de funciones de miscelania
*/

#include "utilities.h"

/**
 * @brief Funcion para obtener los parametros de la terminal. Devuelve el directorio en donde se ejecutara el programa
 * @param argc Cantidad de argumentos
 * @param argv Argumentos
 * @return char* Directorio en donde se ejecutara el programa
 * @note Devuelve NULL si no se quiere/puede ejecutar el programa según lo dado
 */
char* get_terminal_parameters(int argc, char **argv){
    int opt; // Variable para el manejo de opciones
	int opt_index = 0;

    // estructura para las opciones
	static struct option long_options[] = {
        {"help", no_argument, 0, 'h'},
        {"directory", required_argument, 0, 'd'},
        {0, 0, 0, 0}
    };

    while((opt = getopt_long(argc, argv, ":hd:", long_options, &opt_index)) != -1){

		switch(opt){
			case 'h':
				printf("NOMBRE -d <directorio>      Ejecuta el programa sobre un directorio\n");
				return NULL;
                break;
			case 'd':
                return optarg;
                break;
			case ':':
                printf("Uso: 'NOMBRE -d <directorio>'\n'NOMBRE -h' para mostrar ayuda\n");
				return NULL;
				break;
			default:
				printf("Uso: 'NOMBRE -d <directorio>'\n'NOMBRE -h' para mostrar ayuda\n");
                return NULL;
				break;
		}
	}
    printf("Uso: 'NOMBRE -d <directorio>'\n'fly -h' para mostrar ayuda\n");
    return NULL;
}

/**
 * @brief Funcion para comparar si un valor es mayor o igual a otro
 * @param a Primer valor
 * @param b Segundo valor
 * @return TRUE si @p a es mayor o igual a @p b, FALSE en caso contrario
*/
bool increasing(double a, double b){
    return a <= b;
}

/**
 * @brief Funcion para comparar si un valor es menor o igual a otro
 * @param a Primer valor
 * @param b Segundo valor
 * @return TRUE si @p a es menor o igual a @p b, FALSE en caso contrario
*/
bool decreasing(double a, double b){
    return a >= b;
}