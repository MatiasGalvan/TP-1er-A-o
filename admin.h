#ifndef ADMIN_H_INCLUDED
#define ADMIN_H_INCLUDED
#include "persistencia.h"
#include "nodoArbolZona.h"

nodoArbolZona * menuAdmin(nodoUsuario * lista, nodoArbolZona * mapa);
nodoArbolZona * agregarZona(nodoArbolZona * arbol);
nodoEnemigo * agregarEnemigo(nodoEnemigo * lista, int idZona);
int generarIDEnemigo(nodoEnemigo * lista);
void modificarZona(nodoArbolZona * mapa);
void modificarEnemigos(nodoArbolZona * mapa);

#endif // ADMIN_H_INCLUDED
