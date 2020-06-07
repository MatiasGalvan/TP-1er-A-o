#ifndef NODOUSUARIO_H_INCLUDED
#define NODOUSUARIO_H_INCLUDED
#include "nodoPersonaje.h"

typedef struct //Pasar estructura a archivos.h y hacer el include
{
    int idUser;
    char nombre[20];
    char pass[12];
    nodoPersonaje * lista;
} usuario;

typedef struct _nodoUser
{
	usuario dato;
	struct _nodoUser * siguiente;
} nodoUsuario;

nodoUsuario * inicListaUsr();
nodoUsuario * crearNodoUsr( usuario dato);
nodoUsuario * agregarFinalUsr( nodoUsuario * lista, usuario dato);
nodoUsuario * buscarNodoUsr( nodoUsuario * lista, char nombre[]);
nodoUsuario * buscarUsuarioID( nodoUsuario * lista, int id);
nodoUsuario * buscarUltimoUsr( nodoUsuario * lista);
void mostrarUnNodoUsr( nodoUsuario * aux);
void recorrerYmostrarUsr( nodoUsuario * lista);
nodoUsuario * borrarNodo(nodoUsuario * lista, int idUser);

#endif // NODOUSUARIO_H_INCLUDED
