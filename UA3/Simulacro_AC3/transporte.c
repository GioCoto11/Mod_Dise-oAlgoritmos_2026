// transporte.c - Simulacro AC3 parte 2: pases de bus estudiantiles
// ENUNCIADO: un colegio controla los pases de bus de sus estudiantes y
//   registra hasta 5 pases. De cada pase se guarda el codigo (100 a 999,
//   no se repite), el nombre del estudiante (una palabra, hasta 19
//   letras), los viajes disponibles y si el pase esta activo o dado de baja. El programa
//   inicia con 3 pases ya cargados: 201 Ana (5 viajes), 202 Luis (1) y 203 Sofia (8).
//   Debe mostrar un menú que se repite hasta elegir 0; toda opción o dato fuera de rango se vuelve a pedir.
//   Menu: 1 Incluir pase, 2 Consultar pases, 3 Registrar un viaje, 4 Dar
//   de baja un pase, 5 Buscar por codigo y 0 Salir; todo dato fuera de
//   rango se vuelve a pedir. No se registra un viaje si no quedan viajes;
//   un pase dado de baja ya no aparece.

// QUE SE LOGRA: un sistema que incluye, consulta, modifica (registrar un
//   viaje), elimina (dar de baja) y busca registros guardados en arreglos
//   paralelos, con funciones y punteros.
// COMO SE LOGRA: la posicion i es el mismo pase en los cuatro arreglos;
//   buscarCodigo devuelve la posicion o -1; incluir aumenta la cantidad
//   con (*n)++; usarViaje y darDeBaja reciben la DIRECCION de un dato del
//   pase y lo cambian con *. La baja es logica: activo pasa de 1 a 0.
// RESULTADO ESPERADO (caso de prueba): incluir 202 -> ya existe; incluir
//   204 Mario 3 -> 4 de 5; viaje 202 -> quedan 0; otra vez -> sin viajes;
//   baja 201 -> hecha; buscar 201 -> no existe; buscar 203 -> Sofia 8;
//   consultar -> 202 (0), 203 (8) y 204 (3), 3 pases activos.
// COMO LEER LOS COMENTARIOS: antes de cada linea se explica QUE hace,
//   COMO lo hace y PARA QUE se usa.

// QUE: bibliotecas. COMO: #include.
// PARA QUE: printf/scanf (stdio.h) y strcpy (string.h).
#include <stdio.h>
#include <string.h>

// QUE: limites del enunciado. COMO: #define.
// PARA QUE: tamanos y rangos en un solo lugar.
#define MAX_PASES 5     // espacios para pases
#define TAM_NOMBRE 20   // 19 letras + el '\0'
#define COD_MIN 100     // codigo minimo
#define COD_MAX 999     // codigo maximo
#define VIAJES_MAX 40   // viajes maximos al incluir

// QUE: prototipos (una funcion por tarea). COMO: terminan en ;.
// PARA QUE: main puede llamarlas antes de sus definiciones.
int leerEntero(const char mensaje[], int minimo, int maximo);
int buscarCodigo(const int cod[], const int activo[], int n, int codigo);
void incluir(int cod[], char nom[][TAM_NOMBRE], int viajes[], int activo[],
             int *n, int codigo, const char nombre[], int cantidad);
void consultar(const int cod[], const char nom[][TAM_NOMBRE],
               const int viajes[], const int activo[], int n);
int usarViaje(int *viajes);
void darDeBaja(int *activo);

