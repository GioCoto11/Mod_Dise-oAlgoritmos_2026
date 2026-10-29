// cine.c - Venta de entradas de un cine (forma elegida: funciones,
//   switch, arreglos y punteros)
// ENUNCIADO: un cine registra las compras de una funcion (de 1 a 10). De
//   cada compra se digita el nombre del cliente (una palabra), el tipo de
//   entrada (1 General 3500, 2 Nino 2500, 3 Adulto mayor 2000) y la
//   cantidad de entradas (de 1 a 8); un dato invalido se vuelve a pedir.
//   Si la compra tiene 5 o mas entradas se aplica un 10 % de descuento.
//   Mostrar una tabla con el cliente, las entradas y el total de cada
//   compra, el total vendido, la compra mayor y cuantas compras tuvieron
//   descuento.
// QUE SE LOGRA: resolver el problema con el metodo de 8 pasos, usando la
//   forma elegida en el paso 6.
// COMO SE LOGRA: leerEntero valida cualquier dato entero (se usa tres
//   veces); precioEntrada elige el precio con switch; calcularTotal aplica
//   el descuento; resumir recorre los arreglos UNA vez y devuelve tres
//   resultados por direccion (punteros); main solo organiza el trabajo.
// RESULTADO ESPERADO: Ana 1 2, Luis 2 5, Sofia 3 1, Mario 1 6 -> totales
//   7000, 11250, 2000 y 18900; total vendido 39150.00; compra mayor Mario
//   (18900.00); 2 compras con descuento.
// COMO LEER LOS COMENTARIOS: antes de cada linea se explica QUE hace,
//   COMO lo hace y PARA QUE se usa.

// QUE: biblioteca de entrada y salida. COMO: #include.
// PARA QUE: poder usar printf y scanf.
#include <stdio.h>

// QUE: constantes del enunciado (paso 2: datos que no cambian).
// COMO: #define cambia cada nombre por su valor antes de compilar.
// PARA QUE: si cambia un precio o una regla, se toca un solo lugar.
#define MAX_COMPRAS 10         // maximo de compras de la funcion
#define PRECIO_GENERAL 3500.0  // tipo 1
#define PRECIO_NINO 2500.0     // tipo 2
#define PRECIO_MAYOR 2000.0    // tipo 3
#define MIN_DESCUENTO 5        // entradas necesarias para el descuento
#define TASA_DESCUENTO 0.10    // 10 % de descuento

// QUE: prototipos: una funcion por tarea del paso 4.
// COMO: tipo de retorno, nombre y parametros, terminados en ;.
// PARA QUE: main puede llamarlas antes de sus definiciones.
int leerEntero(const char mensaje[], int minimo, int maximo);
double precioEntrada(int tipo);
double calcularTotal(int tipo, int cantidad);
void resumir(const int cant[], const double tot[], int n,
             double *total, int *posMayor, int *conDescuento);

