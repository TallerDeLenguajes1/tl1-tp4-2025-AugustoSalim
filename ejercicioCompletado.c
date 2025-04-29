#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definición de estructuras
typedef struct Tarea {
    int TareaID;        // ID autoincremental comenzando en 1000
    char *descripcion;  // Descripción de la tarea
    int duracion;       // Duración entre 10 y 100
} Tarea;

typedef struct Nodo {
    Tarea T;            // Datos de la tarea
    struct Nodo *Siguiente; // Puntero al siguiente nodo
} Nodo;

// Prototipos de funciones
Nodo* CrearNodo(int id, char *desc, int duracion);
void InsertarNodo(Nodo **Lista, Nodo *nuevo);
void MostrarTareas(Nodo *Lista, char *mensaje);
Nodo* buscarNodo(Nodo *Lista, int id);
Nodo* eliminarNodo(Nodo **Lista, int id);
int ContienePalabra(char *descripcion, char *palabraClave);
void BuscarTarea(Nodo *Pendientes, Nodo *Realizadas);

int main() {
    Nodo *Pendientes = NULL;   // Lista de tareas pendientes
    Nodo *Realizadas = NULL;   // Lista de tareas realizadas
    int idActual = 1000;        // ID inicial
    char seguir = 's';

    // Carga de tareas
    while (seguir == 's' || seguir == 'S') {
        char desc[100];
        int duracion;

        printf("\nIngrese la descripcion de la tarea: ");
        getchar(); // limpiar el buffer
        gets(desc);

        printf("Ingrese la duracion de la tarea (entre 10 y 100): ");
        scanf("%d", &duracion);

        // Validar duración
        while (duracion < 10 || duracion > 100) {
            printf("Duracion invalida. Ingrese una duracion entre 10 y 100: ");
            scanf("%d", &duracion);
        }

        // Crear nuevo nodo y agregarlo a la lista de pendientes
        Nodo *nuevo = CrearNodo(idActual, desc, duracion);
        InsertarNodo(&Pendientes, nuevo);

        idActual++; // Incrementar ID

        printf("\n¿Desea ingresar otra tarea? (S/N): ");
        getchar(); // limpiar buffer
        scanf("%c", &seguir);
    }

    // Mostrar lista de tareas pendientes
    MostrarTareas(Pendientes, "Tareas Pendientes:");

    // Mover tareas realizadas
    char moverOtra = 's';
    while (moverOtra == 's' || moverOtra == 'S') {
        int idMover;

        printf("\nIngrese el ID de la tarea que ya realizo: ");
        scanf("%d", &idMover);

        Nodo *movida = eliminarNodo(&Pendientes, idMover);
        if (movida != NULL) {
            InsertarNodo(&Realizadas, movida);
            printf("Tarea movida a realizadas.\n");
        } else {
            printf("Tarea no encontrada en pendientes.\n");
        }

        printf("\n¿Desea mover otra tarea? (S/N): ");
        getchar(); // limpiar buffer
        scanf("%c", &moverOtra);
    }

    // Mostrar listas actualizadas
    MostrarTareas(Pendientes, "Tareas Pendientes:");
    MostrarTareas(Realizadas, "Tareas Realizadas:");

    // Búsqueda de tareas
    char buscarOtra = 's';
    while (buscarOtra == 's' || buscarOtra == 'S') {
        printf("\n¿Desea buscar una tarea? (S/N): ");
        getchar(); // limpiar buffer
        scanf("%c", &buscarOtra);

        if (buscarOtra == 's' || buscarOtra == 'S') {
            BuscarTarea(Pendientes, Realizadas);
        }
    }

    return 0;
}

// Función para crear un nuevo nodo
Nodo* CrearNodo(int id, char *desc, int duracion) {
    Nodo *nuevo = (Nodo*)malloc(sizeof(Nodo));
    nuevo->T.TareaID = id;
    nuevo->T.descripcion = (char*)malloc(strlen(desc) + 1);
    strcpy(nuevo->T.descripcion, desc);
    nuevo->T.duracion = duracion;
    nuevo->Siguiente = NULL;
    return nuevo;
}

// Función para insertar nodo al principio de la lista
void InsertarNodo(Nodo **Lista, Nodo *nuevo) {
    nuevo->Siguiente = *Lista;
    *Lista = nuevo;
}

