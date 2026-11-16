#include <SFML/Graphics.hpp>  // Ventanas, formas, colores y eventos de SFML
#include <optional>           // std::optional: en SFML 3, pollEvent() devuelve un evento "opcional"
#include <vector>             // Arreglo dinámico para guardar las alturas de las barras
#include <algorithm>          // std::max, para que el retraso nunca baje de 1 ms
#include "Utilidades.hpp"     // generarValores()
#include "BubbleSort.hpp"     // Clase de BubbleSort

int main() 
{
    const int ANCHO = 900;
    const int ALTO = 500;
    const int CANTIDAD = 60;
    const float anchoBarra = static_cast<float>(ANCHO) / CANTIDAD;

    sf::RenderWindow ventana(sf::VideoMode({ANCHO, ALTO}), "Visualizador de ordenamientos");
    ventana.setFramerateLimit(60);

    std::vector<int> valores = generarValores(CANTIDAD, ALTO - 20);
    BubbleSort burbuja(CANTIDAD);
    bool ejecutando = false;
    sf::Clock reloj;        // Mide cuánto tiempo pasó desde el último paso
    int retrasoMs = 100;    // Milisegundos entre cada paso (más alto = más lento)

    // Ciclo principal: se repite mientras la ventana esté abierta
    while (ventana.isOpen()) 
    {
        // 1) ENTRADA: pollEvent() devuelve un evento o nada si no hay pendientes
        while (const std::optional evento = ventana.pollEvent()) 
        {
            if (evento->is<sf::Event::Closed>())
                ventana.close();

            if (const auto* tecla = evento->getIf<sf::Event::KeyPressed>()) 
            {
                if (tecla->code == sf::Keyboard::Key::R)            // R: barras nuevas
                {         
                    valores = generarValores(CANTIDAD, ALTO - 20);
                    burbuja.reiniciar(CANTIDAD);
                    ejecutando = false;
                }
                if (tecla->code == sf::Keyboard::Key::Space)       // Espacio: iniciar/pausar
                    ejecutando = !ejecutando;
                if (tecla->code == sf::Keyboard::Key::Up)           // Flecha arriba: más rápido
                    retrasoMs = std::max(1, retrasoMs - 20);
                if (tecla->code == sf::Keyboard::Key::Down)         // Flecha abajo: más lento
                    retrasoMs += 20;
            }
        }

        // 2) ACTUALIZACIÓN: da un paso solo si ya pasó el tiempo de retraso
        if (ejecutando && reloj.getElapsedTime().asMilliseconds() >= retrasoMs) 
        {
            burbuja.paso(valores);
            reloj.restart();    // Reinicia la cuenta para el siguiente paso
        }

        // 3) DIBUJO
        ventana.clear(sf::Color(20, 20, 30));

        for (int i = 0; i < CANTIDAD; i++) 
        {
            sf::Color color(80, 160, 255);                          // Azul: normal

            if (burbuja.terminado() || i >= CANTIDAD - burbuja.fijados())
                color = sf::Color(80, 220, 120);                    // Verde: ya en su lugar
            else if (i == burbuja.posicion() || i == burbuja.posicion() + 1)
                color = sf::Color(255, 90, 90);                     // Rojo: comparando

            sf::RectangleShape barra(sf::Vector2f(anchoBarra - 2, static_cast<float>(valores[i])));
            barra.setPosition({i * anchoBarra, static_cast<float>(ALTO - valores[i])});
            barra.setFillColor(color);
            ventana.draw(barra);
        }

        ventana.display();
    }

    return 0;
}