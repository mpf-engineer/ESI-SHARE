#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "usuarios.h"
#include "viajes.h"
#include "vehiculos.h"

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



void leerUsuarios(Usuarios **E_usuarios, int *num_usuarios)
{
    FILE *archivo;
    char linea[100], *Id_usuario, *Nombre, *Localidad, Perfil, *Usuario, *Password;

    // Abrir el archivo para lectura
    archivo = fopen("Usuarios.txt", "r");
    if (archivo == NULL)
    {
        printf("Error al abrir el archivo.\n");
        return;
    }

    // Inicializar el puntero al Usuarios
    *E_usuarios = NULL;

    // Inicializar el contador num_usuarios
    *num_usuarios = 0;

    // Contar el número de usuarios
    while (fgets(linea, 100, archivo) != NULL)
    {
        (*num_usuarios)++;

        // Asignar memoria para el nuevo Usuarios
        *E_usuarios = realloc(*E_usuarios, *num_usuarios * sizeof(Usuarios));
        if (*E_usuarios == NULL)
        {
            printf("Error al asignar memoria.\n");
            return;
        }

        // Extraer los datos del usuario de la línea
        Id_usuario = strtok(linea, "-");
        Nombre = strtok(NULL, "-");
        Localidad = strtok(NULL, "-");
        Perfil = strtok(NULL, "-")[0];
        Usuario = strtok(NULL, "-");
        Password = strtok(NULL, "\n");

        // Copiar los datos del usuario al struct
        strcpy((*E_usuarios)[*num_usuarios - 1].Id_usuario, Id_usuario);
        strcpy((*E_usuarios)[*num_usuarios - 1].Nombre, Nombre);
        strcpy((*E_usuarios)[*num_usuarios - 1].Localidad, Localidad);
        (*E_usuarios)[*num_usuarios - 1].Perfil = Perfil;
        strcpy((*E_usuarios)[*num_usuarios - 1].Usuario, Usuario);
        strcpy((*E_usuarios)[*num_usuarios - 1].Password, Password);
}

    // Cerrar el archivo
    fclose(archivo);

}


void guardarUsuarios(Usuarios *E_usuarios, int num_usuarios)
{
    int i;

    FILE *archivo;

    // Abrir el archivo para escritura
    archivo = fopen("usuarios.txt", "w");
    if (archivo == NULL)
    {
        printf("Error al abrir el archivo.\n");
        return;
    }

    // Escribir los datos de los usuarios al archivo
    for (i = 0; i < num_usuarios; i++)
    {
        fprintf(archivo, "%s-%s-%s-%c-%s-%s\n", E_usuarios[i].Id_usuario, E_usuarios[i].Nombre, E_usuarios[i].Localidad, E_usuarios[i].Perfil, E_usuarios[i].Usuario, E_usuarios[i].Password);
    }

    // Cerrar el archivo
    fclose(archivo);
}

void bajaUsuario(Usuarios **E_usuarios, int *num_usuarios)
{
    char id[5];
    int i, encontrado = 0, posicionUsuario;


    system("cls");
    printf("\033[33m" "\n\n\t------------------------------------------------------\n" "\033[0m");
    printf("\033[33m" "\t\t MENU ADMINISTRADOR -> BAJA USUARIO\n" "\033[0m");
    printf("\033[33m" "\t------------------------------------------------------\n" "\033[0m");
    printf("\033[35m" "\n\tIngrese el ID del usuario a dar de baja (0001-9999): " "\033[0m");
    scanf("%4s", id);

    // Buscar el usuario en el vector de struct
    for (i = 0; i < *num_usuarios; i++)
    {
        if (strcmp((*E_usuarios)[i].Id_usuario, id) == 0)
        {
            posicionUsuario = i;
            encontrado = 1;
        }

    }
    if (encontrado == 1)
    {
        // Reordenar vector de struct
        for (i = posicionUsuario; i < *num_usuarios - 1; i++)
        {

            strcpy((*E_usuarios)[i].Id_usuario, (*E_usuarios)[i+1].Id_usuario);
            strcpy((*E_usuarios)[i].Nombre, (*E_usuarios)[i+1].Nombre);
            strcpy((*E_usuarios)[i].Localidad, (*E_usuarios)[i+1].Localidad);
            (*E_usuarios)[i].Perfil = (*E_usuarios)[i+1].Perfil;
            strcpy((*E_usuarios)[i].Usuario, (*E_usuarios)[i+1].Usuario);
            strcpy((*E_usuarios)[i].Password, (*E_usuarios)[i+1].Password);

        }

        // Eliminar última posición del vector struct
        (*num_usuarios)--;

        // Reasignar memoria para el nuevo tamaño de struct
        *E_usuarios = realloc(*E_usuarios, *num_usuarios * sizeof(Usuarios));


        // Actualizar los Id's de los usuarios para que queden ordenados
        for (i = 0; i < *num_usuarios; i++)
        {
            sprintf((*E_usuarios)[i].Id_usuario, "%04d", i+1);
        }
        system("cls");
        printf("\033[0;32m" "\n\n\tUsuario dado de baja con exito!: " "\033[0m");
        system("pause");
    }

    else
    {
        system("cls");
        printf("\033[0;31m" "\n\n\tERROR: El usuario con ID %s no fue encontrado. \n" "\033[0m", id);
        system("pause");

    }

}



