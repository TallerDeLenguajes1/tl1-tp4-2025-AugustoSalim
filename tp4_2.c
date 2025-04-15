#include <stdio.h>
#include <stdlib.h>

typedef struct 
{
    int TareaID; // Numerico autoincremental comenzando en 1000
    char *descripcion;
    int duracion; //entre 10-100
} Tarea;

typedef struct 
{
    Tarea T;
    Nodo *Siguiente;
} Nodo;

int main(){
    Tarea *Pendientes;
    Tarea *Realizadas;

    return 0;
}
