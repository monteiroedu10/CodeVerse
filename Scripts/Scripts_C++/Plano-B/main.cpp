#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <cmath>
#include <climits>
#include <algorithm> // Para usar a função reverse

using namespace std;

// Definição da estrutura do nó
struct Node {
    int x, y; // coordenadas do nó
    double cost; // custo do caminho até este nó
    double heuristic; // valor heurístico (estimativa do custo restante até o destino)
    Node* parent; // ponteiro para o nó pai

    Node(int _x, int _y, double _cost, double _heuristic, Node* _parent) : x(_x), y(_y), cost(_cost), heuristic(_heuristic), parent(_parent) {}

    // Função de custo total (f = g + h)
    double getTotalCost() const {
        return cost + heuristic;
    }
};

// Comparador para a fila de prioridade (menor custo total tem prioridade)
struct CompareNode {
    bool operator()(const Node* lhs, const Node* rhs) const {
        return lhs->getTotalCost() > rhs->getTotalCost();
    }
};

// Função heurística simples (distância de Manhattan)
double heuristic(int x, int y, int targetX, int targetY) {
    return abs(targetX - x) + abs(targetY - y);
}

// Função A* para resolver o labirinto
vector<pair<int, int>> aStar(vector<vector<int>>& maze, int startX, int startY, int targetX, int targetY) {
    priority_queue<Node*, vector<Node*>, CompareNode> pq;

    // Adicionando o nó inicial à fila de prioridade
    pq.push(new Node(startX, startY, 0.0, heuristic(startX, startY, targetX, targetY), nullptr));

    // Vetor para armazenar os custos mínimos até cada posição
    vector<vector<double>> minCost(maze.size(), vector<double>(maze[0].size(), INT_MAX));
    minCost[startX][startY] = 0.0;

    while (!pq.empty()) {
        // Pegando o nó com menor custo total da fila de prioridade
        Node* current = pq.top();
        pq.pop();

        // Verificando se chegamos ao destino
        if (current->x == targetX && current->y == targetY) {
            // Reconstruindo o caminho a partir do nó final
            vector<pair<int, int>> path;
            while (current != nullptr) {
                path.emplace_back(current->x, current->y);
                current = current->parent;
            }
            reverse(path.begin(), path.end()); // Invertendo o caminho
            return path;
        }

        // Explorando os vizinhos
        for (int i = -1; i <= 1; ++i) {
            for (int j = -1; j <= 1; ++j) {
                if (i == 0 && j == 0) continue;
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

// Função para ler o labirinto de um arquivo
vector<vector<int>> readMazeFromFile(const string& filename) {
    vector<vector<int>> maze;
    ifstream file(filename);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            vector<int> row;
            for (char c : line) {
                row.push_back(c - '0'); // converte caractere para inteiro
            }
            maze.push_back(row);
        }
        file.close();
    } else {
        cerr << "Erro ao abrir o arquivo: " << filename << endl;
    }
    return maze;
}

int main() {
    // Lendo o labirinto do arquivo
    vector<vector<int>> maze = readMazeFromFile("labirinto.txt");
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
        cerr << "Labirinto inválido: ponto inicial ou saída não encontrados." << endl;
        return 1;
    }

    // Resolvendo o labirinto usando o algoritmo A*
    vector<pair<int, int>> path = aStar(maze, startX, startY, targetX, targetY);

    // Imprimindo o caminho encontrado
    if (!path.empty()) {
        cout << "Caminho encontrado:" << endl;
        for (const auto& point : path) {
            cout << "(" << point.first << ", " << point.second << ")" << endl;
        }
    } else {
        cout << "Não foi possível encontrar um caminho." << endl;
    }

    return 0;
}