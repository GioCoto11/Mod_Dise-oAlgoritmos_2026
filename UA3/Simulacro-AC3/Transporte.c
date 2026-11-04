/*Un colegio controla los pases de bus de sus estudiantes y puede registrar hasta 5 pases. De cada pase se guarda: el código (100 a 999, no se repite), el nombre del estudiante (una sola palabra, hasta 19 letras), los viajes disponibles y si el pase está activo o dado de baja. El programa inicia con 3 pases ya cargados (tabla de abajo). Debe mostrar un menú que se repite hasta elegir 0; toda opción o dato fuera de rango se vuelve a pedir.*/

//>>> ============================== REVISION ==============================
//>>> Los comentarios que empiezan con //>>> marcan los errores encontrados:
//>>>   QUE se observaba, POR QUE pasaba y la CORRECCION aplicada.
//>>>   ERROR 1 (linea de la definicion de buscarCodigo): el nombre estaba
//>>>           escrito "bucarCodigo" (sin la s). Error del ENLAZADOR (ld):
//>>>           "referencia a 'buscarCodigo' sin definir". No genera el .exe.
//>>>   ERROR 2 (case 1, Incluir): la llave del if "no hay espacio" se
//>>>           cerraba despues de leer el codigo; esas lineas quedaban
//>>>           DESPUES del break y nunca se ejecutaban. Error LOGICO: nunca
//>>>           pedia el codigo, no revisaba repetidos y el pase se guardaba
//>>>           con un codigo basura. Ademas faltaba el aviso de repetido.
//>>>   Observacion 1: "esxiste" mal escrito en el aviso de codigo.
//>>>   Observacion 2: el encabezado "Viajes disponibles" no cabe en %6s y
//>>>           la tabla sale desalineada.
//>>> Prueba despues de corregir: el caso de prueba completo da los 8
//>>>   resultados esperados del enunciado.
//>>> ======================================================================

/*Pases cargados al iniciar:
Código	Nombre	Viajes
201	    Ana	    5
202	    Luis	1
203	    Sofia	8
*/  

//Cargar las bibliotecas
#include <stdio.h>
#include <string.h>

//Definir las constantes
#define MAX_PASES 5       //espacios para los pases disponibles
#define TAM_NOMBRE 20     //19 caracteres o letras + el \0
#define COD_MIN 100       //codigo minimo
#define COD_MAX 999
#define VIAJES_MAX 40      //viajes maximos a incluir

//Prototipos (una funcion por tarea)
int leerEntero(const char mensaje[], int minimo, int maximo);
int buscarCodigo(const int cod[], const int activo[], int n, int codigo);
void incluir(int cod[], char nom[][TAM_NOMBRE], int viajes[], int activo[], int *n, int codigo, const char nombre[], int cantidad);
void consultar(const int cod[], const char nom[][TAM_NOMBRE], const int viajes[], const int activo[], int n);
int usarViaje(int *viajes);
void darDeBaja(int *activo);

