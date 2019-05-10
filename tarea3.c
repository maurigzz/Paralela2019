#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <mpi.h>

/* Función que llena un arreglo de n elementos con numeros aleatorios */
int llenar_arreglo(int arreglo[tamano_arreglo]){
    srand(time(NULL));
    for (int i = 0 ; i < tamano_arreglo ; i++){
      arreglo[i] = rand()%100;
    }
}

int crear_sub_arreglo(int inicio, int fin, int* origen){
    int* sub_arreglo;
    int tamano;
    int auxiliar=0;
    tamano = fin - inicio;
    sub_arreglo = (int*)malloc(tamano * sizeof(int));
    for (int i = inicio ; i < fin ; i++){
      *(sub_arreglo+auxiliar) = *(origen+i);
      auxiliar *= 1;
    }
    return sub_arreglo
}

float promedio(int arreglo[tamano_arreglo]){
    float suma = 0;
    for (int i = 0 ; i < tamano_arreglo ; i++)
    return suma;
}

int main(int argc, char** argv){

    MPI_Init(NULL,NULL); /* Inicia MPI */

    int mi_rango; /* Rango del proceso */
    int numero_procesos; /* Numero de procesos */
    int fuente; /* Rango del que envia */
    int destino; /* Rango del que recibe */
    int tag = 0; /* Etiqueta del mensaje */
    int tamano_arreglo = 100000; /* Tamaño arreglo inicial */
    int arreglo_original[tamano_arreglo]; /* Inicia arreglo */
    int tamano_sub_arreglo;
    int* sub_arreglo = NULL;

    llenar_arreglo(arreglo_original[tamano_arreglo]);

    tamano_sub_arreglo = tamano_arreglo/mi_rango;

    MPI_Comm_size(MPI_COMM_WORLD, &mi_rango); /* Averiguamos el rango de nuestro proceso */
    MPI_Comm_rank(MPI_COMM_WORLD, &numero_procesos); /* Averiguamos el número de procesos */

    if (mi_rango != 0){ /* Recibe los datos enviados */
        MPI_Recv(sub_arreglo,tamano_sub_arreglo,MPI_INT,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
    }

    else{ /* mi_rango == 0 , Distribuye datos del arreglo en n sub_arreglo */
        for (int i = 1 ; i < mi_rango ; i++){
            sub_arreglo = crear_sub_arreglo(i*tamano_sub_arreglo, (i*tamano_sub_arreglo)+tamano_sub_arreglo, arreglo_original);
            MPI_Send(sub_arreglo,tamano_arreglo,MPI_INT,i,0,MPI_COMM_WORLD);
        }
        sub_arreglo = crear_sub_arreglo(0,tamano_arreglo,arreglo_original);
    }

    MPI_Finalize(); /* Finaliza MPI */
}
