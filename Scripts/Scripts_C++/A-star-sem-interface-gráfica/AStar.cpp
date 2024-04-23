#include "AStar.hpp"
#include <queue> // Incluindo a biblioteca <queue> para priority_queue
#include <algorithm> // Incluindo a biblioteca <algorithm> para reverse

std::vector<std::pair<int, int>> aStar(std::vector<std::vector<int>>& maze, int startX, int startY, int targetX, int targetY) {
    std::priority_queue<Node*, std::vector<Node*>, CompareNode> pq;

    // Adicionando o nó inicial à fila de prioridade
    pq.push(new Node(startX, startY, 0.0, heuristic(startX, startY, targetX, targetY), nullptr));

    // Vetor para armazenar os custos mínimos até cada posição
    std::vector<std::vector<double>> minCost(maze.size(), std::vector<double>(maze[0].size(), INT_MAX));
    minCost[startX][startY] = 0.0;

    int iteration = 0; // Contador de iterações

    while (!pq.empty()) {
        ++iteration; // Incrementando o contador de iterações

        // Pegando o nó com menor custo total da fila de prioridade
        Node* current = pq.top();
        pq.pop();

        // Imprimindo a descrição da evolução
        std::cout << "i = " << iteration << "; pos = [" << current->x + 1 << "," << current->y + 1 << "]" << std::endl;

        // Verificando se chegamos ao destino
        if (current->x == targetX && current->y == targetY) {
            // Reconstruindo o caminho a partir do nó final
            std::vector<std::pair<int, int>> path;
            while (current != nullptr) {
                path.emplace_back(current->x, current->y);
                current = current->parent;
            }
            std::reverse(path.begin(), path.end()); // Invertendo o caminho
            return path;
        }

        // Explorando os vizinhos
        for (int i = -1; i <= 1; ++i) {
            for (int j = -1; j <= 1; ++j) {
            // Ignorando os movimentos diagonais e a posição atual
            if ((i != 0 && j != 0) || (i == 0 && j == 0)) continue;

            int newX = current->x + i;
            int newY = current->y + j;

            // Verificando se a posição está dentro dos limites do labirinto
            if (newX >= 0 && newX < maze.size() && newY >= 0 && newY < maze[0].size()) {
            // Verificando se o nó é acessível (não é um obstáculo)
            if (maze[newX][newY] != 1) {
                double newCost = current->cost + 1.0; // assumindo que todos os movimentos têm custo 1
                if (newCost < minCost[newX][newY]) {
                    minCost[newX][newY] = newCost;
                    double newHeuristic = heuristic(newX, newY, targetX, targetY);
                    pq.push(new Node(newX, newY, newCost, newHeuristic, current));
                }
            }
        }
    }
}

    }

    // Se chegarmos aqui, não há caminho possível
    return {};
}

std::vector<std::vector<int>> readMazeFromFile(const std::string& filename) {
    std::vector<std::vector<int>> maze;
    std::ifstream file(filename);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            std::vector<int> row;
            for (char c : line) {
                row.push_back(c - '0'); // converte caractere para inteiro
            }
            maze.push_back(row);
        }
        file.close();
    } else {
        std::cerr << "Erro ao abrir o arquivo: " << filename << std::endl;
    }
    return maze;
}

