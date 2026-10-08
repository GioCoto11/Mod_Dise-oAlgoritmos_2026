//circulo.c trabaja con la costante de PI
#include <stdio.h>
#define PI 3.14159265358979  //Constante simbolica: el procesodor cambia PI por el nuemero
int main(void){
    //Constante de cadena: no puede cambiar durante el programa
    const char UNIDAD[] = "cm";
    //Variables reales para el radio y loas resultados
    double radio, area, perimetro;

    //ENTRADA: lee el radio -> radio = 4
    printf("Radio del circulo (cm): ");
    scanf("%lf", &radio);

    //PROCESO: En C no existe ^; radio al cuadrado = radio * radio -> 50.27
    area = PI * radio * radio;
    
    //Perimetro = 2 * PI * radio -> 23.13
    perimetro = 2 * PI * radio;

    //SALIDA: %.2f muestra 2 decimales y %s muestra la cadana UNIDAD
    printf("Area: %.2f %s2\n", area, UNIDAD);
    printf("Perimetro: %.2f %s\n", perimetro, UNIDAD);
    return 0;
}