void altaUsuario(Usuarios **E_usuarios, int *num_usuarios)
{

    int i;

    // Reservar memoria para el nuevo usuario
    *E_usuarios = realloc(*E_usuarios, (*num_usuarios + 1) * sizeof(Usuarios));

    // Verificar si la asignación de memoria se realizó correctamente
    if (*E_usuarios == NULL)
    {
        system("cls");
        printf("\033[0;31m" "\n\n\tERROR EN LA ASIGNACION DE MEMORIA. \n" "\033[0m");
        system("pause");
    }

    else
    {
        system("cls");
        printf("\033[33m" "\n\n\t------------------------------------------------------\n" "\033[0m");
        printf("\033[33m" "\t\t MENU ADMINISTRADOR -> ALTA USUARIO\n" "\033[0m");
        printf("\033[33m" "\t------------------------------------------------------\n" "\033[0m");
        system("pause");



        // Obtener el nombre del usuario y verificar que sea válido
        do
        {
            system("cls");
            printf("\033[33m" "\n\n\t------------------------------------------------------\n" "\033[0m");
            printf("\033[33m" "\t\t MENU ADMINISTRADOR -> ALTA USUARIO\n" "\033[0m");
            printf("\033[33m" "\t------------------------------------------------------\n" "\033[0m");
            printf("\033[0;36m" "\n\n\tNombre [1-20]: " "\033[0m");
            fflush(stdin);
            scanf("%s", (*E_usuarios)[*num_usuarios].Nombre);
            if (strlen((*E_usuarios)[*num_usuarios].Nombre) > 20 || strlen((*E_usuarios)[*num_usuarios].Nombre) <=1)
            {
                system("cls");
                printf("\033[0;31m" "\n\n\tERROR: LONGITUD DE CADENA INCORRECTA. \n" "\033[0m");
                system("pause");
            }

        } while (strlen((*E_usuarios)[*num_usuarios].Nombre) > 20 || strlen((*E_usuarios)[*num_usuarios].Nombre) <=1);

        // Obtener la localidad del usuario y verificar que sea válida
        do
        {
            system("cls");
            printf("\033[33m" "\n\n\t------------------------------------------------------\n" "\033[0m");
            printf("\033[33m" "\t\t MENU ADMINISTRADOR -> ALTA USUARIO\n" "\033[0m");
            printf("\033[33m" "\t------------------------------------------------------\n" "\033[0m");
            printf("\033[0;36m" "\n\n\tLocalidad [1-20]: " "\033[0m");
            fflush(stdin);
            scanf("%s", (*E_usuarios)[*num_usuarios].Localidad);
            if (strlen((*E_usuarios)[*num_usuarios].Localidad) > 20 || strlen((*E_usuarios)[*num_usuarios].Localidad) <=1)
            {
                system("cls");
                printf("\033[0;31m" "\n\n\tERROR: LONGITUD DE CADENA INCORRECTA. \n" "\033[0m");
                system("pause");
            }

        } while (strlen((*E_usuarios)[*num_usuarios].Localidad) > 20 || strlen((*E_usuarios)[*num_usuarios].Localidad) <=1);


        (*E_usuarios)[*num_usuarios].Perfil = 'u';

        // Obtener el nombre de usuario y verificar que sea válido
        do
        {
            system("cls");
            printf("\033[33m" "\n\n\t------------------------------------------------------\n" "\033[0m");
            printf("\033[33m" "\t\t MENU ADMINISTRADOR -> ALTA USUARIO\n" "\033[0m");
            printf("\033[33m" "\t------------------------------------------------------\n" "\033[0m");
            printf("\033[0;36m" "\n\n\tUsuario [1-5]: " "\033[0m");
            fflush(stdin);
            scanf("%s", (*E_usuarios)[*num_usuarios].Usuario);
            if (strlen((*E_usuarios)[*num_usuarios].Usuario) > 5 || strlen((*E_usuarios)[*num_usuarios].Usuario) <=1)
            {
                system("cls");
                printf("\033[0;31m" "\n\n\tERROR: LONGITUD DE CADENA INCORRECTA. \n" "\033[0m");
                system("pause");
            }

        } while (strlen((*E_usuarios)[*num_usuarios].Usuario) > 5 || strlen((*E_usuarios)[*num_usuarios].Usuario) <=1);

        // Obtener la contraseña y verificar que sea válida
        do
        {
            system("cls");
            printf("\033[33m" "\n\n\t------------------------------------------------------\n" "\033[0m");
            printf("\033[33m" "\t\t MENU ADMINISTRADOR -> ALTA USUARIO\n" "\033[0m");
            printf("\033[33m" "\t------------------------------------------------------\n" "\033[0m");
            printf("\033[0;36m" "\n\n\tPassword [1-8] :" "\033[0m");
            fflush(stdin);
            scanf("%s", (*E_usuarios)[*num_usuarios].Password);
            if (strlen((*E_usuarios)[*num_usuarios].Password) > 8 || strlen((*E_usuarios)[*num_usuarios].Password) <=1)
            {
                system("cls");
                printf("\033[0;31m" "\n\n\tERROR: LONGITUD DE CADENA INCORRECTA. \n" "\033[0m");
                system("pause");
            }
        } while (strlen((*E_usuarios)[*num_usuarios].Password) > 8 || strlen((*E_usuarios)[*num_usuarios].Password) <=1);

        // Actualizar el número de usuarios
        (*num_usuarios)++;

        // Actualizar los Id's de los usuarios para que queden ordenados
        for (i = 0; i < *num_usuarios; i++)
        {
            sprintf((*E_usuarios)[i].Id_usuario, "%04d", i+1);
        }
        system("cls");
        printf("\033[0;32m" "\n\n\tUsuario dado de alta con exito!: " "\033[0m");
        system("pause");
    }

}

