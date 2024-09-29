#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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



void imprimirVehiculosAdmin (Vehiculos *E_vehiculos, int tam_vehiculo)
{
    bool atLeast1;
    int i;
    unsigned contador = 0; //
    atLeast1 = false;

    system("cls");
    printf
    ("\033[33m" "\n\n\t------------------------------------------------------\n" "\033[0m"  //Este printf está asi por motivos esteticos al verse en el compilador
     "\033[33m" "\t\t ADMINISTRADOR -> VEHICULOS REGISTRADOS\n" "\033[0m");
    for (i = 0; i < tam_vehiculo; i++) //Imprimiremos todos los vehiculos del sistema sin ninguna comprobacion adicional
    {
      contador++;
      printf
       ("\033[33m" "\t------------------------------------------------------\n\n" "\033[0m"
       "\033[0;36m" "\n\tVehiculo: %u\n" "\033[0m"
       "\033[0;36m" "\tMatricula: %s\n" "\033[0m"
       "\033[0;36m" "\tID del usuario: %s\n" "\033[0m"
       "\033[0;36m" "\tPlazas del vehiculo: %i\n" "\033[0m"
       "\033[0;36m" "\tDescripcion del vehiculo: %s\n" "\033[0m"
       ,contador
       ,E_vehiculos[i].Id_mat
       ,E_vehiculos[i].Id_usuario
       ,E_vehiculos[i].Num_plazas
       ,E_vehiculos[i].Desc_veh
       );
       atLeast1=true;
    }
    if (atLeast1 == false && i == tam_vehiculo) //Cuando la hemos recorrido y no habia ningun vehiculo en el sistema daremos un mensaje de error
    {
        printf
        ("\033[0;31m" "\n\tERROR: NO HAY VEHICULOS DADOS DE ALTA EN EL SISTEMA" "\033[0m"
         "\033[31m" "\n\tVolviendo a menu vehiculos... \n" "\033[0m");
    }
}


void imprimirVehiculos(char Id_usuario[], Vehiculos *E_vehiculos, int tam_vehiculo)
{
    bool atLeast1;
    unsigned contador = 0;
    int i;
    atLeast1 = false;
    system("cls");
    printf
    ("\033[33m" "\n\n\t------------------------------------------------------\n" "\033[0m" //Este printf se ve raro pero es por mejoras estéticas al compilar
     "\033[33m" "\t\t USUARIO -> MIS VEHICULOS\n" "\033[0m");
    for (i = 0; i < tam_vehiculo; i++)
    {
      if(strcmp(E_vehiculos[i].Id_usuario,Id_usuario)==0)
      {
          atLeast1 = true;
          contador++;
          printf
          (
           "\033[33m" "\t------------------------------------------------------\n\n" "\033[0m"
           "\033[0;36m" "\n\tVehiculo: %u\n" "\033[0m"
           "\033[0;36m" "\tMatricula: %s\n" "\033[0m"
           "\033[0;36m" "\tPlazas del vehiculo: %i\n" "\033[0m"
           "\033[0;36m" "\tDescripcion del vehiculo: %s\n" "\033[0m"
           ,contador
           ,E_vehiculos[i].Id_mat
           ,E_vehiculos[i].Num_plazas
           ,E_vehiculos[i].Desc_veh);
      }
    }
    if (atLeast1 == false && i==tam_vehiculo) //Cuando la hemos recorrido y no habia ningun vehiculo en el sistema registrado para ese usuario daremos un mensaje de error antes de volver
    {
        printf
        ("\033[0;31m" "\n\tERROR: NO DISPONE DE VEHICULOS DADOS DE ALTA\n""\033[0m"
         "\033[;31m" "\n\tVolviendo a menu vehiculos... \n" "\033[0m");
    }
}

void annadirVehiculoAdmin(Vehiculos **E_vehiculos, int *tam_vehiculo)
{
    char Id_usuarioChange[5];
    do
    {
        system ("cls");
        printf
        ("\033[33m" "\n\n\t------------------------------------------------------\n" "\033[0m"
         "\033[33m" "\t\t MENU VEHICULO DE ADMIN -> ALTA VEHICULOS\n" "\033[0m"
         "\033[33m" "\t------------------------------------------------------\n\n" "\033[0m"
         "\033[35m" "\n\tBienvenido administrador, cual es la id del usuario que desea dar de alta: " "\033[0m");
        fflush(stdin);
        scanf("%s", Id_usuarioChange);
    }while (strlen(Id_usuarioChange) != 4);
    annadirVehiculo(Id_usuarioChange, E_vehiculos, tam_vehiculo );
}

