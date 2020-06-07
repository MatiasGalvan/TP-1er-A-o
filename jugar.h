#ifndef JUGAR_H_INCLUDED
#define JUGAR_H_INCLUDED

nodoPersonaje * inicioJuego(nodoPersonaje * P, nodoArbolZona * mapa);
nodoPersonaje * asignarEstadisticas(nodoPersonaje * P);
void menuEstadisticas();
nodoPersonaje * tutorial(nodoPersonaje * P);
void menuTutorial();
void comprobarNivel(nodoPersonaje * P);
void menuOpciones();
nodoPersonaje * encontrarCofre(nodoPersonaje * P);
int recuperarVida(nodoPersonaje * P,int curacion);
nodoPersonaje * movimientos(nodoPersonaje * P, nodoArbolZona * mapa);
nodoArbolZona * comprobarMovimiento(nodoArbolZona * mapa, nodoArbolZona * actual);
nodoPersonaje * eventos(nodoPersonaje * P, nodoArbolZona * mapa);
nodoEnemigo * apareceEnemigoAleatorio(int idZonaActual, nodoArbolZona * mapa);
nodoPersonaje * pelea(nodoPersonaje * P, nodoEnemigo * E);
nodoPersonaje * atacar(nodoPersonaje * P, nodoEnemigo E);
nodoPersonaje * enemigoAtaca(nodoPersonaje * P, nodoEnemigo E);
int pelearOEscapar();
int menuAtaque();

#endif // JUGAR_H_INCLUDED
