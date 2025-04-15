#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct 
{
    int TareaID; // Numerico autoincremental comenzando en 1000
    char *descripcion;
    int duracion; //entre 10-100
} Tarea;

typedef struct Nodo
{
    Tarea T;
    Nodo *Siguiente;
} Nodo;

Nodo * CrearListaVacia();
Nodo * NuevoNodo(Tarea * tarea);
void InsertarNodo(Nodo ** Start, Nodo * Nodo);
Nodo * QuitarNodoPorId(Nodo ** Start, int tareaID);
Nodo * buscarNodo(Nodo * Start, int IdBuscado);
void InsertarAlFinal(Nodo ** Start, Nodo * Nodo);
void EliminarNodo(Nodo * nodo);

int main(){
    Nodo * Start;
    Tarea *Pendientes;
    Tarea *Realizadas;

    Start = CrearListaVacia();

    return 0;
}

Nodo * CrearListaVacia(){
    return NULL;
}

Nodo * NuevoNodo(Tarea * tarea){
    Nodo * NNodo = (Nodo *)malloc(sizeof(Nodo));
    NNodo->T.duracion = tarea->duracion;
    NNodo->T.TareaID = tarea->TareaID;
    NNodo->T.descripcion = (char *)malloc(strlen(tarea->descripcion)+1);
    strcpy(NNodo->T.descripcion, tarea->descripcion);
    NNodo->Siguiente = NULL;
    return NNodo;
}


void InsertarNodo(Nodo ** Start, Nodo * Nodo){
    Nodo->Siguiente = *Start;
    *Start = Nodo;
}

Nodo * QuitarNodoPorId(Nodo ** Start, int tareaID)

{
    Nodo ** aux = Start;
    while (*aux != NULL && (*aux)->T.TareaID != tareaID) {  // Comparar con el TareaID
        aux = &(*aux)->Siguiente;
    }
    
    if (*aux) {
        Nodo *temp = *aux;  // Guardar el nodo que vamos a quitar
        *aux = (*aux)->Siguiente;  // El puntero del nodo anterior apunta al siguiente
        temp->Siguiente = NULL;  // Desvincular el nodo quitado
        return temp;  // Devolver el nodo eliminado
    }
    
    return NULL;  // Si no se encuentra la tarea, devolver NULL
}

Nodo * buscarNodo(Nodo * Start, int IdBuscado)
{
    Nodo * Aux = Start;
    while(Aux && Aux->T.TareaID != IdBuscado)
    {
        Aux = Aux -> Siguiente;
    }
    return Aux;
}

void InsertarAlFinal(Nodo **start, Nodo *nuevoNodo) {
    if (*start == NULL) {
        *start = nuevoNodo;
    } else {
        Nodo *aux = *start;
        while (aux->Siguiente != NULL) {
            aux = aux->Siguiente;
        }
        aux->Siguiente = nuevoNodo;
    }
}

void EliminarNodo(Nodo * nodo)
{
    free(nodo->T.descripcion);
    free(nodo);
}