void annadirVehiculo(char Id_usuarioLog[], Vehiculos **E_vehiculos, int *tam_vehiculo)
{
    char Id_matAnnadir [8],Desc_vehAnnadir[51]; //Variables usadas para comprobar antes de añadir
    int  num_plazasAnnadir, i;
    bool AlreadyReg;
    do
    {
        AlreadyReg = false;
        do
        {
            system("cls");
            printf
            ("\033[33m" "\n\n\t------------------------------------------------------\n" "\033[0m"
             "\033[33m" "\t\t MENU VEHICULO -> ALTA VEHICULOS\n" "\033[0m"
             "\033[33m" "\t------------------------------------------------------\n\n" "\033[0m"
             "\033[35m" "\n\tIntroduzca matricula del vehiculo que desea dar de alta:  \n\t(7 caracteres como maximo): " "\033[0m");
            fflush(stdin);
            scanf("\t%s", Id_matAnnadir);
            for (i=0;i<(*tam_vehiculo);i++)
            {
                if(strcmp((*E_vehiculos)[i].Id_mat,Id_matAnnadir)==0)
                {
                    printf("\033[0;31m" "\n\tERROR: MATRICULA YA REGISTRADA\n" "\033[0m");
                    system("pause");
                    AlreadyReg=true;
                    i=(*tam_vehiculo);
                }
            }
        }while (strlen(Id_matAnnadir) > 7 || strlen(Id_matAnnadir) <=1); //Comprobamos que el tipo de dato introducido tiene la longitud adecuada
    }while (AlreadyReg==true); //Seguiremos pidiendo matriculas hasta que nos de una no registrada

    do
    {
        printf("\033[35m" "\n\tDescripcion del vehiculo:(Hasta 50 caracteres): " "\033[0m");
        fflush(stdin);
        scanf("\t%s", Desc_vehAnnadir);
    }while (strlen(Desc_vehAnnadir) > 50 || strlen(Desc_vehAnnadir) <=1);

    printf("\033[35m" "\n\tEscriba el numero de plazas del vehiculo: " "\033[0m");
    fflush(stdin);
    scanf("\t%i", &num_plazasAnnadir);

    (*tam_vehiculo)++;

    *E_vehiculos = realloc(*E_vehiculos, *tam_vehiculo * sizeof(Vehiculos));
    if ((*E_vehiculos) == NULL) //Comprobar que se registran bien la reserva de espacio en la estructura
    {
        printf("\033[0;31m" "\n\t ERROR AL ASIGNAR MEMORIA\n" "\033[0m");
    }else printf("\033[0;32m" "\n\t Vehiculo dado de alta!\n" "\033[0m");

    system("pause");

    strcpy((*E_vehiculos)[(*tam_vehiculo)-1].Id_mat, Id_matAnnadir);
    strcpy((*E_vehiculos)[(*tam_vehiculo)-1].Id_usuario, Id_usuarioLog);
    (*E_vehiculos)[(*tam_vehiculo)-1].Num_plazas = num_plazasAnnadir;
    strcpy((*E_vehiculos)[(*tam_vehiculo)-1].Desc_veh, Desc_vehAnnadir);
}

