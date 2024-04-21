#include "Node.hpp"

Node::Node(int _x, int _y, double _cost, double _heuristic, Node* _parent) : x(_x), y(_y), cost(_cost), heuristic(_heuristic), parent(_parent) {}

double Node::getTotalCost() const {
    return cost + heuristic;
}

bool CompareNode::operator()(const Node* lhs, const Node* rhs) const {
    return lhs->getTotalCost() > rhs->getTotalCost();
}

double heuristic(int x, int y, int targetX, int targetY) {
    return abs(targetX - x) + abs(targetY - y);
}
