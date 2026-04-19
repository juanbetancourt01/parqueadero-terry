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
struct Historial {
 std::string placa;
 int pago;
};
// ===== VARIABLES GLOBALES =====
Espacio parqueadero[NIVELES][FILAS][COLS];
bool vias[FILAS][COLS];
Historial historial[MAX_HISTORIAL];
int contadorHistorial = 0;
// ===== UTILIDADES =====
std::string obtenerEmoji(int tipo) {
 if (tipo == 1) return " ";
 if (tipo == 2) return " ";
 return " ";
}
std::string obtenerColor(int tipo) {
 if (tipo == 1) return ROJO;
 if (tipo == 2) return AMARILLO;
 return CYAN;
}
void limpiarPantalla() {
#ifdef _WIN32
 std::system("cls");
#else
 std::system("clear");
#endif
}
