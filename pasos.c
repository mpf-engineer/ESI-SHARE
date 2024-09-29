#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pasos.h"

// COLORES TEXTO:
// MODO DE EMPLEO: printf("COLOR" "TEXTO" "COLOR OFF");
// COLOR_RED "\033[0;31m" -> PARA MENSAJE DE ERROR
// COLOR_GREEN "\033[0;32m" -> PARA MENSAJE DE CONFIRMACIÓN
// COLOR_YELLOW "\033[0;33m" -> PARA TÍTULOS DEL MENÚ
// COLOR_BLUE "\033[0;34m"
// COLOR_MAGENTA "\033[0;35m" -> PARA MENSAJE DE PEDIR UN DATO POR TECLADO
// COLOR_CYAN "\033[0;36m" -> PARA MENÚ DE OPCIONES
// COLOR_WHITE "\033[0;37m"
// COLOR OFF "\033[0m" -> PARA VOLVER A COLOR BASE TERMINAL (IMPORTANTE: Añadir en cada printf)


void leerPasos(Pasos **E_pasos, int *num_pasos)
{
    FILE *archivo;
    char linea[100], *Id_viaje, *Poblacion;

    // Abrir el archivo para lectura
    archivo = fopen("Pasos.txt", "r");
    if (archivo == NULL)
    {
        printf("Error al abrir el archivo.\n");
        return;
    }

    // Inicializar el puntero al Pasos
    *E_pasos = NULL;

    // Inicializar el contador num_pasos
    *num_pasos = 0;

    // Contar el número de pasos
    while (fgets(linea, 100, archivo) != NULL)
    {
        (*num_pasos)++;

        // Asignar memoria para el nuevo Pasos
        *E_pasos = realloc(*E_pasos, *num_pasos * sizeof(Pasos));
        if (*E_pasos == NULL)
        {
            printf("Error al asignar memoria.\n");
            return;
        }

        // Extraer los datos del paso de la línea
        Id_viaje = strtok(linea, "-");
        Poblacion = strtok(NULL, "\n");

        // Copiar los datos del paso al struct
        strcpy((*E_pasos)[*num_pasos - 1].Id_viaje, Id_viaje);
        strcpy((*E_pasos)[*num_pasos - 1].Poblacion, Poblacion);
    }

    // Cerrar el archivo
    fclose(archivo);
}


void guardarPasos(Pasos *E_pasos, int num_pasos)
{
    FILE *archivo;

    // Abrir el archivo para escritura
    archivo = fopen("pasos.txt", "w");
    if (archivo == NULL)
    {
        printf("Error al abrir el archivo.\n");
        return;
    }

    // Escribir los datos de los pasos al archivo
    for (int i = 0; i < num_pasos; i++)
    {
        fprintf(archivo, "%s-%s\n", E_pasos[i].Id_viaje, E_pasos[i].Poblacion);
    }

    // Cerrar el archivo
    fclose(archivo);
}



