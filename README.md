
# Informe Laboratorio #1

##                  Integrantes

- [Julian Isaza Marin](https://github.com/julianisazam)
- [Sebastian Pelaez Acevedo](https://github.com/SPelaez122)
- [Simon Sanchez Sepulveda](https://github.com/Simonsanchezs)


## Forma de trabajo
Para este laboratorio notamos que el trabajo era mucho más extenso que el anterior por lo que tomamos la decisión de repartirnos el trabajo con el compromiso de reunirnos cada cierto periodo de tiempo para socializar el trabajo hecho por cada integrante y consolidarlo en conjunto en el repositorio, esto con el fin de que los demás integrantes del grupo tuvieran conocimiento de toda la estructura y funcionamiento del proyecto. Esta metodología nos llevó a un proceso lento por las reuniones acordadas pero consideramos que fue la mejor forma de hacerlo. 

 ## Primer commit
 Esta Versión la tomamos como introducción para planificar la estructura o camino para el desarrollo del código, en este primer commit se implementa la estructura base del shell wish, incluyendo la lógica para operar en modo interactivo (con un prompt  `wish> `) y modo batch (leyendo comandos desde un archivo). El programa valida el número de argumentos recibidos, abre el archivo de entrada si se proporciona, y utiliza un bucle principal que lee líneas de comandos mediante  `getline() `, manejando adecuadamente condiciones como el fin de archivo o errores de lectura. Además, libera la memoria dinámica asignada para cada línea y garantiza el cierre correcto de archivos abiertos. Con esta base, el shell ya puede recibir y procesar comandos de entrada, sentando las bases para integrar posteriormente funcionalidades como la ejecución de procesos, redirección de salida, manejo de errores y comandos internos Además, hicimos la identificación del funcionmiento del shell y optamos por realizar dos tipos de vectores que serán explicadas en las próximas versiones
 
 ## Segundo commit
Este commit introduce la implementación de una estructura dinámica de datos llamada Vector. Su objetivo es manejar colecciones de cadenas `char*` de manera flexible, permitiendo agregar, acceder, buscar y eliminar elementos sin preocuparse por el tamaño fijo de un arreglo tradicional. El archivo `vector.h` define la estructura y sus operaciones básicas el cual contiene tres campos: `data`, un puntero doble a char donde se almacenan las cadenas. `capacity`, que indica la capacidad actual del arreglo. `size`, que indica cuántos elementos están realmente ocupados. También declara las funciones para crear, modificar, buscar y destruir el vector. El archivo `vector.c` implementa estas funciones: `create_vector()` inicializa un nuevo vector con una capacidad inicial de 8 elementos. `push_back()` agrega un nuevo elemento al final; si el vector está lleno, duplica automáticamente la capacidad mediante realocación de memoria, copiando los elementos existentes. `pop_back()` elimina el último elemento simplemente reduciendo el tamaño lógico. `get()` devuelve el elemento en una posición dada, validando los límites. `get_size()` retorna el número de elementos actuales. `search_key()` busca una cadena específica y devuelve su índice o -1 si no la encuentra. `destroy()` libera la memoria asignada para el vector. 

Además, en este commit también se agregó en la función main de nuestro proyecto. Se recorre la lista de argumentos recibidos por línea de comandos para intentar abrir cada archivo de entrada, verificando posibles errores mediante la función `showError()`. Si no se especifica ningún archivo, el programa entra en un bucle interactivo que muestra el prompt "wish> " y espera que el usuario introduzca comandos desde la consola. Cada línea ingresada se lee dinámicamente con getline(), lo que permite manejar entradas de cualquier longitud, y se libera la memoria después de su uso. Esta estructura prepara el entorno para que, en futuras versiones, las líneas leídas sean tokenizadas, interpretadas y ejecutadas como comandos del shell, ya sea en modo interactivo o mediante archivos de entrada.

## Tercer commit ( Finalizacion del Laboratorio )

Modo Batch:
Se implementó la lectura de archivos por línea de comando para ejecutar secuencias de instrucciones automáticamente.
El programa valida que el archivo exista y que no se repita la referencia al mismo archivo (verificación mediante isSameFile).
Una vez abierto, el archivo se redirige a la entrada estándar (stdin), permitiendo procesar sus comandos de forma secuencial sin intervención del usuario.
Este modo es ideal para pruebas automatizadas o ejecución de scripts con varios comandos.

Shell Dinámica (Interactiva):
Cuando no se especifica un archivo de entrada, la shell opera en modo interactivo, mostrando el prompt wish> .
El usuario puede escribir comandos en tiempo real, los cuales se leen con getline() y se procesan inmediatamente.
Se soportan comandos internos (cd, path, exit) y externos ubicados en las rutas almacenadas en la variable global PATH.
La ejecución se mantiene en bucle hasta recibir el comando exit.

Ejecución en Paralelo:
Se implementó la capacidad de ejecutar múltiples comandos en paralelo mediante el uso del operador &.
La shell analiza la línea de comandos y separa las instrucciones por el símbolo &, ejecutando cada una en un proceso independiente.
Cada comando se lanza mediante una llamada a fork() y se espera su finalización con waitpid() para asegurar la sincronización correcta de procesos.
Además, se validan los casos donde el operador & se usa incorrectamente (por ejemplo, al inicio, duplicado o al final de la línea), garantizando que solo se ejecute cuando la sintaxis sea válida.
Esta funcionalidad permite que el usuario ejecute tareas de manera concurrente, simulando el comportamiento de shells reales en sistemas Unix.

Manejo de Errores:
Se centraliza el manejo de errores mediante la función showError(), que imprime un mensaje uniforme a stderr.
Se validan errores como:

Archivos inexistentes o duplicados en modo batch.

Sintaxis incorrecta en redirección (>).

Uso indebido del operador &.

Comandos mal estructurados o inexistentes.
Ante cualquier error, el sistema no se detiene abruptamente, sino que continúa procesando los siguientes comandos (excepto en casos críticos).

Ejecución y Redirección de Comandos:
Se añadió soporte para redirección de salida (>), permitiendo enviar la salida estándar a un archivo.
Los comandos externos se ejecutan mediante fork() y execv(), comprobando previamente permisos de ejecución con access().
El manejo de procesos, tanto en serie como en paralelo, asegura una ejecución eficiente y controlada de los programas.

Correcto Funcionamiento Global:
Se garantiza la gestión adecuada de memoria mediante la creación y destrucción de vectores (Vector) para los tokens de comando.
Se asegura un entorno mínimo funcional inicializando la variable PATH con /bin.
La shell mantiene un comportamiento consistente en ambos modos (batch e interactivo), reproduciendo el flujo básico de una shell Unix simplificada.
