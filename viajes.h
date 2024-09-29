#ifndef _VIAJES_H_
#define _VIAJES_H_
#include "pasos.h"
#include "usuarios.h"
#include "vehiculos.h"
#include "time.h"
//Estructuras
typedef struct
{
    char Id_viaje[7];
    char Id_mat[8];
    char F_inic[11]; //Si el formato es DD/MM/AAAA ser�n un total de 10 car�cteres
    char H_inic[6]; //Al ser los formatos 10:30 ser�n 5 los car�cteres necesarios para expresarlos
    char H_fin[6];
    int Plazas_Libres;
    char Viaje[7];
    float Importe;
    char Estado[11];
}Viajes;


//CABECERA:void leerViajes(Viajes **E_viajes, int *num_viajes);
//PRECONDICION: Debe existir un fichero "viajes.txt" y el entero num_viajes y debe haber espacio suficiente en memoria para almacenar los viajes
//POSTCONDICIÓN: Carga en memoria el array de estructuras E_viajes en memoria
void leerViajes(Viajes **, int *);

//CABECERA:void guardarViajes(Viajes *E_viajes, int num_viajes);
//PRECONDICION: Debe existir un array de estructuras "Viajes" y un entero "num_viajes"
//POSTCONDICIÓN: Guarda en un fichero Viajes.txt los viajes
void guardarViajes(Viajes *, int);

//CABECERA:void publicarViajesUsuario(Viajes**E_viajes, int *num_viajes, int *posicionUsuario, Pasos **E_pasos, int *num_pasos, Usuarios **E_usuarios, int *num_usuarios, Vehiculos **E_vehiculos, int *num_vehiculos);
//PRECONDICION: Las estructuras deben estar cargadas correctamente
//POSTCONDICIÓN: Publica un nuevo viaje en la estructura
void publicarViajesUsuario(Viajes**, int *, int *, Pasos **, int *, Usuarios **, int *, Vehiculos **, int *);

//CABECERA:void modificarViajesUsuario(Viajes**E_viajes, int *num_viajes, int *posicionUsuario, Pasos **E_pasos, int *num_pasos, Usuarios **E_usuarios, int *num_usuarios, Vehiculos **E_vehiculos, int *num_vehiculos);
//PRECONDICION: Las estructuras deben estar cargadas correctamente
//POSTCONDICIÓN: Modifican los parámetros elegidos por los menús al viaje del usuario seleccionado
void modificarViajesUsuario(Viajes**, int *, int *, Pasos **, int *, Usuarios **, int *, Vehiculos **, int *);

//CABECERA: void mostrarViajeUsuario(Viajes**E_viajes, int *num_viajes, int *posicionUsuario, Vehiculos **E_vehiculos, int *num_vehiculos, Usuarios **E_usuarios, int *num_usuarios,Pasos **E_pasos, int *num_pasos);
//PRECONDICION:Las estructuras deben estar cargadas correctamente
//POSTCONDICIÓN:Muestra en detalle los datos del viaje seleccionado del usuario
void mostrarViajeUsuario(Viajes**, int *, int *, Vehiculos **, int *, Usuarios **, int *, Pasos **, int *);

//CABECERA:void incorporarViajeUsuario(Viajes**E_viajes, int *num_viajes, int *posicionUsuario, Pasos **E_pasos, int *num_pasos, Usuarios **E_usuarios, int *num_usuarios, Vehiculos **E_vehiculos, int *num_vehiculos);
//PRECONDICION:Las estructuras deben estar cargadas correctamente
//POSTCONDICIÓN: Muestra los viajes que pasarán cerca del usuario y estén disponibles para incorporarse
void incorporarViajeUsuario(Viajes**, int *, int *, Pasos **, int *, Usuarios **, int *, Vehiculos **, int *);

//CABECERA:void menuViajeUsuario(Viajes**E_viajes, int *num_viajes, int *posicionUsuario, Pasos **E_pasos, int *num_pasos, Usuarios **E_usuarios, int *num_usuarios, Vehiculos **E_vehiculos, int *num_vehiculos);
//PRECONDICION: Todas las estructuras han de estar cargadas correctamente
//POSTCONDICIÓN:Muestra las diversas opciones para acceder a las funciones usuario
void menuViajeUsuario(Viajes**, int *, int *, Pasos **, int *, Usuarios **, int *, Vehiculos **, int *);

//==========================================FUNCIONES ADMINISTRADOR============================================//
//CABECERA:void publicarViajesAdmin(Viajes**E_viajes, int *num_viajes, Pasos **E_pasos, int *num_pasos,Usuarios **E_usuarios, int *num_usuarios, Vehiculos **E_vehiculos, int *num_vehiculos);
//PRECONDICION: Todas las estructuras han de estar cargadas en memoria
//POSTCONDICIÓN:Publica un viaje con independencia del usuario, agregando el vehiculo y por ende al conductor
void publicarViajesAdmin(Viajes**, int *, Pasos **, int *, Usuarios **, int *, Vehiculos **, int *);

//CABECERA:void eliminarViajesAdmin(Viajes**E_viajes, int *num_viajes);
//PRECONDICION:Todas las estructuras han de estar cargadas en memoria
//POSTCONDICIÓN:Elimina un viaje y reajusta el array de estructura de Viajes
void eliminarViajesAdmin(Viajes**, int *);

//CABECERA:void modificarViajesAdmin(Viajes**E_viajes, int *num_viajes, Pasos **E_pasos, int *num_pasos,Usuarios **E_usuarios, int *num_usuarios, Vehiculos **E_vehiculos, int *num_vehiculos);
//PRECONDICION:Todas las estructuras han de estar cargadas en memoria
//POSTCONDICIÓN:Modifica un viaje con independencia del usuario
void modificarViajesAdmin(Viajes**, int *, Pasos **, int *, Usuarios **, int *, Vehiculos **, int *);

