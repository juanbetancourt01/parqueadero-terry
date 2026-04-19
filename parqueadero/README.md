##Parqueadero Terry
#Integrantes
Juan Jose Guerrero
Juan Camilo Betancourt
#¿De qué trata?
Sistema de gestión de parqueadero desarrollado en C++. Simula el funcionamiento básico
de un parqueadero real: entrada y salida de vehículos, ocupación de espacios, cobro por
tiempo y registro de pagos.
##Funcionalidades
Mapa visual del parqueadero (16x16)
Vías de circulación, entrada (E) y salida (S)
Registro de placa, tipo de vehículo y hora de ingreso
Cálculo del valor a pagar según tiempo de permanencia
Disponibilidad en tiempo real reflejada en el mapa
Historial de pagos
Animaciones de movimiento del vehículo
##Conceptos técnicos aplicados
Requisito Dónde se usa
Funciones mostrarMapa() , ingresarVehiculo() , retirarVehiculo() ,
calcularPago() , entre otras
Ciclos for Generación y recorrido del mapa en todas las funciones de visualización
Punteros buscarEspacio() recibe int *nivel, *x, *y para modificar valores
desde la función
Matrices parqueadero[NIVELES][FILAS][COLS] y vias[FILAS][COLS] , ambas de
16x16
Modularidad main() solo contiene el menú; toda la lógica está en funciones separadas
Lo que agregamos más allá de los requisitos
##1. Matriz de vías independiente
Se creó una matriz booleana vias[FILAS][COLS] separada del arreglo de espacios. Esto
permite que la lógica de búsqueda de espacio libre ( buscarEspacio ) descarte
automáticamente las celdas que son vía, sin mezclar responsabilidades en una sola
estructura.
Por qué: En una implementación básica es fácil que un vehículo quede “parqueado” sobre
una vía. Separar la matriz evita ese problema sin necesidad de condiciones extra en cada
función.
Cómo: Con if (i % 4 == 0 || j % 4 == 0) vias[i][j] = true se generan calles
horizontales y verticales distribuidas regularmente, dando una cuadrícula de acceso real.
##2. Dos niveles de parqueadero
El sistema maneja dos niveles ( NIVELES = 2 ). Las bicicletas solo pueden ocupar el nivel 0
(planta principal); carros y motos pueden usar cualquiera. La búsqueda de espacio prioriza
los más cercanos a la entrada.
Por qué: Agrega una capa de organización más cercana a un parqueadero real, donde no
todos los espacios son iguales para todos los vehículos.
##3. Animaciones de movimiento
El vehículo se desplaza celda por celda desde la entrada hasta su posición asignada (y
viceversa al salir), actualizando el mapa en cada paso con un pequeño delay.
Por qué: Hace el sistema más fácil de entender visualmente. Ver el movimiento deja claro
que las vías sí son transitables y que el espacio asignado es accesible desde la entrada.
Cómo: La función moverVehiculo() incrementa x e y gradualmente hacia el destino,
llamando mostrarMapa() con la posición actual del vehículo en cada iteración.
##4. Diferenciación visual por tipo de vehículo
Cada tipo de vehículo tiene un emoji y un color de consola distinto:
 Carros — rojo
 Motos — amarillo
 Bicicletas — cyan
Por qué: Con un mapa de 16x16 lleno de símbolos es difícil leer el estado de un vistazo. Los
colores permiten identificar de inmediato qué espacios están ocupados y por qué tipo de
vehículo.
##5. Historial de pagos
Cada vez que un vehículo sale, se guarda su placa y el monto cobrado en un arreglo
historial[] . Se puede consultar en cualquier momento desde el menú.
Por qué: El enunciado pide un sistema de cobro, pero sin registro histórico no hay forma de
saber cuánto se recaudó en la sesión.
Tarifas
Tipo Tarifa por minuto
Carro $150
Moto $100
Bicicleta $50
Cómo compilar y ejecutar
g++ main.cpp -o parqueadero
./parqueadero
##En Windows: g++ main.cpp -o parqueadero.exe y luego parqueadero.exe
Referencias
Stroustrup, B. (2013). The C++ Programming Language (4th ed.). Addison-Wesley.
cppreference.com — documentación de <ctime> , <chrono> y <thread>
Brooks, F. P. (1995). The Mythical Man-Month. Addison-Wesley.
