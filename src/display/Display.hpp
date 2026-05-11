#pragma once
#include <cstdint>
#include <string>
#include <SDL2/SDL.h>

#define DISPLAY_SCALE 3

class Display {
public:
    Display();
    ~Display();

    bool    init(const std::string& title);
    void    destroy();

    void    update(const uint32_t* framebuffer);
    bool    pollEvents(SDL_Event& event);

    bool    isOpen() const { return window != nullptr; }

private:
    SDL_Window*     window;
    SDL_Renderer*   renderer;
    SDL_Texture*    texture;
};
