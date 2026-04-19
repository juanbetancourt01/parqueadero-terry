# Parqueadero Terry

**Integrantes**
- Juan Jose Guerrero
- Juan Camilo Betancourt

---

## ¿De qué trata?

Sistema de gestión de parqueadero desarrollado en C++. Simula el funcionamiento básico de un parqueadero real: entrada y salida de vehículos, ocupación de espacios, cobro por tiempo y registro de pagos.

---

## Funcionalidades

- Mapa visual del parqueadero (16x16)
- Vías de circulación, entrada (E) y salida (S)
- Registro de placa, tipo de vehículo y hora de ingreso
- Cálculo del valor a pagar según tiempo de permanencia
- Disponibilidad en tiempo real reflejada en el mapa
- Historial de pagos
- Animaciones de movimiento del vehículo

---

## Conceptos técnicos aplicados

| Requisito | Dónde se usa |
|---|---|
| Funciones | `mostrarMapa()`, `ingresarVehiculo()`, `retirarVehiculo()`, `calcularPago()` |
| Ciclos `for` | Generación y recorrido del mapa en todas las funciones de visualización |
| Punteros | `buscarEspacio()` recibe `int *nivel, *x, *y` para modificar valores desde la función |
| Matrices | `parqueadero[NIVELES][FILAS][COLS]` y `vias[FILAS][COLS]`, ambas de 16x16 |
| Modularidad | `main()` solo contiene el menú; toda la lógica está en funciones separadas |

---

## Innovaciones implementadas

### 1. Matriz de vías independiente

Se creó una matriz booleana `vias[FILAS][COLS]` separada del arreglo de espacios. Permite que la búsqueda de espacio libre descarte automáticamente las celdas que son vía, sin mezclar responsabilidades en una sola estructura.

**¿Para qué?** Para que ningún vehículo quede parqueado sobre una calle.

**¿Por qué?** En una implementación básica es fácil que eso ocurra. Separar la matriz evita el problema sin necesidad de condiciones extra en cada función.

**¿Cómo?** Con `if (i % 4 == 0 || j % 4 == 0) vias[i][j] = true` se generan calles horizontales y verticales distribuidas regularmente.

---

### 2. Dos niveles de parqueadero

El sistema maneja dos niveles. Las bicicletas solo ocupan el nivel 0; carros y motos pueden usar cualquiera. La búsqueda prioriza los espacios más cercanos a la entrada.

**¿Para qué?** Organizar el espacio según el tipo de vehículo.

**¿Por qué?** Se acerca más al funcionamiento de un parqueadero real donde no todos los espacios son iguales.

**¿Cómo?** En `buscarEspacio()` se filtra con `if (tipo == 3 && n != 0) continue` antes de evaluar el espacio.

---

### 3. Animaciones de movimiento

El vehículo se desplaza celda por celda desde la entrada hasta su posición asignada, actualizando el mapa en cada paso.

**¿Para qué?** Hacer el sistema más fácil de entender visualmente.

**¿Por qué?** Ver el movimiento confirma que las vías son transitables y que el espacio asignado es accesible.

**¿Cómo?** La función `moverVehiculo()` incrementa `x` e `y` gradualmente hacia el destino, llamando `mostrarMapa()` con la posición actual en cada iteración.

---

### 4. Diferenciación visual por tipo de vehículo

Cada tipo tiene un emoji y un color de consola distinto:
- Carros — rojo
- Motos — amarillo
- Bicicletas — cyan

**¿Para qué?** Identificar de un vistazo qué espacios están ocupados y por qué tipo.

**¿Por qué?** Con un mapa de 16x16 lleno de símbolos, los colores reducen el tiempo de lectura.

**¿Cómo?** Las funciones `obtenerEmoji()` y `obtenerColor()` devuelven el valor según el tipo y se usan en cada punto donde se dibuja el mapa.

---

### 5. Historial de pagos

Cada vez que un vehículo sale, se guarda su placa y el monto cobrado. Se puede consultar en cualquier momento desde el menú.

**¿Para qué?** Llevar control de cuánto se recaudó durante la sesión.

**¿Por qué?** El cobro sin registro no deja trazabilidad de las transacciones.

**¿Cómo?** Un arreglo `historial[MAX_HISTORIAL]` de structs guarda placa y pago. Se incrementa `contadorHistorial` con cada salida, con validación para no desbordar el arreglo.

---

## Tarifas

| Tipo | Tarifa por minuto |
|---|---|
| Carro | $150 |
| Moto | $100 |
| Bicicleta | $50 |

---

## Cómo compilar y ejecutar

```bash
g++ main.cpp -o parqueadero
./parqueadero
## Referencias

- cppreference.com — `std::time`, `std::difftime`, `<ctime>`: https://en.cppreference.com/w/cpp/chrono/c/time
- cppreference.com — `std::this_thread::sleep_for`, `<thread>`, `<chrono>`: https://en.cppreference.com/w/cpp/thread/sleep_for
- cppreference.com — `std::system`, `<cstdlib>`: https://en.cppreference.com/w/cpp/utility/program/system
- learncpp.com — Punteros y paso por referencia: https://www.learncpp.com/cpp-tutorial/introduction-to-pointers
- learncpp.com — Structs en C++: https://www.learncpp.com/cpp-tutorial/introduction-to-structs-members-and-member-selection
- ANSI escape codes — colores en consola: https://en.wikipedia.org/wiki/ANSI_escape_code
- Brooks, F. P. (1995). *The Mythical Man-Month*. Addison-Wesley.

