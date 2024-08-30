#ifndef STUSUARIO_H_INCLUDED
#define STUSUARIO_H_INCLUDED

#include "stCategoria.h"

typedef struct
{
    int idUsuario;                 // auto incremental
    char nombre[30];
    char apellido[30];
    char userName[30];
    char password[20];
    char mail[30];
    char genero;
    int puntaje;
    int nivel;
    char categoriasPreferidas [3][30]; //guarda 3 id de categorias
    int rol;                     // 1: es admin - 0: es comun
    int activo;                 // indica 1 o 0 si el usuario está activo, -1 si esta baneado

} stUsuario;

/*###############PROTOTIPOS FUNCIONES DE MANEJO ESTRUCTURA stUsuario#################*/
int calcularElementosEnArchivo(FILE* archi, int bytesElemento);
stUsuario cargarUsuario (int admin, int idUsuario);
void elegirPreferenciaCategorias ( char categoriasPreferidas [3][30]);
/// void imprimirCategorias(stCategoria* categorias, int validos);
void mostrarUsuario (stUsuario usuarioAMostrar);
void eliminarNuevaLinea(char cadena[]);

/*##################################################################################*/


#endif // STUSUARIO_H_INCLUDED
