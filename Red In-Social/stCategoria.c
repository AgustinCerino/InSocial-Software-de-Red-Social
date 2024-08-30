/*#include <stdio.h>
#include <stdlib.h>
#include "stCategoria.h"
#include "stUsuario.h"

//NO LA VOY A USAR POR UN TEMA DE TIEMPO, PERO HUBIERA ESTADO BUENA LA IMPLEMENTACION TANTO PARA EL ADMIN COMO PARA EL USUARIO

stCategoria cargarCategoria (void){
    stCategoria aux;

    printf("Ingrese la categoria: ");
    scanf("%s", aux.nombreCategoria);
    fflush (stdin);
    printf("\n");
    printf("Ingrese el id de la categoria: ");
    scanf("%i", &aux.idCategoria);
    fflush (stdin);
    printf("\n");

    return aux;
}

int cargarCategoriasDesdeArchi (stCategoria* arregloCategorias, const char* nombreArchiCategorias){
    FILE* archiCategorias=fopen(nombreArchiCategorias, "rb");
    int elementosArchi=0;
    int validos=0;

    if(archiCategorias){
        elementosArchi=calcularElementosEnArchivo(archiCategorias, sizeof(stCategoria));

        arregloCategorias=(stCategoria*) malloc(sizeof(stCategoria)*elementosArchi);

        while(fread(&arregloCategorias[validos],sizeof(stCategoria), 1, archiCategorias)){
            validos++;
        }
        fclose(archiCategorias);
    }


    return validos;

}

int cargarCategoriasDesdeAdmin (stCategoria* arregloCategorias, int validos, int* dimension){
    char continuar = 's';

    while(continuar == 's'){
        if (validos==*dimension){
            arregloCategorias=(stCategoria*)realloc(arregloCategorias, sizeof(stCategoria)+10);
            *dimension=*dimension+10;

        }
        arregloCategorias[validos]=cargarCategoria();
        validos++;
        printf("\n\n Presione 's' para agregar mas categorias o cualquier tecla para salir: ");
        continuar=getchar();
        getchar();
    }

    return validos;

}
*/
