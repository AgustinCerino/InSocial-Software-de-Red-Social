#include <stdio.h>
#include <stdlib.h>
#include "stFavorito.h"
#include "arbolContenido.h"
#include "listaContenido.h"
#include "stUsuario.h"
#include "stContenido.h"
#include "adlUsuarios.h"


stCelda* inicADL (void){
    return NULL;
}


stCelda* crearArregloDeListas (int dimension)
{
    stCelda* pADL=NULL;
    if (dimension>0){
        pADL= (stCelda*)malloc(sizeof(stCelda)*dimension);
    }
    return pADL;

}



stCelda* redimensionarArregloDeListas(stCelda* arregloDeListas, int* dimension) //redimensiona el adl si alcanzo la dimension o si no fue creado
{
    arregloDeListas = (stCelda*) realloc(arregloDeListas,(sizeof(stCelda)+10*sizeof(stCelda)));
    *dimension+= 10;

    return arregloDeListas;
}

int cargarADL(stCelda* adl, FILE* pArchiUsuarios, FILE* pArchiFavoritos, nodoArbolContenido* arbol, int *dimensionADL)
{
    int i=0;
    int validos=0;

    if(pArchiUsuarios && pArchiFavoritos)
    {
        validos = deArchiUsuariosToADL(adl, pArchiUsuarios, dimensionADL);
        for(i=0; i<validos; i++)
        {
            cargarListaFavoritosAUsuario(adl+i, pArchiFavoritos, arbol);

        }
    }

    return validos;
}

int deArchiUsuariosToADL(stCelda* adl, FILE* archivoUsuarios, int *dimension)
{
    int validos=0;

    if (archivoUsuarios)
    {
        if(adl)
        {
            stUsuario aux;
            while(!feof(archivoUsuarios) && validos<*dimension)
            {
                fread(&aux, sizeof(stUsuario), 1,archivoUsuarios);
                validos=agregarACeldaUsuario(&adl, aux, validos, dimension);

            }
            fseek(archivoUsuarios,0, SEEK_SET);    //vuelvo el puntero al inicio del archivo




        }

    }

    return validos;
}

void cargarListaFavoritosAUsuario(stCelda* celdaADL, FILE* pArchiFavoritos, nodoArbolContenido* arbol)
{
    stFavorito aux;
    nodoArbolContenido* nodoAux;

    if(celdaADL)
    {
        while(!feof(pArchiFavoritos))
        {
            fread(&aux, sizeof(stFavorito), 1,pArchiFavoritos);
            if(celdaADL->usuario.idUsuario == aux.idUsuario )
            {
                nodoAux = buscarNodoArbolContenido(arbol, aux.idContenido);
                celdaADL->listaDeContenidosFavoritos=agregarPpioSimple(celdaADL->listaDeContenidosFavoritos, crearNodoSimple(nodoAux->contenido));
            }
        }
        fseek(pArchiFavoritos,0,SEEK_SET);



    }

}



int agregarACeldaUsuario (stCelda** adl, stUsuario aux, int validos, int * dimension){  //PUEDE REDIMENSIONAR EL ARREGLO POR LO CUAL CAMBIARIA LA DIRECCION DE MEMORIA DEL MISMO. POR LO TANTO, SE TRABAJA CON PUNTERO DOBLE

    if(!adl){
        *adl=redimensionarArregloDeListas(*adl, dimension);

    }
    else{
        if(*dimension==validos){
            *adl=redimensionarArregloDeListas(*adl, dimension);
        }

    }
    (*adl)[validos].usuario=aux;
    (*adl)[validos].listaDeContenidosFavoritos=inicListaSimple();
    validos++;

    return validos;

}

int eliminarCeldaUsuario (stCelda* adl, int validos, int idUsuarioBorrar){
    int i, j;

    for (i = 0; i < validos; i++) {
        if (adl[i].usuario.idUsuario == idUsuarioBorrar) {
            for (j = i; j < validos - 1; j++) {
                adl[j] = adl[j + 1];
            }

            validos--;

            break; /// Sale del bucle después de encontrar el elemento

        }
    }
    return validos;
}

