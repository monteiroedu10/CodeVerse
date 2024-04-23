#include <iostream>
#include <SDL2/SDL.h> // Incluindo o cabeçalho SDL

#include "AStar.hpp"

// Função para inicializar a SDL e criar uma janela
bool initSDL(SDL_Window*& window, SDL_Renderer*& renderer, int screenWidth, int screenHeight) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "Erro ao inicializar a SDL: " << SDL_GetError() << std::endl;
        return false;
    }

    window = SDL_CreateWindow("Labirinto", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        std::cerr << "Erro ao criar a janela: " << SDL_GetError() << std::endl;
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr) {
        std::cerr << "Erro ao criar o renderizador: " << SDL_GetError() << std::endl;
        return false;
    }

    return true;
}

// Função para desenhar o labirinto na janela
void drawMaze(SDL_Renderer* renderer, const std::vector<std::vector<int>>& maze, int cellSize) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // cor branca
    SDL_RenderClear(renderer);

    for (size_t i = 0; i < maze.size(); ++i) {
        for (size_t j = 0; j < maze[i].size(); ++j) {
            if (maze[i][j] == 1) { // obstáculo
                SDL_Rect obstacleRect = { static_cast<int>(j * cellSize), static_cast<int>(i * cellSize), cellSize, cellSize };
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // cor preta
                SDL_RenderFillRect(renderer, &obstacleRect);
            }
        }
    }

    SDL_RenderPresent(renderer);
}

// Função para desenhar o caminho na janela
void drawPath(SDL_Renderer* renderer, const std::vector<std::pair<int, int>>& path, int cellSize) {
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // cor verde

    for (const auto& point : path) {
        SDL_Rect cellRect = { point.second * cellSize, point.first * cellSize, cellSize, cellSize };
        SDL_RenderFillRect(renderer, &cellRect);
    }

    SDL_RenderPresent(renderer);
}

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

    // Defina as dimensões da janela e do labirinto
    int screenWidth = 800;
    int screenHeight = 600;
    int cellSize = std::min(screenWidth / maze[0].size(), screenHeight / maze.size());

    // Inicialize a SDL e crie uma janela
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    if (!initSDL(window, renderer, screenWidth, screenHeight)) {
        return 1;
    }

    // Exiba o labirinto inicial
    drawMaze(renderer, maze, cellSize);

    // Resolva o labirinto usando o algoritmo A*
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

    // Aguarde até que o usuário feche a janela
    bool quit = false;
    SDL_Event event;
    while (!quit) {
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
        }
    }

    // Libere os recursos da SDL
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