//funcion principal
int main(void) {
    //Asigane datos de los pases
    int cod[MAX_PASES] = {201, 202, 203};
    char nom[MAX_PASES][TAM_NOMBRE] = {"Ana", "Luis", "Sofia"};
    int viajes[MAX_PASES] = {5, 1, 8};
    int activo[MAX_PASES] = {1, 1, 1};
    int n = 3; //espacios usados 
    int opcion, codigo, pos, cantidad;
    char nombre[TAM_NOMBRE];

    //Ciclo para menú
    do {
        //mostrar el menu
        printf("\n=== Pases de bus ===\n");
        printf("1. Incluir 2. Consultar 3. Registrar viaje 4. Dar de baja\n");
        printf("5. Buscar 0. Salir\n");

        //Leer la opcion
        opcion = leerEntero("Opcion", 0, 5); // no aceptar opciones inexistentes
        if (opcion >= 3) {
            codigo = leerEntero("Codigo", COD_MIN, COD_MAX);
            pos = buscarCodigo(cod, activo, n, codigo); // busca el pase activo
            //revisa si existe
            if (pos == -1) {
                //aviso
                //>>> Observacion 1: decia "No esxiste" (error de escritura).
                printf("No existe un pase activo con el codigo %d\n", codigo);
                //para continuar
                continue;
            }
        }
        switch (opcion) {
            case 1:
            if (n == MAX_PASES) {
                printf("No hay espacio para mas pases\n");
                break;//sale para volver a lmenu
            }   // AQUI se cierra el if (antes estaba despues del repetido)

            //lee codigo com oentero
            codigo = leerEntero("Codigo", COD_MIN, COD_MAX);
            //revisar si el codigo existe
            if (buscarCodigo(cod, activo, n, codigo) != -1) {
                //>>> faltaba el aviso: sin el, el usuario no sabe por que no
                //>>>   se incluyo el pase.
                printf("El codigo %d ya existe\n", codigo);
                break;  //sale para no incluir al repetido
            }
        //pide nombre
        printf("Nombre (una palabra): ");
        //leer nombre
        scanf("%19s", nombre);
        //leer los viajes
        cantidad = leerEntero("Viajes", 1, VIAJES_MAX); // DE 1 A 40 MAX
        //guardar el pase qu viene por direccion
        incluir(cod, nom, viajes, activo, &n, codigo, nombre, cantidad);
        //conformar pase incluido
        printf("Pase incluido (%d de %d)\n", n, MAX_PASES);
        break;

        case 2: 
            consultar(cod, nom, viajes, activo, n);
            break;
        case 3:
        //inetnta regstrar viaje
        if (usarViaje(&viajes[pos]))
        printf("Viaje registrado. A %s le quedan %d\n", nom[pos], viajes[pos]);
        //no quedan vieajes
        else 
            printf("%s no tiene viajes disponibles\n", nom[pos]);
        break;

        case 4: 
            darDeBaja(&activo[pos]);
            printf("Pase de %s dado de baja\n", nom[pos]);
            break;

        case 5: 
            //buscar un pase
            printf("%d %s: %d viajes\n", cod[pos], nom[pos], viajes[pos]);
            break;

        default:
            printf("Hasta luego\n");
        }

    } while (opcion !=0);
    return 0; 
    
 }

 //lectura valida de un entero
 int leerEntero(const char mensaje[], int minimo, int maximo) {
    //dato leido
    int valor;
    //ciclo validacion para qu pida el dato al menos una vez
    do {
        printf("%s (%d a %d): ", mensaje, minimo, maximo);
        //leer

        scanf("%d", &valor);
    } while (valor < minimo || valor > maximo);
    return valor;
 }

 //Busqueda secuencial de un pase

 int buscarCodigo(const int cod[], const int activo[], int n, int codigo){
    int i;
    for (i = 0; i < n; i++)
    //ignora pase dados de baja
    if (cod[i] == codigo && activo[i] == 1)
    return i;
    //no esta activo
    return -1;
 }

 //Agregar espacio en el primer espacio libre
 void incluir(int cod[], char nom[][TAM_NOMBRE], int viajes[], int activo[], int *n, int codigo, const char nombre[], int cantidad){
    //guardar el codigo
    cod[*n] = codigo;
    //guardar el nombre
    strcpy(nom[*n], nombre);
    //guardar los viajes
    viajes[*n] = cantidad;
    //pase activo
    activo[*n] = 1;
    //proximo pase a posicion siguiente
    (*n)++;
 }
 //pases activos y cuantos son
 void consultar(const int cod[], const char nom[][TAM_NOMBRE],
    const int viajes[], const int activo[], int n){
        //indice del contador
    int i, activos = 0;

    //encabezado de la tabla
    //  no cabe y la tabla se desalinea. Se usa %18s aqui y en la fila.
    printf("%-6s %-12s %18s\n", "Codigo", "Nombre", "Viajes disponibles");
    //recorrer los espacios usados
    for (i = 0; i < n; i++){
        //solo activos
        if (activo[i] == 1){
            printf("%-6d %-12s %18d\n", cod[i], nom [i], viajes[i]);
            //cuenta pases
            activos++;
        }
    }
    //mostrar total
    printf("Pases activos: %d\n", activos);
    }
    //registar viajes si quedan
    int usarViaje(int *viajes){
        //revisa si quedan viajes
        if (*viajes == 0)
        //no registra
        return 0;
        //cambio en el arreglo
        (*viajes)--;
        return 1; //para confirmar desde main
    }

    //dar de baja
    void darDeBaja(int *activo){
        //se marca como inactivo
        *activo = 0;
    }







