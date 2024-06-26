#include <stdio.h>

struct pasajero{
    int asiento;
    char Nombre[15];
    char direccion[15];
    int anioDeNacimiento;
    int telefono;
    int DNI;
    int borrado;
};

void fecha(int *fechaActual){
    printf("ingrese la fecha de hoy ");
    scanf("%i",fechaActual);
}

void Flimite(int *fechaDeSalida1,int *fechaDeSalida2,int *fechaDeSalida3,int *fechaDeSalida4,int *fechaLimite){
    printf("\ningrese la fecha de salida en dias del primer viaje");
    scanf("%i",fechaDeSalida1);
    printf("\ningrese la fecha de salida del segundo viaje ");
    scanf("%i",fechaDeSalida2);
    printf("\ningrese la fecha salida del tercer viaje");
    scanf("%i",fechaDeSalida3);
    printf("\ningrese la fecha de salida del cuarto viaje");
    scanf("%i",fechaDeSalida4);    
}

void devolucion(int fechaActual, int fechaLimite, int *colectivo, struct pasajero *pasajeroColectivo, int *cantidad){
    int asiento = 0;
    int fechaLimiteDevolucion = 0;
    fechaLimiteDevolucion = (fechaLimite - fechaActual);
    struct pasajero vacio;

    if (fechaLimiteDevolucion <= 2) {
        printf("\nNo se aceptan devoluciones 48hs antes de la fecha pactada");
        system("pause");
        return;
    }
    
    printf("\nIngrese el numero de asiento elegido para poder realizar la devolucion: ");
    scanf("%i", &asiento);
    colectivo[asiento - 1] = 0;
    pasajeroColectivo[asiento - 1].borrado = 1;
    (*cantidad)--;
    printf("\nDevolucion aceptada!");
    system("\npause");
}

void ingresarPasajero(int *ptrColectivo) {
    int asiento;
    printf("\nIngrese el lugar deseado entre 1 y 20: ");
    scanf("%i", &asiento);

    if (asiento < 1 || asiento > 20) {
        printf("\nError, asiento invalido");
        system("\npause");
        return;
    }

    if (ptrColectivo[asiento - 1] == 1) {
        printf("\nError, lugar ocupado");
        system("\npause");
        return;
    }

    ptrColectivo[asiento - 1] = 1;
    system("\npause");
}

void MostrarLugaresLibres(int *ptrColectivo) {
    printf("Croquis del Omnibus:\n");
    for (int i = 0; i < 20; i += 4) {
        printf("Asiento %2d [ %s ] Asiento %2d [ %s ] | PASILLO | Asiento %2d [ %s ] Asiento %2d [ %s ]\n",
            i + 1, ptrColectivo[i] == 1 ? "Ocupado" : "Libre",
            i + 2, ptrColectivo[i + 1] == 1 ? "Ocupado" : "Libre",
            i + 4, ptrColectivo[i + 2] == 1 ? "Ocupado" : "Libre",
            i + 3, ptrColectivo[i + 3] == 1 ? "Ocupado" : "Libre"
        );
    }
    printf("\n");
    system("pause");
}

int cargarDatosCliente(struct pasajero *pasajeroDelcolectivo, int *cantidad, int *menores, int*ptrColectivo, float *recaudacion, float *recaudacionDiaria) {
    if (*cantidad >= 20) {
        printf("\nNo hay más lugar en este colectivo");
        system("pause");
        return *cantidad;
    }

    printf("\ningrese el asiento: ");
    scanf("%i", &pasajeroDelcolectivo[*cantidad].asiento);

    printf("\ningrese su nombre: ");
    scanf("%s", pasajeroDelcolectivo[*cantidad].Nombre);

    printf("\ningrese direccion: ");
    scanf("%s", pasajeroDelcolectivo[*cantidad].direccion);

    printf("\ningrese su año de nacimiento: ");
    scanf("%d", &pasajeroDelcolectivo[*cantidad].anioDeNacimiento);

    /* Los mayores abonan el 100% del importe, los menores de 6 años el 50% y los menores
    de 2 años viajan gratis. */
    
    int edad = 2024 - pasajeroDelcolectivo[*cantidad].anioDeNacimiento;
    if (edad <= 2) {
        printf("\nViaja gratis");
        pasajeroDelcolectivo[*cantidad].asiento = 0; // en la estructura pasajero su asiento se vuelve 0;
        ptrColectivo[*cantidad] = 0; // se vuelve 0 le posicion donde se encuentra sentado el menor, figurando como asiento libre;
    } else if (edad <= 6) {
        printf("\nDebe pagar el 50%% del boleto");
        *recaudacion = *recaudacion + 0.5;
        *recaudacionDiaria = *recaudacionDiaria + 0.5;
    } else {
        printf("\nDebe pagar el 100%% del boleto");
        *recaudacion = *recaudacion + 1;
        *recaudacionDiaria = *recaudacionDiaria + 1;
    }

    if (edad < 18) {
        (*menores)++;
    }

    printf("\nIngrese el telefono: ");
    scanf("%i", &pasajeroDelcolectivo[*cantidad].telefono);
    printf("\ningrese el numero de dni: ");
    scanf("%i", &pasajeroDelcolectivo[*cantidad].DNI);
    pasajeroDelcolectivo[*cantidad].borrado = 0;
    (*cantidad)++;
    return *cantidad;
}


