#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include "juego.h"

using namespace std;

// Variables para estadística
string ultimoGanador = "";
int puntajeGanador = 0;

// ---------------- UTILIDADES ----------------

void inicializarAleatorio() {
    srand(static_cast<unsigned int>(time(0)));
}

// ---------------- MENÚ ----------------

void mostrarMenuPrincipal() {
    cout << "\n========= TREY =========\n";
    cout << "1 - JUGAR\n";
    cout << "2 - ESTADISTICAS\n";
    cout << "3 - CREDITOS\n";
    cout << "0 - SALIR\n";
    cout << "========================\n";
    cout << "Seleccione una opción: ";
}

void mostrarCreditos() {
    cout << "\n--- Créditos ---\n";
    cout << "Equipo de Desarrollo:\n";
    cout << " - Burolleau, Ana (Legajo Nº 32466)\n";
    cout << " - Lamonaca, Lautaro (Legajo Nº  32388)\n";
    cout << " - Lanzillotta, Gisela (Legajo Nº 32372)\n";
    cout << " - Zahlut, Pablo (Legajo Nº 32449)\n";
}

bool confirmarSalida() {
    char opcion;
    cout << "¿Está seguro que desea salir? (S/N): ";
    cin >> opcion;
    return (opcion == 'S' || opcion == 's');
}

// ---------------- JUEGO ----------------



// --------------------- PARTIDA -------------------------

// Versión sin parámetros, llamada desde el main
void jugarPartida() {
    Jugador jugadores[MAX_JUGADORES];
    int cantidad = MAX_JUGADORES;

    cargarJugadores(jugadores, cantidad);
    jugarPartida(jugadores, cantidad); // Llama a la sobrecargada
}

// Función principal de la partida
void jugarPartida(Jugador jugadores[], int cantidad) {
    const int MAX_RONDAS = 10;
    int ronda = 1;
    bool partidaActiva = true;

    while (partidaActiva && ronda <= MAX_RONDAS) {
        cout << "\n===== RONDA " << ronda << " =====\n";

        for (int i = 0; i < cantidad; i++) {
            Jugador& jugador = jugadores[i];

            cout << "\n--- TURNO DE " << jugador.nombre << " ---\n";

            if (jugador.PT <= 0) {
                cout << jugador.nombre << " se quedó sin PT y no puede continuar esta ronda.\n";
                continue;
            }

            bool seguir = true;

            while (seguir && jugador.PT > 0) {
                int cantidadDados;
                if (!elegirLanzamiento(cantidadDados, jugador))
                    break;

                jugador.PT -= (cantidadDados == 2 ? 1 : 2);
                jugador.lanzamientos++;

                int dados[3];
                tirarDados(dados, cantidadDados);
                mostrarDados(dados, cantidadDados);

                int bugs = contarBUGS(dados, cantidadDados);
                int fixes = contarFIXES(dados, cantidadDados);

                if (bugs > 0) {
                    cout << "\n¡BUGS! Pierdes los puntos de esta ronda.\n";
                    jugador.puntosRonda = 0;
                    aplicarEfectoBUG(jugador, bugs);
                    seguir = false;
                } else {
                    int total = 0;
                    for (int d = 0; d < cantidadDados; d++) total += dados[d];

                    jugador.puntosRonda += total;
                    cout << "Puntos obtenidos: " << total << "\n";
                    aplicarEfectoFIX(jugador, fixes);

                    char continuar;
                    cout << "¿Desea seguir lanzando? (S/N): ";
                    cin >> continuar;

                    if (continuar == 'N' || continuar == 'n') {
                        seguir = false;
                    }
                }
            }

            jugador.puntajeTotal += jugador.puntosRonda;
            cout << "Fin del turno de " << jugador.nombre << "\n";
            cout << "-------------------------\n";
        }

        // Verificar si todos los jugadores están sin PT
        bool todosSinPT = true;
        for (int i = 0; i < cantidad; i++) {
            if (jugadores[i].PT > 0) {
                todosSinPT = false;
                break;
            }
        }

        if (todosSinPT) {
            cout << "\nTodos los jugadores se quedaron sin PT. Fin de la partida.\n";
            partidaActiva = false;
        }

        ronda++;
    }

    // Mostrar tabla final de resultados
    mostrarTablaFinal(jugadores, cantidad);
}



