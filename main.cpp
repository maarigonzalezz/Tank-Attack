#include <QApplication>
#include <QtWidgets>
#include <QtCore>
#include "Game.h"
#include <QTimer>
#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);


    QMainWindow window;
    window.setWindowTitle("Tank Attack!");
    window.resize(900, 600);


    QPushButton *button = new QPushButton("PLAY", &window);
    button->setGeometry(QRect(QPoint(350, 500), QSize(200, 50)));


    Game game;
    QLabel *timerLabel = new QLabel(&game);
    timerLabel->setGeometry(20, 880, 250, 50);
    QFont font = timerLabel->font();
    font.setPointSize(17);
    timerLabel->setFont(font);


    QLabel *turnLabel = new QLabel("Turno: Player 1", &game);
    turnLabel->setGeometry(300, 880, 250, 50);
    turnLabel->setFont(font);



    int timeRemaining = 300;
    int currentPlayer = 1;


    QTimer updateTimer;
    updateTimer.setInterval(1000);

    QTimer turnTimer;
    turnTimer.setInterval(25000);



    QTimer gameTimer;
    gameTimer.setInterval(300000);


    QObject::connect(button, &QPushButton::clicked, [&]() {
        cout << "Iniciando juego..." << endl;


        timeRemaining = 300;  // Reiniciar a 5 minutos
        timerLabel->setText("Tiempo restante: 5:00");
        turnLabel->setText("Turno: Player 1");
        currentPlayer = 1;


        game.resize(1120, 925);
        game.show();


        if (updateTimer.isActive()) {
            updateTimer.stop();
            turnTimer.stop();
        }


        updateTimer.start();
        turnTimer.start();
        gameTimer.start();


        static bool timerConnected = false;
        if (!timerConnected) {
            QObject::connect(&updateTimer, &QTimer::timeout, [&]() {
                timeRemaining--;
                int minutes = timeRemaining / 60;
                int seconds = timeRemaining % 60;
                timerLabel->setText(QString("Tiempo restante: %1:%2")
                                    .arg(minutes)
                                    .arg(seconds, 2, 10, QLatin1Char('0')));

                if (timeRemaining == 0) {
                    updateTimer.stop();
                    turnTimer.stop();
                }
            });
            timerConnected = true;
        }


        static bool turnConnected = false;
        if (!turnConnected) {
            QObject::connect(&turnTimer, &QTimer::timeout, [&]() {
                currentPlayer = (currentPlayer == 1) ? 2 : 1;
                turnLabel->setText(QString("Turno: Player %1").arg(currentPlayer));
            });
            turnConnected = true;
        }



        QObject::connect(&gameTimer, &QTimer::timeout, [&game, &updateTimer, &turnTimer]() {
            game.close();
            turnTimer.stop();
            updateTimer.stop();
            cout << "Juego cerrado automáticamente después de 5 minutos." << endl;
        });
    });


    window.show();

    return app.exec();
}
