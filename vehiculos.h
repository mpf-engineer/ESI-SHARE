#ifndef _VEHICULOS_H_
#define _VEHICULOS_H_

typedef struct
{
    char Id_mat[8];
    char Id_usuario[5];
    int Num_plazas;
    char Desc_veh[51];

}Vehiculos;

typedef enum  //Usado para ciertos controladores de existencia de variables o de haber encontrado una variable en modulos vehiculos y viajes
{false, true}bool;

/*
  CABECERA: void imprimirVehiculosAdmin(Vehiculos *, int);
  PRECONDICIÓN: Debe de existir la estructura E_vehiculos y estar inicializada. Función exclusiva para administradores.
  POSTCONDICIÓN: Muestra todos los elementos de la estructura vehiculos
*/
void imprimirVehiculosAdmin(Vehiculos *, int);

/*
  CABECERA: void imprimirVehiculos(char [], Vehiculos*, int);
  PRECONDICIÓN: Debe de existir la estructura E_vehiculos y estar inicializada.
  POSTCONDICIÓN: Borra un elemento del vector de estructura E_usuarios.
*/
void imprimirVehiculos(char [], Vehiculos*, int);

/*
  CABECERA: void annadirVehiculoAdmin(Vehiculos **, int *);
  PRECONDICIÓN: Debe de existir la estructura E_vehiculos y estar inicializada. Función exclusiva para administradores.
  POSTCONDICIÓN: Un admin añade un vehiculo asociandolo a cualquier usuario
*/
void annadirVehiculoAdmin(Vehiculos **, int *);

/*
  CABECERA: void annadirVehiculo(char [], Vehiculos **, int *);
  PRECONDICIÓN: Debe de existir la estructura E_vehiculos y estar inicializada.
  POSTCONDICIÓN: Un usuario añade un vehiculo asociado a el.
*/
void annadirVehiculo(char [], Vehiculos **, int *);

/*
  CABECERA: void eliminarVehiculoAdmin(Vehiculos **, int *);
  PRECONDICIÓN: Debe de existir la estructura E_vehiculos y estar inicializada. Función exclusiva para administradores.
  POSTCONDICIÓN: Borrar un vehiculo cualquiera
*/
void eliminarVehiculoAdmin(Vehiculos **, int *);

/*
  CABECERA: void eliminarVehiculos(char [], Vehiculos **, int *);
  PRECONDICIÓN: Debe de existir la estructura E_vehiculos y estar inicializada.
  POSTCONDICIÓN: Borrar un vehiculo que sea del usuario con id igual al char que se le pase
*/
void eliminarVehiculos(char [], Vehiculos **, int *);

/*
  CABECERA: void modificarVehiculosAdmin(Vehiculos **, int);
  PRECONDICIÓN: Debe de existir la estructura E_vehiculos y estar inicializada. Función exclusiva para administradores.
  POSTCONDICIÓN: Un administrador podra modificar cualquier dato de cualquier vehiculo
*/
void modificarVehiculosAdmin(Vehiculos **, int);

/*
  CABECERA: void modificarVehiculos(char [], Vehiculos **, int);
  PRECONDICIÓN: Debe de existir la estructura E_vehiculos y estar inicializada.
  POSTCONDICIÓN: Un usuario podra modificar los datos de uno de sus vehiculos
*/
void modificarVehiculos(char [], Vehiculos **, int);

/*
  CABECERA: void leerVehiculos(Vehiculos **E_vehiculos, int *num_vehiculos);
  PRECONDICIÓN:
  POSTCONDICIÓN: Carga en memoria la estrutura vehiculos
*/
void leerVehiculos(Vehiculos **, int *);

/*
  CABECERA: void guardarVehiculos(Vehiculos *E_vehiculos, int num_vehiculos);
  PRECONDICIÓN:
  POSTCONDICIÓN: Guarda en la estructura las modificaciones hechas durante la ejecucion
*/
void guardarVehiculos(Vehiculos *, int);

/*
  void menuVehiculosAdmin(Vehiculos**, int*);
  PRECONDICIÓN: Debe de existir la estructura E_vehiculos y estar inicializada. Función exclusiva para administradores.
  POSTCONDICIÓN: Muestra el menu de administradores
*/
void menuVehiculosAdmin(Vehiculos**, int*);

/*
  CABECERA: void menuVehiculosUser(char [], Vehiculos **, int *);
  PRECONDICIÓN: Debe de existir la estructura E_vehiculos y estar inicializada.
  POSTCONDICIÓN: Inicia por pantalla el menu de usuarios
*/
void menuVehiculosUser(char [], Vehiculos **, int *);

#endif