// QUE: funcion principal. COMO: int main(void).
// PARA QUE: mostrar el menu y atender cada opcion.
int main(void) {
    // QUE: datos de los pases. COMO: arreglos PARALELOS: la posicion i
    //   es el mismo pase en todos; los 3 primeros vienen cargados.
    // PARA QUE: probar el sistema sin digitar todo desde cero.
    int cod[MAX_PASES] = {201, 202, 203};
    char nom[MAX_PASES][TAM_NOMBRE] = {"Ana", "Luis", "Sofia"};
    int viajes[MAX_PASES] = {5, 1, 8};
    // QUE: estado de cada pase. COMO: 1 activo, 0 dado de baja.
    // PARA QUE: la baja no borra datos, solo cambia el estado.
    int activo[MAX_PASES] = {1, 1, 1};
    // QUE: espacios usados. COMO: int que inicia en 3.
    // PARA QUE: saber donde va el proximo pase y cuantos recorrer.
    int n = 3;
    // QUE: opcion, codigo, posicion y viajes del pase nuevo. COMO: int.
    // PARA QUE: controlar el menu y ubicar el pase.
    int opcion, codigo, pos, cantidad;
    // QUE: nombre digitado. COMO: cadena de 20.
    // PARA QUE: incluir un pase nuevo.
    char nombre[TAM_NOMBRE];

    // QUE: ciclo del menu. COMO: do-while.
    // PARA QUE: mostrarlo al menos una vez y repetir hasta 0.
    do {
        // QUE: muestra el menu. COMO: printf.
        // PARA QUE: el usuario ve las opciones.
        printf("\n=== Pases de bus ===\n");
        printf("1 Incluir  2 Consultar  3 Registrar viaje  4 Dar de baja\n");
        printf("5 Buscar  0 Salir\n");
        // QUE: lee la opcion. COMO: leerEntero de 0 a 5.
        // PARA QUE: no aceptar opciones inexistentes.
        opcion = leerEntero("Opcion", 0, 5);
        // QUE: viaje, baja y busqueda necesitan un pase. COMO: opcion >= 3.
        // PARA QUE: pedir y buscar el codigo una sola vez.
        if (opcion >= 3) {
            // QUE: lee el codigo -> 202. COMO: leerEntero de 100 a 999.
            // PARA QUE: saber sobre cual pase operar.
            codigo = leerEntero("Codigo", COD_MIN, COD_MAX);
            // QUE: busca el pase activo. COMO: buscarCodigo.
            // PARA QUE: -1 significa que no existe o esta de baja.
            pos = buscarCodigo(cod, activo, n, codigo);
            // QUE: revisa si no existe. COMO: == -1.
            // PARA QUE: avisar y volver al menu.
            if (pos == -1) {
                // QUE: aviso. COMO: printf con %d.
                // PARA QUE: el usuario sabe por que no se opero.
                printf("No existe un pase activo con el codigo %d\n",
                       codigo);
                // QUE: salta a la condicion del while. COMO: continue.
                // PARA QUE: no entrar al switch sin pase.
                continue;
            }
        }
        // QUE: atiende la opcion. COMO: switch (valores fijos 0 a 5).
        // PARA QUE: una rama por opcion del menu.
        switch (opcion) {
            // QUE: incluir un pase (INCLUSION de un registro).
            // COMO: revisa espacio y codigo, lee datos y llama a incluir.
            // PARA QUE: agregar un pase nuevo al final.
            case 1:
                // QUE: revisa si ya no hay espacio. COMO: n == MAX_PASES.
                // PARA QUE: no escribir fuera de los arreglos.
                if (n == MAX_PASES) {
                    // QUE: aviso. COMO: printf.
                    // PARA QUE: explicar por que no se incluye.
                    printf("No hay espacio para mas pases\n");
                    // QUE: sale del switch. COMO: break.
                    // PARA QUE: volver al menu.
                    break;
                }
                // QUE: lee el codigo -> 204. COMO: leerEntero.
                // PARA QUE: identificar el pase nuevo.
                codigo = leerEntero("Codigo", COD_MIN, COD_MAX);
                // QUE: revisa si el codigo ya existe -> 202.
                // COMO: buscarCodigo distinto de -1.
                // PARA QUE: no repetir codigos.
                if (buscarCodigo(cod, activo, n, codigo) != -1) {
                    // QUE: aviso. COMO: printf con %d.
                    // PARA QUE: el usuario sabe que debe usar otro.
                    printf("El codigo %d ya existe\n", codigo);
                    // QUE: sale del switch. COMO: break.
                    // PARA QUE: no incluir el repetido.
                    break;
                }
                // QUE: pide el nombre. COMO: printf. PARA QUE: guiar.
                printf("Nombre (una palabra): ");
                // QUE: lee el nombre -> "Mario".
                // COMO: %19s deja lugar al '\0'.
                // PARA QUE: no desbordar el arreglo nombre.
                scanf("%19s", nombre);
                // QUE: lee los viajes -> 3. COMO: leerEntero de 1 a 40.
                // PARA QUE: dato del pase ya validado.
                cantidad = leerEntero("Viajes", 1, VIAJES_MAX);
                // QUE: guarda el pase. COMO: &n envia la DIRECCION de la
                //   cantidad para que incluir la aumente.
                // PARA QUE: el contador de main queda actualizado.
                incluir(cod, nom, viajes, activo, &n, codigo, nombre,
                        cantidad);
                // QUE: confirma -> "Pase incluido (4 de 5)". COMO: %d.
                // PARA QUE: el usuario ve el espacio usado.
                printf("Pase incluido (%d de %d)\n", n, MAX_PASES);
                // QUE: sale del switch. COMO: break.
                // PARA QUE: no ejecutar el caso siguiente.
                break;
            // QUE: consultar los pases (CONSULTA de registros).
            // COMO: llama a consultar con los arreglos.
            // PARA QUE: ver la lista de pases activos.
            case 2:
                consultar(cod, nom, viajes, activo, n);
                // QUE: sale del switch. COMO: break.
                // PARA QUE: no ejecutar el viaje.
                break;
            // QUE: registrar un viaje (MODIFICACION del registro).
            // COMO: &viajes[pos] es la DIRECCION de los viajes del pase.
            // PARA QUE: la funcion los rebaja en el arreglo de main.
            case 3:
                // QUE: intenta registrar. COMO: if con el 1 o 0 devuelto.
                // PARA QUE: mostrar el mensaje que corresponde.
                if (usarViaje(&viajes[pos]))
                    // QUE: viaje registrado -> "quedan 0". COMO: %s y %d.
                    // PARA QUE: confirmar.
                    printf("Viaje registrado. A %s le quedan %d\n",
                           nom[pos], viajes[pos]);
                // QUE: no quedaban viajes. COMO: else.
                // PARA QUE: avisar al usuario.
                else
                    printf("%s no tiene viajes disponibles\n", nom[pos]);
                // QUE: sale del switch. COMO: break.
                // PARA QUE: no ejecutar la baja.
                break;
            // QUE: dar de baja un pase (ELIMINACION logica del registro).
            // COMO: envia la direccion de activo[pos].
            // PARA QUE: el pase deja de aparecer y de poder usarse.
            case 4:
                darDeBaja(&activo[pos]);
                // QUE: confirma. COMO: printf con %s.
                // PARA QUE: el usuario sabe que se hizo.
                printf("Pase de %s dado de baja\n", nom[pos]);
                // QUE: sale del switch. COMO: break.
                // PARA QUE: no ejecutar la busqueda.
                break;
            // QUE: buscar un pase (PANTALLA DE BUSQUEDA).
            // COMO: el pase ya se encontro antes del switch (pos).
            // PARA QUE: mostrar sus datos.
            case 5:
                // QUE: datos -> "203 Sofia: 8 viajes". COMO: %d y %s.
                // PARA QUE: resultado de la busqueda.
                printf("%d %s: %d viajes\n", cod[pos], nom[pos],
                       viajes[pos]);
                // QUE: sale del switch. COMO: break.
                // PARA QUE: no ejecutar el default.
                break;
            // QUE: salir. COMO: default (unica opcion restante: 0).
            // PARA QUE: despedirse; el while termina el ciclo.
            default:
                printf("Hasta luego\n");
        }
    // QUE: repite mientras no sea 0. COMO: != 0.
    // PARA QUE: volver a mostrar el menu.
    } while (opcion != 0);
    // QUE: termina main. COMO: return 0.
    // PARA QUE: cerrar el programa de forma correcta.
    return 0;
}