void consultarUsuario(Usuarios *E_usuarios, int num_usuarios) {

    int i, encontrado = 0;
    char id[5];



    system("cls");
    printf("\033[33m" "\n\n\t------------------------------------------------------\n" "\033[0m");
    printf("\033[33m" "\t\t MENU ADMINISTRADOR -> CONSULTAR USUARIO\n" "\033[0m");
    printf("\033[33m" "\t------------------------------------------------------\n" "\033[0m");
    printf("\033[35m" "\n\tIngrese el ID del usuario a consultar (0001-9999): " "\033[0m");
    scanf("%4s", id);

    // Buscar el usuario en el vector de struct
    for (i = 0; i < num_usuarios; i++)
    {
        if (strcmp(E_usuarios[i].Id_usuario, id) == 0)
        {
            encontrado = 1;
            system("cls");
            printf("\033[33m" "\n\tDatos del Usuario con id %s:\n" "\033[0m", id);
            printf("\033[0;36m" "\n\tID de usuario: %s\n" "\033[0m", E_usuarios[i].Id_usuario);
            printf("\033[0;36m" "\tNombre: %s\n" "\033[0m", E_usuarios[i].Nombre);
            printf("\033[0;36m" "\tLocalidad: %s\n" "\033[0m", E_usuarios[i].Localidad);
            printf("\033[0;36m" "\tPerfil: %c\n" "\033[0m", E_usuarios[i].Perfil);
            printf("\033[0;36m" "\tUsuario: %s\n\n" "\033[0m", E_usuarios[i].Usuario);
            system("pause");
        }

    }

    if (encontrado == 0)
    {
        system("cls");
        printf("\033[0;31m" "\n\n\tERROR: El usuario con ID %s no fue encontrado. \n" "\033[0m", id);
        system("pause");
    }


}

