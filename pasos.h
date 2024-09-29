#ifndef _PASOS_H_
#define _PASOS_H_

typedef struct
{
    char Id_viaje[7];
    char Poblacion[21];

}Pasos;

//CABECERA:void leerPasos(Pasos **E_pasos, int *num_pasos);
//PRECONDICION: Debe existir un fichero "pasos.txt" y el entero num_pasos y debe haber espacio suficiente en memoria para almacenar los pasos
//POSTCONDICIÓN: Carga en memoria el array de estructuras E_pasos en memoria
void leerPasos(Pasos **, int *);
//CABECERA:void void guardarPasos(Pasos *E_pasos, int num_pasos);
//PRECONDICION: Debe existir un array de estructuras "Pasos" y un entero "num_pasos" 
//POSTCONDICIÓN: Guarda en un fichero Pasos.txt los viajes
void guardarPasos(Pasos *, int);

#endif
