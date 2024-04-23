#include <iostream>
#include <vector>
#include "AStar.hpp"
#include "Renderer.hpp"

int main() {
    // Lendo o labirinto do arquivo
    std::vector<std::vector<int>> maze = readMazeFromFile("labirinto.txt");
    if (maze.empty()) {
        return 1; // Se houver erro ao ler o arquivo, encerra o programa
    }

    // Encontrando as coordenadas do ponto inicial e da saída
    int startX = -1, startY = -1, targetX = -1, targetY = -1;
    for (int i = 0; i < maze.size(); ++i) {
        for (int j = 0; j < maze[i].size(); ++j) {
            if (maze[i][j] == 2) {
                startX = i;
                startY = j;
            } else if (maze[i][j] == 3) {
                targetX = i;
                targetY = j;
            }
        }
    }

    // Verificando se as coordenadas foram encontradas
    if (startX == -1 || startY == -1 || targetX == -1 || targetY == -1) {
        std::cerr << "Labirinto inválido: ponto inicial ou saída não encontrados." << std::endl;
        return 1;
    }

    // Resolvendo o labirinto usando o algoritmo A*
    std::vector<std::pair<int, int>> path = aStar(maze, startX, startY, targetX, targetY);

    // Imprimindo o caminho encontrado
    if (!path.empty()) {
        std::cout << "Caminho encontrado:" << std::endl;
        for (const auto& point : path) {
            std::cout << "(" << point.first +1 << ", " << point.second + 1 << ")" << std::endl;
        }
    } else {
        std::cout << "Não foi possível encontrar um caminho." << std::endl;
    }

    // Criar um objeto Renderer e renderizar o labirinto e o caminho
    Renderer renderer(maze, path, 40);
    renderer.render();

    return 0;
}

