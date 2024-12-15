# Documentación general del Proyecto

## Simulacion de red social

En este proyecto se desarrollara una "red social" simplificada. Para lograr esto se utilizaran diversas **estructuras de datos**, con el fin de lograr un balance entre eficiencia de espacio y tiempo.

Los principales aspectos de este proyecto son:
- Manejo correcto y eficiente de datos, atraves de EDD adecuadas.
- Manejo correcto y controlado de archivos.
- Manejo de datos a "tiempo real".
- Evolucion de un grafo a traves del tiempo.
- Manejo destacable de memoria.


## Ejecucion Del Programa
Para ejecutar este programa se debe realizar el comando `make folders`, despues de esto se utiliza `make database` para mover los recursos necesarios para la correcta ejecucion del programa, acto siguiente se debe ubicar en la carpeta `build` y desde ahi ejecutar la linea de codigo `./grape.out -h`, lo que le dara acceso al modo de uso del programa.
Existen limitaciones como falta de condicionales en algunos casos (como por ejemplo en el generador de usuarios al anhadir mas de un string), pero fuera de ese caso el programa funciona con normalidad.

Para limpiar los archivos generados por el programa puede utilizar `make clean`, el cual removera la totalidad de los recursos generados por el programa.

*⚠️ Advertencia*
El programa cuenta con una creacion de usuarios sin "límite" dentro de este (esto no es de mucha importancia debido a que está hecho de tal manera que la creación de usuarios decaiga asintóticamente a 1 usuario por tick). Por lo que se recomienda discrecion a la hora de utilizar el programa por grandes periodos de tiempo.


## Documentacion
Doxygen se encuentra habilitado para este programa, sin embargo por problemas tecnicos y de tiempo no fue posible implementar documentacion apropiada para todo el codigo.

## Gestion Ramas
Las gestion de ramas en este proyecto sera la siguiente:
- `master`: Rama principal en donde unicamente estaran las versiones principales y funcionales del programa.
- `testing`: Como su nombre lo indica, alojara las versiones de prueba del programa, aqui se desarrrollara la gran mayoria del programa.
- `docs`: En docs se alojara el desarrollo de la documentacion, especificamente el informe de desarrollo.


## Autores
Manuel González, Pablo Gómez, Ayrton Morrison, Emmanuel Velásquez
