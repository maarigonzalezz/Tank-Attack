#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "raylib.h"

struct Node {
    int row, col;
    bool isObstacle;
    std::vector<Node*> neighbors;

    Node(int r, int c) : row(r), col(c), isObstacle(false) {}
};

class Graph {
public:
    int rows, cols;
    std::vector<std::vector<Node*>> grid;

    Graph(int r, int c) : rows(r), cols(c) {
        // Inicializar la grilla con nodos
        grid.resize(rows);
        for (int i = 0; i < rows; i++) {
            grid[i].resize(cols);
            for (int j = 0; j < cols; j++) {
                grid[i][j] = new Node(i, j);
            }
        }
        // Conectar nodos adyacentes
        connectNodes();
    }

    ~Graph() {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                delete grid[i][j];
            }
        }
    }

    void connectNodes() {
        // Conectar cada nodo con sus vecinos adyacentes
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (i > 0) grid[i][j]->neighbors.push_back(grid[i - 1][j]); // Arriba
                if (i < rows - 1) grid[i][j]->neighbors.push_back(grid[i + 1][j]); // Abajo
                if (j > 0) grid[i][j]->neighbors.push_back(grid[i][j - 1]); // Izquierda
                if (j < cols - 1) grid[i][j]->neighbors.push_back(grid[i][j + 1]); // Derecha
            }
        }
    }

    void generateRandomObstacles(int numObstacles) {
        srand(static_cast<unsigned int>(time(0)));
        int count = 0;

        // Definir los índices de las columnas permitidas para generar obstáculos
        int startCol = 4; // Ahora comienza en la cuarta columna (índice 3)
        int endCol = cols - 1; // Sigue siendo la antepenúltima columna

        while (count < numObstacles) {
            int randRow = rand() % rows;
            int randCol = startCol + (rand() % (endCol - startCol + 1)); // Genera una columna dentro del rango permitido

            // Solo crea un obstáculo si no hay otro obstáculo en esa posición
            if (!grid[randRow][randCol]->isObstacle) {
                grid[randRow][randCol]->isObstacle = true;
                count++;
            }
        }
    }

    bool isObstacle(int row, int col) {
        return grid[row][col]->isObstacle;
    }

    // Método para generar una matriz de adyacencia
    std::vector<std::vector<int>> generateAdjacencyMatrix() {
        std::vector<std::vector<int>> adjMatrix(rows, std::vector<int>(cols, 0));  // Matriz de adyacencia
        // Recorrer todos los nodos
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (isObstacle(i, j)) {
                    adjMatrix[i][j] = 1;
                }
            }
        }
        return adjMatrix;
    }

    void printAdjacencyMatrix(const std::vector<std::vector<int>>& adjMatrix) {
        int n = adjMatrix.size();  // Tamaño de la matriz (nodos)

        // Recorrer la matriz y imprimir cada fila
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                std::cout << adjMatrix[i][j] << " ";  // Imprimir cada elemento
            }
            std::cout << std::endl;  // Cambiar de línea al final de cada fila
        }
    }
};