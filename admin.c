#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "admin.h"
#include "color.h"

//Menu general de la vista de administrador.
nodoArbolZona * menuAdmin(nodoUsuario * lista, nodoArbolZona * mapa)
{
    int sel = 0;
    int ctrl = 0;
    int aux = 0;

    do{
        system("cls");
        Color(BLACK, LRED);
        printf("\n MENU DE ADMIN\n");
        Color(BLACK, LGREY);
        printf("\n 1. Cargar zona.");
        printf("\n 2. Listar zonas.");
        printf("\n 3. Listar usuarios.");
        printf("\n 4. Modificar zona.");
        printf("\n 5. Modificar enemigo.");
        printf("\n 6. Borrar zona.");
        printf("\n 7. Borrar usuario.");
        printf("\n 9. Salir.");
        printf("\n");
        printf("\n Que desea hacer?: ");
        scanf("%d",&sel);

        switch(sel)
        {
        case 1:
            mapa = agregarZona(mapa);
            system("pause");
            break;
        case 2:
            preorder(mapa);
            system("pause");
            break;
        case 3:
            recorrerYmostrarUsr(lista);
            system("pause");
            break;
        case 4:
            modificarZona(mapa);
            break;
        case 5:
            modificarEnemigos(mapa);
            break;
        case 6:
            preorder(mapa);
            printf("\n Ingrese ID de zona a eliminar: ");
            scanf("%d",&aux);
            mapa = borrarNodoArbol(mapa, aux);
            printf("\n La zona se ha eliminado.\n");
            system("pause");
            break;
        case 7:
            system("cls");
            recorrerYmostrarUsr(lista);
            printf("\n Ingrese ID de usuario a eliminar: ");
            scanf("%d",&aux);
            lista = borrarNodo(lista, aux);
            printf("\n El usuario se ha eliminado.\n");
            system("pause");
            break;
        case 9:
            ctrl = 1;
            break;
        }
    } while(ctrl == 0);

    return mapa;
}

void modificarZona(nodoArbolZona * mapa)
{
    int sel = 0;
    int idZona = 0;
    nodoArbolZona * mod = inicArbolZona();

    system("cls");
    preorder(mapa);
    printf("\n Ingrese ID de zona a modificar: ");
    scanf("%d",&idZona);

    mod = buscarZonaPorId(mapa, idZona);

    if(mod)
    {
        system("cls");
        mostrarZona(mod->dato);
        printf("\n 1.- Cambiar nombre");
        printf("\n 2.- Cambiar descripcion");
        printf("\n\n Que quiere modificar?: ");
        scanf("%d",&sel);

        switch(sel)
        {
        case 1:
            printf("\n Ingrese nuevo nombre: ");
            fflush(stdin);
            gets(mod->dato.nombre);
            break;
        case 2:
            printf("\n Ingrese nueva descripcion: \n");
            fflush(stdin);
            gets(mod->dato.descripcion);
            break;
        }
    }
}

void modificarEnemigos(nodoArbolZona * mapa)
{
    int sel = 0;
    int idZona = 0;
    nodoArbolZona * mod = inicArbolZona();
    nodoEnemigo * lista = inicListaEnemigo();

    system("cls");
    preorder(mapa);
    printf("\n Ingrese ID de zona a modificar: ");
    scanf("%d",&idZona);

    mod = buscarZonaPorId(mapa, idZona);

    if(mod)
    {
        system("cls");
        lista = mod->dato.lista;
        recorrerYmostrarEnemigo(lista);

        printf("\n Ingrese ID de enemigo: ");
        scanf("%d",&sel);

        lista = buscarNodoPorIdEnemigo(lista, sel);

        if(lista)
        {
            system("cls");
            mostrarUnNodoEnemigo(lista);

            printf("\n 1.- Cambiar nombre");
            printf("\n 2.- Cambiar salud");
            printf("\n\n Que quiere modificar?: ");
            scanf("%d",&sel);

            switch(sel)
            {
            case 1:
                printf("\n Ingrese nuevo nombre: ");
                fflush(stdin);
                gets(mod->dato.nombre);
                break;
            case 2:
                printf("\n Ingrese salud: ");
                scanf("%d", &sel);
                lista->dato.salud = sel;
                break;
            }
        }
    }
}


//Agregar una zona, determinando  ID, Nombre, Descripcion y si se desea, Agregarle enemigos a la misma.
nodoArbolZona * agregarZona(nodoArbolZona * arbol)
{
    zona dato;
    char ctrl = 's';

    printf("\n Agregar zona: \n");

    printf("\n Ingrese ID: ");
    scanf("%d", &dato.idZona);

    printf("\n Ingrese nombre: ");
    fflush(stdin);
    gets(dato.nombre);

    printf("\n Ingrese descripcion: ");
    fflush(stdin);
    gets(dato.descripcion);

    dato.lista = inicListaEnemigo();

    do
    {
        dato.lista = agregarEnemigo(dato.lista, dato.idZona);

        printf("\n Desea continuar cargando?: ");
        fflush(stdin);
        scanf("%c", &ctrl);

    } while(ctrl == 's');

    arbol = insertarZona(arbol, dato);

    return arbol;
}
//Funcion de creacion de enemigos los cuales son asignados a una zona previamente creada.
nodoEnemigo * agregarEnemigo(nodoEnemigo * lista, int idZona)
{
    enemigo dato;

    printf("\n Agregar enemigo: \n");

    dato.idEnemigo = generarIDEnemigo(lista);
    dato.idZona = idZona;

    printf("\n Ingrese nombre: ");
    fflush(stdin);
    gets(dato.nombre);

    printf("\n Ingrese salud: ");
    fflush(stdin);
    scanf("%d", &dato.salud);

    lista = agregarFinalEnemigo(lista, dato);

    return lista;
}
//Funcion que genera un ID para un enemigo nuevo a partir de su posicion en la lista.
int generarIDEnemigo(nodoEnemigo * lista)
{
    int res = 0;

    while(lista)
    {
        res++;
        lista = lista->siguiente;
    }

    return res;
}
