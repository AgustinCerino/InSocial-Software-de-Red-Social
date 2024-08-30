#ifndef STMENSAJERIA_H_INCLUDED
#define STMENSAJERIA_H_INCLUDED

#include "stUsuario.h"
#include "stContenido.h"
#include "listaContenido.h"
#include "stCategoria.h"
#include "arbolContenido.h"
#include "stFavorito.h"
#include "adlUsuarios.h"

typedef struct
{
    int idUsuarioEmisor;
    int idUsuarioReceptor;
    int idContenidoEnviado;
    char mensaje[300];
    int leido;                      // 1:si 0:no
} stMensajeria;

typedef struct
{
    stMensajeria mensaje;
    struct nodoListaMensajes* siguiente;

} nodoListaMensajes;


nodoListaMensajes* inicListaMensajes();
nodoListaMensajes* crearNodoMensajes(stMensajeria unMensaje);
nodoListaMensajes* agregarPpioMensajes (nodoListaMensajes* lista, nodoListaMensajes* nuevoNodo);
void recorrerYMostrarMensajes(nodoListaMensajes* lista);
void mostrarNodoMensajes (nodoListaMensajes* nodito);

/*###############PROTOTIPOS FUNCIONES DE MANEJO ESTRUCTURA stMensajeria#################*/

stMensajeria crearNuevoMensaje(stCelda* adl, int validosADL, stUsuario a);
nodoListaMensajes* subProgramaCrearNuevoMensaje(stMensajeria nuevoMensaje, nodoListaMensajes* lista);
void mostrarListaMensajes(nodoListaMensajes* lista);
void subProgramaMostrarMensajesRecibidos(nodoListaMensajes* lista, stCelda* adl, int posUsuario);
void mostrarUnMensajeRecibido(stMensajeria unMensaje);
void guardarUnMensajeNuevoArchivo(stMensajeria unMensaje, char nombreArchivo[]);
nodoListaMensajes* archivoToListaMensajeria(nodoListaMensajes* lista, char nombreArchivo[]);
void mostrarUnMensaje(stMensajeria unMensaje);

/*#####################################################################################*/

#endif // STMENSAJERIA_H_INCLUDED