void eliminarVehiculoAdmin(Vehiculos **E_vehiculos, int *tam_vehiculo)
{
    char Id_matBorrar[8];
    int i, posicionEliminar;
    bool exist;
    exist = false;
    do
    {
        printf
        ("\033[33m" "\n\n\t------------------------------------------------------\n" "\033[0m"
         "\033[33m" "\t\t MENU VEHICULO ADMINISTRADOR -> ELIMINAR VEHICULOS\n" "\033[0m"
         "\033[33m" "\t------------------------------------------------------\n\n" "\033[0m"
         "\033[35m" "\n\tIntroduzca la matricula del vehiculo que desea borrar: " "\033[0m");
        fflush(stdin);
        scanf("%s",Id_matBorrar);
        for(i=0;i<(*tam_vehiculo);i++) //Comprobamos que dicha matricula exista y almacenamos su posicion en posicionEliminar
        {
            if(strcmp((*E_vehiculos)[i].Id_mat,Id_matBorrar)==0)
                {
                   exist=true;
                   posicionEliminar = i;
                }
        }
        if (exist == false && i == (*tam_vehiculo))
        {
            printf
            ("\033[0;31m" "\n\tNo existe dicho vehiculo, o no pertenece a la persona adecuada\n" "\033[0m");
            system("pause");
        }
    }while (exist==false);
    if (exist == true) //Eliminamos dicho vehiculo, moviendo uno menos todos los que hay delante de el
    {
        for(i = posicionEliminar; i< *tam_vehiculo - 1; i++)
        {
            strcpy((*E_vehiculos)[i].Id_mat,(*E_vehiculos)[i+1].Id_mat);
            strcpy((*E_vehiculos)[i].Id_usuario,(*E_vehiculos)[i+1].Id_usuario);
            (*E_vehiculos)[i].Num_plazas = (*E_vehiculos)[i+1].Num_plazas;
            strcpy((*E_vehiculos)[i].Desc_veh,(*E_vehiculos)[i+1].Desc_veh);
        }
        //Eliminar uno de los vehiculos y hacer sizeof para reasignar memoria para struct
        (*tam_vehiculo)--;
        *E_vehiculos = realloc(*E_vehiculos, *tam_vehiculo * sizeof(Vehiculos));
        system ("cls");
        printf("\033[0;32m" "\n\tModificacion hecha con exito \n" "\033[0m");
        system ("pause");
    }
}

void eliminarVehiculos(char Id_UsuarioLog[], Vehiculos **E_vehiculos, int *tam_vehiculo)
{
    char Id_matBorrar[8];
    int i, posicionEliminar;
    bool exist;
    exist = false;
    do
    {
        printf
        ("\033[33m" "\n\n\t------------------------------------------------------\n" "\033[0m"
         "\033[33m" "\t\t MENU VEHICULO -> ELIMINAR VEHICULOS\n" "\033[0m"
         "\033[33m" "\t------------------------------------------------------\n\n" "\033[0m"
         "\033[35m" "\n\tIntroduzca la matricula que desea borrar de sus vehiculos: " "\033[0m");
        fflush(stdin);
        scanf("%s",Id_matBorrar);
        for(i=0;i<(*tam_vehiculo);i++) //Comprobamos que dicha matricula exista y que es del usuario logeado, almacenamos su posicion en posicionEliminar
        {
            if(strcmp((*E_vehiculos)[i].Id_mat,Id_matBorrar)==0 && strcmp((*E_vehiculos)[i].Id_usuario,Id_UsuarioLog)==0)
                {
                   exist=true;
                   posicionEliminar = i;
                }
        }
        if (exist == false && i == (*tam_vehiculo)) printf("\033[0;31m" "\n\tNo existe dicho vehiculo, o no pertenece a la persona adecuada" "\033[0m");
    }while (exist==false);
    if (exist == true)
    {
        for(i = posicionEliminar; i< *tam_vehiculo - 1; i++)
        {
            strcpy((*E_vehiculos)[i].Id_mat,(*E_vehiculos)[i+1].Id_mat);
            strcpy((*E_vehiculos)[i].Id_usuario,(*E_vehiculos)[i+1].Id_usuario);
            (*E_vehiculos)[i].Num_plazas = (*E_vehiculos)[i+1].Num_plazas;
            strcpy((*E_vehiculos)[i].Desc_veh,(*E_vehiculos)[i+1].Desc_veh);
        }
        //Eliminar uno de los vehiculos y hacer sizeof para reasignar memoria para struct
        (*tam_vehiculo)--;
        *E_vehiculos = realloc(*E_vehiculos, *tam_vehiculo * sizeof(Vehiculos));
        system ("cls");
        printf("\033[0;32m" "\n\tModificacion hecha con exito \n" "\033[0m");
        system ("pause");
    }

}

