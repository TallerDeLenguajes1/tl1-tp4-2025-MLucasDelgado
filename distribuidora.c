#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int TareaID; // Numérico autoincremental comenzando en 1000
    char *Descripcion;
    int Duracion; // entre 10 – 100
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
void mostrarTareas(Nodo **start, Nodo **realizadas);
void mostrarNodo(Nodo *Nodo);
void consultarTareas(Nodo **start, Nodo **realizadas);

int main()
{
    Nodo *Start = crearListaVacia(); // lista de tarea pendientes;
    Nodo *realizadas = crearListaVacia();

    cargarTareas(&Start);
    transferirTareas(&Start, &realizadas);
    mostrarTareas(&Start, &realizadas);
    consultarTareas(&Start, &realizadas);

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

    do {
        printf("Por favor ingrese la duracion (10-100): ");
        scanf("%d", &Nodo->T.Duracion);

        if (Nodo->T.Duracion < 10 || Nodo->T.Duracion > 100) {
            printf("\n Duracion invalida. Debe estar entre 10 y 100.\n");
        }

    } while (Nodo->T.Duracion < 10 || Nodo->T.Duracion > 100);
}

void cargarTareas(Nodo **Start)
{
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

void transferirTareas(Nodo **start, Nodo **realizadas)
{
    Nodo *actual = *start;
    Nodo *anterior = NULL;

    while (actual != NULL)
    {
        printf("\n--------------------------\n");
        printf("ID: %d\n", actual->T.TareaID);
        printf("Descripcion: %s\n", actual->T.Descripcion);
        printf("Duracion: %d\n", actual->T.Duracion);

        char respuesta;
        printf("Marcar esta tarea como realizada? (s/n): ");
        scanf(" %c", &respuesta);

        if (respuesta == 's')
        {
            Nodo *tareaRealizada = actual;

            actual = actual->Siguiente;

            // Eliminar de la lista de pendientes
            if (anterior == NULL)
            { // // Caso unicamaente para eliminar el primer nodo
                *start = actual;
            }
            else
            {
                anterior->Siguiente = actual;
            }

            // Insertar en la lista de realizadas
            tareaRealizada->Siguiente = NULL;
            insertarNodo(realizadas, tareaRealizada);
        }
        else
        {
            anterior = actual;
            actual = actual->Siguiente;
        }
    }
}

void mostrarTareas(Nodo **start, Nodo **realizadas)
{
    Nodo *pendientes = *start;
    Nodo *terminadas = *realizadas;

    printf("\n------------Tareas Pendientes------------\n");
    while (pendientes)
    {
        mostrarNodo(pendientes);
        pendientes = pendientes->Siguiente;
    }

    // Mostrar tareas realizadas
    printf("\n------------Tareas Realizadas------------\n");
    while (terminadas)
    {
        mostrarNodo(terminadas);
        terminadas = terminadas->Siguiente;
    }
}

void mostrarNodo(Nodo *Nodo)
{
    if (Nodo != NULL)
    {
        printf("\nID: %d\n", Nodo->T.TareaID);
        printf("Descripcion: %s", Nodo->T.Descripcion);
        printf("Duracion: %d\n", Nodo->T.Duracion);
    }
}

void consultarTareas(Nodo **start, Nodo **realizadas)
{
    char continuar = 's';

    while (continuar == 's') {
        int tipoBusqueda;
        int idBuscado;
        int encontrada = 0;
    
        printf("\n--------TIPOS DE BUSQUEDA-------- \n");
        printf(" 1 - Busqueda por ID\n");
        printf(" 2 - Busqueda por palabra clave\n");
        printf("Elija su tipo: ");
        scanf("%d", &tipoBusqueda);
    
        Nodo *pendientes = *start;
        Nodo *terminadas = *realizadas;
    
        if (tipoBusqueda == 1) {
            printf("Ingrese el ID de la tarea: ");
            scanf("%d", &idBuscado);
    
            while (pendientes && pendientes->T.TareaID != idBuscado) {
                pendientes = pendientes->Siguiente;
            }
    
            if (pendientes != NULL) {
                printf("\n----------------------------\n");
                printf("\n Tarea PENDIENTE con ese ID: \n");
                mostrarNodo(pendientes);
                encontrada = 1;
            }
    
            while (terminadas && terminadas->T.TareaID != idBuscado) {
                terminadas = terminadas->Siguiente;
            }
    
            if (terminadas != NULL) {
                printf("\n----------------------------\n");
                printf("\n Tarea REALIZADA encontrada: \n");
                mostrarNodo(terminadas);
                encontrada = 1;
            }
    
            if (!encontrada) {
                printf("No se encontro ninguna tarea con ese ID.\n");
            }
    
        } else if (tipoBusqueda == 2) {
            char palabraClave[100];
            printf("Ingrese la palabra clave: ");
            getchar(); // limpiar buffer
            fgets(palabraClave, 100, stdin);
            palabraClave[strcspn(palabraClave, "\n")] = '\0';
    
            while (pendientes != NULL) {
                if (strstr(pendientes->T.Descripcion, palabraClave)) {
                    printf("\n----------------------------\n");
                    printf("\n Tarea PENDIENTE encontrada:\n");
                    mostrarNodo(pendientes);
                    encontrada = 1;
                }
                pendientes = pendientes->Siguiente;
            }
    
            while (terminadas != NULL) {
                if (strstr(terminadas->T.Descripcion, palabraClave)) {
                    printf("\n----------------------------\n");
                    printf("\n Tarea REALIZADA encontrada:\n");
                    mostrarNodo(terminadas);
                    encontrada = 1;
                }
                terminadas = terminadas->Siguiente;
            }
    
            if (!encontrada) {
                printf("No se encontraron tareas con esa palabra clave.\n");
            }
    
        } else {
            printf("Opcion invalida.\n");
        }
    
        printf("Desea seguir buscando tareas? (s/n): ");
        scanf(" %c", &continuar);
    }
}
