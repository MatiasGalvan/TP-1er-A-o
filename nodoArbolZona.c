#include <stdio.h>
#include <stdlib.h>
#include "nodoArbolZona.h"

//Funciones relacionadas a la creacion y busqueda de zonas del mapa.

nodoArbolZona * inicArbolZona()
{
    return NULL;
}

nodoArbolZona * crearNodoArbolZona(zona dato)
{
    nodoArbolZona * aux = (nodoArbolZona*) malloc(sizeof(nodoArbolZona));

    aux->dato = dato;
    aux->izquierda = NULL;
    aux->derecha = NULL;
    return aux;
}

nodoArbolZona * insertarZona(nodoArbolZona * arbol, zona dato)
{
    if(!arbol)
    {
        arbol = crearNodoArbolZona(dato);
    }
    else
    {
        if(dato.idZona > arbol->dato.idZona)
            arbol->derecha = insertarZona(arbol->derecha, dato);
        else
            arbol->izquierda= insertarZona(arbol->izquierda, dato);
    }
    return arbol;
}

void preorder(nodoArbolZona * arbol)
{
    if(arbol)
    {
        mostrarZona(arbol->dato);
        preorder(arbol->izquierda);
        preorder(arbol->derecha);
    }
}

void inorder(nodoArbolZona * arbol)
{
    if(arbol)
    {
        inorder(arbol->izquierda);
        mostrarZona(arbol->dato);
        inorder(arbol->derecha);
    }
}

void postorder(nodoArbolZona * arbol)
{
    if(arbol)
    {
        postorder(arbol->izquierda);
        postorder(arbol->derecha);
        mostrarZona(arbol->dato);
    }
}

void mostrarZona(zona dato)
{
    printf("\n ZONA: %d", dato.idZona);
    puts("\n -------------------------");
    printf(" Nombre: %s",dato.nombre);
    printf("\n Descripcion: %s\n", dato.descripcion);
    recorrerYmostrarEnemigo(dato.lista);
    puts(" -------------------------");
}

nodoArbolZona * buscarZonaPorId(nodoArbolZona * arbol, int idZona)
{
   nodoArbolZona * aux = inicArbolZona();

    if(arbol)
    {
        if(idZona == arbol->dato.idZona)
        {
            aux = arbol;
        }
        else
        {
            if(idZona > arbol->dato.idZona)
                aux = buscarZonaPorId(arbol->derecha, idZona);

            else
                aux = buscarZonaPorId(arbol->izquierda, idZona);
        }
    }

    return aux;
}

//Retorna la zona anteriormente visitada, de esta manera  el jugador puede volver si lo desea.
nodoArbolZona * buscarZonaAnterior(nodoArbolZona * arbol, nodoArbolZona * actual)
{
    nodoArbolZona * aux = inicArbolZona();

    if(arbol)
    {
        if(arbol->derecha == actual || arbol->izquierda == actual)
        {
            aux = arbol;
        }
        else
        {
            if(actual->dato.idZona > arbol->dato.idZona)
                aux = buscarZonaAnterior(arbol->derecha, actual);

            else
                aux = buscarZonaAnterior(arbol->izquierda, actual);
        }
    }

    return aux;
}

void mostrarZonaJuego(zona dato)
{
    printf("\n ---------------------- \n");
    printf(" %s ",dato.nombre);
    printf("\n ---------------------- \n");
    printf("\n %s \n", dato.descripcion);
    printf("\n ---------------------- \n");
}

nodoArbolZona * buscarMenor(nodoArbolZona * arbol)
{
    nodoArbolZona * aux = inicArbolZona();

    if(arbol)
    {
        if(arbol->izquierda)
            aux = buscarMenor(arbol->izquierda);
        else
            aux = arbol;
    }
    return aux;
}

nodoArbolZona * buscarMayor(nodoArbolZona * arbol)
{
    nodoArbolZona * aux = inicArbolZona();

    if(arbol)
    {
        if(arbol->derecha)
            aux = buscarMayor(arbol->derecha);
        else
            aux = arbol;
    }
    return aux;
}

nodoArbolZona * borrarNodoArbol(nodoArbolZona * arbol, int idZona)
{
    nodoArbolZona * aux = inicArbolZona();

    if(arbol)
    {
        if(idZona < arbol->dato.idZona)
        {
            arbol->izquierda = borrarNodoArbol(arbol->izquierda, idZona);
        }
        else if(idZona > arbol->dato.idZona)
        {
            arbol->derecha = borrarNodoArbol(arbol->derecha, idZona);
        }
        else
        {
            if(!arbol->izquierda && !arbol->derecha)
            {
                arbol->dato.lista = borrarListaEnemigos(arbol->dato.lista);
                free(arbol);
                arbol = NULL;
            }
            else
            {
                if(arbol->izquierda)
                {
                    aux = buscarMayor(arbol->izquierda);
                    arbol->dato = aux->dato;
                    aux->dato.lista = NULL;
                    arbol->izquierda = borrarNodoArbol(arbol->izquierda, aux->dato.idZona);
                }
                else if(arbol->derecha)
                {
                    aux = buscarMenor(arbol->derecha);
                    arbol->dato = aux->dato;
                    aux->dato.lista = NULL;
                    arbol->derecha = borrarNodoArbol(arbol->derecha, aux->dato.idZona);
                }
            }
        }
    }

    return arbol;
}