void modificarVehiculosAdmin (Vehiculos **E_vehiculos, int tam_vehiculo)
{
    char Id_matMod[8];
    int i,posicionVehiculo,opcionMenuMod;
    bool exist = false;
    posicionVehiculo = -1; //Uso un entero negativo y no mi tipo enum bool, porque asi con una sola variable, controlo si existe dicho vehiculo, y su posicion en la estructura
    do
    {
         printf
        ("\033[33m" "\n\n\t------------------------------------------------------\n" "\033[0m"
         "\033[33m" "\t\t MENU VEHICULO ADMIN -> MODIFICAR VEHICULOS\n" "\033[0m"
         "\033[33m" "\t------------------------------------------------------\n\n" "\033[0m"
         "\033[35m" "\n\tIntroduzca la matricula del vehiculo que desea modificar:" "\033[0m");
        fflush(stdin);
        scanf("%s", Id_matMod);
        system("cls");
        for(i=0;i<tam_vehiculo;i++)
        {
            if(strcmp((*E_vehiculos)[i].Id_mat,Id_matMod)==0)
            {
                posicionVehiculo=i;
                i=tam_vehiculo;
                exist = true;
            }else
            if (i==tam_vehiculo && exist == false)
                {
                    printf
                    ("\033[0;31m" "ERROR: INTRODUJO MAL LA MATRICULA" "\033[0m");
                    system("pause");
                }
        }
    }while (posicionVehiculo==-1); //Comprobamos que exista dicha matricula y si no volvemos a pedirselo

    //Imprimir datos de ese vehiculo antes de darselo al usuario
    system("cls");
      printf
       ("\033[33m" "\n\n\t----------------------------------------------------------------\n" "\033[0m"
        "\033[33m" "\t\t MENU VEHICULO ADMINISTRADOR -> MODIFICAR VEHICULO\n" "\033[0m"
        "\033[33m" "\t----------------------------------------------------------------\n" "\033[0m"
        "\033[33m" "\n\tVehiculo para modificar:\n" "\033[0m"
        "\033[0;36m" "\tMatricula: %s \n""\033[0m"
        "\033[0;36m" "\tPlazas vehiculo: %i \n" "\033[0m"
        "\033[0;36m" "\tDescripcion actual: %s \n""\033[0m"
        "\033[0;36m" "\tId Usuario: %s \n" "\033[0m"
       ,(*E_vehiculos)[posicionVehiculo].Id_mat
       ,(*E_vehiculos)[posicionVehiculo].Num_plazas
       ,(*E_vehiculos)[posicionVehiculo].Desc_veh
       ,(*E_vehiculos)[posicionVehiculo].Id_usuario);
       do
           {
             printf
            ("\033[0;36m" "\n\tQue desea modificar?\n" "\033[0m"
             "\033[0;36m" "\t1.Matricula\n" "\033[0m"
             "\033[0;36m" "\t2.Plazas del vehiculo\n" "\033[0m"
             "\033[0;36m" "\t3.Descripcion tierra\n" "\033[0m"
             "\033[0;36m" "\t4.Id Usuario\n" "\033[0m"
             "\033[0;36m" "\t5.Salir\n" "\033[0m"
             "\033[0;35m" "\n\n\t Seleccione una opcion: " "\033[0m");
             fflush(stdin);
             scanf("%i", &opcionMenuMod);
             switch(opcionMenuMod)
                {
                 case 1:
                     {
                     printf
                     ("\033[33m" "\n\n\t--------------------------------------------------------------\n" "\033[0m"
                      "\033[33m" "\t\t MENU VEHICULO ADMINISTRADOR -> MODIFICAR MATRICULA\n" "\033[0m"
                      "\033[33m" "\t--------------------------------------------------------------\n" "\033[0m"
                      "\033[0;36m" "\n\n\tMatricula nueva: " "\033[0m");
                     fflush(stdin);
                     scanf("\t%s",(*E_vehiculos)[posicionVehiculo].Id_mat);
                     break;
                     }
                 case 2:
                    {
                     printf
                     ("\033[33m" "\n\n\t--------------------------------------------------------------\n" "\033[0m"
                      "\033[33m" "\t\t MENU VEHICULO ADMINISTRADOR -> MODIFICAR PLAZAS\n" "\033[0m"
                      "\033[33m" "\t--------------------------------------------------------------\n" "\033[0m"
                      "\033[0;36m" "\n\n\tPlazas: " "\033[0m");
                    fflush(stdin);
                    scanf("\t%i",&(*E_vehiculos)[posicionVehiculo].Num_plazas);
                    break;
                    }
                 case 3:
                    {
                      printf
                     ("\033[33m" "\n\n\t--------------------------------------------------------------\n" "\033[0m"
                      "\033[33m" "\t\t MENU VEHICULO ADMINISTRADOR -> MODIFICAR DESCRIPCION\n" "\033[0m"
                      "\033[33m" "\t-------------------------------------------------------------\n" "\033[0m"
                      "\033[0;36m" "\n\n\tDescripcion nueva: " "\033[0m");
                     fflush(stdin);
                     scanf("\t%s",(*E_vehiculos)[posicionVehiculo].Desc_veh);
                     break;
                    }
                 case 4:
                    {
                      printf
                     ("\033[33m" "\n\n\t----------------------------------------------------------------\n" "\033[0m"
                      "\033[33m" "\t\t MENU VEHICULO ADMINISTRADOR -> MODIFICAR USUARIO\n" "\033[0m"
                      "\033[33m" "\t----------------------------------------------------------------\n" "\033[0m"
                      "\033[0;36m" "\n\n\tUsuario nuevo: " "\033[0m");
                     fflush(stdin);
                     scanf("\t%s",(*E_vehiculos)[posicionVehiculo].Id_usuario);
                     break;
                    }
                }
                printf("\033[0;32m" "\n\tModificacion hecha con exito\n" "\033[0m");
           }while(opcionMenuMod!=5);
}


