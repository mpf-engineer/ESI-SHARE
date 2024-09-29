#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "viajes.h"

// COLORES TEXTO:
// MODO DE EMPLEO: printf("COLOR" "TEXTO" "COLOR OFF");
// COLOR_RED "\033[0;31m" -> PARA MENSAJE DE ERROR
// COLOR_GREEN "\033[0;32m" -> PARA MENSAJE DE CONFIRMACI�N
// COLOR_YELLOW "\033[0;33m" -> PARA T�TULOS DEL MEN�
// COLOR_BLUE "\033[0;34m"
// COLOR_MAGENTA "\033[0;35m" -> PARA MENSAJE DE PEDIR UN DATO POR TECLADO
// COLOR_CYAN "\033[0;36m" -> PARA MEN� DE OPCIONES
// COLOR_WHITE "\033[0;37m"
// COLOR OFF "\033[0m" -> PARA VOLVER A COLOR BASE TERMINAL (IMPORTANTE: A�adir en cada printf)


void leerViajes(Viajes **E_viajes, int *num_viajes)
{
    FILE *archivo;
    char linea[100], *Id_viaje, *Id_mat, *F_inic, *H_inic, *H_fin, *Viaje, *Estado;
    int Plazas_Libres;
    float Importe;

    // Abrir el archivo para lectura
    archivo = fopen("Viajes.txt", "r");
    if (archivo == NULL)
    {
        printf("Error al abrir el archivo.\n");
        return;
    }

    // Inicializar el puntero al Viajes
    *E_viajes = NULL;

    // Inicializar el contador num_viajes
    *num_viajes = 0;

    // Contar el n�mero de viajes
    while (fgets(linea, 100, archivo) != NULL)
    {
        (*num_viajes)++;

        // Asignar memoria para el nuevo Viajes
        *E_viajes = realloc(*E_viajes, *num_viajes * sizeof(Viajes));
        if (*E_viajes == NULL)
        {
            printf("Error al asignar memoria.\n");
            return;
        }

        // Extraer los datos del viaje de la l�nea
        Id_viaje = strtok(linea, "-");
        Id_mat = strtok(NULL, "-");
        F_inic = strtok(NULL, "-");
        H_inic = strtok(NULL, "-");
        H_fin = strtok(NULL, "-");
        Plazas_Libres = atoi(strtok(NULL, "-"));
        Viaje = strtok(NULL, "-");
        Importe = atof(strtok(NULL, "-"));
        Estado = strtok(NULL, "\n");

        // Copiar los datos del viaje al struct
        strcpy((*E_viajes)[*num_viajes - 1].Id_viaje, Id_viaje);
        strcpy((*E_viajes)[*num_viajes - 1].Id_mat, Id_mat);
        strcpy((*E_viajes)[*num_viajes - 1].F_inic, F_inic);
        strcpy((*E_viajes)[*num_viajes - 1].H_inic, H_inic);
        strcpy((*E_viajes)[*num_viajes - 1].H_fin, H_fin);
        (*E_viajes)[*num_viajes - 1].Plazas_Libres = Plazas_Libres;
        strcpy((*E_viajes)[*num_viajes - 1].Viaje, Viaje);
        (*E_viajes)[*num_viajes - 1].Importe = Importe;
        strcpy((*E_viajes)[*num_viajes - 1].Estado, Estado);
    }

    // Cerrar el archivo
    fclose(archivo);
}

void guardarViajes(Viajes *E_viajes, int num_viajes)
{
    FILE *archivo;

    // Abrir el archivo para escritura
    archivo = fopen("viajes.txt", "w");
    if (archivo == NULL)
    {
        printf("Error al abrir el archivo.\n");
        return;
    }

    // Escribir los datos de los viajes al archivo
    for (int i = 0; i < num_viajes; i++)
    {
        fprintf(archivo, "%s-%s-%s-%s-%s-%d-%s-%.2f-%s\n", E_viajes[i].Id_viaje, E_viajes[i].Id_mat, E_viajes[i].F_inic, E_viajes[i].H_inic, E_viajes[i].H_fin, E_viajes[i].Plazas_Libres, E_viajes[i].Viaje, E_viajes[i].Importe, E_viajes[i].Estado);
    }

    // Cerrar el archivo
    fclose(archivo);
}

//Funciones Usuario
void publicarViajesUsuario(Viajes**E_viajes, int *num_viajes, int *posicionUsuario, Pasos **E_pasos, int *num_pasos, Usuarios **E_usuarios, int *num_usuarios, Vehiculos **E_vehiculos, int *num_vehiculos)
{
    char *auxStr;
    int auxStrLen = 0, i = 0, auxInput1 = 0, auxInput2 = 0, auxInput3 = 0, auxInput4 = 0;
    float auxFloatInput = 0.0f;
    bool check = false;

    *E_viajes = realloc(*E_viajes, (*num_viajes+1)*sizeof(Viajes));
    if(*E_viajes == NULL)
    {
        system("cls");
        printf("\033[0;31m" "\n\n\tERROR EN LA ASIGNACION DE MEMORIA. \n" "\033[0m");
        system("pause");
        exit(1);
    }
    else
    {
        //Agregamos el identificador del viaje
        auxStrLen = 6;
        auxStr = (char*)calloc(auxStrLen,(sizeof(char)));
        if(auxStr == NULL)
        {
            system("cls");
            printf("\033[0;31m" "\n\n\tERROR EN LA ASIGNACION DE MEMORIA. \n" "\033[0m");
            system("pause");
            exit(1);
        }
        else
        {
            //Asignamos el identificador del viaje
            fillIdentifier(auxStr,*num_viajes+1,auxStrLen);
            strcpy((*E_viajes)[*num_viajes].Id_viaje,auxStr);
            //Vehiculo
            system("cls");
            printf("\033[33m" "\n\n\t------------------------------------------------------\n" "\033[0m");
            printf("\033[33m" "\t\t MENU USUARIO -> PUBLICAR VIAJE\n" "\033[0m");
            printf("\033[33m" "\t------------------------------------------------------\n" "\033[0m");
            do
            {
                for(i=0;i<*num_vehiculos;i++)
                {
                    if(strcmp((*E_usuarios)[*posicionUsuario].Id_usuario,(*E_vehiculos)[i].Id_usuario)==0)
                        printf("\033[0;36m" "(%d): ""\033[0;37m""%s\n" "\033[0m",i+1,E_vehiculos[i]->Id_mat);
                }
                auxStrLen = 8;
                auxStr = (char*)realloc(auxStr,auxStrLen*sizeof(char));
                printf("\033[0;35m" "\n\n\tPor favor introduzca un vehiculo por su matricula: " "\033[0m");
                scanf("%s", auxStr);
                check = checkCarLicencePlate(auxStr,posicionUsuario,*E_vehiculos,*E_usuarios,num_vehiculos);
                if(check == false)
                    printf("\033[0;31m""\tEl vehiculo elegido no existe\n""\033[0;31m" );
            } while (check == false);

            strcpy((*E_viajes)[*num_viajes].Id_mat,auxStr);

            //Las plazas del viaje se agregan a partir del vehiculo

            (*E_viajes)[*num_viajes].Plazas_Libres =lookForCar(auxStr,E_vehiculos,num_vehiculos);

            system("cls");
            printf("\033[33m" "\n\n\t------------------------------------------------------\n" "\033[0m");
            printf("\033[33m" "\t\t MENU USUARIO -> PUBLICAR VIAJE\n" "\033[0m");
            printf("\033[33m" "\t------------------------------------------------------\n" "\033[0m");

            do
            {
                printf("\033[0;35m" "\n\n\tIntroduzca la fecha del viaje con el siguiente formato:" "\033[0;32m" " 'DD/MM/AAAA'\n" "\033[0m");
                printf("\033[0;32m" "\n\tIntroduzca el DIA numerico""\033[0;34m" "(1-31): "  "\033[0m");
                scanf("%d",&auxInput1);
                printf("\033[0;32m" "\n\tIntroduzca el MES numerico""\033[0;34m" "(1-12): "  "\033[0m");
                scanf("%d",&auxInput2);
                printf("\033[0;32m" "\n\tIntroduzca el AÑO numerico""\033[0;34m" "(20xx): " "\033[0m");
                scanf("%d",&auxInput3);
                check = dateCheck(&auxInput1,&auxInput2,&auxInput3);
                if(check ==false)
                    printf("\033[0;31m""\tFecha incorrecta, no cumple el formato establecido :'DD/MM/AAAA' o es una fecha previa al reloj del sistema\n""\033[0;31m" );
            }while (check == false);

            //Redimensionamos para guardar el temaño de la fecha
            auxStrLen = 11;
            auxStr = (char*)realloc(auxStr,auxStrLen*sizeof(char));

            dateIntToString(&auxInput1,&auxInput2,&auxInput3,auxStr);
            strcpy((*E_viajes)[*num_viajes].F_inic, auxStr);

            //Hora de Inicio
            system("cls");
            printf("\033[33m" "\n\n\t------------------------------------------------------\n" "\033[0m");
            printf("\033[33m" "\t\t MENU USUARIO -> PUBLICAR VIAJE\n" "\033[0m");
            printf("\033[33m" "\t------------------------------------------------------\n" "\033[0m");
            do
            {
                printf("\033[0;35m" "\n\tIntroduzca la hora de INICIO de la siguiente forma" "\033[0;32m" "(HH:MM):\n" "\033[0m");
                printf("\033[0;32m" "\n\tHoras: " "\033[0m");
                while(getchar() != '\n');
                scanf("%d",&auxInput1);
                printf("\033[0;32m" "\n\tMinutos: " "\033[0m");
                while(getchar() != '\n');
                scanf("%d",&auxInput2);
                check = hourCheck(&auxInput1,&auxInput2);
                if(check ==false)
                    printf("\033[0;31m""\tHora incorrecta\n" "\033[0m");
            } while (check == false);
            //Hora fin
            auxStrLen = 6;
            auxStr = (char*)realloc(auxStr,auxStrLen*sizeof(char));
            hourIntToString(&auxInput1,&auxInput2,auxStr);
            strcpy((*E_viajes)[*num_viajes].H_inic, auxStr);

            system("cls");
            printf("\033[33m" "\n\n\t------------------------------------------------------\n" "\033[0m");
            printf("\033[33m" "\t\t MENU USUARIO -> PUBLICAR VIAJE\n" "\033[0m");
            printf("\033[33m" "\t------------------------------------------------------\n" "\033[0m");
            do
            {
                printf("\033[0;35m" "\n\tIntroduzca la hora de FIN de la siguiente forma" "\033[0;32m" "(HH:MM):\n" "\033[0m");
                printf("\033[0;32m" "\n\tHoras: " "\033[0m");
                while(getchar() != '\n');
                scanf("%d",&auxInput3);
                printf("\033[0;32m" "\n\tMinutos: " "\033[0m");
                while(getchar() != '\n');
                scanf("%d",&auxInput4);
                check = hourCheckReturn(&auxInput3,&auxInput4,&auxInput1,&auxInput2);
                if(check ==false)
                    printf("\033[0;31m""\tFormato de hora incorrecto u hora de vuelta invalida\n""\033[0;31m" );
            } while (check == false);

            hourIntToString(&auxInput3,&auxInput4,auxStr);
            strcpy((*E_viajes)[*num_viajes].H_fin, auxStr);

            //Tipo de viaje
            system("cls");
            printf("\033[33m" "\n\n\t------------------------------------------------------\n" "\033[0m");
            printf("\033[33m" "\t\t MENU USUARIO -> PUBLICAR VIAJE\n" "\033[0m");
            printf("\033[33m" "\t------------------------------------------------------\n" "\033[0m");
            do
            {
                printf("\n\t""\033[0;35m""Introduzca el TIPO de viaje: ""\033[0;32m" "IDA(1) / VUELTA(2):""\033[0m");
                scanf("%i",&auxInput1);
            } while (auxInput1!=1 && auxInput1!=2);

            if(auxInput1 == 1)
                strcpy((*E_viajes)[*num_viajes].Viaje, "ida");
            else
                strcpy((*E_viajes)[*num_viajes].Viaje, "vuelta");
            //Importe
            do
            {
                printf("\033[0;35m""\n\tIntroduzca el""\033[0;32m"" IMPORTE:""\033[0m");
                scanf("%f",&auxFloatInput);
            } while (auxFloatInput < 0.0f);
            (*E_viajes)[*num_viajes].Importe = auxFloatInput;

            //Por defecto cuando se crea un viaje su estado será Abierto
            strcpy((*E_viajes)[*num_viajes].Estado, "abierto");
        }
        printf("\033[0;32m""\n\tVIAJE AGREGADO CON EXITO\n""\033[0m");
        (*num_viajes)++;
        free(auxStr);
    }
}