//CABECERA:void mostrarViajesAdmin(Viajes**E_viajes, int *num_viajes, Pasos **E_pasos, int *num_pasos);
//PRECONDICION:Debe estar la estructura "E_viajes" cargada en memoria
//POSTCONDICIÓN:Muestra los datos de los viajes seleccionados por el administrador
void mostrarViajesAdmin(Viajes**, int *, Pasos **, int *);

//CABECERA:void menuViajesAdmin(Viajes**E_viajes, int *num_viajes, Pasos **E_pasos, int *num_pasos, Usuarios **E_usuarios, int *num_usuarios, Vehiculos **E_vehiculos, int *num_vehiculos);
//PRECONDICION:Todas las estructuras han de estar cargadas en memoria
//POSTCONDICIÓN:Muestra las diversas opciones para acceder a las funciones Administrador
void menuViajesAdmin(Viajes**, int *, Pasos **, int *, Usuarios **, int *, Vehiculos **, int *);

//==========================================FUNCIONES AUXILIARES============================================//
//CABECERA:static void fillIdentifier(char* identifier, int num, int length);
//PRECONDICION: Se le pasa una cadena de carácteres, el número entero que llevará y la longitud de la ID
//POSTCONDICIÓN:Transforma de entero a cadena de carácteres rellena con 0 hasta que llegue a la posición del entero devolviendo su ID
static void fillIdentifier(char*, int, int);

//CABECERA:static bool dateCheck(int *dia, int *mes, int *anno);
//PRECONDICION: Ninguno de los enteros son nulos
//POSTCONDICIÓN:Devuelve si la fecha introducida es válida o no, true o false
static bool dateCheck(int *, int *, int *);

//CABECERA:static void dateIntToString(int* dia, int* mes, int* anno, char* string);
//PRECONDICION: Ninguna de las variables son null
//POSTCONDICIÓN: Convierte la fecha numérica en una cadena de carácteres con el formato DD/MM/AAAA
static void dateIntToString(int*, int*, int*, char*);

//CABECERA:static bool hourCheck(int *hora, int *minutos);
//PRECONDICION: Ninguna de las variables son null
//POSTCONDICIÓN: Comprueba que la hora introducida es correcta según la hora del sistema
static bool hourCheck(int *, int *);

//CABECERA:static void hourIntToString(int* horas, int* minutos, char* string);
//PRECONDICION: Ninguna de las variables son null
//POSTCONDICIÓN: Convierte la hora numérica en una cadena de carácteres con el formato HH:MM
static void hourIntToString(int*, int*, char*);

//CABECERA:static bool hourCheckReturn(int *horas, int *minutos, int *horasIDA, int *minutosIDA);
//PRECONDICION:Ninguna de las variables son null
//POSTCONDICIÓN:Comprueba que la hora de llegada introducida es correcta según la hora del sistema, comprobando también que son menores que la de salida
static bool hourCheckReturn(int *, int *, int *, int *);

//CABECERA:static bool checkCarLicencePlate(char *mat, int *user, Vehiculos *E_vehiculos, Usuarios *E_usuarios, int *num_vehiculos);
//PRECONDICION:Ninguna de las variables son null y las estructuras están cargadas
//POSTCONDICIÓN: Comprueba que la matrícula pertenece al usuario en cuestión.
static bool checkCarLicencePlate(char *, int *, Vehiculos *, Usuarios *, int *);

//CABECERA:static int lookForCar(char *auxStr, Vehiculos **E_vehiculos, int *num_vehiculos);
//PRECONDICION:Ninguna de las variables son null y las estructuras están cargadas
//POSTCONDICIÓN:Busca el coche según la matrícula introducida en auxStr
static int lookForCar(char *, Vehiculos **, int *);

//CABECERA:static int checkTravelCode(char *auxStr, Vehiculos **E_vehiculos, int *posicionUsuario, int *num_vehiculos, Viajes **E_viajes, int *num_viajes, Usuarios **E_usuarios, int *num_usuarios);
//PRECONDICION:Ninguna de las variables son null y las estructuras están cargadas
//POSTCONDICIÓN:Comprueba el código de viaje entre todos los usuarios devolviendo el correspondiente con la estructura y la variable auxStr
static int checkTravelCode(char *, Vehiculos **, int *, int *, Viajes **, int *, Usuarios **, int *);

//CABECERA:static bool checkCarCapacity(int *input, Vehiculos **E_vehiculos, int *num_vehiculos, Viajes **E_viajes, int *num_viajes);
//PRECONDICION:Las estructuras no están vacías el input no es null
//POSTCONDICIÓN: Comprueba la capacidad del vehículo para ver si el input es correcto con respecto a la capacidad, devuelve true o false
static bool checkCarCapacity(int *, Vehiculos **, int *, Viajes **, int *);

//CABECERA:static int lookForUser(char *auxStr, Usuarios **E_usuarios, int *num_usuarios);
//PRECONDICION:Ninguna de las variables son null y las estructuras están cargadas
//POSTCONDICIÓN: Comprueba el código de usuario entre todos los usuarios devolviendo el correspondiente con la estructura y la variable auxStr
static int lookForUser(char *, Usuarios **, int *);

//CABECERA:static int lookForTravel(char *auxStr, Viajes **E_Viajes, int *num_viajes);s
//PRECONDICION:Ninguna de las variables son null y las estructuras están cargadas
//POSTCONDICIÓN:Comprueba el código de usuario entre todos los usuarios devolviendo el correspondiente con la estructura y la variable auxStr
static int lookForTravel(char *, Viajes **, int *);
#endif
