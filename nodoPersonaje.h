#ifndef NODOPERSONAJE_H_INCLUDED
#define NODOPERSONAJE_H_INCLUDED
#include "nodoArbolZona.h"

typedef struct
{
    int idPersonaje;
    int idUsuario;
    int idZonaActual; //Guarda la zona en la que se encuentra el personaje
    char nombre[20];
    char raza[20];
    char clase[20];
    int fuerza;
    int defensa;
    int inteligencia;
    int nivel;
    int puntosExperiencia;
    int salud;
    int saludMaxima;
    int tutorial; //Guarda si el personaje ya vio el tutorial para no mostrarlo de nuevo
    int puntosAsignar;
} personaje;


typedef struct _nodoPersonaje
{
	personaje dato;
	struct _nodoPersonaje * siguiente;
} nodoPersonaje;

nodoPersonaje * inicLista();
nodoPersonaje * crearNodo (personaje dato);
nodoPersonaje * buscarUltimo(nodoPersonaje * lista);
nodoPersonaje * agregarFinal(nodoPersonaje * lista,personaje dato);
void mostrarUnNodo(nodoPersonaje * aux);
void recorrerYmostrar(nodoPersonaje * lista);
nodoPersonaje * buscarNodoPorId(nodoPersonaje * lista, int idPersonaje);
void mostrarEstadisticas(nodoPersonaje * aux);
nodoPersonaje * borrarNodoPj(nodoPersonaje * lista, int idPersonaje);

#endif // NODOPERSONAJE_H_INCLUDED
