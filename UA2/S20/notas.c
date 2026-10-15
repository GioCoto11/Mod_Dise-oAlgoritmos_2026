/*notas.c - PromedioN (sesion 7) con arreglo: ahora las notas se GUARDAN.
QUE SE LOGRA: leer las notas del grupo (validadas), guardarlas en unarreglo y usarlas despues: promedio, mayor, menor y la lista de notas que superan el promedio (eso era imposible sin guardarlas). RESULTADO ESPERADO: con 80, 75, 90, 65 y 100 -> Promedio: 82.00, Mayor: 100.0, Menor: 65.0 y Sobre el promedio: 90.0 100.0.*/

#include <stdio.h>
#include <stdlib.h>
#define N 5

int main(void){
    double notas[N];  // definicion del arreglo
    double suma = 0, promedio, mayor, menor;
    int i;

    //LECTURA DEDATOS
    for (i = 0; i < N; i++){
        //validacion
        do {
            printf("Nota %d (0 a 100): ", i + 1);
            scanf("%lf", &notas[i]); //guarda en notas[i]
        }while (notas[i] < 0 || notas[i] > 100);
        suma += notas[i];
    }
    promedio = suma / N;

    //MAYOR Y MENOR. Se comienza desde la primera nota y se compara con el resto
    mayor = notas[0];
    menor = notas[0];

    for (i = 1; i < N; i++){
        if (notas[i] > mayor){
            mayor = notas[i];
        }

        if (notas[i] < menor){
            menor = notas[i];
        }
    }
    printf("Promedio: %.2f\n", promedio);
    printf("Mayor: %.lf Menor: %.lf\n", mayor, menor);

    //Segundo recorrido
    printf("Sobre el promedio:");
    for (i = 0; i < N; i++){
        if (notas[i] > promedio){
            printf(" %.lf", notas[i]);
        }
    }
    printf("\n");

    system("pause");
    return 0;

}
