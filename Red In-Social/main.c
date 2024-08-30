#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "stContenido.h"
#include "listaContenido.h"
#include "arbolContenido.h"
#include "stUsuario.h"
#include "adlUsuarios.h"
#include "stFavorito.h"
#include "stMensajeria.h"
#include <locale.h>

void menuInicio (void);
void quienesSomos(void);
void faq(const char *nombreArchivo);
nodoArbolContenido* subprogramaLogIn (stCelda* adl, int validosADL, nodoArbolContenido* arbol);
stCelda* subprogramaSignIn(stCelda* adl, int* validosADL, int* dimension);
nodoArbolContenido* subprogramaABM (stCelda* adl, int validosADL, nodoArbolContenido* arbol);
nodoArbolContenido* logInABM (stCelda* adl, int* validosADL, int* dimension, nodoArbolContenido* arbol);


int existeUsuario (stCelda* adl, int validos, const char identidadUsuario[30]);
void cargarUsuarioYPassword ( char identidadUser [30], char passwordUser [30]);
int logInCorrecto (stUsuario user, const char passwordUser[30]);
void opcionesMenuUsuarioLogueado();
void opcionesLikeYCompartir (void);
nodoArbolContenido* like (stCelda* adl, int posicionUsuario, nodoArbolContenido* arbol);
nodoArbolContenido* opcionesMenuPublicacion (stCelda* adl, int posicionUsuario, nodoArbolContenido* arbol);
nodoArbolContenido* menuUsuarioLogueado(stCelda* adl, int posicionUsuario, int validosADL ,nodoArbolContenido* arbol, const char* nombreArchivoMensajeria);
void opcionesMenuUsuarioAdmin();
nodoArbolContenido* ABM (stCelda* adl, int* validosADL, int* dimension, nodoArbolContenido* arbol);
nodoArbolContenido* subprogramaAdmin (stCelda* adl, int posUsuario, int* validos, int* dimension, nodoArbolContenido* arbol);
int existeUsuario (stCelda* adl, int validos, const char identidadUsuario[30]);  //retorna -1 si no existe, o 1 si existe


void opcionesMenuUsuarioAdmin();