void modificarViajesUsuario(Viajes**E_viajes, int *num_viajes, int *posicionUsuario, Pasos **E_pasos, int *num_pasos, Usuarios **E_usuarios, int *num_usuarios, Vehiculos **E_vehiculos, int *num_vehiculos)
{
    //Sólo mostrará los viajes editables como restricción del problema
    int i = 0, j = 0, auxStrLen = 0, auxInput1 = 0, auxInput2 = 0, auxInput3 = 0, auxInput4 = 0, travelPosition = 0, optionMenu = 0;
    char *auxStr;
    float auxFloatInput;
    bool check = false;

    auxStrLen = 6;
    auxStr = (char*)calloc(auxStrLen,(sizeof(char)));
    if(auxStr == NULL)
    {
        system("cls");
        printf("\033[0;31m" "\n\n\tERROR EN LA ASIGNACION DE MEMORIA. \n" "\033[0m");
        system("pause");
        exit(1);
    }
    else
    {
        system("cls");
        printf("\033[33m" "\n\n\t------------------------------------------------------\n" "\033[0m");
        printf("\033[33m" "\t\t MENU USUARIO -> MODIFICAR VIAJE\n" "\033[0m");
        printf("\033[33m" "\t------------------------------------------------------\n" "\033[0m");



        for(i=0; i<*num_vehiculos;i++) //Este bucle mostrará los viajes editables, aquellos cuales no estén ocupados, es decir, el número de plazas del viaje es igual al del vehiculo asignado a este
            {
                for(j=0;j<*num_viajes;j++)
                {
                    if(strcmp((*E_usuarios)[*posicionUsuario].Id_usuario,(*E_vehiculos)[i].Id_usuario)==0 &&
                    strcmp((*E_vehiculos)[i].Id_mat,(*E_viajes)[j].Id_mat)==0 && (*E_vehiculos)[i].Num_plazas == (*E_viajes)[j].Plazas_Libres)
                    {
                        printf("\033[0;36m""\tID VIAJE:""\033[0;36m" "\033[0;37m""%s\n""\033[0m",(*E_viajes)[j].Id_viaje);
                    }
                }
            }
        do
        {
            printf("\033[0;32m""\tIntroduzca el ID del viaje a editar: " "\033[0m");
            scanf("%s",auxStr);
            travelPosition = checkTravelCode(auxStr,E_vehiculos, posicionUsuario,num_vehiculos,E_viajes,num_viajes,E_usuarios, num_usuarios);
            if(travelPosition == -1)
                printf("\033[0;31m""\tFormato de ID incorrecto o no existe viaje con ese ID para el usuario.\n""\033[0m" );
        } while (travelPosition == -1);
        //Con travel position conseguimos el id del viaje a editar en el fichero

        system("cls");
        printf("\033[33m" "\n\n\t------------------------------------------------------\n" "\033[0m");
        printf("\033[33m" "\t\t MENU USUARIO -> MODIFICAR VIAJE\n" "\033[0m");
        printf("\033[33m" "\t------------------------------------------------------\n" "\033[0m");

        do
        {

            printf("\033[0;36m" "\n\n\t 1. Vehiculo.\n" "\033[0m");
            printf("\033[0;36m" "\t 2. Fecha de Viaje.\n" "\033[0m");
            printf("\033[0;36m" "\t 3. Hora de Inicio.\n" "\033[0m");
            printf("\033[0;36m" "\t 4. Hora de Fin.\n" "\033[0m");
            printf("\033[0;36m" "\t 5. Plazas libres.\n" "\033[0m");
            printf("\033[0;36m" "\t 6. Importe.\n" "\033[0m");
            printf("\033[0;36m" "\t 7. Estado del viaje.\n" "\033[0m");
            printf("\033[0;36m" "\t 8. Salir.\n" "\033[0m");
            printf("\033[0;32m" "\tElija una opcion: " "\033[0m");
            scanf("%i",&optionMenu);
        } while (optionMenu<1 || optionMenu>8 );

        switch (optionMenu)
        {
            case 1: //Cambio de vehiculo
                {
                    system("cls");
                    printf("\033[33m" "\n\n\t------------------------------------------------------\n" "\033[0m");
                    printf("\033[33m" "\t\t MENU USUARIO -> MODIFICAR VIAJE\n" "\033[0m");
                    printf("\033[33m" "\t------------------------------------------------------\n" "\033[0m");
                    do
                    {
                        for(i=0;i<*num_vehiculos;i++)
                            if(strcmp((*E_usuarios)[*posicionUsuario].Id_usuario,(*E_vehiculos)[i].Id_usuario)==0)
                                printf("\033[0;32m" "\t(%d): " "\033[0;36m" "%s\n" "\033[0m",i+1,(*E_vehiculos)[i].Id_mat);
                        auxStrLen = 8;
                        auxStr = (char*)realloc(auxStr,auxStrLen*sizeof(char));
                        printf("\033[0;35m" "\n\tPor favor introduzca la matricula de un vehiculo: " "\033[0m");
                        scanf("%s", auxStr);
                        check = checkCarLicencePlate(auxStr,posicionUsuario,*E_vehiculos,*E_usuarios,num_vehiculos);
                        if(check == false)
                            printf(  "\033[0;31m" "\n\tVehiculo de formato incorrecto o no perteneciente al usuario \n" "\033[0m");
                    }while (check == false);
                    strcpy((*E_viajes)[travelPosition].Id_mat,auxStr);
                }
                break;
            case 2: //Fecha del viaje
                {
                    system("cls");
                    printf("\033[33m" "\n\n\t------------------------------------------------------\n" "\033[0m");
                    printf("\033[33m" "\t\t MENU USUARIO -> MODIFICAR VIAJE\n" "\033[0m");
                    printf("\033[33m" "\t------------------------------------------------------\n" "\033[0m");
                    do
                    {
                        printf("\033[0;35m" "\n\n\tIntroduzca la fecha del viaje con el siguiente formato:" "\033[0;32m" " 'DD/MM/AAAA'\n" "\033[0m");
                        printf("\033[0;32m" "\n\tIntroduzca el DIA numerico""\033[0;34m" "(1-31): "  "\033[0m");
                        scanf("%d",&auxInput1);
                        printf("\033[0;32m" "\n\tIntroduzca el MES numerico""\033[0;34m" "(1-12): "  "\033[0m");
                        scanf("%d",&auxInput2);
                        printf("\033[0;32m" "\n\tIntroduzca el AÑO numerico""\033[0;34m" "(20xx): " "\033[0m");
                        scanf("%d",&auxInput3);
                        check = dateCheck(&auxInput1,&auxInput2,&auxInput3);
                        if(check ==false)
                            printf("\033[0;31m""\tFecha incorrecta, no cumple el formato establecido :'DD/MM/AAAA' o es una fecha previa al reloj del sistema\n""\033[0m");
                    }while (check == false);
                    auxStrLen = 11;
                    auxStr = (char*)realloc(auxStr,auxStrLen*sizeof(char));
                    dateIntToString(&auxInput1,&auxInput2,&auxInput3,auxStr);
                    strcpy((*E_viajes)[travelPosition].F_inic, auxStr);
                }
                break;
            case 3: //Hora de inicio
                {   system("cls");
                    printf("\033[33m" "\n\n\t------------------------------------------------------\n" "\033[0m");
                    printf("\033[33m" "\t\t MENU USUARIO -> MODIFICAR VIAJE\n" "\033[0m");
                    printf("\033[33m" "\t------------------------------------------------------\n" "\033[0m");
                    do
                    {
                        printf("\033[0;35m" "\n\tIntroduzca la hora de INICIO de la siguiente forma" "\033[0;32m" "(HH:MM)\n" "\033[0m");
                        printf("\033[0;32m" "\n\tHoras: " "\033[0m");
                        while(getchar() != '\n');
                        scanf("%d",&auxInput1);
                        printf("\033[0;32m" "\n\tMinutos: " "\033[0m");
                        while(getchar() != '\n');
                        scanf("%d",&auxInput2);
                        check = hourCheck(&auxInput1,&auxInput2);
                        if(check ==false)
                            printf("\033[0;31m""\tHora incorrecta\n" "\033[0m");
                    } while (check == false);

                    auxStrLen = 6;
                    auxStr = (char*)realloc(auxStr,auxStrLen*sizeof(char));
                    hourIntToString(&auxInput1,&auxInput2,auxStr);
                    strcpy((*E_viajes)[travelPosition].H_inic, auxStr);
                    //printf("%s\n",(*E_viajes)[travelPosition].H_inic);
                }
                break;
            case 4://Hora de fin
                    system("cls");
                    printf("\033[33m" "\n\n\t------------------------------------------------------\n" "\033[0m");
                    printf("\033[33m" "\t\t MENU USUARIO -> MODIFICAR VIAJE\n" "\033[0m");
                    printf("\033[33m" "\t------------------------------------------------------\n" "\033[0m");

                    do
                    {
                         printf("\033[0;35m" "\n\tIntroduzca la hora de FIN de la siguiente forma" "\033[0;32m" "(HH:MM):\n" "\033[0m");
                        printf("\033[0;32m" "\tHoras: " "\033[0m");
                        while(getchar() != '\n');
                        scanf("%d",&auxInput3);
                        printf("\033[0;32m" "\n\tMinutos: " "\033[0m");
                        while(getchar() != '\n');
                        scanf("%d",&auxInput4);
                        check = hourCheckReturn(&auxInput3,&auxInput4,&auxInput1,&auxInput2);
                        if(check ==false)
                            printf("\033[0;31m" "\tFormato de hora incorrecto u hora de vuelta invalida\n" "\033[0m");
                    } while (check == false);

                    hourIntToString(&auxInput3,&auxInput4,auxStr);
                    strcpy((*E_viajes)[travelPosition].H_fin, auxStr);
                break;
            case 5: //Plazas libres
                {
                    system("cls");
                    printf("\033[33m" "\n\n\t------------------------------------------------------\n" "\033[0m");
                    printf("\033[33m" "\t\t MENU USUARIO -> MODIFICAR VIAJE\n" "\033[0m");
                    printf("\033[33m" "\t------------------------------------------------------\n" "\033[0m");

                    do
                    {
                        printf("\033[0;32m" "\n\n\tIntroduzca el numero de plazas libres del vehiculo: " "\033[0m");
                        scanf("%d",&auxInput1);
                        check = checkCarCapacity(&auxInput1,E_vehiculos, num_vehiculos,E_viajes,num_viajes);
                        if(check == false)
                            printf("\033[0;31m" "\tPlazas de transporte del vehiculo incorrecta\n" "\033[0m");
                    } while (check == false);
                    (*E_viajes)[travelPosition].Plazas_Libres = auxInput1;
                }
                break;
            case 6://Importe
                {
                    system("cls");
                    printf("\033[33m" "\n\n\t------------------------------------------------------\n" "\033[0m");
                    printf("\033[33m" "\t\t MENU USUARIO -> MODIFICAR VIAJE\n" "\033[0m");
                    printf("\033[33m" "\t------------------------------------------------------\n" "\033[0m");

                    do
                    {
                        printf("\033[0;32m" "\n\n\tIntroduzca el NUEVO IMPORTE: " "\033[0m");
                        scanf("%f",&auxFloatInput);
                    } while (auxFloatInput < 0.0f);
                    (*E_viajes)[travelPosition].Importe = auxFloatInput;
                }
                break;
            case 7://Estado
                {
                    system("cls");
                    printf("\033[33m" "\n\n\t------------------------------------------------------\n" "\033[0m");
                    printf("\033[33m" "\t\t MENU USUARIO -> MODIFICAR VIAJE\n" "\033[0m");
                    printf("\033[33m" "\t------------------------------------------------------\n" "\033[0m");
                    printf("\033[0;36m" "\n\n\tEstado: " "\033[0m");
                    system("pause");
                    do
                    {
                        printf("\033[0;32m" "\n\n\tElija el NUEVO Estado:\n" "\033[0m");
                        printf("\033[0;32m" "\t(1).""\033[0;36m""Abierto.\n" "\033[0m");
                        printf("\033[0;32m" "\t(2).""\033[0;36m""Cerrado.\n" "\033[0m");
                        printf("\033[0;32m" "\t(3).""\033[0;36m""Iniciado.\n" "\033[0m");
                        printf("\033[0;32m" "\t(4).""\033[0;36m""Finalizado.\n" "\033[0m");
                        printf("\033[0;32m" "\t(5).""\033[0;36m""Anulado.\n" "\033[0m");
                        printf("\033[0;32m" "\n\tIntroduzca el nuevo valor (1-5): " "\033[0m");
                        scanf("%d",&auxInput1);
                    } while (auxInput1>5 && auxInput1<0);

                    switch (auxInput1)
                    {
                    case 1://Abierto
                        strcpy((*E_viajes)[travelPosition].Estado,"abierto");
                        break;
                    case 2://Cerrado
                        strcpy((*E_viajes)[travelPosition].Estado,"cerrado");
                        break;
                    case 3://Iniciado
                        strcpy((*E_viajes)[travelPosition].Estado,"iniciado");
                        break;
                    case 4://Finalizado
                        strcpy((*E_viajes)[travelPosition].Estado,"finalizado");
                        break;
                    case 5://Anulado
                        strcpy((*E_viajes)[travelPosition].Estado,"anulado");
                        break;
                    default:
                        break;
                    }
                }
                break;
            case 8://Salir
                printf("\033[0;32m" "\n\tVIAJE NO MODIFICADO\n""\033[0;32m" "\033[0m");
                return;

                break;
            default:
                break;
            };
    }
    printf("\033[0;32m" "\n\n\tVIAJE MODIFICADO CON EXITO\n" "\033[0m");
    system("pause");
    free(auxStr);
}