// QUE: lectura validada de un entero.
// COMO: do-while hasta que el dato este en el rango.
// PARA QUE: validar opcion, codigo y viajes.
int leerEntero(const char mensaje[], int minimo, int maximo) {
    // QUE: dato leido. COMO: int LOCAL. PARA QUE: validarlo.
    int valor;
    // QUE: ciclo de validacion. COMO: do-while.
    // PARA QUE: pedir el dato al menos una vez.
    do {
        // QUE: muestra el pedido -> "Codigo (100 a 999): ". COMO: %s, %d.
        // PARA QUE: el pedido se repite completo si es invalido.
        printf("%s (%d a %d): ", mensaje, minimo, maximo);
        // QUE: lee el dato. COMO: %d y &valor. PARA QUE: validarlo.
        scanf("%d", &valor);
    // QUE: repite si esta fuera de rango. COMO: ||.
    // PARA QUE: no devolver un valor invalido.
    } while (valor < minimo || valor > maximo);
    // QUE: devuelve el dato valido. COMO: return.
    // PARA QUE: quien llama lo guarda.
    return valor;
}

// QUE: busqueda secuencial de un pase ACTIVO por codigo.
// COMO: recorre los n espacios; compara codigo y estado.
// PARA QUE: devolver la posicion o -1 si no existe o esta de baja.
int buscarCodigo(const int cod[], const int activo[], int n, int codigo) {
    // QUE: indice. COMO: int LOCAL. PARA QUE: recorrer.
    int i;
    // QUE: recorre los espacios usados. COMO: for de 0 a n-1.
    // PARA QUE: revisar cada pase.
    for (i = 0; i < n; i++)
        // QUE: mismo codigo y activo. COMO: == y &&.
        // PARA QUE: ignorar los pases dados de baja.
        if (cod[i] == codigo && activo[i] == 1)
            // QUE: lo encontro. COMO: return i. PARA QUE: indicar donde.
            return i;
    // QUE: no esta. COMO: return -1 (posicion imposible).
    // PARA QUE: quien llama sabe que no existe.
    return -1;
}

