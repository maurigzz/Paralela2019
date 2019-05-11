#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <mpi.h>

using namespace std;

void llenar_arreglo(int arreglo[], int tamano){

    srand(time(NULL));
    for (int i=0; i<tamano; i++){
        arreglo[i]=rand()%100;
    }
}

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

int main(int argc, char** argv)
{
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

    MPI_Status estado; /* Devuelve estado al recibir*/

    MPI_Comm_size(MPI_COMM_WORLD, &tamano_procesadores);
    MPI_Comm_rank(MPI_COMM_WORLD, &mi_rango);

    cantidad_sub_arreglos = tamano/tamano_procesadores;

    for (int i=0; i<tamano; i++){
        cout << i << " = " << arreglo[i] << endl;
    }

    if (mi_rango != 0){
        sub_arreglo = (int*)malloc(cantidad_sub_arreglos * sizeof(int));

        fuente = 0;

        /* MPI_Recv(dato_a_recibir, contador, tipo_de_dato, fuente, tag, comunicador, status) */
        MPI_Recv(sub_arreglo, cantidad_sub_arreglos, MPI_INT, fuente,tag, MPI_COMM_WORLD, &estado);
    }

    else{
        /* Ciclo for para distribuir los datos en distintos arreglos y paralelizarlos */
        printf("Distribuiendo Datos \n");
        for (int destino = 1; destino < tamano_procesadores; destino++){

            sub_arreglo = crear_arreglos(destino*cantidad_sub_arreglos, (destino*cantidad_sub_arreglos)+cantidad_sub_arreglos, arreglo);

            /* MPI_Send(&dato_a_enviar, contador(0/1), tipo_de_dato, destino, tag(0/1), comunicador) */
            MPI_Send(sub_arreglo, cantidad_sub_arreglos, MPI_INT, destino, tag, MPI_COMM_WORLD);
            printf("... \n");
        }
        printf("Datos Distribuidos \n");

        sub_arreglo = crear_arreglos(0, cantidad_sub_arreglos, arreglo);
    }



    /* Finaliza MPI */
    MPI_Finalize();

    return 0;
}
