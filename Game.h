#include "development.cpp"
#include <iostream>
#include <QWindow>
#include <QOpenGLFunctions>
#include <QOpenGLContext>
#include <QMainWindow>
#include <QKeyEvent>
#include <QWidget>

class Game : public QMainWindow {
    Q_OBJECT  // Si estás usando señales y slots

public:
    Game(QWidget *parent = nullptr);  // Constructor

protected:
    void keyPressEvent(QKeyEvent *event) override;  // Sobrescribe el evento de teclado
    void paintEvent(QPaintEvent *event) override;    // Sobrescribe el evento de pintura

private:
    Graph graph;         // Instancia del grafo
    void setupUI();      // Configura la interfaz de usuario
};





//#endif //GAME_H