void modificarUsuario(Usuarios **E_usuarios, int num_usuarios) {

    int i, opcion, posicionUsuario, encontrado = 0;
    char id[5];

    system("cls");
    printf("\033[33m" "\n\n\t------------------------------------------------------\n" "\033[0m");
    printf("\033[33m" "\t\t MENU ADMINISTRADOR -> MODIFICAR USUARIO\n" "\033[0m");
    printf("\033[33m" "\t------------------------------------------------------\n" "\033[0m");
    printf("\033[35m" "\n\tIngrese el ID del usuario a modificar (0001-9999): " "\033[0m");
    scanf("%4s", id);

    // Buscar el usuario en el vector de struct
    for (i = 0; i < num_usuarios; i++)
    {
        if (strcmp((*E_usuarios)[i].Id_usuario, id) == 0)
        {
            posicionUsuario = i;
            encontrado = 1;
        }

    }

    if (encontrado == 1)
    {
        do
        {
            system("cls");
            printf("\033[33m" "\n\n\t------------------------------------------------------\n" "\033[0m");
            printf("\033[33m" "\t\t MENU ADMINISTRADOR -> MODIFICAR USUARIO\n" "\033[0m");
            printf("\033[33m" "\t------------------------------------------------------\n" "\033[0m");
            printf("\033[0;36m" "\n\n\t 1. Nombre \n" "\033[0m");
            printf("\033[0;36m" "\t 2. Localidad \n" "\033[0m");
            printf("\033[0;36m" "\t 3. Usuario \n" "\033[0m");
            printf("\033[0;36m" "\t 4. Password \n" "\033[0m");
            printf("\033[0;36m" "\t 5. Volver al menu de Administrador \n" "\033[0m");
            printf("\033[0;35m" "\n\tSeleccione el campo a editar: " "\033[0m");
            scanf("%i",&opcion);

            switch(opcion)
            {
                case 1:
                    {
                        do
                        {
                            system("cls");
                            printf("\033[33m" "\n\n\t------------------------------------------------------\n" "\033[0m");
                            printf("\033[33m" "\t\t MENU ADMINISTRADOR -> MODIFICAR USUARIO\n" "\033[0m");
                            printf("\033[33m" "\t------------------------------------------------------\n" "\033[0m");
                            printf("\033[0;36m" "\n\n\tNombre [1-20]: " "\033[0m");
                            fflush(stdin);
                            scanf("%s", (*E_usuarios)[posicionUsuario].Nombre);
                            if (strlen((*E_usuarios)[posicionUsuario].Nombre) > 20 || strlen((*E_usuarios)[posicionUsuario].Nombre) <=1)
                            {
                                system("cls");
                                printf("\033[0;31m" "\n\n\tERROR: LONGITUD DE CADENA INCORRECTA. \n" "\033[0m");
                                system("pause");
                            }

                        } while (strlen((*E_usuarios)[posicionUsuario].Nombre) > 20 || strlen((*E_usuarios)[posicionUsuario].Nombre) <=1);
                        printf("\033[0;32m" "\n\n\tNombre modificado con exito!: " "\033[0m");
                        break;
                    }
                case 2:
                    {
                        do
                        {
                            system("cls");
                            printf("\033[33m" "\n\n\t------------------------------------------------------\n" "\033[0m");
                            printf("\033[33m" "\t\t MENU ADMINISTRADOR -> MODIFICAR USUARIO\n" "\033[0m");
                            printf("\033[33m" "\t------------------------------------------------------\n" "\033[0m");
                            printf("\033[0;36m" "\n\n\tLocalidad [1-20]: " "\033[0m");
                            fflush(stdin);
                            scanf("%s", (*E_usuarios)[posicionUsuario].Localidad);
                            if (strlen((*E_usuarios)[posicionUsuario].Localidad) > 20 || strlen((*E_usuarios)[posicionUsuario].Localidad) <=1)
                            {
                                system("cls");
                                printf("\033[0;31m" "\n\n\tERROR: LONGITUD DE CADENA INCORRECTA. \n" "\033[0m");
                                system("pause");
                            }

                        } while (strlen((*E_usuarios)[posicionUsuario].Localidad) > 20 || strlen((*E_usuarios)[posicionUsuario].Localidad) <=1);
                        printf("\033[0;32m" "\n\n\tLocalidad modificada con exito!: " "\033[0m");
                        break;
                    }
                case 3:
                    {
                        do
                        {
                            system("cls");
                            printf("\033[33m" "\n\n\t------------------------------------------------------\n" "\033[0m");
                            printf("\033[33m" "\t\t MENU ADMINISTRADOR -> MODIFICAR USUARIO\n" "\033[0m");
                            printf("\033[33m" "\t------------------------------------------------------\n" "\033[0m");
                            printf("\033[0;36m" "\n\n\tUsuario [1-5]: " "\033[0m");
                            fflush(stdin);
                            scanf("%s", (*E_usuarios)[posicionUsuario].Usuario);
                            if (strlen((*E_usuarios)[posicionUsuario].Usuario) > 5 || strlen((*E_usuarios)[posicionUsuario].Usuario) <=1)
                            {
                                system("cls");
                                printf("\033[0;31m" "\n\n\tERROR: LONGITUD DE CADENA INCORRECTA. \n" "\033[0m");
                                system("pause");
                            }


                        } while (strlen((*E_usuarios)[posicionUsuario].Usuario) > 5 || strlen((*E_usuarios)[posicionUsuario].Usuario) <=1);
                        printf("\033[0;32m" "\n\n\tUsuario modificado con exito!: " "\033[0m");
                        break;
                    }
                case 4:
                    {
                        do
                        {
                            system("cls");
                            printf("\033[33m" "\n\n\t------------------------------------------------------\n" "\033[0m");
                            printf("\033[33m" "\t\t MENU ADMINISTRADOR -> MODIFICAR USUARIO\n" "\033[0m");
                            printf("\033[33m" "\t------------------------------------------------------\n" "\033[0m");
                            printf("\033[0;36m" "\n\n\tPassword [1-8]: " "\033[0m");
                            fflush(stdin);
                            scanf("%s", (*E_usuarios)[posicionUsuario].Password);
                            if (strlen((*E_usuarios)[posicionUsuario].Password) > 8 || strlen((*E_usuarios)[posicionUsuario].Password) <=1)
                            {
                                system("cls");
                                printf("\033[0;31m" "\n\n\tERROR: LONGITUD DE CADENA INCORRECTA. \n" "\033[0m");
                                system("pause");
                            }
                        } while (strlen((*E_usuarios)[posicionUsuario].Password) > 8 || strlen((*E_usuarios)[posicionUsuario].Password) <=1);
                        printf("\033[0;32m" "\n\n\tPassword modificada con exito!: " "\033[0m");
                        break;
                    }
            }

        } while (opcion != 5);
    }



    else
    {
        system("cls");
        printf("\033[0;31m" "\n\n\tERROR: El usuario con ID %s no fue encontrado. \n" "\033[0m", id);
        system("pause");
    }

}

