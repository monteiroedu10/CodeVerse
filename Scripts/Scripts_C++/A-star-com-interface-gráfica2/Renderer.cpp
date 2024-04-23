#include "Renderer.hpp"
#include <iostream>

Renderer::Renderer(const std::vector<std::vector<int>>& maze, const std::vector<std::pair<int, int>>& path, int scale) {
    // Inicializar a SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "Erro ao inicializar a SDL: " << SDL_GetError() << std::endl;
        return;
    }

    // Definir as dimensões desejadas da janela
    int windowWidth = 1920;
    int windowHeight = 1080;

    // Criar a janela
    window = SDL_CreateWindow("Labirinto", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "Erro ao criar a janela: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return;
    }

    // Criar o renderizador
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Erro ao criar o renderizador: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return;
    }

    // Definir a escala
    this->scale = scale;
    this->maze = maze;
    this->path = path;
}

Renderer::~Renderer() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Renderer::render() {
    SDL_Event e;
    bool quit = false;
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        renderMaze();
        renderPath();

        SDL_RenderPresent(renderer);
    }
}

void Renderer::renderMaze() {
    int mazeWidth = maze[0].size() * scale;
    int mazeHeight = maze.size() * scale;

    for (size_t i = 0; i < maze.size(); ++i) {
        for (size_t j = 0; j < maze[i].size(); ++j) {
            SDL_Rect cellRect = {static_cast<int>(j * scale), static_cast<int>(i * scale), scale, scale};
            if (maze[i][j] == 1) { // Obstáculo
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                SDL_RenderFillRect(renderer, &cellRect);
            }
        }
    }
}

void Renderer::renderPath() {
    for (const auto& point : path) {
        SDL_Rect cellRect = {static_cast<int>(point.second * scale), static_cast<int>(point.first * scale), scale, scale};
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        SDL_RenderFillRect(renderer, &cellRect);
    }
}