void listarPasajeros(struct pasajero *pasajeroDelcolectivo, int cantidad) {
    system("cls");
    if (cantidad == 0) {
        printf("\nNo se encontró ningun pasajero...\n");
        system("\npause");
        return;
    }
    for (int i = 0; i < cantidad; i++) {
        if (pasajeroDelcolectivo[i].borrado == 0){
            printf("\n*********** CLIENTE ***********\n");
            printf("Asiento: %d\n", pasajeroDelcolectivo[i].asiento);
            printf("DNI: %d\n", pasajeroDelcolectivo[i].DNI);
            printf("Nombre: %s\n", pasajeroDelcolectivo[i].Nombre);
            printf("Telefono: %d\n", pasajeroDelcolectivo[i].telefono);
            printf("Edad: %d\n", 2024 - pasajeroDelcolectivo[i].anioDeNacimiento);
            printf("borrado: %d\n", pasajeroDelcolectivo[i].borrado);
        }
    }
    system("pause");
}

void calcularEstadisticasPorColectivo(int cantcantidadPasajeros , int cantidadMenores){
    if (cantcantidadPasajeros == 0) {
        printf("\nNo se encontró ningun pasajero...\n");
        system("\npause");
        return;
    }
    int asientos = 20;
    int porcenajeMenores = 0;
    int porcentajeVendido = 0;
    porcentajeVendido = (cantcantidadPasajeros * 100) / asientos;
    porcenajeMenores = (cantidadMenores * 100) / cantcantidadPasajeros;
    printf("\nEl porcentaje de asientos vendidos es de %i%% ", porcentajeVendido);
    printf("\nEl porcentaje de menores es de : %i%% ", porcenajeMenores);
    system("pause");
}

void recaudacion(float colectivo, float precio){
    float recaudacionTotal =  colectivo * precio;
    printf("La recaudacion es : %.2f ", recaudacionTotal);
    system("\npause");
}

void funRecaudacionDiaria(float recaudacionDiaria, float precio){
    float recaudacionTotal =  recaudacionDiaria * precio;
    printf("La recaudacion diaria es : %.2f ", recaudacionTotal);
    system("\npause");
}

