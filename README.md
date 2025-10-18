==============================
        TREY - Juego de Consola
==============================

📌 DESCRIPCIÓN GENERAL:
Trey es un juego por turnos para 2 jugadores que simula el desarrollo de un proyecto de software.
Cada jugador debe alcanzar un objetivo de puntos lanzando dados y evitando errores (BUGS) mientras intenta obtener buenas prácticas (FIXES).

------------------------------
📁 ESTRUCTURA DEL PROYECTO:
- main.cpp        → Función principal y menú del juego.
- juego.h         → Declaraciones de funciones y estructuras.
- juego.cpp       → Implementación de la lógica del juego.
- juegoTrey.cbp   → Proyecto de Code::Blocks.
- .depend/.layout → Archivos generados automáticamente por Code::Blocks.

------------------------------
⚙️ COMPILACIÓN Y EJECUCIÓN:
1. Abrir Code::Blocks.
2. Ir a File > Open > Seleccionar "juegoTrey.cbp".
3. Compilar con Build > Build and Run (F9).
4. Jugar desde la consola siguiendo las instrucciones.

------------------------------
💻 COMPATIBLE CON:
- Windows 10/11
- Code::Blocks con compilador GCC

------------------------------
🎮 FUNCIONALIDADES PRINCIPALES:
- Registro y asignación de cartas objetivo a los jugadores.
- Tiradas de 2 o 3 dados con impacto en puntos, BUGS y FIXES.
- Penalizaciones por acumulación de BUGS y bonificaciones por buenas prácticas.
- Lógica de juego por rondas (hasta 10) o hasta que se alcance el objetivo.
- Cálculo del puntaje final con penalización por BUGS y bonificación por PT restantes.
- Menú interactivo con opciones de juego, créditos y estadísticas.

------------------------------
🔢 REGLAS CLAVE:
- Se juega por turnos, hasta un máximo de 10 rondas.
- Cada jugador tiene una carta objetivo entre 50 y 65 puntos.
- Los puntos de lanzamiento (PT) determinan cuántos dados puede lanzar:
    - 2 dados = 1 PT
    - 3 dados = 2 PT
- Los BUGS (dados con valor 1) se acumulan y pueden penalizar.
- Los FIXES (dados con valor 3) eliminan BUGS y dan bonificación.
- Gana quien alcance el objetivo o tenga mejor puntaje final.

------------------------------
👨‍💻 PARA DESARROLLADORES:
- El código está dividido modularmente.
- Todas las funciones importantes están en juego.cpp/juego.h.
- Los archivos fuente están guardados en codificación UTF-8.
- Se utilizan solo arrays planos (no se usa vector).

------------------------------
📞 CRÉDITOS / AUTORES:
- Burolleau, Ana (Legajo Nº 32466)
- Lamonaca, Lautaro (Legajo Nº 32388)
- Lanzillotta, Gisela (Legajo Nº 32372)
- Zahlut, Pablo (Legajo Nº 32449)