void mostrarUsuario(Usuarios *E_usuarios, int posicionUsuario) {


    printf("\033[33m" "\n\n\t------------------------------------------------------\n" "\033[0m");
    printf("\033[33m" "\t\t MENU USUARIO -> VER PERFIL\n" "\033[0m");
    printf("\033[33m" "\t------------------------------------------------------\n\n" "\033[0m");
    printf("\033[0;36m" "\n\tID de usuario: %s\n" "\033[0m", E_usuarios[posicionUsuario].Id_usuario);
    printf("\033[0;36m" "\tNombre: %s\n" "\033[0m", E_usuarios[posicionUsuario].Nombre);
    printf("\033[0;36m" "\tLocalidad: %s\n" "\033[0m", E_usuarios[posicionUsuario].Localidad);
    printf("\033[0;36m" "\tPerfil: %c\n" "\033[0m", E_usuarios[posicionUsuario].Perfil);
    printf("\033[0;36m" "\tUsuario: %s\n" "\033[0m", E_usuarios[posicionUsuario].Usuario);


}

void editarUsuario(Usuarios **E_usuarios, int posicionUsuario) {

    char opcion;
    int opcion2;

    printf("\033[0;35m" "\n\tEditar Perfil? (s/n): " "\033[0m");

    fflush(stdin);
    scanf("%c", &opcion);

    if (opcion == 's' || opcion == 'S')
    {
        system("cls");
        printf("\033[33m" "\n\n\t------------------------------------------------------\n" "\033[0m");
        printf("\033[33m" "\t\t MENU USUARIO -> EDITAR PERFIL\n" "\033[0m");
        printf("\033[33m" "\t------------------------------------------------------\n\n" "\033[0m");
        printf("\033[0;36m" "\n\n\t 1. Nombre \n" "\033[0m");
        printf("\033[0;36m" "\t 2. Localidad \n" "\033[0m");
        printf("\033[0;36m" "\t 3. Usuario \n" "\033[0m");
        printf("\033[0;36m" "\t 4. Password \n" "\033[0m");
        printf("\033[0;35m" "\n\tSeleccione el campo a editar: " "\033[0m");
        scanf("%i",&opcion2);

        switch(opcion2)
        {
        case 1:
            {
                do
                {
                    system("cls");
                    printf("\033[33m" "\n\n\t------------------------------------------------------\n" "\033[0m");
                    printf("\033[33m" "\t\t MENU USUARIO -> EDITAR PERFIL\n" "\033[0m");
                    printf("\033[33m" "\t------------------------------------------------------\n\n" "\033[0m");
                    printf("\033[0;36m" "\n\n\tNombre [1-20]: " "\033[0m");
                    fflush(stdin);
                    scanf("%s", (*E_usuarios)[posicionUsuario].Nombre);
                    if (strlen((*E_usuarios)[posicionUsuario].Nombre) > 20 || strlen((*E_usuarios)[posicionUsuario].Nombre) <=1)
                        {
                            system("cls");
                            printf("\033[0;31m" "\n\n\tERROR: LONGITUD DE CADENA INCORRECTA. \n" "\033[0m");
                            system("pause");
                        }

                } while (strlen((*E_usuarios)[posicionUsuario].Nombre) > 20 || strlen((*E_usuarios)[posicionUsuario].Nombre) <=1);
                break;
            }
        case 2:
            {
                do
                {
                    system("cls");
                    printf("\033[33m" "\n\n\t------------------------------------------------------\n" "\033[0m");
                    printf("\033[33m" "\t\t MENU USUARIO -> EDITAR PERFIL\n" "\033[0m");
                    printf("\033[33m" "\t------------------------------------------------------\n\n" "\033[0m");
                    printf("\033[0;36m" "\n\n\tLocalidad [1-20]: " "\033[0m");
                    fflush(stdin);
                    scanf("%s", (*E_usuarios)[posicionUsuario].Localidad);
                    if (strlen((*E_usuarios)[posicionUsuario].Localidad) > 20 || strlen((*E_usuarios)[posicionUsuario].Localidad) <=1)
                        {
                            system("cls");
                            printf("\033[0;31m" "\n\n\tERROR: LONGITUD DE CADENA INCORRECTA. \n" "\033[0m");
                            system("pause");
                        }

                } while (strlen((*E_usuarios)[posicionUsuario].Localidad) > 20 || strlen((*E_usuarios)[posicionUsuario].Localidad) <=1);
                break;
            }
        case 3:
            {
                do
                {
                    system("cls");
                    printf("\033[33m" "\n\n\t------------------------------------------------------\n" "\033[0m");
                    printf("\033[33m" "\t\t MENU USUARIO -> EDITAR PERFIL\n" "\033[0m");
                    printf("\033[33m" "\t------------------------------------------------------\n\n" "\033[0m");
                    printf("\033[0;36m" "\n\n\tUsuario [1-5]: " "\033[0m");
                    fflush(stdin);
                    scanf("%s", (*E_usuarios)[posicionUsuario].Usuario);
                    if (strlen((*E_usuarios)[posicionUsuario].Usuario) > 5 || strlen((*E_usuarios)[posicionUsuario].Usuario) <=1)
                        {
                            system("cls");
                            printf("\033[0;31m" "\n\n\tERROR: LONGITUD DE CADENA INCORRECTA. \n" "\033[0m");
                            system("pause");
                        }

                } while (strlen((*E_usuarios)[posicionUsuario].Usuario) > 5 || strlen((*E_usuarios)[posicionUsuario].Usuario) <=1);
                break;
            }
        case 4:
            {
                do
                {
                    system("cls");
                    printf("\033[33m" "\n\n\t------------------------------------------------------\n" "\033[0m");
                    printf("\033[33m" "\t\t MENU USUARIO -> EDITAR PERFIL\n" "\033[0m");
                    printf("\033[33m" "\t------------------------------------------------------\n\n" "\033[0m");
                    printf("\033[0;36m" "\n\n\tPassword [1-8]: " "\033[0m");
                    fflush(stdin);
                    scanf("%s", (*E_usuarios)[posicionUsuario].Password);
                    if (strlen((*E_usuarios)[posicionUsuario].Password) > 8 || strlen((*E_usuarios)[posicionUsuario].Password) <=1)
                        {
                            system("cls");
                            printf("\033[0;31m" "\n\n\tERROR: LONGITUD DE CADENA INCORRECTA. \n" "\033[0m");
                            system("pause");
                        }
                } while (strlen((*E_usuarios)[posicionUsuario].Password) > 8 || strlen((*E_usuarios)[posicionUsuario].Password) <=1);
                break;
            }
        }
        system("cls");
        printf("\033[0;32m" "\n\n\tUsuario editado con exito! \n" "\033[0m");
        system("pause");

    }

    system("cls");
    printf("\033[0;32m" "\n\n\tVolviendo al menu usuario de %s... \n" "\033[0m", (*E_usuarios)[posicionUsuario].Nombre);
    system("pause");

}