void modificarVehiculos (char Id_UsuarioLog[], Vehiculos **E_vehiculos, int tam_vehiculo)
{
    char Id_matMod[8];
    int i,posicionVehiculo,opcionMenuMod;
    posicionVehiculo=-1;
    do
    {
        printf
        ("\033[33m" "\n\n\t----------------------------------------------------------------\n" "\033[0m"
         "\033[33m" "\t\t MENU VEHICULO USUARIO -> MODIFICAR VEHICULOS\n" "\033[0m"
         "\033[33m" "\t----------------------------------------------------------------\n\n" "\033[0m"
         "\033[35m" "\n\tIntroduzca la matricula del vehiculo que desea modificar:" "\033[0m");
        scanf("\t%s", Id_matMod);
        system("cls");
        for(i=0;i<tam_vehiculo;i++) //Comprobación de que la matricula registrada pertenece al usuario logeado actualmente
        {
            if((strcmp((*E_vehiculos)[i].Id_mat,Id_matMod)==0) && strcmp((*E_vehiculos)[i].Id_usuario,Id_UsuarioLog)==0)
            {
                posicionVehiculo=i;
                i=tam_vehiculo;
            }else if (i==tam_vehiculo && posicionVehiculo == -1)
                {
                    printf("\033[0;31m" "ERROR: INTRODUJO MAL LA MATRICULA" "\033[0m");
                    system("pause");
                }
        }
    }while (posicionVehiculo==-1);

    //Imprimir datos de ese vehiculo
    system("cls");
      printf
       ("\033[33m" "\n\n\t----------------------------------------------------------------\n" "\033[0m"
        "\033[33m" "\t\t MENU VEHICULO USUARIO -> MODIFICAR VEHICULO\n" "\033[0m"
        "\033[33m" "\t----------------------------------------------------------------\n" "\033[0m"
        "\033[33m" "\n\tVehiculo para modificar:\n" "\033[0m"
        "\033[0;36m" "\tMatricula: %s \n""\033[0m"
        "\033[0;36m" "\tPlazas vehiculo: %i \n" "\033[0m"
        "\033[0;36m" "\tDescripcion actual: %s \n""\033[0m"
       ,(*E_vehiculos)[posicionVehiculo].Id_mat
       ,(*E_vehiculos)[posicionVehiculo].Num_plazas
       ,(*E_vehiculos)[posicionVehiculo].Desc_veh);
       do
           {
             printf
            ("\033[0;36m" "\n\tQue desea modificar\n" "\033[0m"
             "\033[0;36m" "\t1.Matricula\n" "\033[0m"
             "\033[0;36m" "\t2.Plazas del vehiculo\n" "\033[0m"
             "\033[0;36m" "\t3.Descripcion tierra\n" "\033[0m"
             "\033[0;36m" "\t4.Salir\n" "\033[0m"
             "\033[0;35m" "\n\n\t Seleccione una opcion: " "\033[0m");
             fflush(stdin);
             scanf("\t%i", &opcionMenuMod);
             switch(opcionMenuMod)
                {
                 case 1:
                     {
                     printf
                     ("\033[33m" "\n\n\t--------------------------------------------------------------\n" "\033[0m"
                      "\033[33m" "\t\t MENU VEHICULO USUARIO -> MODIFICAR MATRICULA\n" "\033[0m"
                      "\033[33m" "\t--------------------------------------------------------------\n" "\033[0m"
                      "\033[0;36m" "\n\n\tMatricula nueva: " "\033[0m");
                      fflush(stdin);
                      scanf("\t%s",(*E_vehiculos)[posicionVehiculo].Id_mat);
                      break;
                     }
                 case 2:
                    {
                     printf
                     ("\033[33m" "\n\n\t--------------------------------------------------------------\n" "\033[0m"
                      "\033[33m" "\t\t MENU VEHICULO ADMINISTRADOR -> MODIFICAR PLAZAS\n" "\033[0m"
                      "\033[33m" "\t--------------------------------------------------------------\n" "\033[0m"
                      "\033[0;36m" "\n\n\tPlazas: " "\033[0m");
                      fflush(stdin);
                      scanf("\t%i",&(*E_vehiculos)[posicionVehiculo].Num_plazas);
                      break;
                    }
                 case 3:
                    {
                     printf
                     ("\033[33m" "\n\n\t----------------------------------------------------------------\n" "\033[0m"
                      "\033[33m" "\t\t MENU VEHICULO ADMINISTRADOR -> MODIFICAR DESCRIPCION\n" "\033[0m"
                      "\033[33m" "\t----------------------------------------------------------------\n" "\033[0m"
                      "\033[0;36m" "\n\n\tDescripcion nueva: " "\033[0m");
                      fflush(stdin);
                      scanf("\t%s",(*E_vehiculos)[posicionVehiculo].Desc_veh);
                      break;
                    }
                }
                printf("\033[0;32m" "Modificacion hecha con exito" "\033[0m");
           }while(opcionMenuMod!=4); //Opcion para salir del menu
}