// QUE: funcion principal. COMO: int main(void).
// PARA QUE: organizar el trabajo: leer, calcular, resumir y mostrar.
int main(void) {
    // QUE: nombres de los clientes.
    // COMO: arreglo de cadenas: 10 filas de 15 char (14 letras + '\0').
    // PARA QUE: clientes[i] es el cliente de la compra i.
    char clientes[MAX_COMPRAS][15];
    // QUE: entradas de cada compra. COMO: arreglo paralelo de int.
    // PARA QUE: cantidades[i] corresponde a clientes[i].
    int cantidades[MAX_COMPRAS];
    // QUE: total de cada compra. COMO: arreglo paralelo de double.
    // PARA QUE: tabla final y resumen.
    double totales[MAX_COMPRAS];
    // QUE: cantidad de compras, indice y tipo de entrada.
    // COMO: int. PARA QUE: recorrer y calcular.
    int n, i, tipo;
    // QUE: resultados del resumen.
    // COMO: variables de main que resumir llena por direccion.
    // PARA QUE: mostrar el total, la compra mayor y los descuentos.
    double totalVendido;
    int posMayor, conDescuento;

    // QUE: titulo y lista de tipos. COMO: printf.
    // PARA QUE: el usuario ve los precios una sola vez.
    printf("=== Venta de entradas ===\n");
    printf("Tipos: 1 General 3500, 2 Nino 2500, 3 Adulto mayor 2000\n");
    // QUE: lee la cantidad de compras -> 4.
    // COMO: envia el mensaje y el rango; el valor devuelto se guarda.
    // PARA QUE: limite del ciclo, sin salirse de los arreglos.
    n = leerEntero("Cantidad de compras", 1, MAX_COMPRAS);

    // QUE: una vuelta por compra. COMO: for de 0 a n - 1.
    // PARA QUE: leer y calcular cada compra.
    for (i = 0; i < n; i++) {
        // QUE: numero de compra y pedido del cliente. COMO: printf.
        // PARA QUE: guiar al usuario.
        printf("Compra %d\n  Cliente: ", i + 1);
        // QUE: lee una palabra -> Ana. COMO: %14s, sin & (es arreglo).
        // PARA QUE: guardar el nombre sin desbordar la fila.
        scanf("%14s", clientes[i]);
        // QUE: lee el tipo de entrada -> 1.
        // COMO: la MISMA funcion de lectura con otro mensaje y rango.
        // PARA QUE: validar sin repetir el do-while.
        tipo = leerEntero("  Tipo", 1, 3);
        // QUE: lee la cantidad de entradas -> 2. COMO: rango 1 a 8.
        // PARA QUE: dato del calculo.
        cantidades[i] = leerEntero("  Entradas", 1, 8);
        // QUE: calcula el total de la compra -> 7000.
        // COMO: envia tipo y cantidad; la funcion aplica precio y
        //   descuento y devuelve el total.
        // PARA QUE: la regla de precios vive en un solo lugar.
        totales[i] = calcularTotal(tipo, cantidades[i]);
    }

    // QUE: calcula el resumen en UNA pasada.
    // COMO: los arreglos se pasan por su nombre; &totalVendido,
    //   &posMayor y &conDescuento envian DIRECCIONES para que la funcion
    //   escriba los tres resultados en las variables de main.
    // PARA QUE: una funcion solo devuelve un valor con return; con
    //   punteros devuelve los tres.
    resumir(cantidades, totales, n, &totalVendido, &posMayor,
            &conDescuento);

    // QUE: encabezado de la tabla. COMO: anchos fijos (%-12s, %9s).
    // PARA QUE: columnas alineadas.
    printf("\n%-12s%9s%12s\n", "Cliente", "Entradas", "Total");
    // QUE: recorre las compras. COMO: for.
    // PARA QUE: una fila por compra.
    for (i = 0; i < n; i++)
        // QUE: muestra la fila. COMO: misma posicion i en los arreglos.
        // PARA QUE: detalle de la funcion.
        printf("%-12s%9d%12.2f\n", clientes[i], cantidades[i], totales[i]);
    // QUE: total vendido -> 39150.00. COMO: %.2f.
    // PARA QUE: resultado principal.
    printf("Total vendido:   %12.2f\n", totalVendido);
    // QUE: compra mayor -> Mario (18900.00).
    // COMO: con la posicion se toman el cliente y el total.
    // PARA QUE: dato del reporte.
    printf("Compra mayor:    %s (%.2f)\n", clientes[posMayor],
           totales[posMayor]);
    // QUE: compras con descuento -> 2. COMO: %d.
    // PARA QUE: dato del reporte.
    printf("Con descuento:   %d compra(s)\n", conDescuento);
    // QUE: termina main. COMO: return 0.
    // PARA QUE: cerrar el programa de forma correcta.
    return 0;
}

// QUE: definicion de leerEntero.
// COMO: mensaje recibe el texto a mostrar; minimo y maximo, el rango.
// PARA QUE: una sola validacion para todos los datos enteros.
int leerEntero(const char mensaje[], int minimo, int maximo) {
    // QUE: variable LOCAL para el dato. COMO: int.
    // PARA QUE: guardarlo mientras se valida.
    int valor;
    // QUE: ciclo de validacion. COMO: do-while.
    // PARA QUE: pedir al menos una vez y repetir si es invalido.
    do {
        // QUE: muestra el pedido -> "  Entradas (1 a 8): ".
        // COMO: %s con el mensaje y %d con los limites.
        // PARA QUE: el pedido se repite completo si el dato es invalido.
        printf("%s (%d a %d): ", mensaje, minimo, maximo);
        // QUE: lee el dato. COMO: %d y &valor.
        // PARA QUE: dato a validar.
        scanf("%d", &valor);
    // QUE: repite si esta fuera de rango. COMO: || compara el DATO.
    // PARA QUE: no devolver un valor invalido.
    } while (valor < minimo || valor > maximo);
    // QUE: devuelve el valor valido. COMO: return.
    // PARA QUE: quien llama lo guarda.
    return valor;
}

