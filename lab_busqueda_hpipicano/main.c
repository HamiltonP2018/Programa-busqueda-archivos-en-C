#include <stdio.h>
#include <stdlib.h>
#include "buscar.h"


/*
    argc = 3
    argv[1] = diretcorio
    argv[2] = patron
*/

int main(int argc, char * argv[]){


    int total = 0;

    if(argc != 3){
       
        fprintf(stderr,"Se necesita: %s Directorio - Patron", argv[0]);
        exit(EXIT_FAILURE);

    } else if(!es_directorio(argv[1])){
        
        fprintf(stderr,"\nDirectorio invalido");
        exit(EXIT_FAILURE);

    }


    total = buscar(argv[1], argv[2]);

    if (total > 0)
    {
        printf("\nSe encontraron %d", total);
        printf("\n");
    }
    


    exit(EXIT_SUCCESS);
}



