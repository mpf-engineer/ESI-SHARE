#include <stdio.h>
#include <stdlib.h>
#include "usuarios.h"
#include "viajes.h"
#include "vehiculos.h"
#include "pasos.h"


int main()
{
    // Declaración e inicialización de variables struct
    Usuarios *E_usuarios = NULL;
    Viajes *E_viajes = NULL;
    Vehiculos *E_vehiculos = NULL;
    Pasos *E_pasos = NULL;

    // Variables contadoras de número de elementos de struct y posicines del vector struct
    int num_usuarios, num_viajes,  num_vehiculos, num_pasos, posicionUsuario;

    // Carga de datos de ficheros a memoria principal
    leerUsuarios(&E_usuarios, &num_usuarios);
    leerViajes(&E_viajes, &num_viajes);
    leerVehiculos(&E_vehiculos, &num_vehiculos);
    leerPasos(&E_pasos, &num_pasos);

    system("cls");

    loginUsuarios(E_usuarios, num_usuarios, &posicionUsuario);

    if(E_usuarios[posicionUsuario].Perfil == 'u')
    {
        menuUsuario(&E_usuarios, &num_usuarios, &posicionUsuario, &E_viajes, &num_viajes, &E_vehiculos, &num_vehiculos, &E_pasos, &num_pasos);
    }

    else
    {
        menuAdministrador(&E_usuarios, &num_usuarios, &posicionUsuario, &E_viajes, &num_viajes, &E_vehiculos, &num_vehiculos, &E_pasos, &num_pasos);
    }



    // Guardar cambios en ficheros
    guardarUsuarios(E_usuarios, num_usuarios);
    guardarViajes(E_viajes, num_viajes);
    guardarVehiculos(E_vehiculos, num_vehiculos);
    guardarPasos(E_pasos, num_pasos);



    // Liberar la memoria de los structs
    free(E_usuarios);
    free(E_viajes);
    free(E_vehiculos);
    free(E_pasos);

    return 0;
}
