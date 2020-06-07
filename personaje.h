#ifndef PERSONAJE_H_INCLUDED
#define PERSONAJE_H_INCLUDED
#include "nodoPersonaje.h"
#include "nodoUsuario.h"

personaje crearPersonaje(nodoUsuario * lista);
personaje seleccionarRaza(personaje P);
personaje seleccionarClase(personaje P);
nodoPersonaje * menuPersonaje(nodoUsuario * user, nodoArbolZona * mapa);
int generarIDPersonaje(nodoPersonaje * lista);

#endif // PERSONAJE_H_INCLUDED