void eliminarADL (stCelda* adl, int validos){
    int i=0;

    for(i=0; i<validos; i++){
        borrarLista(adl[i].listaDeContenidosFavoritos);
    }
    free(adl);
    adl=inicADL();

}

nodoArbolContenido* subprogramaEliminarContenidoDesdeAdmin (stCelda* adl, int validos, nodoArbolContenido* arbol, int idContenidoABorrar){
    int i=0;
    arbol=eliminarNodoContenido(arbol, idContenidoABorrar); //elimina contenido del arbol
    for(i=0; i<validos; i++){
        adl[i].listaDeContenidosFavoritos=borrarNodoSimpleSegunidContenido(adl[i].listaDeContenidosFavoritos, idContenidoABorrar); //elimina si esta ese contenido como favorito de una celda usuario
    }

    return arbol;
}

void mostrarUsuariosADL(stCelda* adl, int validosADL){
    int i=0;

    for(i=0;i<validosADL;i++){
        mostrarUsuario(adl[i].usuario);
    }


}

void banearUsuario (stCelda* adl, int validosADL, const char identidadUsuario [30]){
    int posUsuario=-1;

    posUsuario= existeUsuario(adl, validosADL, identidadUsuario);
    if(posUsuario>=0){
        adl[posUsuario].usuario.activo=-1;
    }
    else{
        printf("El usuario no existe. Por favor, vuelva a intentarlo.");
        printf("\n\n");
    }

}

stCelda* buscarUsuarioEnADL(stCelda* adl, int validosADL, const char identidadUsuario [30]){ //devuelve puntero a celda del arreglo del usuario buscado
    int posUsuario=-1;
    stCelda* pUsuarioBuscado=NULL;

    posUsuario= existeUsuario(adl, validosADL, identidadUsuario);
    if(posUsuario>=0){
        pUsuarioBuscado= adl+posUsuario;
    }
    else{
        printf("El usuario no existe. Por favor, vuelva a intentarlo.");
        printf("\n\n");
    }
    return pUsuarioBuscado;
}

nodoArbolContenido* subprogramaAgregarLikeAUsuario (stCelda* adl, int validosADL, nodoArbolContenido* arbol, const char usuario[30]){
    int posUsuario=-1;

    posUsuario=existeUsuario(adl, validosADL);
    if (posUsuario>=-1)
    {
        arbol=like(adl,posUsuario,arbol);
    }
    else{
        printf("El usuario no existe. Por favor, vuelva a intentarlo.");
        printf("\n\n");
    }
    return arbol;
}

int guardarFavoritos (stCelda* adl, int validos, nodoArbolContenido* arbol, FILE* pArchiFavoritos){ //retorna la cantidad de favoritos almacenada en el archivo
    int i=0;
    int j=0;
    stFavorito auxFavorito;
    nodoSimple* seg=NULL;


    for(i=0; i<validos; i++){
        auxFavorito.idUsuario=adl[i].usuario.idUsuario;
        seg=adl[i].listaDeContenidosFavoritos;
        while(seg){
            auxFavorito.idContenido=seg->contenidoSocial.idContenido;
            auxFavorito.idFavorito=j;
            j++;
            fwrite(&auxFavorito, sizeof(stFavorito), 1, pArchiFavoritos);
            seg=seg->siguiente;
        }

    }

    return j;
}

int guardarUsuarios(stCelda* adl, int validos, FILE* pArchiUsuarios){
    int i=0;
    stUsuario usuarioAux;

    for(i=0;i<validos;i++){
        usuarioAux=adl[i].usuario;
        fwrite (&usuarioAux, sizeof(stUsuario), 1, pArchiUsuarios);
    }
    return i;
}


int generarNuevoId(stCelda* adl, int validos) {
    int rta;

    if (validos == 0 || validos == 1) {
        rta = 1;
    } else {
        rta = adl[validos - 1].usuario.idUsuario + 1;
    }

    return rta;
}