void guardarDatos(
    const char *filename, int fechaDeSalida1, int fechaDeSalida2, int fechaDeSalida3, int fechaDeSalida4,
    int fechaActual, int ColectivoIda1[20], int ColectivoIda2[20], int ColectivoVuelta1[20], int ColectivoVuelta2[20],
    struct pasajero colectivo1[20], int pasajeroCantidad1, int cantidadMenoresColectivo1,
    struct pasajero colectivo2[20], int pasajeroCantidad2, int cantidadMenoresColectivo2,
    struct pasajero colectivo3[20], int pasajeroCantidad3, int cantidadMenoresColectivo3,
    struct pasajero colectivo4[20], int pasajeroCantidad4, int cantidadMenoresColectivo4,
    float recaudacionColectivoIda1, float recaudacionColectivoIda2, float recaudacionColectivoVuelta1, float recaudacionColectivoVuelta2, float recaudacionDia ){

        FILE *file = fopen(filename, "wb");
        if (!file) {
            printf("Error al abrir el archivo para escribir.\n");
            return;
        }

        fwrite(&fechaDeSalida1, sizeof(int), 1, file);
        fwrite(&fechaDeSalida2, sizeof(int), 1, file);
        fwrite(&fechaDeSalida3, sizeof(int), 1, file);
        fwrite(&fechaDeSalida4, sizeof(int), 1, file);
        fwrite(&fechaActual, sizeof(int), 1, file);
        fwrite(ColectivoIda1, sizeof(int), 20, file);
        fwrite(ColectivoIda2, sizeof(int), 20, file);
        fwrite(ColectivoVuelta1, sizeof(int), 20, file);
        fwrite(ColectivoVuelta2, sizeof(int), 20, file);
        fwrite(colectivo1, sizeof(struct pasajero), 20, file);
        fwrite(&pasajeroCantidad1, sizeof(int), 1, file);
        fwrite(&cantidadMenoresColectivo1, sizeof(int), 1, file);
        fwrite(colectivo2, sizeof(struct pasajero), 20, file);
        fwrite(&pasajeroCantidad2, sizeof(int), 1, file);
        fwrite(&cantidadMenoresColectivo2, sizeof(int), 1, file);
        fwrite(colectivo3, sizeof(struct pasajero), 20, file);
        fwrite(&pasajeroCantidad3, sizeof(int), 1, file);
        fwrite(&cantidadMenoresColectivo3, sizeof(int), 1, file);
        fwrite(colectivo4, sizeof(struct pasajero), 20, file);
        fwrite(&pasajeroCantidad4, sizeof(int), 1, file);
        fwrite(&cantidadMenoresColectivo4, sizeof(int), 1, file);
        fwrite(&recaudacionColectivoIda1, sizeof(float), 1, file);
        fwrite(&recaudacionColectivoIda2, sizeof(float), 1, file);
        fwrite(&recaudacionColectivoVuelta1, sizeof(float), 1, file);
        fwrite(&recaudacionColectivoVuelta2, sizeof(float), 1, file);
        fwrite(&recaudacionDia, sizeof(float), 1, file);

        fclose(file);
        printf("\nDatos actualizados...\n");
        system("pause");
}

void cargarDatos(
    const char *filename,
    int *fechaDeSalida1, int *fechaDeSalida2, int *fechaDeSalida3, int *fechaDeSalida4,
    int *fechaActual,
    int ColectivoIda1[20], int ColectivoIda2[20], int ColectivoVuelta1[20], int ColectivoVuelta2[20],
    struct pasajero colectivo1[20], int *pasajeroCantidad1, int *cantidadMenoresColectivo1,
    struct pasajero colectivo2[20], int *pasajeroCantidad2, int *cantidadMenoresColectivo2,
    struct pasajero colectivo3[20], int *pasajeroCantidad3, int *cantidadMenoresColectivo3,
    struct pasajero colectivo4[20], int *pasajeroCantidad4, int *cantidadMenoresColectivo4,
    float *recaudacionColectivoIda1, float *recaudacionColectivoIda2, float *recaudacionColectivoVuelta1, float *recaudacionColectivoVuelta2,
    float *recaudacionDia
){
        
        FILE *file = fopen(filename, "rb");
        if (!file) {
            printf("Error al abrir el archivo para leer. Se creara uno nuevo\n");
            FILE *file = fopen(filename, "wb");
        }

        fread(fechaDeSalida1, sizeof(int), 1, file);
        fread(fechaDeSalida2, sizeof(int), 1, file);
        fread(fechaDeSalida3, sizeof(int), 1, file);
        fread(fechaDeSalida4, sizeof(int), 1, file);
        fread(fechaActual, sizeof(int), 1, file);
        fread(ColectivoIda1, sizeof(int), 20, file);
        fread(ColectivoIda2, sizeof(int), 20, file);
        fread(ColectivoVuelta1, sizeof(int), 20, file);
        fread(ColectivoVuelta2, sizeof(int), 20, file);
        fread(colectivo1, sizeof(struct pasajero), 20, file);
        fread(pasajeroCantidad1, sizeof(int), 1, file);
        fread(cantidadMenoresColectivo1, sizeof(int), 1, file);
        fread(colectivo2, sizeof(struct pasajero), 20, file);
        fread(pasajeroCantidad2, sizeof(int), 1, file);
        fread(cantidadMenoresColectivo2, sizeof(int), 1, file);
        fread(colectivo3, sizeof(struct pasajero), 20, file);
        fread(pasajeroCantidad3, sizeof(int), 1, file);
        fread(cantidadMenoresColectivo3, sizeof(int), 1, file);
        fread(colectivo4, sizeof(struct pasajero), 20, file);
        fread(pasajeroCantidad4, sizeof(int), 1, file);
        fread(cantidadMenoresColectivo4, sizeof(int), 1, file);
        fread(recaudacionColectivoIda1, sizeof(float), 1, file);
        fread(recaudacionColectivoIda2, sizeof(float), 1, file);
        fread(recaudacionColectivoVuelta1, sizeof(float), 1, file);
        fread(recaudacionColectivoVuelta2, sizeof(float), 1, file);
        fread(recaudacionDia, sizeof(float), 1, file);

        fclose(file);
}

