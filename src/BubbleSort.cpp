#include "BubbleSort.hpp"
#include <utility>          // Para usar swap

BubbleSort::BubbleSort(int cantidad) 
{
    reiniciar(cantidad);
}

void BubbleSort::reiniciar(int cantidad) 
{
    tamaño = cantidad;
    pasada = 0;
    pos = 0;
    listo = (cantidad < 2);   // Con 0 o 1 elementos no hay nada que ordenar
}

void BubbleSort::paso(std::vector<int>& valores) 
{
    if (listo) return;

    // Compara el par actual y los intercambia si están al revés
    if (valores[pos] > valores[pos + 1])
        std::swap(valores[pos], valores[pos + 1]);

    pos++;

    // ¿Terminó esta pasada? (cada pasada deja una barra más en su lugar)
    if (pos >= tamaño - 1 - pasada) 
    {
        pos = 0;
        pasada++;
        if (pasada >= tamaño - 1)
            listo = true;
    }
}

bool BubbleSort::terminado() const { return listo; }
int BubbleSort::posicion() const { return pos; }
int BubbleSort::fijados() const { return pasada; }

