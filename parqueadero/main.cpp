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
// ===== INICIALIZAR =====
void inicializar() {
 for (int n = 0; n < NIVELES; n++) {
 for (int i = 0; i < FILAS; i++) {
 for (int j = 0; j < COLS; j++) {
 parqueadero[n][i][j].ocupado = false;
 parqueadero[n][i][j].placa = "";
 parqueadero[n][i][j].tipo = 0;
 }
 }
 }
 // Vías cada 4 filas/columnas — forman una cuadrícula de calles
 for (int i = 0; i < FILAS; i++) {
 for (int j = 0; j < COLS; j++) {
 vias[i][j] = (i % 4 == 0 || j % 4 == 0);
 }
 }
}
// ===== MAPA =====
void mostrarMapa(int nivel, int rx = -1, int ry = -1, int tipoAnim = 1) {
 limpiarPantalla();
 std::cout << AZUL << "\n====== NIVEL " << nivel << " ======\n\n" << RESET;
 for (int i = 0; i < FILAS; i++) {
 for (int j = 0; j < COLS; j++) {
 // Vehículo en movimiento
 if (i == rx && j == ry) {
 std::cout << obtenerColor(tipoAnim)
 << obtenerEmoji(tipoAnim) << " "
 << RESET;
 continue;
 }
 if (parqueadero[nivel][i][j].ocupado) {
 std::cout << obtenerColor(parqueadero[nivel][i][j].tipo)
 << obtenerEmoji(parqueadero[nivel][i][j].tipo)
 << " " << RESET;
 } else if (vias[i][j]) {
 if (i == 0 && j == 0)
 std::cout << VERDE << "E " << RESET;
 else if (i == FILAS - 1 && j == COLS - 1)
 std::cout << ROJO << "S " << RESET;
 else
 std::cout << "- ";
 } else {
 std::cout << ". ";
 }
 }
 std::cout << "\n";
 }
}
// ===== MOVIMIENTO =====
void moverVehiculo(int nivel, int destinoX, int destinoY, int tipo) {
 int x = 0, y = 0;
 while (x != destinoX || y != destinoY) {
 mostrarMapa(nivel, x, y, tipo);
 std::this_thread::sleep_for(std::chrono::milliseconds(120));
 if (x < destinoX) x++;
 else if (x > destinoX) x--;
 if (y < destinoY) y++;
 else if (y > destinoY) y--;
 }
 mostrarMapa(nivel, destinoX, destinoY, tipo);
}
// ===== ANIMACIONES =====
void animacionEntrada(int tipo) {
 std::string emoji = obtenerEmoji(tipo);
 std::string color = obtenerColor(tipo);
 std::cout << "\nIngresando vehiculo...\n";
 for (int i = 0; i < 20; i++) {
 std::cout << "\r" << color << emoji << " ";
 for (int j = 0; j < i; j++) std::cout << " ";
 std::cout << "→" << RESET << std::flush;
 std::this_thread::sleep_for(std::chrono::milliseconds(60));
 }
 std::cout << "\n" << VERDE << "Vehiculo parqueado correctamente\n" << RESET;
}
void animacionSalida(int tipo) {
 std::string emoji = obtenerEmoji(tipo);
 std::string color = obtenerColor(tipo);
 std::cout << "\nSaliendo vehiculo...\n";
 for (int i = 20; i > 0; i--) {
 std::cout << "\r" << color << emoji << " ";
 for (int j = 0; j < i; j++) std::cout << " ";
 std::cout << "←" << RESET << std::flush;
 std::this_thread::sleep_for(std::chrono::milliseconds(60));
 }
 std::cout << "\n" << VERDE << "Vehiculo fuera del parqueadero\n" << RESET;
}
// ===== COBRO =====
void mostrarPago(int pago) {
 std::cout << MAGENTA;
 std::cout << "\n=============================\n";
 std::cout << " TOTAL A PAGAR: $" << pago << "\n";
 std::cout << "=============================\n";
 std::cout << RESET;
}
int calcularPago(std::time_t entrada, int tipo) {
 double minutos = std::difftime(std::time(0), entrada) / 60.0;
 int tarifa;
 if (tipo == 1) tarifa = 150;
 else if (tipo == 2) tarifa = 100;
 else tarifa = 50;
 return static_cast<int>(minutos * tarifa);
}
