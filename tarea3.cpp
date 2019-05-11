/* PROGRAMA QUE PERMITE OBTENER EL PROMEDIO, VARIANZA 
Y DESV. ESTANDAR DE UN ARREGLO, LUEGO DE PARALELIZAR SUS PROCESOS */

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <mpi.h>

using namespace std;

/* Función que permite llenar un arreglo de un tamaño determinado con numeros aleatorios */
void llenar_arreglo(int arreglo[], int tamano){

    srand(time(NULL));
    for (int i=0; i<tamano; i++){
        arreglo[i]=rand()%100;
    }
}

/* Función para crear sub_arreglos desde un arreglo inicial */
int* crear_arreglos(int inicio, int fin, int* origen){
    int* sub_arreglo;
    int tamano;
    int aux = 0;
    tamano = fin - inicio;
    sub_arreglo = (int*)malloc(tamano * sizeof(int));
    for (int i = inicio; i < fin; ++i) {
        *(sub_arreglo+aux) = *(origen+i);
        aux += 1;
    }
    return  sub_arreglo;
}

/*  Función para obtener el promedio de un arreglo */
float obtener_promedio(int inicio, int fin, int* sub_arreglo){ /* Se ingresa a la función: el inicio del sub_vec, el fin, el sub_vec y el vector con datos*/
    float sub_promedio = 0.0;
    int aux = 0;
    float suma = 0.0;

    /* Ciclo para obtener la suma total de los valores del arreglo */
    for (int i = inicio; i < fin; ++i) {
        suma += *(sub_arreglo+aux);
        aux += 1;
    }

    sub_promedio = suma/(inicio-fin); /* Obtiene el sub_promedio de un arreglo */
    return sub_promedio;
}

/*  Función para obtener la varianza de un arreglo */
float obtener_varianza(int arreglo[], float promedio, int tamano){
    float varianza = 0.0;
    for(int i=0; i<tamano; i++){
        varianza += pow(arreglo[i] - promedio, 2.0);
    }
    return varianza/=tamano;
}

/*  Función para obtener la desviación estandar de un arreglo */
float obtener_desv_estandar(float varianza){
    return sqrt(varianza);
}


/* PROGRAMA PRINCIPAL */

int main(int argc, char** argv)
{
    /* Variables y Funcion para llenar arreglo */
    int tamano=100000;
    int arreglo[tamano];
    llenar_arreglo(arreglo,tamano);

    /* Inicializa MPI */
    MPI_Init(&argc, &argv);

    int mi_rango; /* Rango del proceso */
    int tamano_procesadores; /* Numero de procesos */
    int fuente; /* Rango del que envia  */
    int destino; /* Rango del que recibe */
    int tag = 0; /* Etiqueta del mensaje */
    int* sub_arreglo = NULL;
    float promedio = 0.0;
    float desv_estandar = 0.0;
    float varianza = 0.0;
    float sub_promedio;
    float cantidad_sub_arreglos;

    MPI_Status estado; /* Devuelve estado al recibir*/

    MPI_Comm_size(MPI_COMM_WORLD, &tamano_procesadores);
    MPI_Comm_rank(MPI_COMM_WORLD, &mi_rango);

    cantidad_sub_arreglos = tamano/tamano_procesadores;

    if (mi_rango != 0){
        sub_arreglo = (int*)malloc(cantidad_sub_arreglos * sizeof(int));

        fuente = 0;

        /* MPI_Recv(dato_a_recibir, contador, tipo_de_dato, fuente, tag, comunicador, status) */
        MPI_Recv(&sub_promedio, cantidad_sub_arreglos, MPI_INT, fuente,tag, MPI_COMM_WORLD, &estado);
        promedio += sub_promedio;
        varianza = obtener_varianza(arreglo,promedio,tamano);
        desv_estandar = obtener_desv_estandar(varianza);

        cout << "Promedio de Arreglo[" << tamano << "] es: " << promedio << endl;
        cout << "Desv.Estandar de Arreglo[" << tamano << "] es: " << desv_estandar << endl;
        cout << "Varianza de Arreglo[" << tamano << "] es: " << varianza << endl;
    }

    else{
        /* Ciclo for para distribuir los datos en distintos arreglos y paralelizarlos */
        cout << "Distribuiendo Datos" << endl;
        for (int destino = 1; destino < tamano_procesadores; destino++){

            sub_arreglo = crear_arreglos(destino*cantidad_sub_arreglos, (destino*cantidad_sub_arreglos)+cantidad_sub_arreglos, arreglo);
            sub_promedio = obtener_promedio(destino*cantidad_sub_arreglos, (destino*cantidad_sub_arreglos)+cantidad_sub_arreglos, sub_arreglo);
            /* MPI_Send(&dato_a_enviar, contador(0/1), tipo_de_dato, destino, tag(0/1), comunicador) */
            MPI_Send(&sub_promedio, cantidad_sub_arreglos, MPI_INT, destino, tag, MPI_COMM_WORLD);
            cout << ("...") << endl;
        }
        cout << "Datos Distribuidos" << endl;

        sub_arreglo = crear_arreglos(0, cantidad_sub_arreglos, arreglo);
        sub_promedio = obtener_promedio(0,cantidad_sub_arreglos, sub_arreglo);
    }



    /* Finaliza MPI */
    MPI_Finalize();

    return 0;
}
