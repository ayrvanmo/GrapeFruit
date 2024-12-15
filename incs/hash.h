/**
 * @file hash.h
 * @author Pendiente
 * @brief Cabeceras para funciones de hash.c
*/
#ifndef HASH_H
#define HASH_H

#include <stdio.h>
#include <stdlib.h>

#include "errors.h"

unsigned int jenkins_hash(char* key);

unsigned int hashFile (char *filename);

#endif