// QUE: agrega un pase en el primer espacio libre.
// COMO: escribe en la posicion *n de cada arreglo y luego (*n)++.
// PARA QUE: la cantidad de main aumenta por medio del puntero.
void incluir(int cod[], char nom[][TAM_NOMBRE], int viajes[], int activo[],
             int *n, int codigo, const char nombre[], int cantidad) {
    // QUE: guarda el codigo. COMO: *n es la primera posicion libre.
    // PARA QUE: el pase queda despues del ultimo.
    cod[*n] = codigo;
    // QUE: guarda el nombre. COMO: strcpy (las cadenas no usan =).
    // PARA QUE: copiar el texto en la misma posicion.
    strcpy(nom[*n], nombre);
    // QUE: guarda los viajes. COMO: asignacion.
    // PARA QUE: viajes disponibles del pase nuevo.
    viajes[*n] = cantidad;
    // QUE: el pase nace activo. COMO: = 1.
    // PARA QUE: que aparezca en consultas y busquedas.
    activo[*n] = 1;
    // QUE: hay un espacio usado mas -> de 3 a 4. COMO: (*n)++.
    // PARA QUE: el proximo pase va en la posicion siguiente.
    (*n)++;
}

// QUE: lista los pases activos y cuantos son.
// COMO: recorre los arreglos y muestra solo los de estado 1.
// PARA QUE: consulta general de los pases.
void consultar(const int cod[], const char nom[][TAM_NOMBRE],
               const int viajes[], const int activo[], int n) {
    // QUE: indice y CONTADOR de activos. COMO: int LOCALES; el contador
    //   inicia en 0. PARA QUE: recorrer y contar.
    int i, activos = 0;
    // QUE: encabezado de la tabla. COMO: anchos fijos.
    // PARA QUE: columnas alineadas.
    printf("%-6s %-12s %6s\n", "Codigo", "Nombre", "Viajes");
    // QUE: recorre los espacios usados. COMO: for.
    // PARA QUE: revisar cada pase.
    for (i = 0; i < n; i++) {
        // QUE: solo los activos. COMO: activo[i] == 1.
        // PARA QUE: los dados de baja no aparecen.
        if (activo[i] == 1) {
            // QUE: una fila -> "202    Luis    0". COMO: anchos fijos.
            // PARA QUE: mostrar el pase.
            printf("%-6d %-12s %6d\n", cod[i], nom[i], viajes[i]);
            // QUE: cuenta el pase. COMO: ++. PARA QUE: total al final.
            activos++;
        }
    }
    // QUE: muestra el total -> 3. COMO: %d. PARA QUE: cerrar la consulta.
    printf("Pases activos: %d\n", activos);
}

// QUE: registra un viaje si quedan viajes.
// COMO: *viajes es el dato de main; si es 0 no hace nada.
// PARA QUE: devolver 1 si lo registro y 0 si no quedaban.
int usarViaje(int *viajes) {
    // QUE: revisa si no quedan. COMO: == 0.
    // PARA QUE: no dejar viajes negativos.
    if (*viajes == 0)
        // QUE: no se registro. COMO: return 0. PARA QUE: main avisa.
        return 0;
    // QUE: rebaja uno -> de 1 a 0. COMO: (*viajes)--.
    // PARA QUE: el cambio queda en el arreglo de main.
    (*viajes)--;
    // QUE: se registro. COMO: return 1. PARA QUE: main confirma.
    return 1;
}

// QUE: da de baja un pase (eliminacion logica).
// COMO: *activo = 0 escribe en el arreglo de main.
// PARA QUE: buscarCodigo y consultar lo ignoran desde ahora.
void darDeBaja(int *activo) {
    // QUE: marca el pase como inactivo. COMO: *activo = 0.
    // PARA QUE: eliminar el pase de consultas y busquedas.
    *activo = 0;
}

