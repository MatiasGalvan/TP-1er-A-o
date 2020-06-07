#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "personaje.h"
#include "persistencia.h"
#include "nodoArbolZona.h"
#include "jugar.h"
#include "color.h"

nodoPersonaje * inicioJuego(nodoPersonaje * P, nodoArbolZona * mapa)
{
    int opcion = 0;

    if(P->dato.tutorial == 0)
    {
        P = tutorial(P);
    }

    do
    {
        system("cls");
        Color(BLACK, LGREY);
        menuOpciones();

        printf("\n Que deseas hacer?: ");
        scanf("%d",&opcion);
        system("cls");

        switch(opcion)
        {
        case 1:
            P = movimientos(P, mapa);
            P = eventos(P, mapa);
            break;
        case 2:
            P = asignarEstadisticas(P);
            system("pause");
            break;
        case 3:
            mostrarEstadisticas(P);
            system("pause");
            break;
        }

        comprobarNivel(P);
    }
    while(opcion !=4);

    return P;
}

nodoPersonaje * movimientos(nodoPersonaje * P, nodoArbolZona * mapa)
{
    nodoArbolZona * actual = inicArbolZona();
    actual = buscarZonaPorId(mapa, P->dato.idZonaActual);

    actual = comprobarMovimiento(mapa, actual);
    P->dato.idZonaActual = actual->dato.idZona;

    system("cls");
    mostrarZonaJuego(actual->dato);

    return P;
}

nodoArbolZona * comprobarMovimiento(nodoArbolZona * mapa, nodoArbolZona * actual)
{
    int ctrl = 0;
    int sel = 0;
    nodoArbolZona * izq = actual->izquierda;
    nodoArbolZona * der = actual->derecha;
    nodoArbolZona * ant = inicArbolZona();

    do
    {
        system("cls");
        printf("\n 1.- Seguir por izquierda.");
        printf("\n 2.- Seguir por derecha.");
        printf("\n 3.- Volver");

        printf("\n\n Que decides hacer?: ");
        scanf("%d",&sel);

        switch(sel)
        {
        case 1:
            if(izq)
            {
                printf("\n Te acercas a %s", izq->dato.nombre);
                actual = izq;
                ctrl++;
            }
            else
                printf("\n No es posible continuar por este camino.");
            break;
        case 2:
            if(der)
            {
                printf("\n Te acercas a %s", der->dato.nombre);
                actual = der;
                ctrl++;
            }
            else
                printf("\n No es posible continuar por este camino.");
            break;
        case 3:
            ant = buscarZonaAnterior(mapa, actual);
            if(ant != NULL)
            {
                printf("\n Vuelves a %s", ant->dato.nombre);
                actual = ant;
                ctrl++;
            }
            else
                printf("\n No puedes hacer eso.");
            break;
        }
        printf("\n\n");
        system("pause");

    }
    while(ctrl == 0);

    return actual;
}


///SUJETO A CAMBIOS--------------------------------------------------

nodoPersonaje * eventos(nodoPersonaje * P, nodoArbolZona * mapa)
{
    int evento = 0;
    int aux = 0;
    evento = rand() % 4 + 1;
    nodoEnemigo * E = inicListaEnemigo();
    //evento = 1;

    switch(evento)
    {
    case 1:
        P = encontrarCofre(P);
        break;
    case 2:
        aux = P->dato.idZonaActual;
        E = apareceEnemigoAleatorio(aux, mapa);
        P = pelea(P, E);
        if(P->dato.salud <= 0)
        {
            P->dato.salud = P->dato.saludMaxima/2;
        }
        break;
    case 3:
        aux = P->dato.idZonaActual;
        E = apareceEnemigoAleatorio(aux, mapa);
        P = pelea(P, E);
        if(P->dato.salud <= 0)
        {
            P->dato.salud = P->dato.saludMaxima/2;
        }
        break;
    case 4:
        if(P->dato.salud == P->dato.saludMaxima)
            printf("\n El camino esta despejado.");
        else
        {
            aux = recuperarVida(P, rand() % 20+5);
            printf("\n El camino esta despejado, recuperas %d puntos de salud.", aux);
        }
        printf("\n\n");
        break;
    }
    system("pause");

    return P;
}

nodoEnemigo * apareceEnemigoAleatorio(int idZonaActual, nodoArbolZona * mapa)
{
    nodoArbolZona * actual = inicArbolZona();
    actual = buscarZonaPorId(mapa,idZonaActual);
    int cantidadEnemigos = contarEnemigosZona(actual->dato.lista);
    int numAleatorio = rand() % cantidadEnemigos;
    nodoEnemigo * enemigo = buscarNodoPorIdEnemigo(actual->dato.lista, numAleatorio);
    return enemigo;
}