void mostrarViajeUsuario(Viajes**E_viajes, int *num_viajes, int *posicionUsuario, Vehiculos **E_vehiculos, int *num_vehiculos, Usuarios **E_usuarios, int *num_usuarios, Pasos **E_pasos, int *num_pasos)
{
    int i = 0, j = 0, k = 0, stops = 0, stopI = 0, travelPosition = 0;

        system("cls");
        printf("\033[33m" "\n\n\t------------------------------------------------------\n" "\033[0m");
        printf("\033[33m" "\t\t MENU USUARIO -> MOSTRAR VIAJE\n" "\033[0m");
        printf("\033[33m" "\t------------------------------------------------------\n" "\033[0m");


        for(i=0; i<*num_vehiculos;i++) //Este bucle mostrará los viajes a mostrar
            {
                for(j=0;j<*num_viajes;j++)
                {
                    if(strcmp((*E_usuarios)[*posicionUsuario].Id_usuario,(*E_vehiculos)[i].Id_usuario)==0 &&
                    strcmp((*E_vehiculos)[i].Id_mat,(*E_viajes)[j].Id_mat)==0 && (*E_vehiculos)[i].Num_plazas == (*E_viajes)[j].Plazas_Libres)
                    {
                        printf("\033[0;36m" "\tID del viaje: %s\n" "\033[0;37m""\tMatricula del vehiculo: %s\n\tFecha del viaje: %s\n\tHora de salida: %s\n\tHora de llegada: %s\n\tPlazas disponibles: %d\n\tTipo de viaje: %s\n\tImporte: %f€\n\tEstado: %s\n\n"  "\033[0m",(*E_viajes)[j].Id_viaje,(*E_viajes)[j].Id_mat,(*E_viajes)[j].F_inic, (*E_viajes)[j].H_inic,(*E_viajes)[j].H_fin,(*E_viajes)[j].Plazas_Libres, (*E_viajes)[j].Viaje, (*E_viajes)[j].Importe, (*E_viajes)[j].Estado);
                        for(k=0;k<*num_pasos;k++)
                        {
                            if(strcmp((*E_viajes)[j].Id_viaje,(*E_pasos)[k].Id_viaje)==0)
                            {
                                stops++;
                                printf("\033[0;36m" "\tPasa por:\n" "\033[0m");
                                for(stopI = 0 ; stopI<stops;stopI++)
                                    printf("\033[0;32m" "\t %s\n" "\033[0m",(*E_pasos)[stopI].Poblacion);
                            }
                        }
                    }
                }
            }
}