void leerVehiculos(Vehiculos **E_vehiculos, int *num_vehiculos)
{
    FILE *archivo;
    char linea[100], *Id_mat, *Id_usuario, *Num_plazas, *Desc_veh;

    // Abrir el archivo para lectura
    archivo = fopen("Vehiculos.txt", "r");
    if (archivo == NULL)
    {
        printf("Error al abrir el archivo.\n");
        return;
    }

    // Inicializar el puntero al Vehiculos
    *E_vehiculos = NULL;

    // Inicializar el contador num_vehiculos
    *num_vehiculos = 0;

    // Contar el número de vehiculos
    while (fgets(linea, 100, archivo) != NULL)
    {
        (*num_vehiculos)++;

        // Asignar memoria para el nuevo Vehiculos
        *E_vehiculos = realloc(*E_vehiculos, *num_vehiculos * sizeof(Vehiculos));
        if (*E_vehiculos == NULL)
        {
            printf("Error al asignar memoria.\n");
            return;
        }

        // Extraer los datos del vehiculo de la línea
        Id_mat = strtok(linea, "-");
        Id_usuario = strtok(NULL, "-");
        Num_plazas = strtok(NULL, "-");
        Desc_veh = strtok(NULL, "\n");

        // Copiar los datos del vehiculo al struct
        strcpy((*E_vehiculos)[*num_vehiculos - 1].Id_mat, Id_mat);
        strcpy((*E_vehiculos)[*num_vehiculos - 1].Id_usuario, Id_usuario);
        (*E_vehiculos)[*num_vehiculos - 1].Num_plazas = atoi(Num_plazas);
        strcpy((*E_vehiculos)[*num_vehiculos - 1].Desc_veh, Desc_veh);
    }

    // Cerrar el archivo
    fclose(archivo);
}

void guardarVehiculos(Vehiculos *E_vehiculos, int num_vehiculos)
{
    FILE *archivo;

    // Abrir el archivo para escritura
    archivo = fopen("vehiculos.txt", "w");
    if (archivo == NULL)
    {
        printf("Error al abrir el archivo.\n");
        return;
    }

    // Escribir los datos de los vehiculos al archivo
    for (int i = 0; i < num_vehiculos; i++)
    {
        fprintf(archivo, "%s-%s-%d-%s\n", E_vehiculos[i].Id_mat, E_vehiculos[i].Id_usuario, E_vehiculos[i].Num_plazas, E_vehiculos[i].Desc_veh);
    }

    // Cerrar el archivo
    fclose(archivo);
}



