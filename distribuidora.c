#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int TareaID;       // Numérico autoincremental comenzando en 1000
    char *Descripcion; 
    int Duracion;      // entre 10 – 100
} Tarea;

typedef struct Nodo
{
    Tarea T;
    struct Nodo *Siguiente;
} Nodo;

Nodo *crearListaVacia();
Nodo *crearNodo();
void insertarNodo(Nodo **start, Nodo *Nodo);
void pedirDatos(Nodo *Nodo, int idTarea);
void cargarTareas(Nodo **start);
void transferirTareas(Nodo **start, Nodo **realizadas);
void mostrarTareas (Nodo **start, Nodo **realizadas);
void mostrarNodo (Nodo *Nodo);

int main()
{
    Nodo *Start = crearListaVacia(); // lista de tarea pendientes;
    Nodo *realizadas = crearListaVacia();

    cargarTareas(&Start);
    transferirTareas(&Start, &realizadas);
    mostrarTareas(&Start, &realizadas);

    return 0;
}

Nodo *crearListaVacia()
{
    return NULL;
}

Nodo *crearNodo()
{
    Nodo *NodoCreado = (Nodo *)malloc(sizeof(Nodo));
    NodoCreado->Siguiente = NULL;
    return NodoCreado;
}

void insertarNodo(Nodo **start, Nodo *Nodo)
{
    Nodo->Siguiente = *start;
    *start = Nodo;
}

void pedirDatos(Nodo *Nodo, int idTarea)
{
    Nodo->T.TareaID = idTarea;
    printf("ID de la tarea: %d \n", Nodo->T.TareaID);

    Nodo->T.Descripcion = (char *)malloc(100 * sizeof(char));

    printf("Por favor ingrese la descripcion de la tarea: ");
    fflush(stdin); // Limpia el buffer 
    fgets(Nodo->T.Descripcion, 100, stdin);
    // scanf(" %[^\n]", Nodo->T.Descripcion); otra forma en vez de usar el fgets

    printf("Por favor ingrese la duracion '(10-100)': ");
    scanf("%d", &Nodo->T.Duracion);
}

void cargarTareas(Nodo **Start) {
    char continuar = 's';
    int idTarea = 1000;

    while (continuar == 's')
    {
        Nodo *tareaCreada = crearNodo();
        pedirDatos(tareaCreada, idTarea);
        insertarNodo(Start, tareaCreada);

        idTarea++;
        printf("Desea continuar? (s/n): ");
        scanf(" %c", &continuar);
    }
}

void transferirTareas(Nodo **start, Nodo **realizadas) {
    Nodo *actual = *start;
    Nodo *anterior = NULL;

    while (actual != NULL) {
        printf("\n--------------------------\n");
        printf("ID: %d\n", actual->T.TareaID);
        printf("Descripcion: %s\n", actual->T.Descripcion);
        printf("Duracion: %d\n", actual->T.Duracion);

        char respuesta;
        printf("Marcar esta tarea como realizada? (s/n): ");
        scanf(" %c", &respuesta);

        if (respuesta == 's') {
            Nodo *tareaRealizada = actual;

            actual = actual->Siguiente;

            // Eliminar de la lista de pendientes
            if (anterior == NULL) { // // Caso unicamaente para eliminar el primer nodo  
                *start = actual;
            } else {
                anterior->Siguiente = actual;
            }

            // Insertar en la lista de realizadas
            tareaRealizada->Siguiente = NULL;
            insertarNodo(realizadas, tareaRealizada);

        } else {
            anterior = actual;
            actual = actual->Siguiente;
        }
    }
}

void mostrarTareas (Nodo **start, Nodo **realizadas) {
    Nodo *pendientes = *start;
    Nodo *terminadas = *realizadas;

    printf("\n------------Tareas Pendientes------------\n");
    while (pendientes) {
        mostrarNodo(pendientes);
        pendientes = pendientes->Siguiente;
    }

    // Mostrar tareas realizadas
    printf("\n------------Tareas Realizadas------------\n");
    while (terminadas) {
        mostrarNodo(terminadas);
        terminadas = terminadas->Siguiente;
    } 
}

void mostrarNodo (Nodo *Nodo) {
    if (Nodo != NULL)
    {
        printf("\nID: %d\n", Nodo->T.TareaID);
        printf("Descripcion: %s", Nodo->T.Descripcion);
        printf("Duracion: %d\n", Nodo->T.Duracion);
    }
    
}
