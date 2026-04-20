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
// ===== BUSCAR ESPACIO =====
// Devuelve true si encontró un espacio libre, false si el parqueadero está lleno.
// Usa punteros para devolver el nivel y posición encontrados.
bool buscarEspacio(int tipo, int *nivel, int *x, int *y) {
 int mejorDist = 9999;
 for (int n = 0; n < NIVELES; n++) {
 for (int i = 0; i < FILAS; i++) {
 for (int j = 0; j < COLS; j++) {
 if (parqueadero[n][i][j].ocupado) continue;
 if (vias[i][j]) continue;
 // Bicicletas solo en nivel 0
 if (tipo == 3 && n != 0) continue;
 int dist = i + j; // distancia aproximada desde la entrada
 if (dist < mejorDist) {
 mejorDist = dist;
 *nivel = n;
 *x = i;
 *y = j;
 }
 }
 }
 }
 return mejorDist != 9999;
}
// ===== INGRESAR =====
void ingresarVehiculo() {
 int tipo, nivel = 0, x = 0, y = 0;
 std::string placa;
 std::cout << "Tipo (1=Carro, 2=Moto, 3=Bici): ";
 std::cin >> tipo;
 if (tipo < 1 || tipo > 3) {
 std::cout << ROJO << "Tipo invalido.\n" << RESET;
 return;
 }
 std::cout << "Placa: ";
 std::cin >> placa;
 if (!buscarEspacio(tipo, &nivel, &x, &y)) {
 std::cout << ROJO << "No hay espacios disponibles.\n" << RESET;
 return;
 }
 animacionEntrada(tipo);
 moverVehiculo(nivel, x, y, tipo);
 parqueadero[nivel][x][y].ocupado = true;
 parqueadero[nivel][x][y].placa = placa;
 parqueadero[nivel][x][y].tipo = tipo;
 parqueadero[nivel][x][y].entrada = std::time(0);
 std::cout << VERDE << "\nUbicado en Nivel " << nivel
 << " Posicion [" << x << "," << y << "]\n" << RESET;
}
// ===== RETIRAR =====
void retirarVehiculo() {
 std::string placa;
 std::cout << "Ingrese placa: ";
 std::cin >> placa;
 for (int n = 0; n < NIVELES; n++) {
 for (int i = 0; i < FILAS; i++) {
 for (int j = 0; j < COLS; j++) {
 if (!parqueadero[n][i][j].ocupado) continue;
 if (parqueadero[n][i][j].placa != placa) continue;
 int tipo = parqueadero[n][i][j].tipo;
 animacionSalida(tipo);
 moverVehiculo(n, 0, 0, tipo);
 int pago = calcularPago(parqueadero[n][i][j].entrada, tipo);
 mostrarPago(pago);
 // Guardar en historial si hay espacio
 if (contadorHistorial < MAX_HISTORIAL) {
 historial[contadorHistorial].placa = placa;
 historial[contadorHistorial].pago = pago;
 contadorHistorial++;
 }
 parqueadero[n][i][j].ocupado = false;
 parqueadero[n][i][j].placa = "";
 parqueadero[n][i][j].tipo = 0;
 return;
 }
 }
 }
 std::cout << ROJO << "Vehiculo no encontrado.\n" << RESET;
}
// ===== DISPONIBILIDAD =====
void mostrarDisponibilidad() {
 int carros = 0, motos = 0, bicis = 0;
 int totalEspacios = 0;
 for (int n = 0; n < NIVELES; n++) {
 for (int i = 0; i < FILAS; i++) {
 for (int j = 0; j < COLS; j++) {
 if (!vias[i][j]) totalEspacios++;
 if (parqueadero[n][i][j].ocupado) {
 if (parqueadero[n][i][j].tipo == 1) carros++;
 else if (parqueadero[n][i][j].tipo == 2) motos++;
 else bicis++;
 }
 }
 }
 }
 int ocupados = carros + motos + bicis;
 int libres = totalEspacios - ocupados;
 std::cout << "\n===== DISPONIBILIDAD =====\n";
 std::cout << " Carros: " << carros << "\n";
 std::cout << " Motos: " << motos << "\n";
 std::cout << " Bicicletas: " << bicis << "\n";
 std::cout << "--------------------------\n";
 std::cout << "Ocupados: " << ocupados << "\n";
 std::cout << "Libres: " << libres << "\n";
 std::cout << "==========================\n";
}
// ===== HISTORIAL =====
void verHistorial() {
 if (contadorHistorial == 0) {
 std::cout << "Sin registros aun.\n";
 return;
 }
 std::cout << "\n===== HISTORIAL DE PAGOS =====\n";
 for (int i = 0; i < contadorHistorial; i++) {
 std::cout << historial[i].placa
 << " -> $" << historial[i].pago << "\n";
 }
 std::cout << "==============================\n";
}
