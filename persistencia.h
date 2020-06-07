#ifndef PERSISTENCIA_H_INCLUDED
#define PERSISTENCIA_H_INCLUDED
#include "login.h"
#include "nodoArbolZona.h"

//levantar todo ();
void usuariosToArchivo(nodoUsuario * lista);
nodoUsuario * levantarUsuarios(nodoUsuario * lista);
void personajesToArchivo(nodoPersonaje * lista);
nodoUsuario * levantarPersonajes(nodoUsuario * lista);

void zonasToArchivo(nodoArbolZona * arbol);
void grabarZona(nodoArbolZona * arbol);
void enemigosToArchivo(nodoEnemigo * lista);
nodoArbolZona * levantarZonas(nodoArbolZona * arbol);
nodoArbolZona * levantarEnemigos(nodoArbolZona * arbol);
void vaciarArchivos();

#endif // PERSISTENCIA_H_INCLUDED