int main (void)
{
    system("color 60");
    setlocale(LC_ALL, "");
    int dimensionADL=0;
    int validos = 0;
    int opcion=0;
    FILE* pArchiUsuarios=fopen("usuarios.dat", "r+w");
    FILE* pArchiContenido=fopen("contenidos.dat", "r+w");
    FILE* pArchiFavoritos=fopen("favoritos.dat", "r+w");
    FILE* pArchiMensajeria=fopen("mensajes.dat", "r+w");


    stCelda* adl= inicADL();
    nodoArbolContenido* arbolContenido =inicArbolContenido();

    if(pArchiUsuarios && pArchiContenido && pArchiFavoritos)
    {
        dimensionADL=calcularElementosEnArchivo(pArchiUsuarios, sizeof(stUsuario)); //si pudo abrir el archivo de usuarios, calculo la cantidad de usuarios

        adl=crearArregloDeListas(dimensionADL); //creo en el heap el arreglo de listas de usuario con contenidos favoritos

        arbolContenido=deArchiToArbolContenido (arbolContenido, pArchiContenido); //cargo el arbol contenido


        ///////////////////////////////////////////BORRAR///////////////////////////////////////////

//        printf("validos antes de cargar el adl: %d\n\n", validos);
//        printf("dimension antes de cargar el adl: %d\n\n", dimensionADL);
//        system("pause");
        ////////////////////////////////////////BORRAR//////////////////////////////////////////////

        validos=cargarADL (adl, pArchiUsuarios, pArchiFavoritos, arbolContenido, &dimensionADL); //cargo los usuarios en cada celda del arreglo y del archivo de favoritos, saco que contenido agregar a cada lista de contenidos de favoritos por usuario

//        ///////////////////////////////////////////BORRAR///////////////////////////////////////////
        validos=agregarACeldaUsuario(&adl, cargarUsuario(1, generarNuevoId(adl, validos)),validos, &dimensionADL); // LINEA DE CODIGO PARA CREAR EL PRIMER ADMIN (mail: admin - contraseña: admin)
//        printf("validos despues cargar el adl: %d\n\n", validos);
//        printf("dimension despues cargar el adl: %d\n\n", dimensionADL);
//        getchar();
//        mostrarUsuariosADL(adl,validos);
//        system("pause");
//

        ////////////HASTA ACA FUNCIONA BIEN////////////////////BORRAR//////////////////////////////////////////////

        do
        {
            system("cls");
            menuInicio();
            scanf("%d", &opcion);
            fflush(stdin);
            printf("\n\n\n");
            switch (opcion)
            {
            case 1:
//                ///////////////////////////////////////////BORRAR///////////////////////////////////////////
//
//                printf("validos antes del log in %d\n\n", validos);
//                system("pause");
//                mostrarUsuariosADL(adl,validos);
//                ////////////////////////////////////////BORRAR//////////////////////////////////////////////
                arbolContenido = subprogramaLogIn(adl, validos, arbolContenido); //puede modificar el arbol, por eso retorna el arbol
                break;
            case 2:
                adl=subprogramaSignIn(adl,&validos,&dimensionADL); //puede modificar el adl, por eso retorna los validos (si creo o borro un usuario)
                break;
            case 3:
                quienesSomos();
                break;
            case 4:
                faq("meme.txt");
                break;
            case 9:
                arbolContenido=logInABM(adl, &validos, &dimensionADL, arbolContenido);        //puede modificar el adl, por eso retorna los validos
                break;

            default:

                if(opcion==0)
                {
                    system ("cls");
                    printf("\n\n\n\nGracias por utilizar iN-Social! Hasta pronto!\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
                    printf("%*s%s\n", 50, "", "version 2.0");
                    printf("\n\n\n\n\n");

                }
                break;

            }
            system("pause");

        }
        while (opcion!=0);
        guardarArbolContenidoEnArchivo (arbolContenido, pArchiContenido);
        guardarFavoritos(adl, validos, arbolContenido,pArchiFavoritos);
        guardarUsuarios(adl, validos,pArchiUsuarios);
        fclose(pArchiContenido);
        fclose(pArchiUsuarios);
        fclose(pArchiFavoritos);
        eliminarADL(adl,validos);
        eliminarArbolContenido(arbolContenido);
        //eliminarListaDeMensajes
    }
    else
    {
        system ("cls");
        if(!pArchiContenido)
        {
            perror("Error al abrir al cargar los contenidos.\n\n");
        }
        if(!pArchiUsuarios)
        {
            perror("Error al cargar el usuario\n\n");
        }
        if(!pArchiFavoritos)
        {
            perror("Error al cargar los favoritos\n\n");
        }
        exit(EXIT_FAILURE);
    }


    return 0;

}



void quienesSomos(void)
{
    system("cls");
    printf("\n\n\niN-Social! nace como una forma de comunicarnos en clase.\n\n");
    printf("Somos un grupo de cuatro estudiantes realizando el trabajo práctico final de Laboratorio de Programacion 2.\n");
    printf("Conformamos el grupo denominado \"Los Simuladores\"\n");
    printf("Esperamos con ansias aprobar este trabajo de la mejor manera posible y cumplir con todas las expectativas de la catedra *guinio guinio*\n\n\n\n");
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    printf("Saludos Gustavo *guinio guinio*\n\n\n");

}


nodoArbolContenido* subprogramaLogIn (stCelda* adl, int validosADL, nodoArbolContenido* arbol)
{
    char identidadUser [30];
    char passwordUser [30];
    int posUsuario=-1;
    char salir = '0';

    do
    {
        cargarUsuarioYPassword(identidadUser, passwordUser);
        posUsuario= existeUsuario(adl, validosADL, identidadUser);

//            ///////////////////////////////////////////BORRAR///////////////////////////////////////////
//
//                printf(" ENTRE AL SUBPROGRAMA LOG IN. Pos USUARIO %d\n\n", posUsuario);
//                printf("VALIDOS: %d\n\n", validosADL);
//                printf("LOG IN CORRECTO: %d", logInCorrecto(adl[posUsuario].usuario, passwordUser));
//                system("pause");
//
//                ////////////////////////////////////////BORRAR//////////////////////////////////////////////

        if(posUsuario>=0)
        {

            if(logInCorrecto(adl[posUsuario].usuario, passwordUser)==1)
            {

                if(adl[posUsuario].usuario.activo == 0)
                {
                    printf("Parece que estas intentando acceder a una cuenta eliminada tiempo atras. Si quieres habilitar de nuevo esta cuenta, presiona 's'...");
                    salir = getchar();
                    fflush(stdin);
                    if(salir=='s')
                    {
                        arbol = menuUsuarioLogueado(adl,posUsuario,validosADL,arbol,"archivoMensajeria.dat");
                    }

                }
                else
                {
                    if(adl[posUsuario].usuario.activo == -1)
                    {
                        printf("Su cuenta fue suspendida. No tiene permiso para acceder a la cuenta. ");
                        printf("\n\n");
                    }
                    else
                    {
//
//             ///////////////////////////////////////////BORRAR///////////////////////////////////////////
//
//                printf(" ENTRE A usuario que no existe ni esta baneado. Pos USUARIO %d\n\n", posUsuario);
//                printf("VALIDOS: %d\n\n", validosADL);
//                printf("LOG IN CORRECTO: %d", logInCorrecto(adl[posUsuario].usuario, passwordUser));
//                system("pause");
//
//                ////////////////////////////////////////BORRAR//////////////////////////////////////////////

                        arbol = menuUsuarioLogueado(adl,posUsuario,validosADL,arbol,"archivoMensajeria.dat");


                    }

                }

            }
        }
        else
        {
            printf("El mail o usuario que has introducido no está conectado a una cuenta. Por favor, intentelo nuevamente\n");
            printf("\n\n");
        }
        printf("Presione la tecla '0' si desea volver al menu anterior.\n\n");
        salir=getchar();
        fflush(stdin);
    } while (salir != '0');

    return arbol;


}


nodoArbolContenido* menuUsuarioLogueado(stCelda* adl, int posicionUsuario, int validosADL ,nodoArbolContenido* arbol, const char* nombreArchivoMensajeria)
{

    FILE* archiMensajes = fopen(nombreArchivoMensajeria, "a+b");
    nodoListaMensajes* listaMensajes=inicListaMensajes();
    listaMensajes=archivoToListaMensajeria(listaMensajes, archiMensajes);
    stMensajeria nuevoMensaje;
    int opcion=0;

    if(archiMensajes)
    {

        do
        {
            system ("cls");
            opcionesMenuUsuarioLogueado();
            scanf("%d", &opcion);
            fflush(stdin);
            system("cls");
            switch (opcion)
            {
            case 1:
                //mostrarContenidosSegunPreferencias(adl[posicionUsuario].usuario, arbol); //NO PUDE HACER QUE FUNCIONARA, MUESTRO EL ARBOL ENTERO
                imprimirInorderArbolContenido(arbol);
                arbol=opcionesMenuPublicacion(adl, posicionUsuario, arbol);
                break;
            case 2:
                arbol=agregarNuevoContenidoAutoincremental(arbol);
                break;
            case 3:
                nuevoMensaje=crearNuevoMensaje(adl, validosADL, adl[posicionUsuario].usuario);
                mostrarUnMensaje(nuevoMensaje);
                listaMensajes=subProgramaCrearNuevoMensaje(nuevoMensaje,listaMensajes);
                guardarUnMensajeNuevoArchivo(nuevoMensaje, archiMensajes);
                break;
            case 4:
                break;
            case 5:
                recorrerYMostrarSimple(adl[posicionUsuario].listaDeContenidosFavoritos);
                system("pause");
                break;
            case 6:
                mostrarUsuario(adl[posicionUsuario].usuario);
                break;
            default:
                if(opcion==0)
                {
                    system("cls");
                    printf("Hasta pronto %s %s ", adl[posicionUsuario].usuario.nombre, adl[posicionUsuario].usuario.apellido);
                    printf("\n\n");
                    system("pause");

                }

                break;



            }

        }
        while(opcion!=0);

            fclose(archiMensajes);





    }
    else
    {

        perror("Error al cargar los mensajes\n\n");
        exit(EXIT_FAILURE);
    }

    return arbol;
}

nodoArbolContenido* opcionesMenuPublicacion (stCelda* adl, int posicionUsuario, nodoArbolContenido* arbol)
{
    int opcion = 0;

    do
    {
        opcionesLikeYCompartir();
        scanf("%d", &opcion);
        fflush(stdin);
        switch (opcion)
        {
        case 1:
            arbol=like(adl, posicionUsuario, arbol);
            break;
        case 2:
            //compartir();
            break;
        default:
            break;
        }

    }
    while(opcion!=0);
    return arbol;
}



nodoArbolContenido* like (stCelda* adl, int posicionUsuario, nodoArbolContenido* arbol)
{
    int idALikear=-500;
    nodoArbolContenido* nodoArbolAux=NULL;
    nodoSimple* nodoListaAux=NULL;


    do
    {
        printf("Id de la publicacion a likear: "); //si likea una publicacion ya likeada por el usuario, se quita el like
        scanf("%d", &idALikear);
        fflush(stdin);
        printf("\n\n");
        nodoArbolAux=buscarNodoArbolContenido(arbol, idALikear);
        nodoListaAux=buscarNodoSimpleSegunCampo(adl[posicionUsuario].listaDeContenidosFavoritos, idALikear);
        if(nodoArbolAux && !nodoListaAux)
        {
            adl[posicionUsuario].listaDeContenidosFavoritos=agregarPpioSimple(adl[posicionUsuario].listaDeContenidosFavoritos, crearNodoSimple(nodoArbolAux->contenido));
            nodoArbolAux->contenido.likes=nodoArbolAux->contenido.likes + 1;
        }
                if(nodoArbolAux && nodoListaAux)
        {
            adl[posicionUsuario].listaDeContenidosFavoritos=borrarNodoSimpleSegunidContenido(adl[posicionUsuario].listaDeContenidosFavoritos, idALikear);
            nodoArbolAux->contenido.likes=nodoArbolAux->contenido.likes - 1;

        }
    }
    while(nodoArbolAux==NULL);

    return arbol;

}

void opcionesLikeYCompartir (void)
{
    printf("1. Me gusta");
    printf("\n");
    printf("2. Compartir");
    printf("\n");
    printf("0. Salir");
    printf("\n\n");
    printf("Opcion Elegida: ");

}

void opcionesMenuUsuarioLogueado(/*stMensajeria* listaMensajes*/)
{
    printf("1. Ver publicaciones");
    printf("\n");
    printf("2. Crear publicacion");
    printf("\n");
    printf("3. Enviar un mensaje");
    printf("\n");
    printf("4. Ver mensajes recibidos");
    printf("\n");
    printf("5. Publicaciones que te han gustado");
    printf("\n");
    printf("6. Ver mi perfil");
    printf("\n");
    printf("0. Cerrar sesion");
    printf("\n\n\n");
    printf("Opcion elegida: ");

}





int logInCorrecto (stUsuario user, const char passwordUser[30])
{
    if (strcmp(user.password, passwordUser)==0)
    {
        return 1;
    }
    else{
        return 0;
    }
    //(strcmp(user.password, passwordUser)==0) ? return 1 : return 0;
}


void cargarUsuarioYPassword ( char identidadUser [30], char passwordUser [30])
{
    printf("Mail: ");
    fgets(identidadUser, sizeof(identidadUser), stdin);
    printf("\n");
    fflush (stdin);
    printf("Password: ");
    fgets(passwordUser, sizeof(passwordUser), stdin);
    printf("\n");
    printf("\n");
    fflush(stdin);
}

int existeUsuario (stCelda* adl, int validos, const char identidadUsuario[30])  //retorna -1 si no existe, o 1 si existe
{
    int posUsuario=-1;
    int i = 0;
    if(adl)
    {
        while(i<validos && (strcmp(identidadUsuario, adl[i].usuario.mail)!=0))
        {
            i++;
        }
        if(strcmp(identidadUsuario, adl[i].usuario.mail)==0)
        {
            posUsuario=i;
        }




    }

    return posUsuario;
}



void faq(const char *nombreArchivo)
{
    FILE *archivo = fopen(nombreArchivo, "r");

    if (archivo == NULL)
    {
        perror("Error al abrir el meme");
        exit (EXIT_FAILURE);
    }
    else
    {
        char linea[1000];

        while (fgets(linea, sizeof(linea), archivo) != NULL)
        {
            printf("%s", linea);
        }

        fclose(archivo);
    }

}

void menuInicio (void)
{
    system("cls");
    printf("Bienvenido a la Red Social mas usada. \n\n\n\n\n");
    printf("%*s%s\n", 50, "", "iN-Social");
    printf("\n\n\n\n");
    printf("iN-Social! te ayuda a comunicarte y compartir con las personas que forman parte de tu vida.");
    printf("\n\n\n\n\n");
    printf("Menu de opciones: \n\n");
    printf("1) log in\n");
    printf("2) sign in\n");
    printf("3) Acerca de nosotros\n");
    printf("4) FAQ\n");
    printf("9) In social para administradores\n\n");
    printf("0) SALIR\n");
    printf("\n\n\n\n");
    printf("OPCION ELEGIDA:  ");

}

stCelda* subprogramaSignIn(stCelda* adl, int* validosADL, int* dimension) {
    char identidadUser[30];
    int posUsuario = -1;
    char salir = '0';


    do{
        printf("Ingrese un mail: ");
        fgets(identidadUser, sizeof(identidadUser), stdin);
        printf("\n\n");
//
//        //////////////////BORRAR/////////////////
//        printf("%s", identidadUser);
//        printf("\n\n");
//        ////////////////////////////////////////////

        fflush(stdin); // Limpiar el búfer del teclado

        posUsuario = existeUsuario(adl, *validosADL, identidadUser);

//        //////////////////BORRAR/////////////////
//        printf("se ejecuta existe usuario");
//        printf("%d", posUsuario);
//        printf("\n\n");
//        system("pause");
//        ////////////////////////////////////////////

        if (posUsuario == -1) {
            *validosADL = agregarACeldaUsuario(&adl, cargarUsuario(0, generarNuevoId(adl,*validosADL)), *validosADL, dimension);
            printf("Su cuenta fue creada con éxito. Por favor, inicie sesión para poder continuar.\n");
        } else {
            printf("El mail que quiere utilizar ya pertenece a una cuenta. Por favor, inténtelo con uno nuevo...\n\n");
        }

        printf("Presione la tecla '0' si desea volver al menu anterior: ");
        scanf(" %c", &salir); // Leer un solo carácter
        fflush(stdin); // Limpiar el búfer del teclado
    } while (salir != '0');

    return adl;
}

nodoArbolContenido* logInABM (stCelda* adl, int* validosADL, int* dimension, nodoArbolContenido* arbol){
    char identidadUser [30];
    char passwordUser [30];
    int posUsuario=-1;
    char salir = '0';

    do
    {
        cargarUsuarioYPassword(identidadUser, passwordUser);
        posUsuario= existeUsuario(adl, *validosADL, identidadUser);

        if(posUsuario>=0)
        {

            if(logInCorrecto(adl[posUsuario].usuario, passwordUser) && adl[posUsuario].usuario.rol==1)
            {
                if(adl[posUsuario].usuario.activo == 0)
                {
                    printf("Parece que estas intentando acceder a una cuenta eliminada tiempo atras. Si quieres habilitar de nuevo esta cuenta, presiona 's'...");
                    salir = getchar();
                    getchar();
                    if(salir=='s')
                    {
                        arbol=subprogramaAdmin(adl, posUsuario, validosADL, dimension, arbol);

                    }

                }
                else
                {
                    if(adl[posUsuario].usuario.activo == -1)
                    {
                        printf("Su cuenta fue suspendida. No tiene permiso para acceder a la cuenta. ");
                        printf("\n\n");
                        system ("pause");
                    }
                    else
                    {
                        arbol=subprogramaAdmin(adl, posUsuario, validosADL, dimension, arbol);
                    }

                }

            }
        }
        else
        {
            printf("El mail o usuario que has introducido no está conectado a una cuenta admin. Por favor, intentelo nuevamente");
            system("pause");
            printf("\n\n");
        }
        printf("Presione la tecla '0' si desea volver al menu anterior.");
        salir=getchar();
        getchar();
    } while (salir != '0');
    return arbol;


}

nodoArbolContenido* subprogramaAdmin (stCelda* adl, int posUsuario, int* validosADL, int* dimension, nodoArbolContenido* arbol)
{
    int opcion=0;
    do
    {
        printf("BIENVENIDO %s %s", adl[posUsuario].usuario.nombre, adl[posUsuario].usuario.apellido);
        printf("\n\n");
        printf("1. MENU ADMIN ");
        printf("\n");
        printf("2. MENU USUARIO");
        printf("\n");
        printf("0. salir");
        printf("\n\n");
        printf("Opcion elegida: ");
        scanf("%d", &opcion);
        fflush(stdin);

        switch (opcion)
        {
        case 1:
            arbol = ABM(adl, validosADL, dimension, arbol);
            break;
        case 2:
            arbol = menuUsuarioLogueado(adl,posUsuario,validosADL, arbol,"archivoMensajeria.dat");
            break;
        default:
            printf("Hasta luego!");
            printf("\n\n");
            break;

        }


    }while (opcion!=0);

    return arbol;
}




nodoArbolContenido* ABM (stCelda* adl, int* validosADL, int* dimension, nodoArbolContenido* arbol)
{
    int opcion=0;
    nodoArbolContenido* nodoArbolAux=NULL;
    int rta=0;
    char usuario[30];
    stCelda* pUsuario=NULL;

    do
    {
        system ("cls");
        opcionesMenuUsuarioAdmin();
        scanf("%d", &opcion);
        fflush(stdin);
        printf("\n\n\n");
        system ("cls");
        switch (opcion)
        {
        case 1:
            imprimirInorderArbolContenido(arbol);

            break;
        case 2:
            nodoArbolAux= crearNodoArbolContenido(cargarContenido());
            arbol=insertarNuevoNodoContenido(arbol, nodoArbolAux);
            break;
        case 3:
            printf("Ingrese el id de la publicacion que desea eliminar: ");
            scanf("%d", &rta);
            printf("\n");
            fflush(stdin);
            arbol=subprogramaEliminarContenidoDesdeAdmin(adl, *validosADL, arbol, rta);
            break;
        case 4:
            mostrarUsuariosADL(adl,*validosADL);
            break;
        case 5:
            printf("Ingrese 1 si el usuario sera admin: ");
            scanf("%d", &rta);
            printf("\n");
            fflush(stdin);
            if(rta==1)
            {
                *validosADL=agregarACeldaUsuario(&adl, cargarUsuario(1, generarNuevoId(adl,*validosADL)), *validosADL, dimension);
            }
            else
            {
                *validosADL=agregarACeldaUsuario(&adl, cargarUsuario(0,generarNuevoId(adl,*validosADL)), *validosADL, dimension);
            }
            break;
        case 6:
            printf("Ingrese el id del Usuario a Eliminar: ");
            scanf("%d", &rta);
            printf("\n");
            fflush(stdin);
            *validosADL=eliminarCeldaUsuario(adl, *validosADL,rta);
            break;
        case 7:
            printf("Ingrese el mail o username del usuario: ");
            scanf("%s", usuario);
            printf("\n");
            fflush(stdin);
            printf("\n");
            banearUsuario(adl, *validosADL, usuario);
            break;
        case 8:
            printf("Ingrese el mail o username del usuario: ");
            scanf("%s", usuario);
            printf("\n");
            fflush(stdin);
            arbol=subprogramaAgregarLikeAUsuario(adl,*validosADL, arbol, usuario);
            break;
        case 9:
            break;
        case 10:
            break;
        case 11:
            printf("Ingrese el mail o username del usuario: ");
            scanf("%s", usuario);
            printf("\n");
            fflush(stdin);
            pUsuario=buscarUsuarioEnADL(adl, *validosADL, usuario);
            mostrarUsuario(pUsuario->usuario);
            break;
        default:
            if(opcion==0)
            {
                printf("Hasta luego!");
                printf("\n\n");
            }

        }
        system ("pause");
        break;
    }
    while(opcion != 0);

    return arbol;
}

void opcionesMenuUsuarioAdmin()
{
    printf("1. Ver publicaciones");
    printf("\n");
    printf("2. Crear publicacion");
    printf("\n");
    printf("3. Borrar publicacion");
    printf("\n");
    printf("4. Ver usuarios");
    printf("\n");
    printf("5. Crear usuario");
    printf("\n");
    printf("6. Borrar usuario");
    printf("\n");
    printf("7. Banear usuario");
    printf("\n");
    printf("8. Agregar o quitar favorito a un usuario");
    printf("\n");
    printf("9. Mostrar mensajes de un usuario");
    printf("\n");
    printf("10. Borrar mensajes de un usuario");
    printf("\n");
    printf("11. Ver mi perfil");
    printf("\n");
    printf("0. Cerrar sesion");
    printf("\n\n\n");
    printf("Opcion elegida: ");

}



