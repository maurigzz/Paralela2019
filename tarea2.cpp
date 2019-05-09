#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <math.h>

using namespace std;

void llenar_arreglo(int arreglo[100000]){
    srand(time(NULL));
    for (int i=0; i<100000; i++){
        arreglo[i]=rand()%100;
    }
}

float promedio(int arreglo[100000]){
    float suma = 0.0;
    for (int i=0; i<100000; i++){
        suma += arreglo[i];
    }
    return suma/100000.0;
}

float varianza(int arreglo[100000]){
    float prom = promedio(arreglo);
    float varianza = 0.0;
    for (int i=0; i<100000; i++){
        varianza += pow(arreglo[i] - prom, 2.0);
    }
    return varianza/=100000;
}

float desv_estandar(int arreglo[100000]){
    return sqrt(varianza(arreglo));
}

int main()
{
    int arreglo[100000];
    llenar_arreglo(arreglo);
    cout << "El Promedio es " << promedio(arreglo) << endl;
    cout << "La Varianza es " << varianza(arreglo) << endl;
    cout << "La Desviacion Estandar es " << desv_estandar(arreglo) << endl;
    return 0;
}
