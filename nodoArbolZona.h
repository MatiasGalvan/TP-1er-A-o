#ifndef NODOARBOLZONA_H_INCLUDED
#define NODOARBOLZONA_H_INCLUDED
#include "nodoEnemigo.h"

typedef struct
{
    int idZona;
    char nombre[50];
    char descripcion[500];
    nodoEnemigo * lista;
}zona;

typedef struct _nodoArbolZona
{
    zona dato;
    struct _nodoArbolZona * izquierda;
    struct _nodoArbolZona * derecha;
} nodoArbolZona;


nodoArbolZona * inicArbolZona();
nodoArbolZona * crearNodoArbol(zona dato);
nodoArbolZona * insertarZona(nodoArbolZona * arbol, zona dato);
void preorder(nodoArbolZona * arbol);
void inorder(nodoArbolZona * arbol);
void postorder(nodoArbolZona * arbol);
nodoArbolZona * buscarZonaPorId(nodoArbolZona * arbol, int idZona);
nodoArbolZona * buscarZonaAnterior(nodoArbolZona * arbol, nodoArbolZona * actual);
void mostrarZona(zona dato);
void mostrarZonaJuego(zona dato);
nodoArbolZona * borrarNodoArbol(nodoArbolZona * arbol, int idZona);
nodoArbolZona * buscarMayor(nodoArbolZona * arbol);
nodoArbolZona * buscarMenor(nodoArbolZona * arbol);

//void mostrarPersona(persona dato);
#endif // NODOARBOLZONA_H_INCLUDED
