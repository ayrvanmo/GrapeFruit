# Documentación general del Proyecto

## Simulación de red social

En este proyecto se desarrollará una "red social" simplificada. Para lograr esto se utilizarán diversas **estructuras de datos**, con el fin de lograr un balance entre eficiencia de espacio y tiempo.

Los principales aspectos de este proyecto son:
- Manejo correcto y eficiente de datos, a través de EDD adecuadas.
- Manejo correcto y controlado de archivos.
- Manejo de datos a "tiempo real".
- Evolución de un grafo a través del tiempo.
- Manejo destacable de memoria.


## Ejecución del Programa
Para ejecutar este programa se debe realizar el comando `make folders`, después de esto se utiliza `make database` y `make` para mover los recursos necesarios para la correcta ejecución del programa, acto siguiente se debe ubicar en la carpeta `build` y desde ahí ejecutar la línea de código `./grape.out -h`, lo que le dará acceso al modo de uso del programa.
Existen limitaciones como falta de condicionales en algunos casos (como por ejemplo en el generador de usuarios al añadir más de un string), pero fuera de ese caso el programa funciona con normalidad.

Para limpiar los archivos generados por el programa puede utilizar `make clean`, el cual removerá la totalidad de los recursos generados por el programa.

*⚠️ Advertencia 1*
>El programa cuenta con una creación de usuarios, este es "sin límite" (esto no es de mucha importancia debido a que está hecho de tal manera que la creación de usuarios decaiga asintóticamente a 1 usuario por tick). Por lo que se recomienda discreción a la hora de utilizar el programa por grandes periodos de tiempo.
*⚠️ Advertencia 2*
>Nótese que el programa utiliza las bibliotecas `sys/types.h` y `sys/stat.h` para la creación de directorios. Por lo que solamente se puede utilizar correctamente en sistemas UNIX. 

## Documentación
Doxygen se encuentra habilitado para este programa, sin embargo por problemas técnicos y de tiempo no fue posible implementar documentación apropiada para todo el código.

## Gestión de Ramas
La gestión de ramas en este proyecto será la siguiente:
- `master`: Rama principal en donde únicamente estarán las versiones principales y funcionales del programa.
- `testing`: Rama que aloja las versiones de prueba del programa, aquí se desarrollará la gran mayoría del programa.
- `docs`: Rama donde se alojará el desarrollo de la documentación, específicamente el informe de desarrollo.

## Manejo de errores
Dentro del archivo [errors.c](src/errors.c) se encuentra la función `print_error` que se encarga de manejar los errores que puedan ocurrir en el programa. Los códigos de error que se manejan son los siguientes:
| Código de error | Descripción |
| --- | --- |
| 100 | No se pudo leer el archivo |
| 200 | No hay memoria disponible |
| 201 | No se pudo acceder al sistema |
| 202 | Cantidad inválida, la cantidad ingresada debe estar en los límites |
| 203 | Acceso a puntero nulo |
| 204 | No se pudo leer la palabra |
| 205 | No se pudo crear el usuario |
| 300 | Lista vacía |
| 301 | Nodo no encontrado |
| 302 | Tabla hash no existe |
| 303 | No se encontró el enlace |
| 304 | No se encontró el archivo |
| 305 | No se pudo abrir el directorio |
| 306 | Usuario no encontrado |
| 307 | Nombre no válido |
| 308 | Descripción no válida o muy larga |
| 309 | Edad no válida |
Donde:
- 100 - 199 corresponden a errores comunes
- 200 - 299 corresponden a errores fatales
- 300 - 399 corresponden a advertencias



## Autores
- Ayrton Morrison:      Líder de proyecto y programador.
- Manuel González:      Documentador.
- Pablo Gómez:          Programador.
- Emmanuel Velásquez:   Documentador.