void loginUsuarios(Usuarios *E_usuarios, int num_usuarios, int *posicionUsuario)
{
    int i, u, p, error;
    char Usuario[6], Password[9];



    // Mientras error = 1, no habrá ningún logueo completado, y sigue haciendo login, si error = 0, logueo completado.
    error = 1;
    do
    {
        printf("\033[33m" "\n\n\t ---------------------------\n" "\033[0m");
        printf("\033[33m" "\t\t ESI - Share\n" "\033[0m");
        printf("\033[33m" "\t ---------------------------\n" "\033[0m");
        printf("\033[0;36m" "\n\n\t Usuario: " "\033[0m");
        gets(Usuario);
        printf("\033[0;36m" "\n\t Password: " "\033[0m");
        gets(Password);


        for(i = 0; i < num_usuarios; i++)
        {
            u = strcmp(E_usuarios[i].Usuario, Usuario);
            p = strcmp(E_usuarios[i].Password, Password);
            if(u==0 && p==0)
            {
                *posicionUsuario = i;
                error = 0;
                system("cls");
                printf("\033[0;32m" "\n\n\tBienvenido %s\n" "\033[0m", E_usuarios[i].Nombre);
                system("pause");
            }
            else if (error == 1 && i == num_usuarios - 1)
            {
                system("cls");
                printf("\033[31m" "\n\n\tERROR : USUARIO O PASSWORD INCORRECTO! \n" "\033[0m");
                printf("\033[31m" "\n\tVolviendo a login... \n" "\033[0m");
                system("pause");
                system("cls");
            }

        }
    }while(error != 0);


}