void incorporarViajeUsuario(Viajes**E_viajes, int *num_viajes, int *posicionUsuario, Pasos **E_pasos, int *num_pasos, Usuarios **E_usuarios, int *num_usuarios, Vehiculos **E_vehiculos, int *num_vehiculos)
{
    int i = 0, j = 0, k = 0, auxStrLen = 0, travelPosition = 0;
    bool nearTrip = false;
    char *auxStr;

    system("cls");
    printf("\033[33m" "\n\n\t------------------------------------------------------\n" "\033[0m");
    printf("\033[33m" "\t\t MENU USUARIO -> INCORPORAR VIAJE\n" "\033[0m");
    printf("\033[33m" "\t------------------------------------------------------\n" "\033[0m");

    printf("\033[0;32m" "\tMostrando viajes disponibles por su localidad:" "\033[0m" "\033[0;37m""%s \n" "\033[0m",(*E_usuarios)[*posicionUsuario].Localidad);
    //Filtramos los resultados para ver si hay viajes disponibles para el usuario, igualando vehículos a viajes, viajes a usuario, usuario a pasos con la localidad y los pasos
    for(i=0;i<*num_viajes;i++)
        for(j=0;j<*num_vehiculos;j++)
            for(k=0;k<*num_pasos;k++)
                if(strcmp((*E_viajes)[i].Id_mat,(*E_vehiculos)[j].Id_mat)==0 && strcmp((*E_viajes)[i].Estado,"abierto")==0 && strcmp((*E_viajes)[i].Estado,"iniciado")!=0 && strcmp((*E_viajes)[i].Id_viaje,(*E_pasos)[k].Id_viaje)==0 && strcmp((*E_pasos)[k].Poblacion, (*E_usuarios)[*posicionUsuario].Localidad)==0)
                {
                    nearTrip = true;
                    printf("\033[0;32m" "Id del viaje: %s - Plazas disponibles: %d - Pasa por: %s\n" "\033[0m",(*E_viajes)[i].Id_viaje, (*E_viajes)[i].Plazas_Libres, (*E_pasos)[k].Poblacion);
                }
    if(nearTrip == false)
    {
        printf("\033[0;31m" "\n\n\tNo hay viajes disponibles cerca tuya :(  \n" "\033[0m");
        return;
    }
    else
    {

        auxStrLen = 6;
        auxStr = (char*)calloc(auxStrLen,(sizeof(char)));
        if(auxStr == NULL)
        {
            system("cls");
            printf("\033[0;31m" "\n\n\tERROR EN LA ASIGNACION DE MEMORIA. \n" "\033[0m");
            system("pause");
            exit(1);
        }
        else
        {
            system("cls");
            printf("\033[33m" "\n\n\t------------------------------------------------------\n" "\033[0m");
            printf("\033[33m" "\t\t MENU USUARIO -> INCORPORAR VIAJE\n" "\033[0m");
            printf("\033[33m" "\t------------------------------------------------------\n" "\033[0m");

            do
            {
                printf("\033[0;32m""\tIntroduzca el ID del viaje, del formato:""\033[0;34m""(00000X), por ejemplo:" "\033[0;32m" "000004 :""\033[0m");
                scanf("%s",auxStr);
                travelPosition = checkTravelCode(auxStr,E_vehiculos, posicionUsuario,num_vehiculos,E_viajes,num_viajes,E_usuarios, num_usuarios);
                if(travelPosition == -1)
                    printf("\033[0;31m" "\n\t.Id incorrecto o de formato incompatible \n" "\033[0m");
            } while (travelPosition == -1);
            //Decrementamos el número de plazas disponibles del viaje
            (*E_viajes)[travelPosition].Plazas_Libres = (*E_viajes)[travelPosition].Plazas_Libres-1;
            if((*E_viajes)[travelPosition].Plazas_Libres == 0)
            {
                strcpy((*E_viajes)[travelPosition].Estado,"cerrado");
            }
            printf("\033[0;32m" "\n\n\tTE HAS UNIDO AL VIAJE CON EXITO\n" "\033[0m");
        }
    }
    free(auxStr);
}

void menuViajeUsuario(Viajes**E_viajes, int *num_viajes, int *posicionUsuario, Pasos **E_pasos, int *num_pasos, Usuarios **E_usuarios, int *num_usuarios, Vehiculos **E_vehiculos, int *num_vehiculos)
{
    int optionMenu = 0, repeatIntMenu = 0;
    char repeatMenu;
    do
    {
        system("cls");
        printf("\033[33m" "\n\n\t------------------------------------------------------\n" "\033[0m");
        printf("\033[33m" "\t\t MENU USUARIO\n" "\033[0m");
        printf("\033[33m" "\t------------------------------------------------------\n" "\033[0m");
        do
        {

            system("cls");
            printf("\033[33m" "\n\n\t------------------------------------------------------\n" "\033[0m");
            printf("\033[33m" "\t\t MENU USUARIO -> VIAJES\n" "\033[0m");
            printf("\033[33m" "\t------------------------------------------------------\n\n" "\033[0m");
            printf("\033[0;36m" "\n\n\t 1. Publicar Viaje \n" "\033[0m");
            printf("\033[0;36m" "\t 2. Modificar Viaje \n" "\033[0m");
            printf("\033[0;36m" "\t 3. Mostrar Viaje \n" "\033[0m");
            printf("\033[0;36m" "\t 4. Incorporarse a un viaje \n" "\033[0m");
            printf("\033[0;36m" "\t 5. Salir \n" "\033[0m");
            printf("\033[0;35m" "\n\n\t Seleccione una opcion: " "\033[0m");
            scanf("%d",&optionMenu);
            switch (optionMenu)
            {
            case 1://Publicar
                publicarViajesUsuario(E_viajes, num_viajes, posicionUsuario, E_pasos, num_pasos, E_usuarios, num_usuarios, E_vehiculos, num_vehiculos);
                break;
            case 2://Modificar
                modificarViajesUsuario(E_viajes, num_viajes, posicionUsuario, E_pasos, num_pasos, E_usuarios, num_usuarios, E_vehiculos, num_vehiculos);
                break;
            case 3://Mostrar
                mostrarViajeUsuario(E_viajes, num_viajes, posicionUsuario, E_vehiculos, num_vehiculos, E_usuarios, num_usuarios, E_pasos, num_pasos);
                break;
            case 4://Incorporarse
                incorporarViajeUsuario(E_viajes, num_viajes, posicionUsuario, E_pasos, num_pasos, E_usuarios, num_usuarios, E_vehiculos, num_vehiculos);
                break;
            case 5: //Salir
                repeatMenu ='n';
                break;
            default:
                break;
            }
        }while(optionMenu>5 || optionMenu <1);
        printf("\033[0;35m" "\n\n\tDesea hacer algo mas?""\033[0;32m" "(1 -> Si / 2 -> No):" "\033[0m");
        scanf("%d",&repeatIntMenu);
    }while (repeatIntMenu == 1);

}
//Funciones Administrador

