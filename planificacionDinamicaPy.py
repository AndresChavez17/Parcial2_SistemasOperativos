import subprocess
import time

# Estructura de un proceso
class Process:
    def __init__(self, id, burst_time, name):
        self.id = id
        self.burst_time = burst_time
        self.name = name

# Cola de procesos
class Queue:
    def __init__(self):
        self.queue = []

    def enqueue(self, process):
        self.queue.append(process)

    def dequeue(self):
        return self.queue.pop(0)

    def is_empty(self):
        return len(self.queue) == 0

# Función para ejecutar procesos
def execute_process(process):
    print(f"Ejecutando proceso {process.id} ({process.name})")
    start_time = time.process_time()  # Guardar el tiempo de inicio de la ejecución del proceso
    subprocess.run([process.name])  # Ejecutar el proceso
    end_time = time.process_time()  # Guardar el tiempo de finalización de la ejecución del proceso
    execution_time = end_time - start_time
    print(f"Tiempo de ejecución del proceso {process.id}: {execution_time} segundos")
    return execution_time

# Función principal
def main():
    # Inicializar la cola de procesos
    fifo_queue = Queue()

    # Crear procesos específicos
    terminal = Process(1, 5, "/usr/bin/gnome-terminal")
    calculator = Process(2, 3, "/usr/bin/gnome-calculator")
    browser = Process(3, 7, "/usr/bin/firefox")

    # Añadir los procesos a la cola
    fifo_queue.enqueue(terminal)
    fifo_queue.enqueue(calculator)
    fifo_queue.enqueue(browser)

    # Simular la ejecución de procesos
    print("Ejecutando procesos de la cola FIFO:")
    total_execution_time = 0
    while not fifo_queue.is_empty():
        current_process = fifo_queue.dequeue()
        total_execution_time += execute_process(current_process)

    print(f"Tiempo total de ejecución de todos los procesos: {total_execution_time} segundos")

if __name__ == "__main__":
    main()
