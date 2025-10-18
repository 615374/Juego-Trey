#ifndef JUEGO_H
#define JUEGO_H

#include <string>
using namespace std;

const int MAX_JUGADORES = 2;
const int MAX_DADOS = 3;

struct Jugador {
    string nombre;
    int PT;
    int bugs;
    int puntajeTotal;
    int cartaObjetivo;
    int puntosRonda;
    int lanzamientos;
};

// Menú principal y utilidades
void mostrarMenuPrincipal();
void jugarPartida();
void mostrarEstadisticas();
void mostrarCreditos();
bool confirmarSalida();
void inicializarAleatorio();

// Jugabilidad

void jugarPartida(Jugador jugadores[], int cantidad);
void cargarJugadores(Jugador jugadores[], int cantidad);
void asignarCartaProyecto(Jugador& jugador);
void tirarDados(int dados[], int cantidad);
void mostrarDados(const int dados[], int cantidad);
int contarBUGS(const int dados[], int cantidad);
int contarFIXES(const int dados[], int cantidad);
bool elegirLanzamiento(int& cantidadElegida, const Jugador& jugador);
void aplicarEfectoBUG(Jugador& jugador, int cantidadBUGS);
void aplicarEfectoFIX(Jugador& jugador, int cantidadFIXES);
void resolverTirada(Jugador& jugador, const int dados[], int cantidadDados);
void jugarTurno(Jugador& jugador);
void mostrarTablaFinal(Jugador jugadores[], int cantidad);

#endif