void publicarViajesAdmin(Viajes**E_viajes, int *num_viajes, Pasos **E_pasos, int *num_pasos,Usuarios **E_usuarios, int *num_usuarios, Vehiculos **E_vehiculos, int *num_vehiculos)
{
    //El administrador será el que añada viajes con los destinos
    char *auxStr;
    int auxStrLen = 0, i = 0, auxInput1 = 0, auxInput2 = 0, auxInput3 = 0, auxInput4 = 0, posUsuarioAux = 0;
    float auxFloatInput = 0.0f;
    bool check = false;

    auxStrLen = 6;
    auxStr = (char*)calloc(auxStrLen,(sizeof(char)));
    if(auxStr == NULL)
    {
        system("cls");
        printf("\033[0;31m" "\n\n\tERROR EN LA ASIGNACION DE MEMORIA. \n" "\033[0m");
        system("pause");
        exit(1);
    }
    else
    {
        //Incrementamos el número de viajes
        *E_viajes = realloc(*E_viajes, (*num_viajes+1)*sizeof(Viajes));

        //Agregamos el número del id_viaje de la variable
        fillIdentifier(auxStr,*num_viajes+1,auxStrLen);
        strcpy((*E_viajes)[*num_viajes].Id_viaje,auxStr);

        system("cls");
        printf("\033[33m" "\n\n\t------------------------------------------------------\n" "\033[0m");
        printf("\033[33m" "\t\t MENU ADMINISTRADOR -> PUBLICAR VIAJE\n" "\033[0m");
        printf("\033[33m" "\t------------------------------------------------------\n" "\033[0m");

        auxStrLen = 5;
        auxStr = (char*)realloc(auxStr,auxStrLen*sizeof(char));
        do
        {

            for(i=0;i<*num_usuarios;i++)
                printf("\033[0;32m""\t(%d)" "\033[0;36m""ID Usuario:""\033[0;36m" "\033[0;37m"" %s\n" "\033[0m",i+1,(*E_usuarios)[i].Id_usuario);
            printf("\033[0;35m""\n\n\tIntroduzca el ID de Usuario asignado al viaje: " "\033[0m");
            scanf("%s",auxStr);
            posUsuarioAux = lookForUser(auxStr, E_usuarios, num_usuarios);
            if(posUsuarioAux==-1)
                printf("\033[0;31m" "\n\tUsuario no encontrado o formato incorrecto \n" "\033[0m");

        } while (posUsuarioAux == -1);

        system("cls");
        printf("\033[33m" "\n\n\t------------------------------------------------------\n" "\033[0m");
        printf("\033[33m" "\t\t MENU ADMINISTRADOR -> PUBLICAR VIAJE\n" "\033[0m");
        printf("\033[33m" "\t------------------------------------------------------\n" "\033[0m");
        do
        {

            for(i = 0;i<*num_vehiculos;i++)
            {
                if(strcmp((*E_usuarios)[posUsuarioAux].Id_usuario,(*E_vehiculos)[i].Id_usuario)==0)
                    printf("\033[0;32m" "\t(%d)""\033[0;36m"": %s\n" "\033[0m",i+1,(*E_vehiculos)[i].Id_mat);
            }
            auxStrLen = 8;
            auxStr = (char*)realloc(auxStr,auxStrLen*sizeof(char));
            printf("\033[0;35m" "\n\n\tPor favor introduzca una matricula de vehiculo: " "\033[0m");
            scanf("%s", auxStr);
            check = checkCarLicencePlate(auxStr,&posUsuarioAux,*E_vehiculos,*E_usuarios,num_vehiculos);
            if(check == false)
                printf("\033[0;31m" "\n\tMatricula no encontrada o formato incorrecto \n" "\033[0m");
        } while (check == false);
        strcpy((*E_viajes)[*num_viajes].Id_mat,auxStr);

        //Las plazas del viaje se agregan a partir del vehiculo

        (*E_viajes)[*num_viajes].Plazas_Libres =lookForCar(auxStr,E_vehiculos,num_vehiculos);


        system("cls");
        printf("\033[33m" "\n\n\t------------------------------------------------------\n" "\033[0m");
        printf("\033[33m" "\t\t MENU ADMINISTRADOR -> PUBLICAR VIAJE\n" "\033[0m");
        printf("\033[33m" "\t------------------------------------------------------\n" "\033[0m");

        do
        {
            printf("\033[0;35m" "\n\n\tIntroduzca la fecha del viaje con el siguiente formato:" "\033[0;32m" " 'DD/MM/AAAA'\n\n" "\033[0m");
            printf("\033[0;32m" "\n\tIntroduzca el DIA numerico""\033[0;34m" "(1-31):" "\033[0m");
            scanf("%d",&auxInput1);
            printf("\033[0;32m" "\n\tIntroduzca el MES numerico""\033[0;34m" "(1-12):" "\033[0m");
            scanf("%d",&auxInput2);
            printf("\033[0;32m" "\n\tIntroduzca el ANNO numerico""\033[0;34m" "(20xx):" "\033[0m");
            scanf("%d",&auxInput3);
            check = dateCheck(&auxInput1,&auxInput2,&auxInput3);
            if(check ==false)
                printf("\033[0;31m" "\tFecha incorrecta, no cumple el formato establecido :'DD/MM/AAAA' o es una fecha previa al reloj del sistema\n" "\033[0m");
        }while (check == false);

        //Redimensionamos para guardar el temaño de la fecha
        auxStrLen = 11;
        auxStr = (char*)realloc(auxStr,auxStrLen*sizeof(char));

        dateIntToString(&auxInput1,&auxInput2,&auxInput3,auxStr);
        strcpy((*E_viajes)[*num_viajes].F_inic, auxStr);

        //Hora de Inicio
        system("cls");
        printf("\033[33m" "\n\n\t------------------------------------------------------\n" "\033[0m");
        printf("\033[33m" "\t\t MENU ADMINISTRADOR -> PUBLICAR VIAJE\n" "\033[0m");
        printf("\033[33m" "\t------------------------------------------------------\n" "\033[0m");

        do
        {
            printf("\033[0;35m" "\n\tIntroduzca la hora de INICIO de la siguiente forma" "\033[0;32m" "(HH:MM):\n" "\033[0m");
            printf("\033[0;32m" "\n\tHoras:" "\033[0m");
            while(getchar() != '\n');
            scanf("%d",&auxInput1);
            printf("\033[0;32m" "\n\tMinutos:" "\033[0m");
            while(getchar() != '\n');
            scanf("%d",&auxInput2);
            check = hourCheck(&auxInput1,&auxInput2);
            if(check ==false)
                printf("\033[0;31m""\tHora incorrecta\n" "\033[0m");
        } while (check == false);

        auxStrLen = 6;
        auxStr = (char*)realloc(auxStr,auxStrLen*sizeof(char));
        hourIntToString(&auxInput1,&auxInput2,auxStr);
        strcpy((*E_viajes)[*num_viajes].H_inic, auxStr);

        system("cls");
        printf("\033[33m" "\n\n\t------------------------------------------------------\n" "\033[0m");
        printf("\033[33m" "\t\t MENU ADMINISTRADOR -> PUBLICAR VIAJE\n" "\033[0m");
        printf("\033[33m" "\t------------------------------------------------------\n" "\033[0m");
        //Hora de fin
        do
        {
            printf("\033[0;35m" "\n\tIntroduzca la hora de FIN de la siguiente forma" "\033[0;32m" "(HH:MM):\n\n" "\033[0m");
            printf("\033[0;32m" "\tHoras:" "\033[0m");
            while(getchar() != '\n');
            scanf("%d",&auxInput3);
            printf("\033[0;32m" "\n\tMinutos:" "\033[0m");
            while(getchar() != '\n');
            scanf("%d",&auxInput4);
            check = hourCheckReturn(&auxInput3,&auxInput4,&auxInput1,&auxInput2);
            if(check ==false)
                printf("\033[0;31m""\tFormato de hora incorrecto u hora de vuelta invalida\n" "\033[0m");
        } while (check == false);

        hourIntToString(&auxInput3,&auxInput4,auxStr);
        strcpy((*E_viajes)[*num_viajes].H_fin, auxStr);

        //Tipo de viaje
        system("cls");
        printf("\033[33m" "\n\n\t------------------------------------------------------\n" "\033[0m");
        printf("\033[33m" "\t\t MENU ADMINISTRADOR -> PUBLICAR VIAJE\n" "\033[0m");
        printf("\033[33m" "\t------------------------------------------------------\n" "\033[0m");
        printf("\033[0;36m" "\n\n\tTipo de viaje: " "\033[0m");
        system("pause");

        do
        {
            printf("\033[0;35m" "\n\tIntroduzca el TIPO de viaje: ""\033[0;32m" "IDA(1) / VUELTA(2):" "\033[0m");
            scanf("%i",&auxInput1);
        } while (auxInput1!=1 && auxInput1!=2);

        if(auxInput1 == 1)
            strcpy((*E_viajes)[*num_viajes].Viaje, "ida");
        else
            strcpy((*E_viajes)[*num_viajes].Viaje, "vuelta");
        //Importe
        do
        {
            printf("\033[0;35m" "\n\n\tIntroduzca el " "\033[0;32m" "IMPORTE:" "\033[0m");
            scanf("%f",&auxFloatInput);
        } while (auxFloatInput < 0.0f);
        (*E_viajes)[*num_viajes].Importe = auxFloatInput;

        //Por defecto cuando se crea un viaje su estado será Abierto
        strcpy((*E_viajes)[*num_viajes].Estado, "abierto");

    }
    printf("\033[0;32m" "\n\n\tVIAJE AGREGADO CON EXITO\n" "\033[0m");
    (*num_viajes)++;
    free(auxStr);
}

