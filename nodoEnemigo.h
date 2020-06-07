#ifndef NODOENEMIGO_H_INCLUDED
#define NODOENEMIGO_H_INCLUDED

typedef struct
{
    int idEnemigo;
    int idZona;
    char nombre[50];
    int salud;
} enemigo;

typedef struct _nodoEnemigo{
    enemigo dato;
    struct _nodoEnemigo * siguiente;
} nodoEnemigo ;

nodoEnemigo * inicListaEnemigo();
nodoEnemigo * crearNodoEnemigo(enemigo dato);
nodoEnemigo * buscarUltimoEnemigo(nodoEnemigo * lista);
nodoEnemigo * agregarFinalEnemigo(nodoEnemigo * lista, enemigo dato);
void mostrarUnNodoEnemigo(nodoEnemigo * aux);
void recorrerYmostrarEnemigo(nodoEnemigo * lista);
nodoEnemigo * buscarNodoPorIdEnemigo(nodoEnemigo * lista, int idEnemigo);
nodoEnemigo * borrarListaEnemigos(nodoEnemigo * lista);
int contarEnemigosZona(nodoEnemigo * lista);

#endif // NODOENEMIGO_H_INCLUDED