// --------------------- REGISTRO DE JUGADORES -------------------------

//Se carga el registro de jugadores
void cargarJugadores(Jugador jugadores[], int cantidad) {
    for (int i = 0; i < cantidad; i++) {
        cout << "Ingrese nombre del jugador " << i + 1 << ": ";
        cin >> jugadores[i].nombre;
        jugadores[i].PT = 5;
        jugadores[i].bugs = 0;
        jugadores[i].puntajeTotal = 0;
        jugadores[i].puntosRonda = 0;
        jugadores[i].lanzamientos = 0;
        asignarCartaProyecto(jugadores[i]);
    }
}


//Se asignan las cartas a los jugadores
void asignarCartaProyecto(Jugador& jugador) {
    jugador.cartaObjetivo = 50 + rand() % 16; // entre 50 y 65
}



// --------------------- TIRADA DE DADOS -------------------------


// Tira los dados
void tirarDados(int dados[], int cantidad) {
    for (int i = 0; i < cantidad; i++) {
        dados[i] = 1 + rand() % 6;
    }
}

//Muestra los dados
void mostrarDados(const int dados[], int cantidad) {
    const string caras[6][5] = {
        {
            "+-------+",
            "|       |",
            "|   x   |",
            "|       |",
            "+-------+"
        },
        {
            "+-------+",
            "| x     |",
            "|       |",
            "|     x |",
            "+-------+"
        },
        {
            "+-------+",
            "| x     |",
            "|   x   |",
            "|     x |",
            "+-------+"
        },
        {
            "+-------+",
            "| x   x |",
            "|       |",
            "| x   x |",
            "+-------+"
        },
        {
            "+-------+",
            "| x   x |",
            "|   x   |",
            "| x   x |",
            "+-------+"
        },
        {
            "+-------+",
            "| x   x |",
            "| x   x |",
            "| x   x |",
            "+-------+"
        }
    };

    cout << "\n";

    // Mostrar todas las líneas de los dados en paralelo
    for (int linea = 0; linea < 5; linea++) {
        for (int i = 0; i < cantidad; i++) {
            int valor = dados[i];
            if (valor >= 1 && valor <= 6)
                cout << caras[valor - 1][linea] << "  ";
            else
                cout << "ERROR" << "  ";
        }
        cout << "\n";
    }
}

//Cuenta los BUGS
int contarBUGS(const int dados[], int cantidad) {
    int bugs = 0;
    for (int i = 0; i < cantidad; i++) {
        if (dados[i] == 1) bugs++;
    }
    return bugs;
}


//Cuenta los FIXES
int contarFIXES(const int dados[], int cantidad) {
    int fixes = 0;
    for (int i = 0; i < cantidad; i++) {
        if (dados[i] == 3) fixes++;
    }
    return fixes;
}


//Elige cantidad de dados a lanzar
bool elegirLanzamiento(int& cantidadElegida, const Jugador& jugador) {
    if (jugador.PT >= 2) {
        cout << "¿Cuántos dados desea lanzar? (2 o 3): ";
        cin >> cantidadElegida;

        if (cantidadElegida == 2 || cantidadElegida == 3)
            return true;
        else {
            cout << "Cantidad de dados no válida.\n";
            return false;
        }

    } else if (jugador.PT == 1) {
        cout << "Solo tiene 1 PT, puede lanzar 2 dados. Presione 2 para continuar: ";
        cin >> cantidadElegida;

        if (cantidadElegida == 2)
            return true;
        else {
            cout << "Opción inválida. Solo puede lanzar 2 dados con 1 PT.\n";
            return false;
        }

    } else {
        cout << jugador.nombre << " no tiene PT suficientes para lanzar dados.\n";
        return false;
    }
}


