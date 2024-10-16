#include <iostream>
#include <QPainter>
#include <QWidget>
#include <iostream>
using namespace std;


class Graph: public QWidget {
private:
    bool** adjMatrix;
    bool* isObstacle;
    int numVertices;
    int rows, cols;
    const int TILE_SIZE = 40;

public:
    Graph(int rows, int cols) {
        this->rows = rows;
        this->cols = cols;
        numVertices = rows * cols;

        adjMatrix = new bool*[numVertices];
        for (int i = 0; i < numVertices; i++) {
            adjMatrix[i] = new bool[numVertices];
            for (int j = 0; j < numVertices; j++)
                adjMatrix[i][j] = false;
        }

        isObstacle = new bool[numVertices];
        for (int i = 0; i < numVertices; i++) {
            isObstacle[i] = false;
        }

        generateRandomMap();
    }

    int Random(int max) {
        static unsigned long seed = reinterpret_cast<unsigned long>(this);
        seed = (214013 * seed + 2531011);
        return (seed >> 16) % max;
    }

    void generateRandomMap() {
        conexionesNodos();
        randomObstacles();
    }

    void conexionesNodos() {
        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                int currentNode = r * cols + c;
                if (r > 0) addEdge(currentNode, (r - 1) * cols + c); // Arriba
                if (r < rows - 1) addEdge(currentNode, (r + 1) * cols + c); // Abajo
                if (c > 0) addEdge(currentNode, r * cols + (c - 1)); // Izquierda
                if (c < cols - 1) addEdge(currentNode, r * cols + (c + 1)); // Derecha
            }
        }
    }

    void randomObstacles() {
        int maxObstacles = numVertices / 3;
        int obstaclesPlaced = 0;

        while (obstaclesPlaced < maxObstacles) {
            int randomCell = Random(numVertices);

            if (!isObstacle[randomCell]) {
                isObstacle[randomCell] = true;
                if (!areaAccesible()) {
                    isObstacle[randomCell] = false;
                } else {
                    obstaclesPlaced++;
                }
            }
        }
    }

    void addEdge(int i, int j) {
        adjMatrix[i][j] = true;
        adjMatrix[j][i] = true;
    }

    bool areaAccesible() {
        bool* visited = new bool[numVertices]();
        int startNode = -1;

        for (int i = 0; i < numVertices; i++) {
            if (!isObstacle[i]) {
                startNode = i;
                break;
            }
        }

        if (startNode == -1) {
            delete[] visited;
            return true;
        }

        DFS(startNode, visited);

        bool conectados = true;
        for (int i = 0; i < numVertices; i++) {
            if (!isObstacle[i] && !visited[i]) {
                conectados = false;
                break;
            }
        }

        delete[] visited;
        return conectados;
    }

    void DFS(int startNode, bool* visited) {
        int* stack = new int[numVertices];
        int top = -1;

        stack[++top] = startNode;
        visited[startNode] = true;

        while (top != -1) {
            int currentNode = stack[top--];

            for (int i = 0; i < numVertices; i++) {
                if (adjMatrix[currentNode][i] && !visited[i]) {
                    visited[i] = true;
                    stack[++top] = i;
                }
            }
        }

        delete[] stack;
    }

    void mapaobstacles() {
        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                int currentNode = r * cols + c;
                if (isObstacle[currentNode]) {
                    cout << "X ";
                } else {
                    cout << ". ";
                }
            }
            cout << "\n";
        }
    }



    void render(QPainter &painter) {
        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                int currentNode = r * cols + c;
                QRect cell(c * TILE_SIZE, r * TILE_SIZE, TILE_SIZE, TILE_SIZE);


                if (isObstacle[currentNode]) {
                    painter.setBrush(Qt::black);
                } else {
                    painter.setBrush(Qt::white);
                }

                painter.drawRect(cell);
                painter.fillRect(cell, painter.brush());
            }
        }
    }


    ~Graph() {
        for (int i = 0; i < numVertices; i++)
            delete[] adjMatrix[i];
        delete[] adjMatrix;
        delete[] isObstacle;
    }
};