#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stMensajeria.h"
#include "stUsuario.h"
#include "stContenido.h"

///FUNCIONES DE LISTA DE MENSAJES:

nodoListaMensajes* inicListaMensajes()
{
    return NULL;
}

nodoListaMensajes* crearNodoMensajes(stMensajeria unMensaje)
{
    nodoListaMensajes* aux = (nodoListaMensajes*) malloc(sizeof(nodoListaMensajes));
    aux->mensaje= unMensaje;
    aux->siguiente = NULL;

    return aux;
}

nodoListaMensajes* agregarPpioMensajes (nodoListaMensajes* lista, nodoListaMensajes* nuevoNodo)
{
    if(!lista)
    {
        lista = nuevoNodo;
    }
    else
    {
        nuevoNodo->siguiente = lista;
        lista=nuevoNodo;
    }

    return lista;
}

void mostrarNodoMensajes (nodoListaMensajes* nodito)
{
    mostrarUnMensaje(nodito->mensaje);
}

void recorrerYMostrarMensajes(nodoListaMensajes* lista)
{
    nodoListaMensajes* seg=NULL;

    if(lista)
    {
        while(seg)
        {
            mostrarNodoMensajes(seg);
            seg=seg->siguiente;
        }
    }
}

///FUNCIONES DE MENSAJERIA:
stMensajeria crearNuevoMensaje(stCelda* adl, int validosADL, stUsuario a)
{
    stMensajeria nuevoMensaje;
    char userNameReceptor[20];
    int posReceptor;

    printf("=============MENSAJE NUEVO=============\n");
    nuevoMensaje.idUsuarioEmisor = a.idUsuario;

    printf("Ingrese el MAIL del usuario al que desea enviar el mensaje:\n");

    fgets(userNameReceptor, 30, stdin);

    posReceptor = existeUsuario(adl, validosADL, userNameReceptor);

    if (posReceptor != -1)
    {
        nuevoMensaje.idUsuarioReceptor = adl[posReceptor].usuario.idUsuario;

        printf("Mensaje:\n");

        fgets(nuevoMensaje.mensaje, 300, stdin);

        nuevoMensaje.leido = 0;
    }
    else
    {
        printf("El usuario receptor no se encontró.\n");
        // Puedes manejar este caso según tus necesidades
    }

    return nuevoMensaje;
}

nodoListaMensajes* subProgramaCrearNuevoMensaje(stMensajeria nuevoMensaje, nodoListaMensajes* lista)
{
    nodoListaMensajes* nuevoNodo = crearNodoMensajes(nuevoMensaje);
    lista = agregarPpioMensajes(lista, nuevoNodo);

    return lista;

}

void mostrarListaMensajes(nodoListaMensajes* lista)
{
    while(lista!=NULL)
    {
        mostrarUnMensaje(lista->mensaje);
        lista=lista->siguiente;
    }
}

void subProgramaMostrarMensajesRecibidos(nodoListaMensajes* lista, stCelda* adl, int posUsuario)
{
    while(lista!=NULL)
    {
        if(lista->mensaje.idUsuarioReceptor==adl[posUsuario].usuario.idUsuario)
        {
            //mostrarUnMensajeRecibido(lista->mensaje);
            mostrarUnMensaje(lista->mensaje);
            lista=lista->siguiente;
        }
        else
        {
            lista=lista->siguiente;
        }
    }
}

nodoListaMensajes* archivoToListaMensajeria(nodoListaMensajes* lista, char nombreArchivo[])
{
    stMensajeria unMensaje;
    nodoListaMensajes* nuevo;
    if(nombreArchivo!=NULL)
    {
        while(fread(&unMensaje, sizeof(stMensajeria), 1, nombreArchivo)>0)
        {
            nuevo = crearNodoMensajes(unMensaje);
            lista = agregarPpioMensajes(lista, nuevo);
        }
    }
    return lista;
}

void guardarUnMensajeNuevoArchivo(stMensajeria unMensaje, char nombreArchivo[])
{
    if (nombreArchivo!=NULL)
    {
        fwrite(&unMensaje, sizeof(stMensajeria), 1, nombreArchivo);
    }
}

void mostrarUnMensajeRecibido(stMensajeria unMensaje)
{
    //char cad;
    // a = buscarUsuarioEstructuraPorID(unMensaje.idUsuarioEmisor); ///HACER LA FUNCION

    printf("\n \n \n \n");
    printf("\t \t======================================================== \n");
    printf("\t \t================ NUEVO MENSAJE RECIBIDO ================ \n");
    printf("\t \t======================================================== \n ");
    printf("ENVIADO POR.............: %d \n", unMensaje.idUsuarioEmisor);
    printf("MENSAJE.................: %s \n", unMensaje.mensaje);
    //unMensaje.leido=1;

    system("pause");
    //cad = getchar();
}

void mostrarUnMensaje(stMensajeria unMensaje)
{
    printf("=============MENSAJE ENVIADO=============\n\n");
    printf("Enviado a usuario ID...............: %d\n", unMensaje.idUsuarioReceptor);
    printf("Enviado por usuario ID.............: %d\n", unMensaje.idUsuarioEmisor);
    printf("Mensaje: %s\n", unMensaje.mensaje);
    system("pause");
    //unMensaje.leido=1;
}

