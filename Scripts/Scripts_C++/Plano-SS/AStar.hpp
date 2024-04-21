#ifndef ASTAR_HPP
#define ASTAR_HPP

#include <vector>
#include <queue>
#include <climits>
#include <fstream>
#include <iostream>
#include "Node.hpp"

// Função A* para resolver o labirinto
std::vector<std::pair<int, int>> aStar(std::vector<std::vector<int>>& maze, int startX, int startY, int targetX, int targetY);

// Função para ler o labirinto de um arquivo
std::vector<std::vector<int>> readMazeFromFile(const std::string& filename);

#endif // ASTAR_HPP
