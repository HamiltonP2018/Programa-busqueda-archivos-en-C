#ifndef BUSCAR_H
#define BUSCAR_H

/**
 * @brief verifica si la ruta dada es un directorio valido 
 * @param ruta Ruta a verficar
 * @return 1 si la ruta es un directorio valido , 0 en casi contrario
 * */
int es_directorio(char *ruta);

/**
 * @brief Busca e imprime recursivamente archivos/directorres i cuyo nombre contenga el patron
 * @param directorio Directorio base de busqueda
 * @param  patron patron de busqueda
 * @return cantidad de directores con el patron por parametro
 * */

int buscar(char * directorio, char * patron);

#endif