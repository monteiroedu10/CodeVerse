#include <SDL2/SDL.h>
#include <iostream>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int CELL_SIZE = 20;

void renderMaze(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Cor branca
    SDL_RenderClear(renderer);

    // Desenhe o labirinto (substitua este código pelo seu próprio)
    for (int y = 0; y < SCREEN_HEIGHT / CELL_SIZE; ++y) {
        for (int x = 0; x < SCREEN_WIDTH / CELL_SIZE; ++x) {
            SDL_Rect rect = {x * CELL_SIZE, y * CELL_SIZE, CELL_SIZE, CELL_SIZE};

            // Desenhe elementos do labirinto
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Cor preta para paredes
            SDL_RenderDrawRect(renderer, &rect);

            // Desenhe outros elementos do labirinto aqui (caminhos, entrada, saída, etc.)
        }
    }

    SDL_RenderPresent(renderer);
}

int main() {
    SDL_Window* window;
    SDL_Renderer* renderer;

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "Erro ao inicializar o SDL: " << SDL_GetError() << std::endl;
        return 1;
    }

    if (SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0, &window, &renderer) != 0) {
        std::cerr << "Erro ao criar janela e renderer: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_SetWindowTitle(window, "Labirinto SDL");

    bool quit = false;
    SDL_Event event;

    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
        }

        renderMaze(renderer); // Renderize o labirinto

        SDL_Delay(100); // Adicione um pequeno atraso para evitar o uso excessivo da CPU
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
