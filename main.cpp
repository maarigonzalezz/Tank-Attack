
#include <QApplication>
#include <QtWidgets>  // Agrupa todos los widgets como QPushButton, QApplication, QMainWindow, etc.
#include <QtCore>
#include "Game.h"
#include <iostream>
/*#include <QMainWindow>
#include <QPushButton>
#include <QObject>
#include <QMessageBox>*/

using namespace std;

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);  // Inicializa la aplicación Qt

    QMainWindow window;  // Crea una ventana principal
    window.setWindowTitle("Tank Attack!");  // Establece el título de la ventana
    window.resize(900, 600);  // Establece el tamaño de la ventana

    // Crear un botón
    QPushButton *button = new QPushButton("PLAY", &window);  // Crea el botón y lo añade a la ventana
    button->setGeometry(QRect(QPoint(350, 500), QSize(200, 50)));

    // Crear la instancia de Game
    Game game;

    // Conectar la señal de clic del botón a una ranura (slot)
    QObject::connect(button, &QPushButton::clicked, [&]() {
        cout << "quiero dormir por fa sirva" << endl; // Asegúrate de usar endl para que la salida se muestre inmediatamente
        game.resize(1120, 880);  // Tamaño de la ventana del juego
        game.show();  // Mostrar la ventana del juego
        window.close();  // Cerrar la ventana principal
    });

    window.show();  // Muestra la ventana principal en pantalla

    return app.exec();  // Ejecuta el bucle de eventos de Qt
}