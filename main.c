#include <stdio.h>
#include <stdlib.h>
#include "persistencia.h"

int main()
{
    nodoUsuario * lista = inicListaUsr();
    nodoArbolZona * mapa = inicArbolZona();
    lista = levantarUsuarios(lista);
    lista = levantarPersonajes(lista);
    mapa = levantarZonas(mapa);
    mapa = levantarEnemigos(mapa);
    /*recorrerYmostrarUsr(lista);
    system("pause");
    preorder(mapa);
    system("pause");*/

    lista = menu(lista, &mapa);

    /* Prueba de buscar zona anterior
    nodoArbolZona * aux = NULL;
    aux = buscarZonaPorId(mapa, 85);
    aux = buscarZonaAnterior(mapa, aux);
    printf("\n%d\n", aux->dato.idZona);*/

    vaciarArchivos();
    usuariosToArchivo(lista);
    zonasToArchivo(mapa);

    return 0;
}