void modificarViajesAdmin(Viajes**E_viajes, int *num_viajes, Pasos **E_pasos, int *num_pasos, Usuarios **E_usuarios, int *num_usuarios, Vehiculos **E_vehiculos, int *num_vehiculos)
{
    int i = 0, auxStrLen = 0, auxInput1 = 0, auxInput2 = 0, auxInput3 = 0, auxInput4 = 0, travelPosition = 0, optionMenu = 0;
    char *auxStr;
    float auxFloatInput;
    bool check = false;

    auxStrLen = 6;
    auxStr = (char*)calloc(auxStrLen,(sizeof(char)));
    if(auxStr == NULL)
    {
        system("cls");
        printf("\033[0;31m" "\n\n\tERROR EN LA ASIGNACION DE MEMORIA. \n" "\033[0m");
        system("pause");
        exit(1);
    }
    else
    {
        system("cls");
        printf("\033[33m" "\n\n\t------------------------------------------------------\n" "\033[0m");
        printf("\033[33m" "\t\t MENU ADMINISTRADOR -> MODIFICAR VIAJE\n" "\033[0m");
        printf("\033[33m" "\t------------------------------------------------------\n" "\033[0m");

        auxStrLen = 6;
        auxStr = (char*)realloc(auxStr,auxStrLen*sizeof(char));
        do
        {

            for(i=0;i<*num_viajes;i++)
                printf("\033[0;32m""\t(%d)""\033[0;36m""ID Viaje:""\033[0;36m" "\033[0;37m"" %s\n" "\033[0m",i+1,(*E_viajes)[i].Id_viaje);
            printf("\033[0;35m""\n\n\tIntroduzca el ID de Usuario asignado al viaje: " "\033[0m");
            scanf("%s",auxStr);
            travelPosition = lookForTravel(auxStr, E_viajes, num_viajes);
            if(travelPosition ==-1)
                printf("\033[0;31m" "\n\n\tID de viaje erroneo o formato incorrecto \n" "\033[0m");
        } while (travelPosition == -1);

        system("cls");
        printf("\033[33m" "\n\n\t------------------------------------------------------\n" "\033[0m");
        printf("\033[33m" "\t\t MENU ADMINISTRADOR -> MODIFICAR VIAJE\n" "\033[0m");
        printf("\033[33m" "\t------------------------------------------------------\n" "\033[0m");

        do
        {

            printf("\033[0;36m" "\n\n\t 1. Vehiculo.\n" "\033[0m");
            printf("\033[0;36m" "\t 2. Fecha de Viaje.\n" "\033[0m");
            printf("\033[0;36m" "\t 3. Hora de Inicio.\n" "\033[0m");
            printf("\033[0;36m" "\t 4. Hora de Fin.\n" "\033[0m");
            printf("\033[0;36m" "\t 5. Plazas libres.\n" "\033[0m");
            printf("\033[0;36m" "\t 6. Importe.\n" "\033[0m");
            printf("\033[0;36m" "\t 7. Estado del viaje.\n" "\033[0m");
            printf("\033[0;36m" "\t 8. Salir.\n" "\033[0m");
            printf("\033[0;35m" "\n\tSeleccione una opcion: " "\033[0m");
            scanf("%i",&optionMenu);
        } while (optionMenu<1 || optionMenu>8 );

        switch (optionMenu)
        {
        case 1:
            { //Vehiculo
            system("cls");
            printf("\033[33m" "\n\n\t------------------------------------------------------\n" "\033[0m");
            printf("\033[33m" "\t\t MENU ADMINISTRADOR -> MODIFICAR VIAJE\n" "\033[0m");
            printf("\033[33m" "\t------------------------------------------------------\n" "\033[0m");
            do
            {
                for(i=0;i<*num_vehiculos;i++)
                        printf("\033[0;35m" "\t(%d): ""\033[0;36m""%s\n" "\033[0m",i+1,(*E_vehiculos)[i].Id_mat);
                auxStrLen = 8;
                auxStr = (char*)realloc(auxStr,auxStrLen*sizeof(char));
                printf("\033[0;35m" "\n\n\tPor favor introduzca un vehiculo por su matricula:" "\033[0m");
                scanf("%s", auxStr);
                for(i=0;i<*num_vehiculos;i++)
                    if(strcmp(auxStr,(*E_vehiculos)[i].Id_mat)==0) //Mientras la matricula introducida no coinicida con alguna, se repite
                        check = true;
            }while (check == false);
            strcpy((*E_viajes)[travelPosition].Id_mat,auxStr);
            }
            break;
        case 2:
            { //Fecha de viaje
            system("cls");
            printf("\033[33m" "\n\n\t------------------------------------------------------\n" "\033[0m");
            printf("\033[33m" "\t\t MENU ADMINISTRADOR -> MODIFICAR VIAJE\n" "\033[0m");
            printf("\033[33m" "\t------------------------------------------------------\n" "\033[0m");

            do
            {
                printf("\033[0;35m" "\n\n\tIntroduzca la NUEVA fecha del viaje con el siguiente formato:" "\033[0;32m" " 'DD/MM/AAAA'\n\n" "\033[0m");
                printf("\033[0;32m" "\n\tIntroduzca el DIA numerico""\033[0;34m" "(1-31): "  "\033[0m");
                scanf("%d",&auxInput1);
                printf("\033[0;32m" "\n\tIntroduzca el MES numerico""\033[0;34m" "(1-12): "  "\033[0m");
                scanf("%d",&auxInput2);
                printf("\033[0;32m" "\n\tIntroduzca el AÑO numerico""\033[0;34m" "(20xx): " "\033[0m");
                scanf("%d",&auxInput3);
                check = dateCheck(&auxInput1,&auxInput2,&auxInput3);
                if(check ==false)
                    printf("\033[0;31m" "\tFecha incorrecta, no cumple el formato establecido :'DD/MM/AAAA' o es una fecha previa al reloj del sistema\n" "\033[0m");
            }while (check == false);
            auxStrLen = 11;
            auxStr = (char*)realloc(auxStr,auxStrLen*sizeof(char));
            dateIntToString(&auxInput1,&auxInput2,&auxInput3,auxStr);
            strcpy((*E_viajes)[travelPosition].F_inic, auxStr);
            }
            break;
        case 3: //Hora de inicio
            {   system("cls");
                    printf("\033[33m" "\n\n\t------------------------------------------------------\n" "\033[0m");
                    printf("\033[33m" "\t\t MENU ADMINISTRADOR -> MODIFICAR VIAJE\n" "\033[0m");
                    printf("\033[33m" "\t------------------------------------------------------\n" "\033[0m");

                    do
                    {
                        printf("\033[0;35m" "\n\tIntroduzca la hora de INICIO de la siguiente forma" "\033[0;32m" "(HH:MM):\n" "\033[0m");
                        printf("\033[0;32m" "\n\tHoras:" "\033[0m");
                        while(getchar() != '\n');
                        scanf("%d",&auxInput1);
                        printf("\033[0;32m" "\n\tMinutos:" "\033[0m");
                        while(getchar() != '\n');
                        scanf("%d",&auxInput2);
                        check = hourCheck(&auxInput1,&auxInput2);
                        if(check ==false)
                            printf("\033[0;31m" "\tHora incorrecta\n" "\033[0m");
                    } while (check == false);

                    auxStrLen = 6;
                    auxStr = (char*)realloc(auxStr,auxStrLen*sizeof(char));
                    hourIntToString(&auxInput1,&auxInput2,auxStr);
                    strcpy((*E_viajes)[travelPosition].H_inic, auxStr);
                }
            break;
        case 4: //Hora fin
            {
                system("cls");
                    printf("\033[33m" "\n\n\t------------------------------------------------------\n" "\033[0m");
                    printf("\033[33m" "\t\t MENU ADMINISTRADOR -> MODIFICAR VIAJE\n" "\033[0m");
                    printf("\033[33m" "\t------------------------------------------------------\n" "\033[0m");

                    do
                    {
                        printf("\033[0;35m" "\n\tIntroduzca la NUEVA hora de FIN de la siguiente forma" "\033[0;32m" "(HH:MM):\n\n" "\033[0m");
                        printf("\033[0;32m" "\tHoras: " "\033[0m");
                        while(getchar() != '\n');
                        scanf("%d",&auxInput3);
                        printf("\033[0;32m" "\n\tMinutos: " "\033[0m");
                        while(getchar() != '\n');
                        scanf("%d",&auxInput4);
                        check = hourCheckReturn(&auxInput3,&auxInput4,&auxInput1,&auxInput2);
                        if(check ==false)
                            printf("\033[0;31m""\tFormato de hora incorrecto u hora de vuelta invalida\n" "\033[0m");
                    } while (check == false);

                    hourIntToString(&auxInput3,&auxInput4,auxStr);
                    strcpy((*E_viajes)[travelPosition].H_fin, auxStr);
            }
            break;
        case 5: //Plazas libres
            {
                system("cls");
                    printf("\033[33m" "\n\n\t------------------------------------------------------\n" "\033[0m");
                    printf("\033[33m" "\t\t MENU ADMINISTRADOR -> MODIFICAR VIAJE\n" "\033[0m");
                    printf("\033[33m" "\t------------------------------------------------------\n" "\033[0m");

                    do
                    {
                        printf("\033[0;32m" "\n\n\tIntroduzca el numero de plazas libres del vehiculo: " "\033[0m");
                        scanf("%d",&auxInput1);
                        check = checkCarCapacity(&auxInput1,E_vehiculos, num_vehiculos,E_viajes,num_viajes);
                    } while (check == false);
                    (*E_viajes)[travelPosition].Plazas_Libres = auxInput1;
            }
            break;
        case 6: //Importe
            {
                system("cls");
                    printf("\033[33m" "\n\n\t------------------------------------------------------\n" "\033[0m");
                    printf("\033[33m" "\t\t MENU ADMINISTRADOR -> MODIFICAR VIAJE\n" "\033[0m");
                    printf("\033[33m" "\t------------------------------------------------------\n" "\033[0m");

                    do
                    {
                        printf("\033[0;35m" "\n\n\tIntroduzca el NUEVO IMPORTE:" "\033[0m");
                        scanf("%f",&auxFloatInput);
                    } while (auxFloatInput < 0.0f);
                    (*E_viajes)[travelPosition].Importe = auxFloatInput;
            }
            break;
        case 7: //Estado
            {
                system("cls");
                printf("\033[33m" "\n\n\t------------------------------------------------------\n" "\033[0m");
                printf("\033[33m" "\t\t MENU ADMINISTRADOR -> MODIFICAR VIAJE\n" "\033[0m");
                printf("\033[33m" "\t------------------------------------------------------\n" "\033[0m");

                do
                {
                    printf("\033[0;36m" "\n\n\t 1. Abierto.\n" "\033[0m");
                    printf("\033[0;36m" "\t 2. Cerrado.\n" "\033[0m");
                    printf("\033[0;36m" "\t 3. Iniciado.\n" "\033[0m");
                    printf("\033[0;36m" "\t 4. Finalizado.\n" "\033[0m");
                    printf("\033[0;36m" "\t 5. Anulado.\n" "\033[0m");
                    printf("\033[0;35m" "\n\n\t Seleccione una opcion: " "\033[0m");
                    scanf("%d",&auxInput1);
                } while (auxInput1>5 && auxInput1<0);

                switch (auxInput1)
                {
                case 1://Abierto
                    strcpy((*E_viajes)[travelPosition].Estado,"abierto");
                    break;
                case 2://Cerrado
                    strcpy((*E_viajes)[travelPosition].Estado,"cerrado");
                    break;
                case 3://Iniciado
                    strcpy((*E_viajes)[travelPosition].Estado,"iniciado");
                    break;
                case 4://Finalizado
                    strcpy((*E_viajes)[travelPosition].Estado,"finalizado");
                    break;
                case 5://Anulado
                    strcpy((*E_viajes)[travelPosition].Estado,"anulado");
                    break;
                default:
                    break;
                }
            }
            break;
        case 8: //Salir
            break;
        default:
            break;
        }
    printf("\033[0;32m" "\n\n\tVIAJE MODIFICADO CON EXITO\n" "\033[0m");
    }
    free(auxStr);
}

