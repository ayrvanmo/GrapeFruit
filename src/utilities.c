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
    printf("Uso: 'NOMBRE -d <directorio>'\n'NOMBRE -h' para mostrar ayuda\n");
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

bool coin_toss(double probability)
{
    double random = (double)rand()/(double)RAND_MAX;
    if(random <= probability){
        //printf("Seguira al usuario! (1)\n");
        return 1;
    }
    else{
        //printf("No seguira al usuario! (0)\n");
        return 0;
    }
}

int profiles_per_tick(int userNumber)
{
    float base = (userNumber + 180)/userNumber;
    printf("Esta es la base %f\n", base);
    int maxProfiles = floor(pow(base, 2.0/3.0));
    printf("Max profiles: %d\n", maxProfiles);
    int profileNumber = rand() % maxProfiles + 1;
    printf("Usuarios creados en este tick: %d\n", profileNumber);
    return profileNumber;
}