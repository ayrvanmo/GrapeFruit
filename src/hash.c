/**
 * @file hash.c
 * @author Pendiente
 * @brief Funciones de hashing
*/
#include "hash.h"

/**
 * @brief Función que calcula el hash de un string usando el algoritmo de Jenkins
 * @param key Palabra a calcular el hash
 * @return Devuelve el hash
 */
unsigned int jenkins_hash(char* key)
{
   unsigned int hash = 0;

   while (*key){
      hash += (unsigned char)(*key);
      hash += (hash << 10);
      hash ^= (hash >> 6);

      key++;
   }

   hash += (hash << 3);
   hash ^= (hash >> 11);
   hash += (hash << 15);

   return hash;
}
