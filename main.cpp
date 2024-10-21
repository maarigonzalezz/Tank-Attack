
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
    /*QApplication app(argc, argv);  // Inicializa la aplicación Qt

    QMainWindow window;  // Crea una ventana principal
    window.setWindowTitle("Tank Attack!");  // Establece el título de la ventana
    window.resize(800, 600);  // Establece el tamaño de la ventana

    // Crear un botón
    QPushButton *button = new QPushButton("Iniciar", &window);  // Crea el botón y lo añade a la ventana
    button->setGeometry(QRect(QPoint(300, 400), QSize(200, 50)));*/

    // Crear la instancia de Game
    Game game(true);
    cout << "trying" << endl;
    game.tGame(true);

    return 0;
}