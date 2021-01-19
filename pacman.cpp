#include <iostream>
#include <SDL2/SDL.h>

using namespace std;
enum KeyPressSurfaces {
    KEY_PRESS_SURFACE_DEFAULT,
    KEY_PRESS_SURFACE_LEFT,
    KEY_PRESS_SURFACE_UP,
    KEY_PRESS_SURFACE_RIGHT,
    KEY_PRESS_SURFACE_DOWN,
    KEY_PRESS_SURFACE_TOTAL
};

const int SCREEN_WIDTH = 3440;
const int SCREEN_HEIGHT = 1440;

bool init(SDL_Window** window, SDL_Surface** surface);
bool load_image(SDL_Surface* surface, const char* image_path);
void main_loop(SDL_Window* window, SDL_Surface* surface);
void update(SDL_Window* window);
void close(SDL_Window* window);


int main(int argc, char* args[]) {
    SDL_Window* window = nullptr;
    SDL_Surface* surface = nullptr;
    const char* image_path = "images/hello_world.bmp";

    if (!init(&window, &surface))
        cout << "Initialization failed!\n";

    main_loop(window, surface);
    close(window);
    return 0;
}

void main_loop(SDL_Window* window, SDL_Surface* surface) {
    SDL_Event e;
    while (true) {
        while(SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT)
                return;
            if (e.type == KEY_PRESS_SURFACE_DOWN) {
                load_image(surface, "images/hello_world.bmp");
                update(window);
            }
        }
    }
}

bool init(SDL_Window** window, SDL_Surface** surface) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cout << "SDL could not initialize!\n";
        return false;
    }
    else {
        *window = SDL_CreateWindow("Pacman", SDL_WINDOWPOS_UNDEFINED, 
        SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (window == nullptr) {
            cout << "Window could not be created!\n";
            return false;
        }
        else {
            *surface = SDL_GetWindowSurface(*window);
        }
    }
    return true;
}

bool load_image(SDL_Surface* surface, const char* image_path) {
    SDL_Surface* image = SDL_LoadBMP(image_path);
    if (image == nullptr)
        return false;
    SDL_BlitSurface(image, NULL, surface, NULL);
    return true;
}

void update(SDL_Window* window) {
    SDL_UpdateWindowSurface(window);
}

void close(SDL_Window* window) {
    SDL_DestroyWindow(window);
    SDL_Quit();
}