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
  PRECONDICI�N: Debe de existir el fichero Usuarios.txt y la estructura E_usuarios.
  POSTCONDICI�N: Carga los datos de Usuarios.txt en la estructura E_usuarios.
*/
void leerUsuarios(Usuarios **, int *);


/*
  CABECERA: void guardarUsuarios(Usuarios *, int );
  PRECONDICI�N: Debe de existir el fichero Usuarios.txt y la estructura E_usuarios.
  POSTCONDICI�N: Guarda los datos de la estructura E_usuarios en el fichero Usuarios.txt.
*/
void guardarUsuarios(Usuarios *, int );


/*
  CABECERA: void bajaUsuario(Usuarios **, int *);
  PRECONDICI�N: Debe de existir la estructura E_usuarios y estar inicializada. Funci�n exclusiva para administradores.
  POSTCONDICI�N: Borra un elemento del vector de estructura E_usuarios.
*/
void bajaUsuario(Usuarios **, int *);


/*
  CABECERA: void altaUsuario(Usuarios **, int *);
  PRECONDICI�N: Debe de existir la estructura E_usuarios y estar inicializada. Funci�n exclusiva para administradores.
  POSTCONDICI�N: A�ade un elemento al vector de estructura E_usuarios.
*/
void altaUsuario(Usuarios **, int *);

/*
  CABECERA: void consultarUsuario(Usuarios *, int );
  PRECONDICI�N: Debe de existir la estructura E_usuarios y estar inicializada. Funci�n exclusiva para administradores.
  POSTCONDICI�N: Dado un ID de Usuario, imprime por pantalla los datos de ese Usuario.
*/
void consultarUsuario(Usuarios *, int );


/*
  CABECERA: void modificarUsuario(Usuarios **, int );
  PRECONDICI�N: Debe de existir la estructura E_usuarios y estar inicializada. Funci�n exclusiva para administradores.
  POSTCONDICI�N: Permite al administrador que dado un ID de Usuario, modifique los datos de ese Usuario excepto el campo Id_usuario y Password.
*/
void modificarUsuario(Usuarios **, int );


/*
  CABECERA: void loginUsuarios(Usuarios *, int , int *);
  PRECONDICI�N: Debe de existir la estructura E_usuarios y estar inicializada.
  POSTCONDICI�N: Dado un ID de Usuario y un PASSWORD, comprueba si el usuario est� registrado.
*/
void loginUsuarios(Usuarios *, int , int *);


/*
  CABECERA: void mostrarUsuario(Usuarios *, int );
  PRECONDICI�N: Debe de existir la estructura E_usuarios y estar inicializada. Funci�n exclusiva para usuarios.
  POSTCONDICI�N: Imprime por pantalla los datos del Usuario actual.
*/
void mostrarUsuario(Usuarios *, int );


/*
  CABECERA: void editarUsuario(Usuarios **, int );
  PRECONDICI�N: Debe de existir la estructura E_usuarios y estar inicializada. Funci�n exclusiva para usuarios.
  POSTCONDICI�N: Permite que el Usuario actual modifique sus datos excepto el campo Id_usuario y Perfil.
*/
void editarUsuario(Usuarios **, int );






#endif

