#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <vector>
#include <SDL2/SDL.h>

class Renderer {
public:
    Renderer(const std::vector<std::vector<int>>& maze, const std::vector<std::pair<int, int>>& path, int scale);
    ~Renderer();
    void render();

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    int scale;
    std::vector<std::vector<int>> maze;
    std::vector<std::pair<int, int>> path;

    void renderMaze();
    void renderPath();
};

#endif // RENDERER_HPP