//Factura con IVA
#include <stdio.h>

int main(void){
    //Constante para el IVA
    const double TASA_IVA = 0.13;

    //Variable sentras para cantidad y reales para montos
    int cantidad;
    double precio, subtotal, iva, total;

    //ENTRADA: pedir y almacenar cantidad. Lee entero = 3
    printf("Cantidad: ");
    scanf("%d", &cantidad);

    //leer u double precio = 5000
    printf("Precio unitario: ");
    scanf("%lf", &precio);

    //PROCESO: int * double da double -> subtotal = 15000
    subtotal = cantidad * precio;
    //sacamos IVA con la constante -> iva = 1950
    iva = subtotal * TASA_IVA;
    // Toal -> 16950
    total = subtotal + iva;

    //SALIDAS: Usar 2 decimales, 10 espacios
    printf("Subtotal: %10.2f\n", subtotal);
    printf("IVA (13%%): %10.2f\n", iva);
    printf("Total:      %10.2f\n", total);
    return 0;

}