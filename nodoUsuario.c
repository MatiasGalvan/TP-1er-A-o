#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "nodoUsuario.h"


//Funciones para el manejo de una lista de usuarios.
nodoUsuario * inicListaUsr()
{
    return NULL;
}

nodoUsuario * crearNodoUsr( usuario dato)
{
    nodoUsuario * aux = (nodoUsuario *) malloc(sizeof(nodoUsuario));
    aux->dato = dato;
    aux->siguiente = NULL;
    return aux;
}

nodoUsuario * agregarFinalUsr( nodoUsuario * lista, usuario dato)
{
    if (lista == NULL)
    {
        lista = crearNodoUsr(dato);
    }
    else
    {
        nodoUsuario * ultimo = buscarUltimoUsr(lista);
        ultimo->siguiente = crearNodoUsr(dato);
    }
    return lista;
}

void mostrarUnNodoUsr( nodoUsuario * aux)
{
    printf("\n Usuario: ");
    printf("\n ID: %d \n Nombre: %s \n Pass: %s\n",aux->dato.idUser, aux->dato.nombre, aux->dato.pass);
}

void recorrerYmostrarUsr( nodoUsuario * lista)
{
    nodoUsuario * seg = lista;
    while(seg)
    {
        mostrarUnNodoUsr(seg);
        recorrerYmostrar(seg->dato.lista);
        seg = seg->siguiente;
    }
}

nodoUsuario * buscarNodoUsr( nodoUsuario * lista, char nombre[])
{
    nodoUsuario * seg = lista;
    if(lista)
    {
        while(seg!=NULL && strcmp(seg->dato.nombre, nombre) != 0)
        {
            seg = seg->siguiente;
        }
    }
    return seg;
}

nodoUsuario * buscarUsuarioID( nodoUsuario * lista, int id)
{
    nodoUsuario * seg = lista;
    if(lista)
    {
        while(seg!=NULL && id != seg->dato.idUser)
        {
            seg = seg->siguiente;
        }
    }
    return seg;
}

nodoUsuario * buscarUltimoUsr( nodoUsuario * lista)
{
    nodoUsuario * seg = lista;
    if (seg != NULL)
    {
        while (seg->siguiente != NULL)
        {
            seg = seg->siguiente;
        }
    }
    return seg;
}

nodoUsuario * borrarNodo(nodoUsuario * lista, int idUser)
{
    nodoUsuario * seg;
    nodoUsuario * ante;

    if (lista && lista->dato.idUser == idUser)
    {
        nodoUsuario * aux = lista;
        lista = lista->siguiente;
        free(aux);
    }
    else
    {
        seg = lista;
        while (seg && seg->dato.idUser != idUser)
        {
            ante = seg;
            seg = seg->siguiente;
        }
        if (seg)
        {
            ante->siguiente = seg->siguiente;
            free(seg);
        }
    }
    return lista;
}

