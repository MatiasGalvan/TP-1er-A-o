#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "personaje.h"
#include "persistencia.h"
#include "jugar.h"
#include "color.h"

//Funcion principal de creacion de personaje.
personaje crearPersonaje(nodoUsuario * lista)
{
    personaje P;
    printf("\n ---------------------------");
    printf("\n Creacion de personaje:");
    printf("\n ---------------------------\n");
    printf("\n Ingrese nombre: ");
    scanf("%s",P.nombre);
    system("cls");
    P = seleccionarRaza(P);
    P = seleccionarClase(P);
    P.nivel = 1;
    P.puntosExperiencia = 0;
    /*SUJETO A CAMBIOS XDDDDDDDDD
    A.idPersonaje=generarIDpersonaje(nombre_archivo);
    A.zonaActual=-1;*/
    P.idPersonaje = generarIDPersonaje(lista->dato.lista);
    P.tutorial = 0;
    P.puntosAsignar = 0;
    P.idUsuario = lista->dato.idUser;
    P.idZonaActual = 20;
    return P;
}
//Funcion para generar ID a partir de la posicion de la lista.
int generarIDPersonaje(nodoPersonaje * lista)
{
    int res = 0;

    while(lista)
    {
        res++;
        lista = lista->siguiente;
    }

    return res;
}
//Menu auxiliar de razas de personajes
void menuRazas()
{
    puts("\n -------------------------");
    printf(" 1.- Humano");
    printf("\n Mantiene estadisticas basicas de combate");
    puts("\n -------------------------");
    printf("\n Vitalidad: 100 puntos");
    printf("\n Fuerza: 10 puntos");
    printf("\n Defensa: 10 puntos");
    printf("\n Inteligencia: 10 puntos");
    puts("\n\n -------------------------");
    printf(" 2.- Orco");
    printf("\n Recibe un aumento de vitalidad y fuerza pero no es muy inteligente XD");
    puts("\n -------------------------");
    printf("\n Vitalidad: 120 puntos");
    printf("\n Fuerza: 20 puntos");
    printf("\n Defensa: 10 puntos");
    printf("\n Inteligencia: 0 puntos");
    puts("\n\n -------------------------");
    printf(" 3.- Elfo");
    printf("\n Obtiene mayor fuerza a costa de su baja salud y defensa");
    puts("\n -------------------------");
    printf("\n Vitalidad: 80 puntos");
    printf("\n Fuerza: 30 puntos");
    printf("\n Defensa: 10 puntos");
    printf("\n Inteligencia: 10 puntos");
    puts("\n\n -------------------------");

}
//Funcion para la seleccion de la raza y la consecuente asignacion de estadisticas.
personaje seleccionarRaza(personaje P)
{
    int seleccion=0;
    printf("\n RAZAS DISPONIBLES:\n");
    menuRazas();
    printf(" Ingrese raza: ");
    scanf("%d",&seleccion);
    switch(seleccion)
    {
    case 1:
        strcpy(P.raza,"Humano");
        P.fuerza=10;
        P.defensa=10;
        P.inteligencia=10;
        P.saludMaxima=100;
        P.salud=P.saludMaxima;
        break;
    case 2:
        strcpy(P.raza,"Orco");
        P.fuerza=20;
        P.defensa=10;
        P.inteligencia=0;
        P.saludMaxima=120;
        P.salud=P.saludMaxima;
        break;
    case 3:
        strcpy(P.raza,"Elfo");
        P.fuerza=30;
        P.defensa=10;
        P.inteligencia=10;
        P.saludMaxima=80;
        P.salud=P.saludMaxima;
        break;
    }
    return P;
}

//Funcion auxiliar de clases.
void menuClases()
{
    puts("\n -------------------------");
    printf(" 1.- Guerrero");
    printf("\n Se vale de una espada y escudo. Obtiene +5 puntos en ataque y defensa.");
    puts("\n -------------------------");
    printf(" 2.- Mago");
    printf("\n Utiliza un baston y su sombrero. Obtiene +10 puntos en inteligencia.");
    puts("\n -------------------------");
    printf(" 3.- Arquero");
    printf("\n Usando el arco, puede asestar letales golpes. Gana +10 puntos en fuerza.");
    puts("\n -------------------------");
}
//Funcion de seleccion de clase y posterior aplicacion de estadisticas.
personaje seleccionarClase(personaje P)
{
    int seleccion;
    system("cls");
    printf("\n CLASES DISPONIBLES:\n");
    menuClases();
    printf("\n Ingrese clase: ");
    scanf("%d",&seleccion);
    switch(seleccion)
    {
    case 1:
        strcpy(P.clase,"Guerrero");
        P.fuerza+=5;
        P.defensa+=5;
        break;
    case 2:
        strcpy(P.clase,"Mago");
        P.inteligencia+=10;
        break;
    case 3:
        strcpy(P.clase,"Arquero");
        P.fuerza+=10;
        break;
    }
    return P;
}
//Funcion de seleccion / creacion de personajes
nodoPersonaje * menuPersonaje(nodoUsuario * user, nodoArbolZona * mapa)
{
    int sel=0, selPJ=0;
    system("cls");

    Color(BLACK, LRED);
    printf("\n MENU DE PERSONAJES\n");
    Color(BLACK, LGREY);

    recorrerYmostrar(user->dato.lista);

    printf("\n 1. Elegir personaje.");
    printf("\n 2. Crear nuevo.");
    printf("\n 3. Eliminar personaje.");
    printf("\n 4. Salir.\n");
    printf("\n Que desea hacer?: ");
    scanf("%d",&sel);

    switch(sel)
    {
    case 1:
        printf("\n Que personaje desea elegir?: ");
        scanf("%d",&selPJ);
        nodoPersonaje * jugador = buscarNodoPorId(user->dato.lista,selPJ);
        if(jugador)
            jugador = inicioJuego(jugador, mapa);//personaje inicioJuego(a, archivoPersonajes);
        else
        {
            printf("\n Opcion no valida\n");
            system("pause");
            menuPersonaje(user, mapa);
        }
        break;
    case 2:
        system("cls");
        user->dato.lista = agregarFinal(user->dato.lista, crearPersonaje(user));
        //recorrerYmostrar(user->dato.lista);
        printf("\n Su personaje a sido creado. \n\n");
        system("pause");
        menuPersonaje(user, mapa);
        break;
    case 3:
        printf("\n Ingrese ID de personaje a eliminar: ");
        scanf("%d",&selPJ);
        user->dato.lista = borrarNodoPj(user->dato.lista, selPJ);
        printf("\n Su personaje a sido eliminado. \n\n");
        system("pause");
        menuPersonaje(user, mapa);
        break;
    case 4: //NO USAR EXIT(0);
        break;
    }

    return user->dato.lista;
}



