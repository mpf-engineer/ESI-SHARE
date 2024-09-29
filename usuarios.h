#ifndef _USUARIOS_H_
#define _USUARIOS_H_


typedef struct
{
    char Id_usuario[5]; //Rango: 0001-9999
    char Nombre[21];
    char Localidad[21];
    char Perfil; //u-> usuario, a->administrador.
    char Usuario[6];
    char Password[9];

}Usuarios;

/*
  CABECERA: void leerUsuarios(Usuarios **, int *);
  PRECONDICIÓN: Debe de existir el fichero Usuarios.txt y la estructura E_usuarios.
  POSTCONDICIÓN: Carga los datos de Usuarios.txt en la estructura E_usuarios.
*/
void leerUsuarios(Usuarios **, int *);


/*
  CABECERA: void guardarUsuarios(Usuarios *, int );
  PRECONDICIÓN: Debe de existir el fichero Usuarios.txt y la estructura E_usuarios.
  POSTCONDICIÓN: Guarda los datos de la estructura E_usuarios en el fichero Usuarios.txt.
*/
void guardarUsuarios(Usuarios *, int );


/*
  CABECERA: void bajaUsuario(Usuarios **, int *);
  PRECONDICIÓN: Debe de existir la estructura E_usuarios y estar inicializada. Función exclusiva para administradores.
  POSTCONDICIÓN: Borra un elemento del vector de estructura E_usuarios.
*/
void bajaUsuario(Usuarios **, int *);


/*
  CABECERA: void altaUsuario(Usuarios **, int *);
  PRECONDICIÓN: Debe de existir la estructura E_usuarios y estar inicializada. Función exclusiva para administradores.
  POSTCONDICIÓN: Añade un elemento al vector de estructura E_usuarios.
*/
void altaUsuario(Usuarios **, int *);

/*
  CABECERA: void consultarUsuario(Usuarios *, int );
  PRECONDICIÓN: Debe de existir la estructura E_usuarios y estar inicializada. Función exclusiva para administradores.
  POSTCONDICIÓN: Dado un ID de Usuario, imprime por pantalla los datos de ese Usuario.
*/
void consultarUsuario(Usuarios *, int );


/*
  CABECERA: void modificarUsuario(Usuarios **, int );
  PRECONDICIÓN: Debe de existir la estructura E_usuarios y estar inicializada. Función exclusiva para administradores.
  POSTCONDICIÓN: Permite al administrador que dado un ID de Usuario, modifique los datos de ese Usuario excepto el campo Id_usuario y Password.
*/
void modificarUsuario(Usuarios **, int );


/*
  CABECERA: void loginUsuarios(Usuarios *, int , int *);
  PRECONDICIÓN: Debe de existir la estructura E_usuarios y estar inicializada.
  POSTCONDICIÓN: Dado un ID de Usuario y un PASSWORD, comprueba si el usuario está registrado.
*/
void loginUsuarios(Usuarios *, int , int *);


/*
  CABECERA: void mostrarUsuario(Usuarios *, int );
  PRECONDICIÓN: Debe de existir la estructura E_usuarios y estar inicializada. Función exclusiva para usuarios.
  POSTCONDICIÓN: Imprime por pantalla los datos del Usuario actual.
*/
void mostrarUsuario(Usuarios *, int );


/*
  CABECERA: void editarUsuario(Usuarios **, int );
  PRECONDICIÓN: Debe de existir la estructura E_usuarios y estar inicializada. Función exclusiva para usuarios.
  POSTCONDICIÓN: Permite que el Usuario actual modifique sus datos excepto el campo Id_usuario y Perfil.
*/
void editarUsuario(Usuarios **, int );






#endif

