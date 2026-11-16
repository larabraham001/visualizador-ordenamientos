#pragma once
#include <vector>       // Para recibir el arreglo de valores

class BubbleSort
{
    private:
        int tamaño;     // Cantidad de elementos
        int pasada;     // Equivale a 'i' del for externo
        int pos;        // Equivale a 'j' del for interno
        bool listo;     // True cuando ya terminó
    public:
        explicit BubbleSort(int cantidad);
        
        void reiniciar(int cantidad);           // Vuelve al estado inicial
        void paso(std::vector<int>& valores);   // Hace UNA comparación
        bool terminado() const;                 // ¿Ya quedó ordenado?
        int posicion() const;                   // Índice que se está comparando
        int fijados() const;                    // Cuántas barras ya quedaron en su posición final
};