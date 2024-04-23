#ifndef NODE_HPP
#define NODE_HPP

#include <cmath>

struct Node {
    int x, y; // coordenadas do nó
    double cost; // custo do caminho até este nó
    double heuristic; // valor heurístico (estimativa do custo restante até o destino)
    Node* parent; // ponteiro para o nó pai

    Node(int _x, int _y, double _cost, double _heuristic, Node* _parent);

    // Função de custo total (f = g + h)
    double getTotalCost() const;
};

// Comparador para a fila de prioridade (menor custo total tem prioridade)
struct CompareNode {
    bool operator()(const Node* lhs, const Node* rhs) const;
};

// Função heurística simples (distância de Manhattan)
double heuristic(int x, int y, int targetX, int targetY);

#endif // NODE_HPP