int main() {

    int fechaDeSalida1 = 0;
    int fechaDeSalida2 = 0;
    int fechaDeSalida3 = 0;
    int fechaDeSalida4 = 0;
    int fechaLimite = 0;
    int fechaActual = 0;
    int opcion = 0;
    
    int ColectivoIda1[20];
    int ColectivoIda2[20];
    int ColectivoVuelta1[20];
    int ColectivoVuelta2[20];

    // Array de pasajeros en colectivos y cantidad de pasajeros respectivamente;
    // Tambien hay una variables que contienen la cantidad de menores; 

    struct pasajero colectivo1[20];
    int pasajeroCantidad1 = 0;
    int cantidadMenoresColectivo1 = 0;

    struct pasajero colectivo2[20];
    int pasajeroCantidad2 = 0;
    int cantidadMenoresColectivo2 = 0;

    struct pasajero colectivo3[20];
    int pasajeroCantidad3 = 0;
    int cantidadMenoresColectivo3 = 0;
    
    struct pasajero colectivo4[20];
    int pasajeroCantidad4 = 0;
    int cantidadMenoresColectivo4 = 0;

    // recaudacion de cada viaje;

    float recaudacionColectivoIda1 = 0;
    float recaudacionColectivoIda2 = 0;
    float recaudacionColectivoVuelta1 = 0;
    float recaudacionColectivoVuelta2 = 0;

    float recaudacionDiaria = 0;

    // recaudacaion del dia;
    float recaudacionDia = 0;

    // Iterador de croquis de colectivo;
    int croquisColectivo = 0;

    //CREAR VARIABLE PARA LISTAR PASAJEROS
    int iteradorDePasajeros = 0;

    // Iterador de devoluicion de pasajeros;
    int devolucionOpcion = 0;

    // precio del boleto;

    float precioBoleto = 0;

    

    cargarDatos("datos.bin", &fechaDeSalida1, &fechaDeSalida2, &fechaDeSalida3, &fechaDeSalida4, &fechaActual, ColectivoIda1, ColectivoIda2, ColectivoVuelta1, ColectivoVuelta2,colectivo1, &pasajeroCantidad1, &cantidadMenoresColectivo1, colectivo2, &pasajeroCantidad2, &cantidadMenoresColectivo2,colectivo3, &pasajeroCantidad3, &cantidadMenoresColectivo3,colectivo4, &pasajeroCantidad4, &cantidadMenoresColectivo4, &recaudacionColectivoIda1, &recaudacionColectivoIda2, &recaudacionColectivoVuelta1, &recaudacionColectivoVuelta2, &recaudacionDia
    );

    printf("\nIngrese el precio del boleto : ");
    scanf("%f", &precioBoleto);

    do{
        guardarDatos("datos.bin", fechaDeSalida1, fechaDeSalida2, fechaDeSalida3, fechaDeSalida4, fechaActual,
                             ColectivoIda1, ColectivoIda2, ColectivoVuelta1, ColectivoVuelta2,
                             colectivo1, pasajeroCantidad1, cantidadMenoresColectivo1,
                             colectivo2, pasajeroCantidad2, cantidadMenoresColectivo2,
                             colectivo3, pasajeroCantidad3, cantidadMenoresColectivo3,
                             colectivo4, pasajeroCantidad4, cantidadMenoresColectivo4,
                             recaudacionColectivoIda1, recaudacionColectivoIda2,
                             recaudacionColectivoVuelta1, recaudacionColectivoVuelta2, precioBoleto);
        system("cls");
        printf("\nFecha actual : %i", fechaActual);
        printf("\nPrecio actual del boleto : %.2f", precioBoleto);
        printf("\n********* - Gestion de pasajeros - *********");
        printf("\n1. Ingresar pasajero de colectivo");
        printf("\n2. Listar pasajeros de colectivo");
        printf("\n3. Mostrar asientos libres de colectivo");
        printf("\n4. Calcular estadisticas por colectivo");
        printf("\n5. Ingrese la fecha de salida de cada colectivo como administrador");
        printf("\n6. Ingresar fecha actual");
        printf("\n7. Devoluciones");
        printf("\n8. Ver recaudacion");
        printf("\n9. Salir del programa...");   
        printf("\nIngrese una opcion : ");

        printf("\nTEST --------------- tests");
        printf("\n");
        printf("\ncantidad de gente en colectivo 1: %i", pasajeroCantidad1);
        printf("\n");
        printf("\nTEST --------------- tests");

            scanf("%d", &opcion);

        switch (opcion){
            case 1:
                do {
                    system("cls");
                    printf("\n1. Ingresar colectivo 1 de ida");
                    printf("\n2. Ingresar colectivo 2 de ida");
                    printf("\n3. Ingresar colectivo 1 de vuelta");
                    printf("\n4. Ingresar colectivo 2 de vuelta");
                    printf("\n5. Volver al menu...");
                    printf("\nIngrese una opcion : ");
                    scanf("%i", &iteradorDePasajeros);
                    if (iteradorDePasajeros == 1) {
                        ingresarPasajero(ColectivoIda1);
                        cargarDatosCliente(colectivo1, &pasajeroCantidad1, &cantidadMenoresColectivo1, &ColectivoIda1, &recaudacionColectivoIda1, &recaudacionDiaria);
                    } else if (iteradorDePasajeros == 2) {
                        ingresarPasajero(ColectivoIda2);
                        cargarDatosCliente(colectivo2, &pasajeroCantidad2, &cantidadMenoresColectivo2, &ColectivoIda2, &recaudacionColectivoIda2, &recaudacionDiaria);
                    } else if (iteradorDePasajeros == 3){
                        ingresarPasajero(ColectivoVuelta1);
                        cargarDatosCliente(colectivo3, &pasajeroCantidad3, &cantidadMenoresColectivo3, &ColectivoVuelta1, &recaudacionColectivoVuelta1, &recaudacionDiaria);
                    } else if (iteradorDePasajeros == 4) {
                        ingresarPasajero(ColectivoVuelta2);
                        cargarDatosCliente(colectivo4, &pasajeroCantidad4, &cantidadMenoresColectivo4, &ColectivoVuelta2, &recaudacionColectivoVuelta2, &recaudacionDiaria);
                    }
                } while (iteradorDePasajeros != 5);
            break;
            case 2:
                do {
                    system("cls");
                    printf("\n1. Listado colectivo 1 de ida");
                    printf("\n2. Listado colectivo 2 de ida");
                    printf("\n3. Listado colectivo 1 de vuelta");
                    printf("\n4. Listado colectivo 2 de vuelta");
                    printf("\n5. Volver al menu...");
                    printf("\nIngrese una opcion : ");
                    scanf("%i", &iteradorDePasajeros);
                    if (iteradorDePasajeros == 1) {
                       listarPasajeros(colectivo1, pasajeroCantidad1);
                    } else if (iteradorDePasajeros == 2) {
                       listarPasajeros(colectivo2, pasajeroCantidad2); 
                    } else if (iteradorDePasajeros == 3){
                        listarPasajeros(colectivo3, pasajeroCantidad3);
                    } else if (iteradorDePasajeros == 4) {
                        listarPasajeros(colectivo4, pasajeroCantidad4);
                    }
                } while (iteradorDePasajeros != 5);
            break;
            case 3:
                do {
                    system("cls");
                    printf("\n1. Croquis colectivo 1 de ida");
                    printf("\n2. Croquis colectivo 2 de ida");
                    printf("\n3. Croquis colectivo 1 de vuelta");
                    printf("\n4. Croquis colectivo 2 de vuelta");
                    printf("\n5. Volver al menu...");
                    printf("\nIngrese una opcion : ");
                    scanf("%i", &croquisColectivo);
                    system("cls");
                    if (croquisColectivo == 1) {
                        MostrarLugaresLibres(ColectivoIda1);
                    } else if (croquisColectivo == 2) {
                        MostrarLugaresLibres(ColectivoIda2);
                    } else if (croquisColectivo == 3){
                        MostrarLugaresLibres(ColectivoVuelta1);
                    } else if (croquisColectivo == 4) {
                        MostrarLugaresLibres(ColectivoVuelta2);
                    }
                } while (croquisColectivo != 5);
            break;
            case 4:
                do {
                    system("cls");
                    printf("\n1. Estadisticas colectivo 1 ida");
                    printf("\n2. Estadisticas colectivo 2 ida");
                    printf("\n3. Estadisticas colectivo 1 vuelta");
                    printf("\n4. Estadisticas colectivo 2 vuelta");
                    printf("\n5. Volver al menu...");
                    printf("\nIngrese una opcion : ");
                    scanf("%i", &croquisColectivo);
                    system("cls");
                    if (croquisColectivo == 1) {
                        calcularEstadisticasPorColectivo(pasajeroCantidad1, cantidadMenoresColectivo1);
                    } else if (croquisColectivo == 2) {
                        calcularEstadisticasPorColectivo(pasajeroCantidad2, cantidadMenoresColectivo2);
                    } else if (croquisColectivo == 3){
                        calcularEstadisticasPorColectivo(pasajeroCantidad3, cantidadMenoresColectivo3);
                    } else if (croquisColectivo == 4) {
                        calcularEstadisticasPorColectivo(pasajeroCantidad4, cantidadMenoresColectivo4);
                    }
                } while (croquisColectivo != 5);
            break;
            case 5:
                system("cls");
                Flimite( &fechaDeSalida1, &fechaDeSalida2, &fechaDeSalida3, &fechaDeSalida4, &fechaLimite);
            break;
            case 6:
                system("cls");
                fecha(&fechaActual);
            break;
            case 7: 
                do {
                    system("cls");
                    printf("\n1. Devolucion colectivo 1 ida");
                    printf("\n2. Devolucion colectivo 2 ida");
                    printf("\n3. Devolucion colectivo 1 vuelta");
                    printf("\n4. Devolucion colectivo 2 vuelta");
                    printf("\n5. Volver al menu...");
                    printf("\nIngrese una opcion : ");
                    scanf("%i", &devolucionOpcion);
                    if (devolucionOpcion == 1) {
                        devolucion(fechaActual, fechaDeSalida1, ColectivoIda1, colectivo1, &pasajeroCantidad1);
                    } else if (devolucionOpcion == 2) {
                        devolucion(fechaActual, fechaDeSalida2, ColectivoIda2, colectivo2, &pasajeroCantidad2);
                    } else if (devolucionOpcion == 3){
                        devolucion(fechaActual, fechaDeSalida3, ColectivoVuelta1, colectivo3, &pasajeroCantidad3);
                    } else if (devolucionOpcion == 4) {
                        devolucion(fechaActual, fechaDeSalida4, ColectivoVuelta2, colectivo4, &pasajeroCantidad4);
                    }
                } while (devolucionOpcion != 5);
            break;
            case 8: 
                do {
                    system("cls");
                    printf("\n1. Recaudacion colectivo 1 ida");
                    printf("\n2. Recaudacion colectivo 2 ida");
                    printf("\n3. Recaudacion colectivo 1 vuelta");
                    printf("\n4. Recaudacion colectivo 2 vuelta");
                    printf("\n5. Recaudacion diaria");
                    printf("\n6. Volver al menu...");
                    printf("\nIngrese una opcion : ");
                    scanf("%i", &devolucionOpcion);
                    if (devolucionOpcion == 1) {
                        recaudacion(recaudacionColectivoIda1, precioBoleto);
                    } else if (devolucionOpcion == 2) {
                        recaudacion(recaudacionColectivoIda2, precioBoleto);
                    } else if (devolucionOpcion == 3){
                        recaudacion(recaudacionColectivoVuelta1, precioBoleto);
                    } else if (devolucionOpcion == 4) {
                        recaudacion(recaudacionColectivoVuelta2, precioBoleto);
                    } else if (devolucionOpcion == 5){
                        funRecaudacionDiaria(recaudacionDiaria, precioBoleto);
                    }
                } while (devolucionOpcion != 6);
            break;
        } 
    } while (opcion != 9 );
}