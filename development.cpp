#include <iostream>
using namespace std;

class Graph {
private:
    bool** adjMatrix;
    bool* isObstacle;
    int numVertices;
    int rows, cols;

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
        static unsigned long seed = reinterpret_cast<unsigned long>(this); // Usa la dirección del objeto
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

    void DFS(int currentNode, bool* visited) {
        visited[currentNode] = true;
        for (int i = 0; i < numVertices; i++) {
            if (adjMatrix[currentNode][i] && !visited[i]) {
                DFS(i, visited);
            }
        }
    }

    void mapaobstacles() {
        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                int currentNode = r * cols + c;
                if (isObstacle[currentNode]) {
                    cout << "X ";  // obstáculo
                } else {
                    cout << ". ";  // celda libre
                }
            }
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