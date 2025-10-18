#include <iostream>
#include <cstdlib>
#include <ctime>
#include <locale.h>
#ifdef _WIN32
    #include <windows.h>
#endif
#include "juego.h"

using namespace std;

int main()

{
    #ifdef _WIN32
        // Configuración específica para Windows
        SetConsoleOutputCP(65001);  // UTF-8
        SetConsoleCP(65001);        // UTF-8
        system("chcp 65001 > nul");
    #endif

    setlocale(LC_ALL, "C.UTF-8");

    int opcion;

    do
    {
        mostrarMenuPrincipal();
        cin >> opcion;

        switch (opcion)
        {
        case 1:
            system("cls");
            jugarPartida();
            system("pause");
            break;
        case 2:
            system("cls");
            mostrarEstadisticas();
            system("pause");
            break;
        case 3:
            system("cls");
            mostrarCreditos();
            system("pause");
            break;
        /*case 4:
            system("cls");
            menuTesting();
            system("cls");

            break;*/

        case 0:
            system("cls");
            if (confirmarSalida())
            {
                cout << "¡Hasta luego!" << endl;
                return 0;
            }
            system("pause");
            break;
        default:
            cout << "Opción no válida. Intente de nuevo." << endl;
            system("pause");
        }
    }
    while (true);

    return 0;
}