void menuUsuario(Usuarios **E_usuarios, int *num_usuarios, int *posicionUsuario,
                 Viajes **E_viajes, int *num_viajes,
                 Vehiculos **E_vehiculos, int *num_vehiculos,
                 Pasos **E_pasos, int *num_pasos)

{
    int opcion;

    do
    {
        system("cls");
        printf("\033[33m" "\n\n\t ----------------------------\n" "\033[0m");
        printf("\033[33m" "\t\t MENU USUARIO\n" "\033[0m");
        printf("\033[33m" "\t ----------------------------\n" "\033[0m");
        printf("\033[0;35m" "\n\t *USUARIO ACTUAL*: %s\n" "\033[0m", (*E_usuarios)[*posicionUsuario].Nombre);
        printf("\033[0;36m" "\n\n\t 1. Perfil \n" "\033[0m");
        printf("\033[0;36m" "\t 2. Vehiculos \n" "\033[0m");
        printf("\033[0;36m" "\t 3. Viajes \n" "\033[0m");
        printf("\033[0;36m" "\t 4. Salir \n" "\033[0m");
        printf("\033[0;35m" "\n\n\t Seleccione una opcion: " "\033[0m");

        fflush(stdin);
        scanf("%i",&opcion);
        system("cls");

        switch (opcion)
        {
            case 1:
                {
                    mostrarUsuario(*E_usuarios, *posicionUsuario);
                    editarUsuario(E_usuarios, *posicionUsuario);
                    break;
                }
            case 2:
                {
                    menuVehiculosUser((*E_usuarios)[*posicionUsuario].Id_usuario,E_vehiculos,num_vehiculos);
                    break;
                }
            case 3:
                {
                    menuViajeUsuario(E_viajes, num_viajes, posicionUsuario, E_pasos, num_pasos, E_usuarios, num_usuarios, E_vehiculos, num_vehiculos);
                    break;
                }

        }
    } while (opcion!=4);



}

