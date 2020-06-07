#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "nodoEnemigo.h"

//Funciones para el manejo de una lista de enemigos.
nodoEnemigo * inicListaEnemigo()
{
    return NULL;
}

nodoEnemigo * crearNodoEnemigo(enemigo dato)
{
    nodoEnemigo * aux = (nodoEnemigo*) malloc(sizeof(nodoEnemigo));
    aux->dato = dato;
    aux->siguiente = NULL;
    return aux;
}

nodoEnemigo * buscarUltimoEnemigo(nodoEnemigo * lista)
{
    nodoEnemigo * seg = lista;
    if(seg != NULL)
    {
        while(seg->siguiente != NULL)
        {
            seg = seg->siguiente;
        }
    }
    return seg;
}

nodoEnemigo * agregarFinalEnemigo(nodoEnemigo * lista, enemigo dato)
{
    if(lista == NULL)
    {
        lista = crearNodoEnemigo(dato);
    }
    else
    {
        nodoEnemigo * ultimo = buscarUltimoEnemigo(lista);
        ultimo->siguiente = crearNodoEnemigo(dato);
    }
    return lista;
}

void mostrarUnNodoEnemigo(nodoEnemigo * aux)
{
    printf("\n ID Enemigo: %d",aux->dato.idEnemigo);
    printf("\n ID de zona: %d",aux->dato.idZona);
    printf("\n Nombre: %s",aux->dato.nombre);
    printf("\n Salud: %d\n",aux->dato.salud);
}

void recorrerYmostrarEnemigo(nodoEnemigo * lista)
{
    nodoEnemigo * seg = lista;
    while(lista!=NULL && seg!=NULL)
    {
        mostrarUnNodoEnemigo(seg);
        seg=seg->siguiente;
    }
}

nodoEnemigo * buscarNodoPorIdEnemigo(nodoEnemigo * lista, int idEnemigo)
{
    nodoEnemigo * seg = lista;
    while(seg && seg->dato.idEnemigo != idEnemigo)
    {
        seg = seg->siguiente;
    }
    return seg;
}

nodoEnemigo * borrarListaEnemigos(nodoEnemigo * lista)
{
    nodoEnemigo * proximo;

    while(lista)
    {
        proximo = lista->siguiente;
        free(lista);
        lista = proximo;
    }

    return lista;
}

int contarEnemigosZona(nodoEnemigo * lista)
{
    int cont = 0;

    while(lista)
    {
        lista = lista->siguiente;
        cont++;
    }
    return cont;
}