//Aplica efecto BUG
void aplicarEfectoBUG(Jugador& jugador, int cantidadBUGS) {
    jugador.bugs += cantidadBUGS;

    if (cantidadBUGS == 3) {
        jugador.puntosRonda = 0;
        cout << "¡Tirada fatal! Se pierden todos los puntos de la ronda.\n";
    }

    if (jugador.bugs >= 5) {
        jugador.PT -= 1;
        jugador.bugs = 0;
        cout << "¡Demasiados BUGS! Se pierde 1 PT.\n";
    }
}

//Aplica efecto FIX
void aplicarEfectoFIX(Jugador& jugador, int cantidadFIXES) {
    int bugsEliminados = (jugador.bugs >= cantidadFIXES) ? cantidadFIXES : jugador.bugs;
    jugador.bugs -= bugsEliminados;

    if (cantidadFIXES >= 3) {
        jugador.PT += 2;
        cout << "¡Gran práctica! Se suman 2 PT.\n";
    }
}

//Resuelve la tirada
void resolverTirada(Jugador& jugador, const int dados[], int cantidadDados) {
    int suma = 0;
    for (int i = 0; i < cantidadDados; i++)
        suma += dados[i];

    int bugs = contarBUGS(dados, cantidadDados);
    int fixes = contarFIXES(dados, cantidadDados);

    jugador.puntosRonda += suma;
    aplicarEfectoBUG(jugador, bugs);
    aplicarEfectoFIX(jugador, fixes);
}

// --------------------- FLUJO DEL JUEGO -------------------------

//Indica turno del jugador
void jugarTurno(Jugador& jugador) {
    system("cls");
    cout << "\n--- TURNO DE " << jugador.nombre << " ---\n";
    jugador.puntosRonda = 0;
    jugador.lanzamientos = 0;

    bool seguir = true;
    while (seguir && jugador.PT > 0) {
        int cantidadDados;
        if (!elegirLanzamiento(cantidadDados, jugador))
            break;

        jugador.PT -= (cantidadDados == 2) ? 1 : 2;
        int dados[3];
        tirarDados(dados, cantidadDados);
        mostrarDados(dados, cantidadDados);
        resolverTirada(jugador, dados, cantidadDados);

        jugador.lanzamientos++;
        cout << "Puntaje ronda: " << jugador.puntosRonda << " | PT: " << jugador.PT
             << " | BUGS: " << jugador.bugs << endl;

        if (jugador.puntosRonda + jugador.puntajeTotal >= jugador.cartaObjetivo)
            break;

        cout << "¿Desea continuar lanzando? (S/N): ";
        char opcion;
        cin >> opcion;
        if (opcion != 'S' && opcion != 's')
            seguir = false;
    }

    jugador.puntajeTotal += jugador.puntosRonda;
}


// --------------------- RESULTADO FINAL -------------------------


void mostrarTablaFinal(Jugador jugadores[], int cantidad) {
    cout << "\n===== RESULTADO FINAL =====\n";
    cout << "Nombre       | Puntos | PT  | BUGS | Puntaje Final\n";
    cout << "-------------+--------+-----+------+----------------\n";

    int mayor = -9999;
    string ganador;

    for (int i = 0; i < cantidad; i++) {
        Jugador& j = jugadores[i];
        int penalizacionBugs = j.bugs * 5;
        int bonificacionPT = j.PT * 7;
        int puntajeFinal = j.puntajeTotal - penalizacionBugs + bonificacionPT;

        cout << j.nombre;
        if (j.nombre.length() < 12) cout << string(12 - j.nombre.length(), ' ');
        cout << " |   " << j.puntajeTotal
             << "   | " << j.PT
             << " |  " << j.bugs
             << "  |      " << puntajeFinal << "\n";

        if (puntajeFinal > mayor) {
            mayor = puntajeFinal;
            ganador = j.nombre;
        }
    }

    cout << "\n🎉 ¡Ganador: " << ganador << " con " << mayor << " puntos! 🎉\n";
}


//Muestra las estadisticas del juego
void mostrarEstadisticas() {
    cout << "\n--- Última Partida ---\n";
    cout << "🏆Ganador: " << ultimoGanador << "\n";
    cout << "Puntaje: " << puntajeGanador << "\n";
}