// QUE: definicion de precioEntrada.
// COMO: recibe el tipo (1 a 3) y elige el precio con switch.
// PARA QUE: la tabla de precios vive en un solo lugar.
double precioEntrada(int tipo) {
    // QUE: elige segun el tipo.
    // COMO: switch compara tipo con cada case (valores fijos).
    // PARA QUE: una rama clara por tipo de entrada.
    switch (tipo) {
        // QUE: tipo 1. COMO: return termina la funcion (no hace falta
        //   break). PARA QUE: precio general.
        case 1:
            return PRECIO_GENERAL;
        // QUE: tipo 2. COMO: return. PARA QUE: precio de nino.
        case 2:
            return PRECIO_NINO;
        // QUE: tipo 3, el unico que queda (leerEntero ya valido 1 a 3).
        // COMO: default con return.
        // PARA QUE: que todos los caminos devuelvan un valor.
        default:
            return PRECIO_MAYOR;
    }
}

// QUE: definicion de calcularTotal.
// COMO: recibe tipo y cantidad; usa precioEntrada y aplica el descuento.
// PARA QUE: devolver el total de una compra.
double calcularTotal(int tipo, int cantidad) {
    // QUE: subtotal -> 2500 * 5 = 12500.
    // COMO: una funcion llama a otra: precioEntrada(tipo).
    // PARA QUE: no repetir la tabla de precios.
    double total = precioEntrada(tipo) * cantidad;
    // QUE: revisa si corresponde descuento. COMO: >= 5.
    // PARA QUE: aplicar la regla del enunciado.
    if (cantidad >= MIN_DESCUENTO)
        // QUE: resta el 10 % -> 12500 * 0.90 = 11250.
        // COMO: total * (1 - TASA_DESCUENTO).
        // PARA QUE: total con descuento.
        total = total * (1 - TASA_DESCUENTO);
    // QUE: devuelve el total. COMO: return.
    // PARA QUE: main lo guarda en el arreglo.
    return total;
}

// QUE: definicion de resumir.
// COMO: recibe los arreglos (const: solo los lee) y tres PUNTEROS donde
//   escribe los resultados con *.
// PARA QUE: calcular total, posicion mayor y descuentos en una pasada.
void resumir(const int cant[], const double tot[], int n,
             double *total, int *posMayor, int *conDescuento) {
    // QUE: indice LOCAL. COMO: int. PARA QUE: recorrer.
    int i;
    // QUE: inicia los tres resultados en la memoria de main.
    // COMO: * delante del puntero escribe en la variable de main.
    // PARA QUE: acumulador y contador en 0; el mayor empieza en 0.
    *total = 0;
    *posMayor = 0;
    *conDescuento = 0;
    // QUE: recorre las compras UNA vez. COMO: for.
    // PARA QUE: actualizar los tres resultados en la misma vuelta.
    for (i = 0; i < n; i++) {
        // QUE: acumula -> 7000, 18250, 20250, 39150.
        // COMO: += sobre *total. PARA QUE: total vendido.
        *total += tot[i];
        // QUE: compara con la compra mayor guardada.
        // COMO: tot[*posMayor] usa la posicion guardada en main.
        // PARA QUE: encontrar la compra mayor.
        if (tot[i] > tot[*posMayor])
            // QUE: guarda la nueva posicion -> 3 (Mario).
            // COMO: *posMayor = i. PARA QUE: main la usa al mostrar.
            *posMayor = i;
        // QUE: revisa si la compra tuvo descuento. COMO: >= 5.
        // PARA QUE: contarla.
        if (cant[i] >= MIN_DESCUENTO)
            // QUE: suma 1 al contador de main -> 2.
            // COMO: (*conDescuento)++: los parentesis hacen que aumente
            //   el VALOR y no el puntero.
            // PARA QUE: cantidad de compras con descuento.
            (*conDescuento)++;
    }
}
