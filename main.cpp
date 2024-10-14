#include <QApplication>
#include <QtWidgets>
#include <QtCore>
#include "Game.h"
#include <QTimer>
#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // Crear la ventana principal
    QMainWindow window;
    window.setWindowTitle("Tank Attack!");
    window.resize(900, 600);

    // Crear el botón PLAY
    QPushButton *button = new QPushButton("PLAY", &window);
    button->setGeometry(QRect(QPoint(350, 500), QSize(200, 50)));

    // Crear la instancia de Game (ventana de juego)
    Game game;
    QLabel *timerLabel = new QLabel(&game);  // Etiqueta para mostrar el temporizador
    timerLabel->setGeometry(20, 880, 250, 50);  // Posición y tamaño del label
    QFont font = timerLabel->font();
    font.setPointSize(17);  // Ajustar el tamaño de la fuente
    timerLabel->setFont(font);

    // Crear variables para el tiempo restante
    int timeRemaining = 300;  // 5 minutos (300 segundos)

    // Crear el temporizador que actualizará el tiempo cada segundo
    QTimer updateTimer;
    updateTimer.setInterval(1000);  // Intervalo de 1 segundo

    // Crear el temporizador para cerrar el juego
    QTimer gameTimer;
    gameTimer.setInterval(300000);  // Intervalo de 5 minutos (300,000 ms)

    // Conectar el botón "PLAY"
    QObject::connect(button, &QPushButton::clicked, [&]() {
        cout << "Iniciando juego..." << endl;

        // Reiniciar el tiempo restante y el label
        timeRemaining = 300;  // Reiniciar a 5 minutos
        timerLabel->setText("Tiempo restante: 5:00");

        // Mostrar la ventana de juego
        game.resize(1120, 925);
        game.show();

        // Detener conexiones previas del temporizador
        if (updateTimer.isActive()) {
            updateTimer.stop();  // Asegurarse de que el temporizador esté detenido
        }

        // Iniciar ambos temporizadores
        updateTimer.start();
        gameTimer.start();

        // Conectar el temporizador que actualiza el tiempo restante (solo una vez)
        static bool timerConnected = false;
        if (!timerConnected) {
            QObject::connect(&updateTimer, &QTimer::timeout, [&]() {
                timeRemaining--;
                int minutes = timeRemaining / 60;
                int seconds = timeRemaining % 60;
                timerLabel->setText(QString("Tiempo restante: %1:%2")
                                    .arg(minutes)
                                    .arg(seconds, 2, 10, QLatin1Char('0')));  // Formato mm:ss

                if (timeRemaining == 0) {
                    updateTimer.stop();  // Detener el temporizador de actualización
                }
            });
            timerConnected = true;  // Solo conectar una vez
        }

        // Conectar el temporizador que cierra el juego
        QObject::connect(&gameTimer, &QTimer::timeout, [&game, &updateTimer]() {
            game.close();  // Cierra la ventana del juego
            updateTimer.stop();  // Detener la actualización del tiempo
            cout << "Juego cerrado automáticamente después de 5 minutos." << endl;
        });
    });

    // Mostrar la ventana principal
    window.show();

    return app.exec();
}
