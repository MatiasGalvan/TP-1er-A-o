#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "nodoPersonaje.h"
#include "color.h"

//Funciones para el manejo de una lista de personajes.
nodoPersonaje * inicLista()
{
    return NULL;
}

nodoPersonaje * crearNodo(personaje dato)
{
    nodoPersonaje * aux = (nodoPersonaje*) malloc(sizeof(nodoPersonaje));
    aux->dato = dato;
    aux->siguiente = NULL;
    return aux;
}

nodoPersonaje * buscarUltimo(nodoPersonaje * lista)
{
    nodoPersonaje * seg = lista;
    if(seg != NULL)
    {
        while(seg->siguiente != NULL)
        {
            seg = seg->siguiente;
        }
    }
    return seg;
}

nodoPersonaje * agregarFinal(nodoPersonaje * lista, personaje dato)
{
    if(lista == NULL)
    {
        lista = crearNodo(dato);
    }
    else
    {
        nodoPersonaje * ultimo = buscarUltimo(lista);
        ultimo->siguiente = crearNodo(dato);
    }
    return lista;
}

void mostrarUnNodo(nodoPersonaje * aux)//sujeto a cambiosXDXD
{
    printf("\n PERSONAJE: %d",aux->dato.idPersonaje);
    Color(BLACK, LRED);
    puts("\n -------------------------");
    Color(BLACK, LGREY);
    printf(" Nombre: %s",aux->dato.nombre);
    printf("\n Raza: %s",aux->dato.raza);
    printf("\n Clase: %s",aux->dato.clase);
    printf("\n Nivel: %d",aux->dato.nivel);
    //printf("\n ID Usuario: %d",aux->dato.idUsuario);
    //printf("\n Salud: %d", aux->dato.salud);
    Color(BLACK, LRED);
    puts("\n -------------------------");
    Color(BLACK, LGREY);
}

void mostrarEstadisticas(nodoPersonaje * aux)
{
    Color(BLACK, LRED);
    printf("\n %s", aux->dato.nombre);
    printf("\n -------------------------");
    Color(BLACK, LGREY);
    printf("\n Nivel: %d",aux->dato.nivel);
    printf("\n Puntos a asignar: %d",aux->dato.puntosAsignar);
    printf("\n Puntos de experiencia: %d",aux->dato.puntosExperiencia);
    printf("\n Necesarios para el siguiente nivel: %d", (aux->dato.nivel*50) - aux->dato.puntosExperiencia);
    Color(BLACK, LGREEN); printf("\n Salud: %d / %d", aux->dato.salud, aux->dato.saludMaxima); Color(BLACK, LGREY);
    printf("\n\n Estadisticas: ");
    Color(BLACK, LRED); printf("\n \tFuerza: %d", aux->dato.fuerza);
    Color(BLACK, CYAN); printf("\n \tDefensa: %d", aux->dato.defensa);
    Color(BLACK, LGREEN); printf("\n \tInteligencia: %d", aux->dato.inteligencia);
    Color(BLACK, LRED);
    printf("\n ------------------------- \n\n");
    Color(BLACK, LGREY);
}

void recorrerYmostrar(nodoPersonaje * lista)
{
    nodoPersonaje * seg=lista;
    while(lista!=NULL && seg!=NULL)
    {
        mostrarUnNodo(seg);
        seg=seg->siguiente;
    }
}

nodoPersonaje * buscarNodoPorId(nodoPersonaje * lista, int idPersonaje)
{
    nodoPersonaje * seg = lista;
    while(seg!=NULL && seg->dato.idPersonaje != idPersonaje)
    {
        seg = seg->siguiente;
    }
    return seg;
}

nodoPersonaje * borrarNodoPj(nodoPersonaje * lista, int idPersonaje)
{
    nodoPersonaje * seg;
    nodoPersonaje * ante;

    if (lista && lista->dato.idPersonaje == idPersonaje)
    {
        nodoPersonaje * aux = lista;
        lista = lista->siguiente;
        free(aux);
    }
    else
    {
        seg = lista;
        while (seg && seg->dato.idPersonaje != idPersonaje)
        {
            ante = seg;
            seg = seg->siguiente;
        }
        if (seg)
        {
            ante->siguiente = seg->siguiente;
            nodoPersonaje * aux = seg->siguiente;

            while(aux)
            {
                aux->dato.idPersonaje--;
                aux = aux->siguiente;
            }
            free(seg);
        }
    }
    return lista;
}








