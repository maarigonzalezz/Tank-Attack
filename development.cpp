#include <iostream>
using namespace std;

class Graph {
private:
    bool** adjMatrix;
    bool* isObstacle;
    int numVertices;
    int rows, cols; //dimension de cuadricula por si luego quiero cambiarlas

public:

    Graph(int rows, int cols, bool* obstacles) {
        this->rows = rows;
        this->cols = cols;
        numVertices = rows * cols; // Total de nodos en la cuadrícula

        adjMatrix = new bool*[numVertices];
        for (int i = 0; i < numVertices; i++) {
            adjMatrix[i] = new bool[numVertices];
            for (int j = 0; j < numVertices; j++)
                adjMatrix[i][j] = false;
        }


        isObstacle = new bool[numVertices];
        for (int i = 0; i < numVertices; i++) {
            isObstacle[i] = obstacles[i]; // Inicializa los obstáculos
        }


        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                int currentNode = r * cols + c;

                if (!isObstacle[currentNode]) { // Solo conecta si no es un obstáculo
                    if (r > 0 && !isObstacle[(r - 1) * cols + c]) addEdge(currentNode, (r - 1) * cols + c); // Arriba
                    if (r < rows - 1 && !isObstacle[(r + 1) * cols + c]) addEdge(currentNode, (r + 1) * cols + c); // Abajo
                    if (c > 0 && !isObstacle[r * cols + (c - 1)]) addEdge(currentNode, r * cols + (c - 1)); // Izquierda
                    if (c < cols - 1 && !isObstacle[r * cols + (c + 1)]) addEdge(currentNode, r * cols + (c + 1)); // Derecha
                }
            }
        }
    }


    void addEdge(int i, int j) {
        adjMatrix[i][j] = true;
        adjMatrix[j][i] = true;
    }


    bool areAllAccessibleNodesConnected() {
        bool* visited = new bool[numVertices]();
        int startNode = -1;

        // Encuentra un nodo accesible para comenzar
        for (int i = 0; i < numVertices; i++) {
            if (!isObstacle[i]) {
                startNode = i;
                break;
            }
        }

        // Si no hay nodos accesibles, retornamos true
        if (startNode == -1) {
            delete[] visited;
            return true;
        }

        // Realiza DFS desde el nodo accesible encontrado
        DFS(startNode, visited);

        // Verifica si todos los nodos accesibles fueron visitados
        bool allConnected = true;
        for (int i = 0; i < numVertices; i++) {
            if (!isObstacle[i] && !visited[i]) {
                allConnected = false;
                break;
            }
        }

        delete[] visited;
        return allConnected;
    }

    void removeEdge(int i, int j) {
        adjMatrix[i][j] = false;
        adjMatrix[j][i] = false;
    }

    void DFS(int currentNode, bool* visited) {
        visited[currentNode] = true;
        cout << "visitando node: " << currentNode << endl;

        for (int i = 0; i < numVertices; i++) {
            if (adjMatrix[currentNode][i] && !visited[i]) {
                DFS(i, visited);
            }
        }
    }

    int getNumVertices() const {
        return numVertices;
    }

    void toString() {
        for (int i = 0; i < numVertices; i++) {
            cout << i << " : ";
            for (int j = 0; j < numVertices; j++)
                cout << adjMatrix[i][j] << " ";
            cout << "\n";
        }
    }

    ~Graph() {
        for (int i = 0; i < numVertices; i++)
            delete[] adjMatrix[i];
        delete[] adjMatrix;
        delete[] isObstacle;
    }
};

