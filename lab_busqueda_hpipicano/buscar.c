#include "buscar.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include "buscar.h"

//Retorna 1 si la ruta dada es un directorio, 0 en caso contrario
int es_directorio(char *ruta){

    struct stat s;
    //Usar el servicio stat para obtener la información de la ruta dada
    int resultado = stat(ruta,&s);

    if(resultado > 0){
        perror("stat"); //C no tiene tipo booleano, 0 = falso
        return 0;
    }



    //Usar el macro S_ISDIR sobre el atributo st_mode de la estructura
    //para verificar si es un directorio
    if(S_ISDIR(s.st_mode)){
        return 1; //C no tiene tipo booleano, 1 = verdadero
    }else{
        return 0;
    }
}



//Busca recursivamente archivos/directorios cuyo nombre contenga patron
//Retorna el total de coincidencias
int buscar(char *directorio, char *patron){
    int total = 0;

    //Abrir el directorio con opendir

    DIR *d = opendir(directorio);

    //Validar el resultado de la llamada al servicio opendir
    //Tenga en cuenta! la comparación de igualdad en C es con ==

    if(d == NULL){
        perror("opendir");
        return total;
    }

    //Leer el directorio con el servicio readdir

    struct dirent *ent;
    
    while((ent = readdir(d)) != NULL){
        
        //Construir la ruta completa directorio/ent->d_name

        //char ruta[] = directorio + "/" + ent->d_name;

        //Tenga en cuenta! En C no se puede concatenar las cadenas de
        //esta forma
        //Se debe reservar memoria suficiente con malloc, usar strcpy
        //para copiar y strcat para concatenar.
        //La cadena de destino (ruta) debe tener suficiente espacio
        //para almacenar directorio, "/" y ent->d_name.
        //Toda cadena válida en C termina en nulo, por lo tanto se
        //debe reservar 1 byte más de memoria
        //Verificar si la entrada (archivo o directorio) contiene
        //el patrón de búsqueda

        char * ruta;

        ruta = (char *)malloc(strlen(directorio)+strlen(ent->d_name)+2);

        strcpy(ruta, directorio);
        strcat(ruta, "/");
        strcat(ruta, ent->d_name);

        if (strstr(ent->d_name, patron) != NULL)
        {
            //imprimir la ruta completa
            printf(ruta);
            printf("\n");
            total = total + 1;
        }
        
        //Si la entrada es un directorio, se debe buscar
        //recursivamente!
        //Precaucion: descartar los directorios "." (actual)
        //y ".." (anterior) para prevenir que la funcion nunca termine
        //Tenga en cuenta! En C, las cadenas se comparan como strcmp

        if (es_directorio(ruta) && strcmp(ent->d_name,".") != 0 && strcmp(ent->d_name,"..")!=0)
        {
            //Buscar recursivamente dentro del subdirectorio
            total = total + buscar(ruta, patron);
        }
        

    }

    //Cerrar el directorio
    closedir(d);
    return total;
}
    