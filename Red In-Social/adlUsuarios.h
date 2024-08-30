#ifndef ADLUSUARIOS_H_INCLUDED
#define ADLUSUARIOS_H_INCLUDED

#include "stContenido.h"
#include "stUsuario.h"
#include "listaContenido.h"
#include "stCategoria.h"
#include "arbolContenido.h"
#include "stFavorito.h"

typedef struct
{
    stUsuario usuario;
    nodoSimple * listaDeContenidosFavoritos;
} stCelda;


/*###############PROTOTIPOS FUNCIONES DE MANEJO ESTRUCTURA ADL USUARIO#################*/

stCelda* inicADL (void);
stCelda* crearArregloDeListas (int dimension);
stCelda* redimensionarArregloDeListas(stCelda* arregloDeListas, int* dimension); //redimensiona el adl si alcanzo la dimension o si no fue creado
int cargarADL(stCelda* adl, FILE* pArchiUsuarios, FILE* pArchiFavoritos, nodoArbolContenido* arbol, int *dimensionADL);
void cargarListaFavoritosAUsuario(stCelda* celdaADL, FILE* pArchiFavoritos, nodoArbolContenido* arbol);
int deArchiUsuariosToADL(stCelda* adl, FILE* archivoUsuarios, int* dimension);
int agregarACeldaUsuario (stCelda** adl, stUsuario aux, int validos, int * dimension);
int eliminarCeldaUsuario (stCelda* adl, int validos, int idUsuarioBorrar);
void eliminarADL (stCelda* adl, int validos);
nodoArbolContenido* subprogramaEliminarContenidoDesdeAdmin (stCelda* adl, int validos, nodoArbolContenido* arbol, int idContenidoABorrar);
void mostrarUsuariosADL(stCelda* adl, int validosADL);
void banearUsuario (stCelda* adl, int validosADL, const char identidadUsuario [30]);
stCelda* buscarUsuarioEnADL(stCelda* adl, int validosADL, const char identidadUsuario [30]); //devuelve puntero a celda del arreglo del usuario buscado
nodoArbolContenido* subprogramaAgregarLikeAUsuario (stCelda* adl, int validosADL, nodoArbolContenido* arbol, const char usuario[30]);
int guardarFavoritos (stCelda* adl, int validos, nodoArbolContenido* arbol, FILE* pArchiFavoritos);
int guardarUsuarios (stCelda* adl, int validos, FILE* pArchiUsuarios);
int generarNuevoId(stCelda* adl, int validos);

/*####################################################################################*/


#endif // ADLUSUARIOS_H_INCLUDED
