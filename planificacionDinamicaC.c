#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define MAX_PROCESSES 10

// Estructura de un proceso
typedef struct {
    int id;
    int burst_time;
    char *name;
} Process;

// Cola de procesos
typedef struct {
    Process *queue[MAX_PROCESSES];
    int front, rear;
} Queue;

// Inicializar una cola
void initializeQueue(Queue *q) {
    q->front = q->rear = -1;
}

// Verificar si la cola está vacía
int isEmpty(Queue *q) {
    return (q->front == -1);
}

// Añadir un proceso a la cola
void enqueue(Queue *q, Process *process) {
    if (q->rear == MAX_PROCESSES - 1) {
        printf("La cola está llena\n");
        exit(EXIT_FAILURE);
    }

    if (q->front == -1)
        q->front = 0;
    q->rear++;
    q->queue[q->rear] = process;
}

// Eliminar un proceso de la cola
Process *dequeue(Queue *q) {
    if (isEmpty(q)) {
        printf("La cola está vacía\n");
        exit(EXIT_FAILURE);
    }

    Process *process = q->queue[q->front];
    if (q->front == q->rear)
        q->front = q->rear = -1;
    else
        q->front++;
    return process;
}

// Función principal
int main() {
    // Variables para medir el tiempo de ejecución total y de cada proceso
    clock_t start, end;
    double tiempo_transcurrido_total = 0.0;

    // Inicializar las colas
    Queue fifoQueue;
    initializeQueue(&fifoQueue);

    // Crear procesos específicos
    Process *terminal = malloc(sizeof(Process));
    terminal->id = 1;
    terminal->burst_time = 5;
    terminal->name = "gnome-terminal";
    Process *calculator = malloc(sizeof(Process));
    calculator->id = 2;
    calculator->burst_time = 3;
    calculator->name = "gnome-calculator";
    Process *browser = malloc(sizeof(Process));
    browser->id = 3;
    browser->burst_time = 7;
    browser->name = "firefox";

    // Añadir los procesos a la cola
    enqueue(&fifoQueue, terminal);
    enqueue(&fifoQueue, calculator);
    enqueue(&fifoQueue, browser);

    // Simular la ejecución de procesos
    printf("Ejecutando procesos de la cola FIFO:\n");
    while (!isEmpty(&fifoQueue)) {
        start = clock(); // Guardar el tiempo de inicio de la ejecución del proceso

        Process *current_process = dequeue(&fifoQueue);
        printf("Proceso %d (%s) en ejecución\n", current_process->id, current_process->name);
        // Ejecutar el proceso
        system(current_process->name); // Ejecuta el proceso en el sistema
        sleep(current_process->burst_time); // Simula el tiempo de ejecución del proceso

        end = clock(); // Guardar el tiempo de finalización de la ejecución del proceso
        double tiempo_transcurrido = ((double) (end - start)) / CLOCKS_PER_SEC; // Calcular el tiempo de ejecución del proceso
        printf("Tiempo de ejecución del proceso %d: %f segundos\n", current_process->id, tiempo_transcurrido);

        tiempo_transcurrido_total += tiempo_transcurrido; // Sumar al tiempo total de ejecución
    }

    // Liberar memoria
    free(terminal);
    free(calculator);
    free(browser);

    printf("Tiempo total de ejecución de todos los procesos: %f segundos\n", tiempo_transcurrido_total); // Mostrar el tiempo total de ejecución de todos los procesos

    return 0;
}