// Función para mostrar todas las tareas de una lista
void MostrarTareas(Nodo *Lista, char *mensaje) {
    printf("\n%s\n", mensaje);
    Nodo *aux = Lista;
    while (aux != NULL) {
        printf("ID: %d, Descripción: %s, Duración: %d\n", aux->T.TareaID, aux->T.descripcion, aux->T.duracion);
        aux = aux->Siguiente;
    }
}

// Función para buscar un nodo por ID
Nodo* buscarNodo(Nodo *Lista, int id) {
    Nodo *aux = Lista;
    while (aux != NULL) {
        if (aux->T.TareaID == id) {
            return aux;
        }
        aux = aux->Siguiente;
    }
    return NULL;
}

// Función para eliminar un nodo de la lista por ID
Nodo* eliminarNodo(Nodo **Lista, int id) {
    Nodo *aux = *Lista;
    Nodo *ant = NULL;

    while (aux != NULL && aux->T.TareaID != id) {
        ant = aux;
        aux = aux->Siguiente;
    }

    if (aux == NULL) {
        return NULL; // No se encontró el nodo
    }

    if (ant == NULL) {
        *Lista = aux->Siguiente; // El nodo a eliminar era el primero
    } else {
        ant->Siguiente = aux->Siguiente; // Saltear el nodo
    }

    aux->Siguiente = NULL; // Desconectar el nodo eliminado
    return aux;
}

// Función para verificar si una descripción contiene una palabra clave
int ContienePalabra(char *descripcion, char *palabraClave) {
    if (strstr(descripcion, palabraClave) != NULL) {
        return 1;
    }
    return 0;
}

// Función para buscar tareas por ID o palabra clave
void BuscarTarea(Nodo *Pendientes, Nodo *Realizadas) {
    int opcionBusqueda;
    printf("\n¿Desea buscar por:\n1. ID\n2. Palabra clave\nIngrese una opción: ");
    scanf("%d", &opcionBusqueda);

    if (opcionBusqueda == 1) {
        int idBuscado;
        printf("Ingrese el ID de la tarea que desea buscar: ");
        scanf("%d", &idBuscado);

        Nodo *resultado = buscarNodo(Pendientes, idBuscado);
        if (resultado != NULL) {
            printf("\nTarea encontrada en lista de Pendientes:\n");
            printf("ID: %d, Descripción: %s, Duración: %d\n", resultado->T.TareaID, resultado->T.descripcion, resultado->T.duracion);
        } else {
            resultado = buscarNodo(Realizadas, idBuscado);
            if (resultado != NULL) {
                printf("\nTarea encontrada en lista de Realizadas:\n");
                printf("ID: %d, Descripción: %s, Duración: %d\n", resultado->T.TareaID, resultado->T.descripcion, resultado->T.duracion);
            } else {
                printf("No se encontró una tarea con el ID %d.\n", idBuscado);
            }
        }
    } else if (opcionBusqueda == 2) {
        char palabraClave[100];
        printf("Ingrese la palabra clave que desea buscar: ");
        getchar(); // limpiar buffer
        gets(palabraClave);

        int encontrado = 0;
        Nodo *aux = Pendientes;
        while (aux != NULL) {
            if (ContienePalabra(aux->T.descripcion, palabraClave)) {
                if (!encontrado) {
                    printf("\nTareas encontradas en lista de Pendientes:\n");
                }
                printf("ID: %d, Descripción: %s, Duración: %d\n", aux->T.TareaID, aux->T.descripcion, aux->T.duracion);
                encontrado = 1;
            }
            aux = aux->Siguiente;
        }

        aux = Realizadas;
        while (aux != NULL) {
            if (ContienePalabra(aux->T.descripcion, palabraClave)) {
                if (!encontrado) {
                    printf("\nTareas encontradas en lista de Realizadas:\n");
                }
                printf("ID: %d, Descripción: %s, Duración: %d\n", aux->T.TareaID, aux->T.descripcion, aux->T.duracion);
                encontrado = 1;
            }
            aux = aux->Siguiente;
        }

        if (!encontrado) {
            printf("No se encontraron tareas que contengan la palabra clave \"%s\".\n", palabraClave);
        }
    } else {
        printf("Opción inválida.\n");
    }
}
