#ifndef LOGIN_H_INCLUDED
#define LOGIN_H_INCLUDED
#include "nodoUsuario.h"
#include "nodoArbolZona.h"

nodoUsuario * menu(nodoUsuario * lista, nodoArbolZona * * mapa);
nodoUsuario * iniciarSesion(nodoUsuario * lista);
nodoUsuario * registrar(nodoUsuario * lista);
int generarIDUsuario(nodoUsuario * lista);
void menuInicio();
int loginSel();

#endif // LOGIN_H_INCLUDED
