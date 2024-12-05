/**
 * @file errors.c
 * @author Pendiente 
 * @brief Funciones para manejo de errores
*/
#include "errors.h"

/**
 * @brief Funcion para imprimir un error
 * @param num Codigo de error
 * @param target Algun parametro que puede ser necesario para el error
 * @param obs Algun texto que puede acompañar el error
*/
void print_error(int num, char* target, char* obs) {
    if(num>=100 && num<200){
        printf(ANSI_COLOR_RED "Error %d: " ANSI_COLOR_RESET, num);
    }
    else
    if(num>=200 && num<300){
        printf(ANSI_COLOR_RED "Fatal Error %d: " ANSI_COLOR_RESET, num);
    }
    else if(num>=300 && num<400){
        printf(ANSI_COLOR_YELLOW "Warning %d: " ANSI_COLOR_RESET, num);
    }
    switch(num) {
        case 100:
            printf("No se pudo leer el archivo %s\n", target);
            break;
        case 200:
            printf("No hay memoria disponible\n");
            exit(-1);
            break;
        case 201:
            printf("No se pudo acceder al sistema\n");
            exit(-1);
            break;
        case 202:
            printf("Cantidad invalida, la cantidad ingresada debe ser mayor a 0\n");
            exit(-1);
            break;
        case 203:
            printf("Acceso a puntero nulo\n");
            break;
        case 300:
            printf("Lista vacia\n");
            break;
        case 301:
            printf("Nodo no encontrado\n");
            break;
        case 302:
            printf("Tabla hash no existe\n");
            break;
        case 303:
            printf("No se encontro el enlace\n");
            break;
        case 304:
            printf("No se encontro el archivo %s\n", target);
            break;
        case 305:
            printf("No se pudo abrir el directorio %s\n", target);
            break;
        default:
            printf("Codigo de error desconocido\n");
    }
    if (obs != NULL) {
        printf("%s\n", obs);
    }
}