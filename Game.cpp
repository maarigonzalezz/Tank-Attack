#include "Game.h"

// Implementación del constructor
Game::Game(QWidget *parent)
    : QMainWindow(parent), graph(10, 10) { // Inicializa el grafo con un tamaño de 10x10
    setupUI();  // Llama a la función para configurar la interfaz
}

// Implementación de la función para configurar la interfaz
void Game::setupUI() {
    setWindowTitle("Tank Attack!");  // Establece el título de la ventana
    resize(800, 600);  // Establece el tamaño de la ventana
}

// Implementación del evento de teclado
void Game::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Escape) {
        close();  // Cierra la ventana si se presiona la tecla Esc
    }
}

// Implementación del evento de pintura
void Game::paintEvent(QPaintEvent *event) {
    QPainter painter(this);  // Crea un QPainter para la ventana
    graph.render(painter);   // Llama al método de renderizado del grafo
}