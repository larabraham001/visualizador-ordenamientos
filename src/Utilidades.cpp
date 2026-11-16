#include "Utilidades.hpp"       // Header propio (con comillas)
#include <random>               // Generador de números aleatorios

std::vector<int> generarValores(int cantidad, int alturaMax)
{
    std::vector<int> valores(cantidad);

    std::random_device semilla;                     // fuente de aleatoriedad del sistema
    std::mt19937 generador(semilla());                // generador de números aleatorios
    std::uniform_int_distribution<int> rango(20, alturaMax);

    for (int& v : valores) v = rango(generador);

    return valores;
}