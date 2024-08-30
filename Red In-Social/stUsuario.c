#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stUsuario.h"
#include "stCategoria.h"

int calcularElementosEnArchivo(FILE* archi, int bytesElemento){
    int cantidadElementos=0;
    fseek(archi, 0, SEEK_END); //seteo cursor al final del archivo
    cantidadElementos=ftell(archi) / bytesElemento;
    fseek(archi,0,SEEK_SET);

    return cantidadElementos;

}

stUsuario cargarUsuario (int admin, int idUsuario){ //recibe 1 ó 0 dependiendo de donde sea llamada (abm o usuario plano) y el id del nuevo usuario a cargar en el adl basado en el ultimo id del ultimo usuario incrementado en 1
    stUsuario aux;                     //abm es solo desde donde puede llegar a introducir un 1 y darle los privilegios de admin

    printf("Ingrese nombre: ");
    fgets(aux.nombre, sizeof(aux.nombre), stdin);
    printf("\n");
    fflush(stdin);
    printf("Ingrese apellido: ");
    fgets(aux.apellido, sizeof(aux.apellido), stdin);
    printf("\n");
    fflush(stdin);
    printf("Ingrese un username: ");
    fgets(aux.userName, sizeof(aux.userName),stdin);
    printf("\n");
    fflush(stdin);
    printf("Ingrese un password: ");
    fgets(aux.password, sizeof(aux.password), stdin);
    printf("\n");
    fflush(stdin);
    printf("Ingrese un mail: ");
    fgets(aux.mail, sizeof(aux.mail), stdin);
    printf("\n");
    fflush(stdin);
    printf("Ingrese su genero: ");
    scanf("%c", &aux.genero);
    printf("\n");
    fflush(stdin);
    aux.puntaje=0;
    aux.nivel=0;
    aux.rol=admin;
    aux.idUsuario=idUsuario;
    printf("\n");
    fflush(stdin);
    elegirPreferenciaCategorias(aux.categoriasPreferidas);
    aux.activo=1;


    return aux;

}


void elegirPreferenciaCategorias ( char categoriasPreferidas [3][30]){
    int j=0;

    while(j<3){
        printf("Ingrese una categoria preferida (Ciencia/Espectaculos/Arte/Deportes/Economia/Salud): ");
        fgets(categoriasPreferidas[j], sizeof(char)*30 ,stdin);
        fflush(stdin);
        printf("\n\n");
        j++;
    }

}
/*
void imprimirCategorias(stCategoria* categorias, int validos){ //no se va a implementar en esta version
    int i=0;


    while(i<validos){
        printf("##########################");
        printf("Categoria: %s", categorias[i].nombreCategoria);
        printf("\n");
        printf("Id de la categoria: %i", categorias[i].idCategoria);
        printf("\n\n");
        printf("##########################");
    }
}

*/

void mostrarUsuario (stUsuario usuarioAMostrar){
    int i=0;
    printf("Nombre y Apellido: %s %s", usuarioAMostrar.nombre, usuarioAMostrar.apellido);
    printf("\n");
    printf("Username: %s", usuarioAMostrar.userName);
    printf("\n");
    printf("Id de Usuario: %i", usuarioAMostrar.idUsuario);
    printf("\n");
    printf("Correo electronico: %s", usuarioAMostrar.mail);
    printf("\n");
    printf("Nivel: %i",usuarioAMostrar.nivel);
    printf("\n");
    printf("Estado: %d", usuarioAMostrar.activo);
    printf("\n\n");
    for(i=0;i<3;i++){
        printf("Categoria Preferida %d: %s\n", i,usuarioAMostrar.categoriasPreferidas[i]);
    }
    printf("\n\n");

}

void eliminarNuevaLinea(char cadena[]) {
    // Buscar la posición del carácter de nueva línea
    size_t longitud = strcspn(cadena, "\n");

    // Reemplazar el carácter de nueva línea con el carácter nulo
    cadena[longitud] = '\0';
}

