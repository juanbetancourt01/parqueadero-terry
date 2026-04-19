#include <iostream>
#include <string>
#include <ctime>
#include <thread>
#include <chrono>
#include <cstdlib>
// ===== COLORES ANSI =====
#define RESET "\033[0m"
#define ROJO "\033[31m"
#define VERDE "\033[32m"
#define AMARILLO "\033[33m"
#define AZUL "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
// ===== CONSTANTES =====
const int NIVELES = 2;
const int FILAS = 16;
const int COLS = 16;
const int MAX_HISTORIAL = 200;
// ===== ESTRUCTURAS =====
struct Espacio {
 bool ocupado;
 std::string placa;
 int tipo; // 1 carro, 2 moto, 3 bici
 std::time_t entrada;
};
