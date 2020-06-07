#include <stdio.h>
#include <stdlib.h>
#include "persistencia.h"

const char archivoUsuarios[] = "usuarios.bin";
const char archivoPersonajes[] = "personajes.bin";
const char archivoZonas[] = "zonas.bin";
const char archivoEnemigos[] = "enemigos.bin";


///no agregar los const char en persistencia.h porque da error de compilacion
//Funcion que baja todos los datos de los usuarios al archivo
void usuariosToArchivo(nodoUsuario * lista)
{
    FILE * archi = fopen(archivoUsuarios, "a+b");
    usuario user;

    if(archi)
    {
        while(lista)
        {
            personajesToArchivo(lista->dato.lista);
            user = lista->dato;
            user.lista = NULL;
            fwrite(&user, sizeof(usuario), 1, archi);
            lista = lista->siguiente;
        }
        fclose(archi);
    }
}
//Funcion que baja todos los personajes de cada usuario al archivo
void personajesToArchivo(nodoPersonaje * lista)
{
    FILE * archi = fopen(archivoPersonajes, "a+b");
    personaje pj;

    if(archi)
    {
        while(lista)
        {
            pj = lista->dato;
            fwrite(&pj, sizeof(personaje), 1, archi);
            lista = lista->siguiente;
        }
        fclose(archi);
    }
}
//Funcion que levanta los usuarios de un archivo a una lista.
nodoUsuario * levantarUsuarios(nodoUsuario * lista)
{
    FILE * archi = fopen(archivoUsuarios, "rb");
    usuario user;

    if(archi)
    {
        while (fread(&user, sizeof(usuario), 1, archi) > 0)
        {
            user.lista = inicLista();
            lista = agregarFinalUsr(lista, user);
        }
        fclose(archi);
    }
    return lista;
}
//Funcion que levanta los personajes, los agrega a una lista
//que a su vez se agrega al usuario que pertenecen.
nodoUsuario * levantarPersonajes(nodoUsuario * lista) /// Paso la lista de usuarios para poder buscar a que user pertenece cada personaje
{
    FILE * archi = fopen(archivoPersonajes, "rb");
    personaje pj;
    nodoUsuario * aux = inicListaUsr();

    if(archi)
    {
        while (fread(&pj, sizeof(personaje), 1, archi) > 0)
        {
            aux = buscarUsuarioID(lista, pj.idUsuario);
            aux->dato.lista = agregarFinal(aux->dato.lista, pj);
        }
        fclose(archi);
    }

    return lista;
}
//Funcion que baja la informacion de las Zonas a un archivo y recorre el arbol
void zonasToArchivo(nodoArbolZona * arbol)
{
    if(arbol)
    {
        grabarZona(arbol);
        zonasToArchivo(arbol->izquierda);
        zonasToArchivo(arbol->derecha);
    }
}
//Funcion auxiliar de zonasToArchivo
void grabarZona(nodoArbolZona * arbol)
{
    FILE * archi = fopen(archivoZonas, "a+b");
    zona dato;

    if(archi)
    {
        enemigosToArchivo(arbol->dato.lista);
        dato = arbol->dato;
        dato.lista = NULL;
        fwrite(&dato, sizeof(zona), 1, archi);

        fclose(archi);
    }
}
//Funcion que baja la lista de enemigos al archivo.
void enemigosToArchivo(nodoEnemigo * lista)
{
    FILE * archi = fopen(archivoEnemigos, "a+b");
    enemigo dato;

    if(archi)
    {
        while(lista)
        {
            dato = lista->dato;
            fwrite(&dato, sizeof(enemigo), 1, archi);
            lista = lista->siguiente;
        }
        fclose(archi);
    }
}
//Funcion que levanta las zonas del archivo y carga la lista de enemigos y el arbol de zonas.
nodoArbolZona * levantarZonas(nodoArbolZona * arbol)
{
    FILE * archi = fopen(archivoZonas, "rb");
    zona dato;

    if(archi)
    {
        while (fread(&dato, sizeof(zona), 1, archi) > 0)
        {
            dato.lista = inicListaEnemigo();
            arbol = insertarZona(arbol, dato);
        }
        fclose(archi);
    }

    return arbol;
}
//Funcion auxiliar que lee los enemigos del archivo.
nodoArbolZona * levantarEnemigos(nodoArbolZona * arbol)
{
    FILE * archi = fopen(archivoEnemigos, "rb");
    enemigo dato;
    nodoArbolZona * aux = inicArbolZona();

    if(archi)
    {
        while (fread(&dato, sizeof(enemigo), 1, archi) > 0)
        {
            aux = buscarZonaPorId(arbol, dato.idZona);
            aux->dato.lista = agregarFinalEnemigo(aux->dato.lista, dato);
        }
        fclose(archi);
    }

    return arbol;
}
//Funcion para borrar todos los archivos, de esta manera al finalizar el juego
//se vuelve a bajar toda la informacion.
void vaciarArchivos()
{
    remove(archivoUsuarios);
    remove(archivoPersonajes);
    remove(archivoZonas);
    remove(archivoEnemigos);
}