void mostrarViajesAdmin(Viajes**E_viajes, int *num_viajes,Pasos **E_pasos, int *num_pasos)
{
    int i = 0, j = 0, stops = 0, travelPosition = 0, stopI = 0;

        system("cls");
        printf("\033[33m" "\n\n\t------------------------------------------------------\n" "\033[0m");
        printf("\033[33m" "\t\t MENU ADMINSITRADOR -> MOSTRAR VIAJE\n" "\033[0m");
        printf("\033[33m" "\t------------------------------------------------------\n" "\033[0m");
        
        for(i = 0; i<*num_viajes;i++)
        {
            printf("\033[0;36m" "\tID del viaje: %s\n" "\033[0;37m""\tMatricula del vehiculo: %s\n\tFecha del viaje: %s\n\tHora de salida: %s\n\tHora de llegada: %s\n\tPlazas disponibles: %d\n\tTipo de viaje: %s\n\tImporte: %f€\n\tEstado: %s\n\n"  "\033[0m",(*E_viajes)[i].Id_viaje,(*E_viajes)[i].Id_mat,(*E_viajes)[i].F_inic, (*E_viajes)[i].H_inic,(*E_viajes)[i].H_fin,(*E_viajes)[i].Plazas_Libres, (*E_viajes)[i].Viaje, (*E_viajes)[i].Importe, (*E_viajes)[i].Estado);
            for(int j = 0; j<*num_pasos;j++)
            if(strcmp((*E_viajes)[i].Id_viaje,(*E_pasos)[i].Id_viaje)==0)
            {
                stops++;
                printf("\033[0;36m" "\tPasa por:\n" "\033[0m");
                for(stopI = 0 ; stopI<stops;stopI++)
                    printf("\033[0;32m" "\t %s\n""\033[0m",(*E_pasos)[stopI].Poblacion);
            }
        }
            
}

void eliminarViajesAdmin(Viajes**E_viajes, int *num_viajes)
{
    char *auxStr;
    int auxStrLen = 6, i = 0, travelPosition = 0;
    auxStr = (char*)calloc(auxStrLen,(sizeof(char)));
    system("cls");
    printf("\033[33m" "\n\n\t------------------------------------------------------\n" "\033[0m");
    printf("\033[33m" "\t\t MENU ADMINISTRADOR -> ELIMINAR VIAJE\n" "\033[0m");
    printf("\033[33m" "\t------------------------------------------------------\n" "\033[0m");


    do
    {
        for(i=0;i<*num_viajes;i++)
            printf("\033[0;36m""\t(%d)ID Viaje:""\033[0;36m" "\033[0;37m"" %s\n" "\033[0m",i+1,(*E_viajes)[i].Id_viaje);
        printf("\033[35m" "\n\tIngrese el ID de VIAJE a eliminar (000001-999999): " "\033[0m");
        scanf("%s",auxStr);
        travelPosition = lookForTravel(auxStr, E_viajes, num_viajes);
        if(travelPosition==-1)
            printf("\033[0;31m" "\tID de viaje incorrecto o fuera de formato. \n" "\033[0m");
    } while (travelPosition == -1);

    for(i = travelPosition; i<*num_viajes; i++)
    {
        strcpy((*E_viajes)[i].Id_viaje, (*E_viajes)[i+1].Id_viaje);
        strcpy((*E_viajes)[i].Id_mat, (*E_viajes)[i+1].Id_mat);
        strcpy((*E_viajes)[i].F_inic, (*E_viajes)[i+1].F_inic);
        (*E_viajes)[i].Plazas_Libres = (*E_viajes)[i+1].Plazas_Libres;
        strcpy((*E_viajes)[i].H_inic, (*E_viajes)[i+1].H_inic);
        strcpy((*E_viajes)[i].H_fin, (*E_viajes)[i+1].H_fin);
        strcpy((*E_viajes)[i].Viaje, (*E_viajes)[i+1].Viaje);
        (*E_viajes)[i].Importe = (*E_viajes)[i+1].Importe;
        strcpy((*E_viajes)[i].Estado, (*E_viajes)[i+1].Estado);
    }
    (*num_viajes)--;
    //Reorganizamos el array
    *E_viajes = realloc(*E_viajes, *num_viajes * sizeof(Viajes));

    for (i = 0; i < *num_viajes; i++)
        {
            sprintf((*E_viajes)[i].Id_viaje, "%05d", i+1);
        }
        system("cls");
        printf("\033[0;32m" "\n\n\tViaje eliminado." "\033[0m");
        system("pause");
}