nodoPersonaje * pelea(nodoPersonaje * P, nodoEnemigo * E)
{
    int sel=0;
    int huir;
    int saludR=0;
    int xp=0;

    printf("\n Has encontrado %s. Salud %d\n",E->dato.nombre, E->dato.salud);
    sel = pelearOEscapar();

    switch(sel)
    {
    case 1:
        P = atacar(P, (*E));
        if(P->dato.salud > 0)
        {
            Color(BLACK, LGREEN);
            printf("\n Has vencido a %s", E->dato.nombre);
            if(P->dato.salud < P->dato.saludMaxima)
            {
                saludR = recuperarVida(P,rand() % 20+5);
                printf("\n Recuperas %d puntos de salud", saludR);
            }
            xp = rand() % 50+10;
            P->dato.puntosExperiencia += xp;
            printf("\n Ganas %d puntos de experiencia\n\n", xp);
            Color(BLACK, LGREY);
        }
        else
        {
            printf("\n %s te ha eliminado\n\n", E->dato.nombre);
        }
        break;
    case 2:
        huir = rand() % 2;
        if(huir==0)
        {
            printf("\n Escape con exito!\n");
        }
        else
        {
            printf("\n El escape no tuvo exito\n");
            P = enemigoAtaca(P, (*E));

            if(P->dato.salud <= 0)
            {
                Color(BLACK, RED);
                printf("\n %s te ha eliminado\n", P->dato.nombre);
                Color(BLACK, LGREY);
                system("pause");
            }
            else
            {
                system("pause");
                P = pelea(P, E);
            }
        }
        break;
    }

    return P;
}

int pelearOEscapar()
{
    int i=0;

    do{
        printf("\n 1.Pelear");
        printf("\n 2.Huir");
        printf("\n\n Que opcion desea elegir?: ");
        fflush(stdin);
        scanf("%d",&i);

        if(i!=1 && i!=2)
        {
            printf("\n Ingrese una opcion valida.\n\n");
            system("pause");
            system("cls");
        }
    }while(i!=1 && i!=2);

    return i;
}

//PERSONAJE ES EL A
//ENEMIGO ES EL B
nodoPersonaje * atacar(nodoPersonaje * P, nodoEnemigo E)
{
    int sel=0;
    int dmg=0;
    int saludExtra=0;

    do
    {
        printf("\n %s tiene %d puntos de vida\n", P->dato.nombre, P->dato.salud);
        printf("\n %s tiene %d puntos de vida\n", E.dato.nombre, E.dato.salud);
        printf("\n");
        system("pause");
        sel = menuAtaque();
        switch(sel)
        {
        case 1:
            dmg = (P->dato.fuerza+P->dato.inteligencia - rand() % 10);
            E.dato.salud -=dmg;
            printf("\n %s ataca a %s por un danio de %d\n", P->dato.nombre, E.dato.nombre, dmg);
            if(E.dato.salud <= 0)
            {
                printf("\n El enemigo ha caido \n\n");
            }
            break;
        case 2:
            saludExtra = P->dato.defensa + (rand() % 30 + 5);
            saludExtra = recuperarVida(P, saludExtra);
            printf("\n El jugador %s recupera %d puntos de salud\n\n", P->dato.nombre, saludExtra);
            break;
        }

        if(E.dato.salud > 0)
        {
            P = enemigoAtaca(P,E);
        }
        system("pause");

    }
    while(P->dato.salud>0 && E.dato.salud>0);

    return P;
}

nodoPersonaje * enemigoAtaca(nodoPersonaje * P, nodoEnemigo E)
{
    int dmg=0;
    dmg = P->dato.fuerza + P->dato.inteligencia - (rand() % 10+15);
    P->dato.salud -= dmg;
    printf("\n %s ataca a %s por un danio de %d\n\n", E.dato.nombre, P->dato.nombre, dmg);
    return P;
}

int menuAtaque() //Menu de ataque
{
    int i=0;
    system("cls");
    printf("\n -----------");
    Color(BLACK, CYAN);
    printf("\n 1. Atacar");
    printf("\n 2. Defender");
    Color(BLACK, LGREY);
    printf("\n -----------");
    printf("\n\n Que opcion desea elegir?: ");
    scanf("%d",&i);
    return i;
}

nodoPersonaje * encontrarCofre(nodoPersonaje * P)
{
    char decision = 's';
    int resultado = 0;
    resultado = rand() % 2 + 1;
    Color(BLACK, MAGENTA);
    printf("\n Aparece un cofre misterioso, queres abrirlo?: ");
    fflush(stdin);
    scanf("%c",&decision);
    Color(BLACK, LGREY);

    if(decision == 's')
    {
        if(resultado == 1)
        {
            Color(BLACK, RED);
            printf("\n Era una trampa!, se restan 10 puntos de salud.\n\n");
            P->dato.salud-=10;
        }
        else
        {
            Color(BLACK, LGREEN);
            printf("\n Felicidades!! , obtienes 1 puntos para asignar a tus estadisticas.\n\n");
            P->dato.puntosAsignar+=1;
        }
    }
    Color(BLACK, LGREY);

    return P;
}

