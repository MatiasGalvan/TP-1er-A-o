#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "login.h"
#include "personaje.h"
#include "persistencia.h"
#include "admin.h"
#include "color.h"

//Funcion de menu de inicio de sesion o registro de jugador.
nodoUsuario * menu(nodoUsuario * lista, nodoArbolZona * * mapa)
{
    nodoUsuario * user = inicListaUsr();
    int sel = 0;

    system("cls");

    sel = loginSel();
    Color(BLACK, LGREY);
    switch(sel)
    {
    case 1:
        user = iniciarSesion(lista);
        if(user != NULL)
        {
            if(strcmp(user->dato.nombre, "admin") == 0)
            {
                nodoArbolZona * aux = (*mapa);
                (*mapa) = menuAdmin(lista, aux);
            }
            else
            {
                //menu de personajes
                user->dato.lista = menuPersonaje(user, (*mapa));
            }
        }
        else
            lista = menu(lista, mapa);
        break;
    case 2:
        // registro de usuario
        lista = registrar(lista);
        lista = menu(lista, mapa);
        //recorrerYmostrarUsr(lista);
        break;
    case 3://NO USAR EXIT(0);
        break;
    }

    return lista;

}
//Funcion auxiliar orientada al registro y verificacion de datos del usuario.
nodoUsuario * registrar(nodoUsuario * lista)
{
    usuario user;
    int control = 0;

    Color(BLACK, LRED);
    printf("\n Registro de usuario \n");
    Color(BLACK, LGREY);

    do
    {
        printf("\n Ingrese nombre: ");
        fflush(stdin);
        scanf("%s", user.nombre);

        if(buscarNodoUsr(lista, user.nombre) == NULL)
            control++;

        else
            printf("\n Nombre de usuario ocupado. \n");

    } while(control==0);

    printf("\n Ingrese contraseña: ");
    fflush(stdin);
    scanf("%s", user.pass);

    user.lista = inicLista();
    user.idUser = generarIDUsuario(lista); //Funcion que cuente la cantidad de elementos de la lista y genere ID
    lista = agregarFinalUsr(lista, user);

    return lista;
}

//Funcion que genera el ID del usuario en funcion de su posicion en la lista.
int generarIDUsuario(nodoUsuario * lista)
{
    int res = 0;

    while(lista)
    {
        res++;
        lista = lista->siguiente;
    }

    return res;
}
//Funcion de inicio de sesion, valida que los datos sean correctos.
nodoUsuario * iniciarSesion(nodoUsuario * lista)
{
    nodoUsuario * res = inicListaUsr();

    if(lista)
    {
        char nombre[20];
        char pass[12];
        int validacion = 1;

        printf("\n Ingrese nombre: ");
        fflush(stdin);
        scanf("%s", nombre);

        res = buscarNodoUsr(lista, nombre);

        if(res)
        {
            do{
                printf("\n Ingrese contraseña o ingrese 0 para salir: ");
                fflush(stdin);
                scanf("%s", pass);

                if(strcmp(res->dato.pass, pass) != 0)
                    printf("\n La contraseña ingresada no es correcta.");

                else if(strcmp(pass, "0") == 0)
                {
                    validacion=0;
                    res = inicListaUsr();
                }
                else
                    validacion=0;;

            } while(validacion == 1);
        }
        else
            printf("\n El usuario ingresado no se encuentra registrado.");
    }

    return res;
}

int loginSel()
{
    int opcion=0;

    system("cls");
    Color(BLACK, LGREY);
    printf("\n Elige una opcion y presiona ENTER para seleccionar.\n\n");

    Color(BLACK, LRED);
    printf(" ---------------------------------------------------\n");
    printf("  _ _ _ _   _ _       _____                   (`-._o_.-')\n");
    printf(" | | | | |_|_| |_ ___|   __|___ ___ ___ ___    `--.|.--'\n");
    printf(" | | | |   | |  _| -_|__   | . | -_| .'|  _|     ( | )\n");
    printf(" |_____|_|_|_|_| |___|_____|  _|___|__,|_|        (|)\n");
    printf("                           |_|                    '|`\n");
    printf(" ---------------------------------------------------\n");
    Color(BLACK, LGREY);
    menuInicio();
    printf("\n Que quiere hacer?: ");
    scanf("%d",&opcion);
    if(opcion != 1 && opcion!=2 && opcion!=3)
    {
        printf("\n Opcion no valida.\n\n");
        system("pause");
        opcion = loginSel();
    }
    return opcion;
}

void menuInicio()
{
    printf("\n 1. Iniciar Sesion   \n");
    printf(" 2. Registrarse   \n");
    printf(" 3. Salir\n");
}
