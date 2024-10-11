#include <iostream>
#include <SDL2/SDL.h>
using namespace std;


class Graph {
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
                    cout << "X ";  // obstáculo
                } else {
                    cout << ". ";  // celda libre
                }
            }
            cout << "\n";
        }
    }



    void render(SDL_Renderer* renderer) {
        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                int currentNode = r * cols + c;
                SDL_Rect cell;
                cell.x = c * TILE_SIZE;
                cell.y = r * TILE_SIZE;
                cell.w = TILE_SIZE;
                cell.h = TILE_SIZE;

                // Si hay un obstáculo, dibuja una celda negra
                if (isObstacle[currentNode]) {
                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Color negro para obstáculos
                } else {
                    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Color blanco para espacios libres
                }

                SDL_RenderFillRect(renderer, &cell);
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Dibujar borde de la celda
                SDL_RenderDrawRect(renderer, &cell);
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