void menuVehiculosAdmin(Vehiculos **E_vehiculos, int *num_vehiculos)
{
    int opcionMenuVehiculos;
    do
    {
        system("cls");
        printf
        ("\033[33m" "\n\n\t------------------------------------------------------\n" "\033[0m"
         "\033[33m" "\t\t MENU ADMINISTRADOR -> VEHICULOS\n" "\033[0m"
         "\033[33m" "\t------------------------------------------------------\n" "\033[0m"
         "\033[0;36m" "\n\n\t 1. Mostrar todos los vehiculos \n" "\033[0m"
         "\033[0;36m" "\t 2. Dar de alta vehiculo \n" "\033[0m"
         "\033[0;36m" "\t 3. Eliminar vehiculo\n" "\033[0m"
         "\033[0;36m" "\t 4. Modificar vehiculo \n" "\033[0m"
         "\033[0;36m" "\t 5. Salir \n" "\033[0m"
         "\033[0;35m" "\n\n\t Seleccione una opcion: " "\033[0m");
        fflush(stdin);
        scanf("%i",&opcionMenuVehiculos);
        switch (opcionMenuVehiculos)
            {
                case 1:
                    {
                        imprimirVehiculosAdmin(*E_vehiculos, *num_vehiculos);
                        system("pause");
                        break;
                    }

                case 2:
                    {
                        annadirVehiculoAdmin(E_vehiculos, num_vehiculos);
                        break;
                    }

                case 3:
                    {
                        imprimirVehiculosAdmin(*E_vehiculos, *num_vehiculos);
                        eliminarVehiculoAdmin(E_vehiculos, num_vehiculos);
                        break;
                    }

                case 4:
                    {
                        imprimirVehiculosAdmin(*E_vehiculos, *num_vehiculos);
                        modificarVehiculosAdmin(E_vehiculos, *num_vehiculos);
                        break;
                    }
            }
    }while(opcionMenuVehiculos != 5);
    guardarVehiculos((*E_vehiculos),(*num_vehiculos));
}


void menuVehiculosUser(char Id_Usuario[], Vehiculos **E_vehiculos, int *num_vehiculos)
{
    int opcionMenuVehiculos;

    do
    {
        system("cls");
         printf
        ("\033[33m" "\n\n\t------------------------------------------------------\n" "\033[0m"
         "\033[33m" "\t\t MENU USUARIO -> VEHICULOS\n" "\033[0m"
         "\033[33m" "\t------------------------------------------------------\n" "\033[0m"
         "\033[0;36m" "\n\n\t 1. Ver mis vehiculos \n" "\033[0m"
         "\033[0;36m" "\t 2. Dar de alta vehiculo \n" "\033[0m"
         "\033[0;36m" "\t 3. Eliminar mis vehiculo\n" "\033[0m"
         "\033[0;36m" "\t 4. Modificar mis vehiculos \n" "\033[0m"
         "\033[0;36m" "\t 5. Salir \n" "\033[0m"
         "\033[0;35m" "\n\n\t Seleccione una opcion: " "\033[0m");
        fflush(stdin);
        scanf("%i",&opcionMenuVehiculos);
        switch (opcionMenuVehiculos)
            {
                case 1:
                    {
                        imprimirVehiculos(Id_Usuario, *E_vehiculos, *num_vehiculos);
                        system("pause");
                        break;
                    }

                case 2:
                    {
                        annadirVehiculo(Id_Usuario, E_vehiculos, num_vehiculos);
                        break;
                    }

                case 3:
                    {
                        imprimirVehiculos(Id_Usuario, *E_vehiculos, *num_vehiculos);
                        eliminarVehiculos(Id_Usuario, E_vehiculos, num_vehiculos);
                        break;
                    }

                case 4:
                    {
                        imprimirVehiculos(Id_Usuario, *E_vehiculos, *num_vehiculos);
                        modificarVehiculos(Id_Usuario, E_vehiculos, *num_vehiculos);
                        break;
                    }
            }

    }while(opcionMenuVehiculos != 5);
    guardarVehiculos((*E_vehiculos),(*num_vehiculos));
}