void menuViajesAdmin(Viajes**E_viajes, int *num_viajes, Pasos **E_pasos, int *num_pasos, Usuarios **E_usuarios, int *num_usuarios, Vehiculos **E_vehiculos, int *num_vehiculos)
{
    int optionMenu = 0, repeatIntMenu = 0;
    char repeatMenu;
    do
    {
        system("cls");
        printf("\033[33m" "\n\n\t------------------------------------------------------\n" "\033[0m");
        printf("\033[33m" "\t\t MENU ADMINSTRADOR -> VIAJES\n" "\033[0m");
        printf("\033[33m" "\t------------------------------------------------------\n" "\033[0m");

        do
        {

            printf("\033[0;36m" "\n\n\t 1. Publicar Viaje \n" "\033[0m");
            printf("\033[0;36m" "\t 2. Modificar Viaje \n" "\033[0m");
            printf("\033[0;36m" "\t 3. Mostrar Viaje \n" "\033[0m");
            printf("\033[0;36m" "\t 4. Eliminar Viaje \n" "\033[0m");
            printf("\033[0;36m" "\t 5. Salir \n" "\033[0m");
            printf("\033[0;35m" "\n\n\t Seleccione una opcion: " "\033[0m");
            scanf("%d",&optionMenu);
            switch (optionMenu)
            {
            case 1://Publicar
                publicarViajesAdmin(E_viajes,num_viajes,E_pasos,num_pasos,E_usuarios,num_usuarios,E_vehiculos,num_vehiculos);
                break;
            case 2://Modificar
                modificarViajesAdmin(E_viajes,num_viajes,E_pasos,num_pasos,E_usuarios,num_usuarios,E_vehiculos,num_vehiculos);
                break;
            case 3://Mostrar
                mostrarViajesAdmin(E_viajes,num_viajes,E_pasos,num_pasos);
                break;
            case 4://Incorporarse
                eliminarViajesAdmin(E_viajes,num_viajes);
                break;
            case 5: //Salir
                repeatMenu ='n';
                break;
            default:
                break;
            }
        }while(optionMenu>5 || optionMenu <1);

        printf("\033[0;35m" "\n\n\tDesea hacer algo mas?""\033[0;32m" "(1 -> Si / 2 -> No):" "\033[0m");
        scanf("%d",&repeatIntMenu);
    }while (repeatIntMenu == 1);
}
//Funciones auxiliares

static void fillIdentifier(char* identifier, int num, int length)
{
    // Calcular la longitud del número como una cadena
    int numLength = snprintf(NULL, 0, "%d", num);

    // Rellenar con ceros a la izquierda si el número es más corto que la longitud deseada
    if (numLength < length) {
        int numZeros = length - numLength;
        for (int i = 0; i < numZeros; i++) {
            identifier[i] = '0';
        }
    }
    // Convertir el número a una cadena y copiarlo en el identificador
    snprintf(identifier + length - numLength, numLength + 1, "%d", num);
}

static bool dateCheck(int *dia, int *mes, int *anno)
{
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    bool result = false;
    //Comprobamos que sea válida el año con las variables que saca del sistema con el struct tm
    if (*anno < 1 || *anno < tm.tm_year + 1900)
    {
        result = false;
        return result;
    }

    if (*mes < 1 || *mes > 12)
    {
        result = false;
        return result;
    }

    if (*dia < 1 || *dia > 31)
    {
        result = false;
        return result;
    }

    if ((*mes == 4 || *mes == 6 || *mes == 9 || *mes == 11) && *dia > 30)
    {
        result = false;
        return result;
    }

    if (*mes == 2) {
        if ((*anno % 4 == 0 && *anno % 100 != 0) || *anno % 400 == 0) {
            if (*dia > 29)
            {
                result = false;
                return result;
            }
        } else {
            if (*dia > 28)
            {
                result = false;
                return result;
            }
        }
    }
    result = true;
    return result;
}

static void dateIntToString(int* dia, int* mes, int* anno, char* string)
{
    // Creamos un buffer de caracteres para almacenar la fecha en formato "dd/mm/aaaa"
    char fecha[11];

    // Copiamos cada componente de la fecha (dia, mes, anno) en el buffer
    sprintf(fecha, "%02d/%02d/%04d", *dia, *mes, *anno);

    // Copiamos la cadena generada al string que se pasa como argumento
    strncpy(string, fecha, 11);

    // Aseguramos que el string tenga terminador nulo
    string[10] = '\0';
}

static bool hourCheck(int *hora, int *minutos)
{
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    bool result = false;

    if(*hora < tm.tm_hour && *minutos < tm.tm_min && *hora > 23 && *minutos > 59)
    {
        result = false;
        return result;
    }
    result = true;
    return result;
}

static void hourIntToString(int* horas, int* minutos, char* string)
{
    // Creamos un buffer de caracteres para almacenar la hora en formato "HH:MM"
    char horaStr[6];

    // Copiamos cada componente de la fecha (horas,minutos) en el buffer
    sprintf(horaStr, "%02d:%02d", *horas, *minutos);

    // Copiamos la cadena generada al string que se pasa como argumento
    strncpy(string, horaStr, 6);

    // Aseguramos que el string tenga terminador nulo
    string[5] = '\0';
}

static bool hourCheckReturn(int *horas, int *minutos, int *horasIDA, int *minutosIDA)
{
    int hc1 = 0; //Variable que se devolverá de hourCheck
    hc1=hourCheck(horas,minutos);
    bool result = false;
    if(hc1 == 0)
    {
        result = false;
        return result;
    }
    else
    {
        if(*horasIDA>*horas && *minutosIDA > *minutos) //Si la hora de llegada es antes de la hora de salida, es incorrecto
        {
            result = false;
            return result;
        }
    }

    result = true;
    return result;
}

static bool checkCarLicencePlate(char *mat, int *user, Vehiculos *E_vehiculos, Usuarios *E_usuarios, int *num_vehiculos)
{
    int i = 0;
    bool result = false;
    for(i=0; i<*num_vehiculos;i++)
    {
        if(strcmp(E_usuarios[*user].Id_usuario,E_vehiculos[i].Id_usuario)==0 && strcmp(E_vehiculos[i].Id_mat,mat)==0)
            result = true;
    }
    return result;

}

static int lookForCar(char *auxStr, Vehiculos **E_vehiculos, int *num_vehiculos)
{
    int i = 0,result=0;
    for(i=0;i<*num_vehiculos;i++)
    {
        if(strcmp((*E_vehiculos)[i].Id_mat,auxStr)==0)
            result = (*E_vehiculos)[i].Num_plazas;
    }
    return result;
}

static int checkTravelCode(char *auxStr, Vehiculos **E_vehiculos, int *posicionUsuario, int *num_vehiculos, Viajes **E_viajes, int *num_viajes, Usuarios **E_usuarios, int *num_usuarios)
{
    int i = 0, j = 0;
    int result = -1;
    for(i=0;i<*num_viajes;i++)
        for(j=0;j<*num_vehiculos;j++)
            if(strcmp((*E_viajes)[i].Id_viaje,auxStr)==0 && strcmp((*E_viajes)[i].Id_mat,(*E_vehiculos)[j].Id_mat)==0 && strcmp((*E_vehiculos)[j].Id_usuario,(*E_usuarios)[*posicionUsuario].Id_usuario)==0)
                result = i;
    return result;
}

static bool checkCarCapacity(int *input, Vehiculos **E_vehiculos, int *num_vehiculos, Viajes **E_viajes, int *num_viajes)
{
    int i = 0, j = 0;
    bool result = false;
    for(i=0;i<*num_viajes;i++)
        for(j=0;j<*num_vehiculos;j++)
            if(strcmp((*E_viajes)[i].Id_mat,(*E_vehiculos)[j].Id_mat)==0 && (*E_vehiculos)[j].Num_plazas >= *input)
                result = true;
    return result;
}

static int lookForUser(char *auxStr, Usuarios **E_usuarios, int *num_usuarios)
{
    int posUsuarioAux = -1;
    int i = 0;
    for(i=0;i<*num_usuarios;i++)
        if(strcmp(auxStr,(*E_usuarios)[i].Id_usuario)==0)
            posUsuarioAux = i;
    return posUsuarioAux;
}

static int lookForTravel(char *auxStr, Viajes **E_Viajes, int *num_viajes)
{
    int posViajeAux = -1;
    int i = 0;
    for(i=0;i<*num_viajes;i++)
        if(strcmp(auxStr,(*E_Viajes)[i].Id_viaje)==0)
            posViajeAux = i;
    return posViajeAux;
}
