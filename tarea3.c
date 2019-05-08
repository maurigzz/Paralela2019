#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <mpi.h>

int numeros_random(){
    srand(time(NULL));
    int r = rand()%100;
    return r;
}

int crear_sub_vector(int inicio, int fin, int* origen){
    int* sub_vector;
    int tamano;
    int auxiliar=0;
    tamano = fin - inicio;
    sub_vector = (int*)malloc(size * sizeof(int));

}

float promedio(){
    float promedio;
    return promedio;
}

int main(int argc, char** argv){

    MPI_Init(NUL,NUL); /* Inicia MPI */

    int mi_rango; /* Rango del proceso    */
    int numero_procesos; /* Numero de procesos   */
    int fuente; /* Rango del que envia  */
    int destino; /* Rango del que recibe */
    int tag = 0; /* Etiqueta del mensaje */
    int tamano_arreglo = 100000; /* Tamaño arreglo inicial */
    int arreglo_original(tamano_arreglo); /* Inicia arreglo */
    int n_over_p;

    llenar_arreglo(arreglo_original);

    n_over_p = tamano_arreglo/mi_rango;


    MPI_Status estado; /* Entrega el estado al recibir */
    MPI_Comm_size(MPI_COMM_WORLD, &mi_rango); /* Aveiguamos el rango de nuestro proceso */
    MPI_Comm_rank(MPI_COMM_WORLD, &numero_procesos); /* Averiguamos el número de procesos */

    if (mi_rango != 0){

    }

    else{ /* mi_rango == 0 , Distribuir datos en n arreglos */
        for (int i = 1 ; i < mi_rango ; i++){
            
        }
    }
}