void menuAdministrador(Usuarios **E_usuarios, int *num_usuarios, int *posicionUsuario,
                       Viajes **E_viajes, int *num_viajes,
                       Vehiculos **E_vehiculos, int *num_vehiculos,
                       Pasos **E_pasos, int *num_pasos)

{
    int opcion, opcion2;
    do
    {
        system("cls");
        printf("\033[33m" "\n\n\t -------------------------------\n" "\033[0m");
        printf("\033[33m" "\t\t MENU ADMINISTRADOR\n" "\033[0m");
        printf("\033[33m" "\t -------------------------------\n" "\033[0m");
        printf("\033[0;35m" "\n\t *ADMINISTRADOR ACTUAL*: %s\n" "\033[0m", (*E_usuarios)[*posicionUsuario].Nombre);
        printf("\033[0;36m" "\n\n\t 1. Usuarios \n" "\033[0m");
        printf("\033[0;36m" "\t 2. Vehiculos \n" "\033[0m");
        printf("\033[0;36m" "\t 3. Viajes \n" "\033[0m");
        printf("\033[0;36m" "\t 4. Salir \n" "\033[0m");
        printf("\033[0;35m" "\n\n\t Seleccione una opcion: " "\033[0m");

        fflush(stdin);
        scanf("%i",&opcion);
        system("cls");

        switch (opcion)
        {
            case 1:
                {
                    printf("\033[33m" "\n\n\t------------------------------------------------------\n" "\033[0m");
                    printf("\033[33m" "\t\t MENU USUARIO -> GESTIONAR USUARIOS\n" "\033[0m");
                    printf("\033[33m" "\t------------------------------------------------------\n\n" "\033[0m");
                    printf("\033[0;36m" "\n\n\t 1. Alta a un Usuario \n" "\033[0m");
                    printf("\033[0;36m" "\t 2. Baja a un Usuario \n" "\033[0m");
                    printf("\033[0;36m" "\t 3. Modificar un Usuario \n" "\033[0m");
                    printf("\033[0;36m" "\t 4. Consultar un Usuario \n" "\033[0m");
                    printf("\033[0;36m" "\t 5. Salir \n" "\033[0m");
                    printf("\033[0;35m" "\n\n\t Seleccione una opcion: " "\033[0m");
                    fflush(stdin);
                    scanf("%i",&opcion2);

                    switch(opcion2)
                    {
                        case 1: altaUsuario(E_usuarios, num_usuarios); break;
                        case 2: bajaUsuario(E_usuarios, num_usuarios); break;
                        case 3: modificarUsuario(E_usuarios, *num_usuarios); break;
                        case 4: consultarUsuario(*E_usuarios, *num_usuarios); break;
                    }
                    break;
                }
             case 2:
                 {
                     menuVehiculosAdmin(E_vehiculos,num_vehiculos);
                     break;
                 }
             case 3:
                {
                    menuViajesAdmin(E_viajes, num_viajes, E_pasos, num_pasos, E_usuarios, num_usuarios, E_vehiculos, num_vehiculos);
                    break;
                }



        }

    } while (opcion!=4);



}


