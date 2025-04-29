#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//Linra extra para probar a
typedef struct 
{
    int TareaID; // Numerico autoincremental comenzando en 1000
    char *descripcion;
    int duracion; //entre 10-100
} Tarea;

typedef struct Nodo Nodo;

typedef struct Nodo {
    Tarea T;
    Nodo *Siguiente;  // Puntero a otro Nodo (esto es lo que enlaza la lista)
} Nodo;

Nodo * CrearListaVacia();
Nodo * NuevoNodo(Tarea * tarea);
void InsertarNodo(Nodo ** Start, Nodo * Nodo);
Nodo * QuitarNodoPorId(Nodo ** Start, int tareaID);
Nodo * buscarNodo(Nodo * Start, int IdBuscado);
void InsertarAlFinal(Nodo ** Start, Nodo * Nodo);
void EliminarNodo(Nodo * nodo);
void MostrarTareas(Nodo * Start);

int main(){
    Nodo *Pendientes = CrearListaVacia();
    Nodo *Realizadas = CrearListaVacia();

    Tarea TareaActual;

    char continuar = 's';
    int id = 1000;
    int eleccion;

    while (continuar == 's' ||  continuar == 'S')
    {
        printf("Ingrese la descripcion de la nueva tarea pendiente \n");
        TareaActual.descripcion = (char *)malloc(100 * sizeof(char));
        gets(TareaActual.descripcion);
        
        do
        {
            printf("Ingrese la duracion de la tarea (entre 10 y 100) ");
            scanf("%d", &TareaActual.duracion);
        } while (TareaActual.duracion < 10 || TareaActual.duracion > 100);

        TareaActual.TareaID = id++;

        Nodo * NNodo = NuevoNodo(&TareaActual);
        InsertarAlFinal(&Pendientes,NNodo);
        
        printf("Desea continuar agregando tareas? (S/N) ");
        getchar();
        scanf("%s",&continuar);
    }
    
    do
    {
        printf("\nLas tareas pendientes son: \n");
        MostrarTareas(Pendientes);

        printf("\nElija el id de la tarea que ya realizo, pulse 0 si no realizo ninguna tarea de la lista \n");
        scanf("%d",&eleccion);

        if (eleccion != 0)
        {
            Nodo * NodoTareaRealizada = QuitarNodoPorId(&Pendientes,eleccion);

            if (NodoTareaRealizada != NULL)
            {
                InsertarAlFinal(&Realizadas,NodoTareaRealizada);
                printf("Tarea con ID %d pasada a lista de tareas realizadas \n", eleccion);
            } else
            {
                printf("Tarea con ID %d no se encontro en la lista \n",eleccion);
            }
        }

    } while (eleccion != 0);
    
    printf("Tareas Pendientes\n");
    MostrarTareas(Pendientes);
    printf("Tareas Realizadas\n");
    MostrarTareas(Realizadas);

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

void MostrarTareas(Nodo * Start) {
    Nodo *aux = Start;
    if (aux == NULL) {
        printf("No hay tareas en la lista.\n");
        return;
    }
    
    while (aux != NULL) {
        printf("ID: %d, Descripción: %s, Duración: %d\n", aux->T.TareaID, aux->T.descripcion, aux->T.duracion);
        aux = aux->Siguiente;
    }
}