int recuperarVida(nodoPersonaje * P, int curacion)
{
    if(P->dato.salud + curacion > P->dato.saludMaxima)
    {
        curacion = P->dato.saludMaxima - P->dato.salud;
        P->dato.salud = P->dato.saludMaxima;
    }
    else
        P->dato.salud += curacion;

    return curacion;
}



///SUJETO A CAMBIOS--------------------------------------------------


nodoPersonaje * asignarEstadisticas(nodoPersonaje * P)
{
    //  Color(BLACK,YELLOW);
    int opcion = 0;
    int asignar = 0;

    system("cls");
    mostrarEstadisticas(P);
    menuEstadisticas();

    if(P->dato.puntosAsignar > 0)
    {
        printf("\n Usted dispone de %d puntos \n", P->dato.puntosAsignar);
        printf("\n Que estadistica desea asignar?: ");
        scanf("%d",&opcion);

        printf("\n Cuantos puntos desea asignar?: ");
        scanf("%d",&asignar);

        while(opcion != 1 && opcion != 2 && opcion != 3)
        {
            printf("\n Ingrese una opcion valida: ");
            scanf("%d",&opcion);
        }

        while(asignar > P->dato.puntosAsignar)
        {
            printf("\n No tiene suficientes puntos que asignar, ingrese otro valor: ");
            scanf("%d",&asignar);
        }

        switch(opcion)
        {
        case 1:

            P->dato.fuerza+=asignar;
            P->dato.puntosAsignar-=asignar;
            break;
        case 2:
            P->dato.defensa+=asignar;
            P->dato.puntosAsignar-=asignar;
            break;
        case 3:
            P->dato.inteligencia+=asignar;
            P->dato.puntosAsignar-=asignar;
            break;
        }
    }
    else
    {
        printf("\n No tiene puntos para asignar\n");
    }

    return P;
}

void menuEstadisticas()
{
    puts("\n -------------------------");
    printf(" 1.- Fuerza");
    printf("\n 2.- Defensa");
    printf("\n 3.- Inteligencia");
    puts("\n -------------------------");
}

nodoPersonaje * tutorial(nodoPersonaje * P)
{
    system("cls");
    char control='s';
    printf("\n Bienvenido a WhiteSpear, parece que es tu primera vez aqui, queres ver las instrucciones? s/n: ");
    fflush(stdin);
    scanf("%c",&control);
    if(control == 's' || control=='S')
    {
        system("cls");
        P->dato.tutorial = 1;
        menuTutorial();
        system("pause");
    }
    return P;
}

void menuTutorial()
{
    Color(BLACK,LBLUE);
    puts("\n ----------------------------------------------------------------------------------------------------------------");
    Color(BLACK,YELLOW); printf(" Moverte: "); Color(BLACK,LBLUE);
    printf("Tienes la opcion de ir hacia izquierda, derecha o volver, en cada movimiento puede ocurrir algun evento.\n");
    Color(BLACK,YELLOW); printf(" Asignar estadisticas: ");Color(BLACK,LBLUE);
    printf("Podras asignar puntos a las estadisticas de tu personaje conforme subas de nivel.\n");
    Color(BLACK,YELLOW); printf(" Ver estado: ");Color(BLACK,LBLUE);
    printf("Puedes revisar el estado de tu personaje, sus estadisticas y vitalidad.\n");
    printf(" Si tu salud llega a cero, ");
    Color(BLACK,LRED); printf("se termina el juego.\n"); Color(BLACK,LBLUE);
    printf(" Iras ganando ");
    Color(BLACK,LGREEN);printf("experiencia ");Color(BLACK,LBLUE);printf("conforme ganes distintos combates.");
    puts("\n ----------------------------------------------------------------------------------------------------------------");
    Color(BLACK,WHITE);
}


void comprobarNivel(nodoPersonaje * P)
{
    if(P->dato.puntosExperiencia >= P->dato.nivel * 50)
    {
        P->dato.puntosExperiencia-=P->dato.nivel * 50;
        P->dato.saludMaxima += 5;
        P->dato.puntosAsignar+=2;
        P->dato.nivel++;
        Color(BLACK, MAGENTA);
        printf("\n Has subido a nivel %d, has obtenido 2 puntos de habilidad y 5 de salud\n\n", P->dato.nivel);
        Color(BLACK, LGREY);
        system("pause");
    }
}

void menuOpciones()
{
    //Color(BLACK,YELLOW);
    printf("\n 1.- Moverte");
    printf("\n 2.- Asignar estadisticas");
    printf("\n 3.- Ver estado del personaje");
    printf("\n 4.- Salir.\n");
}



