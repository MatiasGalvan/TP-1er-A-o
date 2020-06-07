#include "color.h"

void Color(int Background, int Text)  // Función para cambiar el color del fondo y/o letras
{

    HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE); // Tomamos la consola.

// Para cambiar el color, se utilizan números desde el 0 hasta el 255.
// Pero, para convertir los colores a un valor adecuado, se realiza el siguiente cálculo.
    int    New_Color= Text + (Background * 16);

    SetConsoleTextAttribute(Console, New_Color); // Guardamos los cambios en la Consola.
}

