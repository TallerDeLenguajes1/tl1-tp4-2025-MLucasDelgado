#include <stdio.h>
#include <stdlib.h>


typedef struct
{
    int TareaID;       // Numérico autoincremental comenzando en 1000
    char *Descripcion; //
    int Duracion;      // entre 10 – 100
} Tarea;

typedef struct
{
    Tarea T;
    Nodo *Siguiente;
} Nodo;

int main()
{
    Nodo *Start = NULL;
    int idActual = 1000;
    
    CargarTareas(&Start, &idActual);

    
}

Nodo *CrearNodo(int id){
    Nodo *nuevoNodo = (Nodo *)malloc(sizeof(Nodo));
    nuevoNodo->T.TareaID = id;
    nuevoNodo->Siguiente = NULL;
    return nuevoNodo;
};

void insertarNodo (Nodo **Start, Nodo *nodoNuevo) {
    nodoNuevo->Siguiente = *Start;
    *Start = nodoNuevo;
}

void CargarTareas (Nodo **Start, int *idActual) {
    Nodo *nuevaTarea = CrearNodo(*idActual);

    printf("Ingrese la descripcion: ");
    scanf("%s", nuevaTarea->T.Descripcion);
    
    printf("Ingrese la duracion (10 - 100): ");
    scanf("%d", nuevaTarea->T.Duracion);

    insertarNodo(&Start, nuevaTarea);

    (*idActual++);
}