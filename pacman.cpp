#include <iostream>
#include <SDL2/SDL.h>

using namespace std;

enum KEY_PRESS_SURFACES {
    LEFT,
    UP,
    RIGHT,
    DOWN,
    DEFAULT,
    LENGTH
};

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
SDL_Surface* g_key_surfaces[LENGTH];

void main_loop(SDL_Window* window, SDL_Surface* screen_surface);
bool init(SDL_Window** window, SDL_Surface** screen_surface);
bool load_media();
SDL_Surface* load_surface(const char* image_path);
void update(SDL_Window* window);
void close(SDL_Window* window, SDL_Surface* screen_surface); 

int main(int argc, char* args[]) {
    SDL_Window* window = nullptr;
    SDL_Surface* screen_surface = nullptr;

    if (!init(&window, &screen_surface))
        cout << "Initialization failed!\n";

    if (!load_media())
        cout << "Loading media failed!\n";

    main_loop(window, screen_surface);
    close(window, screen_surface);
    return 0;
}

void main_loop(SDL_Window* window, SDL_Surface* screen_surface) {
    SDL_Surface* curr_surface = g_key_surfaces[DEFAULT];
    SDL_BlitSurface(curr_surface, NULL, screen_surface, NULL);
    update(window);
    SDL_Event e;
    while (true) {
        while(SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT)
                return;
            else if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    case SDLK_LEFT:
                    curr_surface = g_key_surfaces[LEFT];
                    break;

                    case SDLK_UP:
                    curr_surface = g_key_surfaces[UP];
                    break;

                    case SDLK_RIGHT:
                    curr_surface = g_key_surfaces[RIGHT];
                    break;

                    case SDLK_DOWN:
                    curr_surface = g_key_surfaces[DOWN];
                    break;

                    default:
                    curr_surface = g_key_surfaces[DEFAULT];
                    break;
                }
                SDL_BlitSurface(curr_surface, NULL, screen_surface, NULL);
                update(window);
            }
        }
    }
}

bool init(SDL_Window** window, SDL_Surface** screen_surface) {
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
            *screen_surface = SDL_GetWindowSurface(*window);
        }
    }
    return true;
}

bool load_media() {
    g_key_surfaces[LEFT] = load_surface("images/left.bmp");
    if (g_key_surfaces[LEFT] == NULL){
        cout << "Failed to load left image!\n";
        return false;
    }

    g_key_surfaces[UP] = load_surface("images/up.bmp");
    if (g_key_surfaces[UP] == NULL){
        cout << "Failed to load up image!\n";
        return false;
    }

    g_key_surfaces[RIGHT] = load_surface("images/right.bmp");
    if (g_key_surfaces[RIGHT] == NULL){
        cout << "Failed to load right image!\n";
        return false;
    }

    g_key_surfaces[DOWN] = load_surface("images/down.bmp");
    if (g_key_surfaces[DOWN] == NULL){
        cout << "Failed to load down image!\n";
        return false;
    }

    g_key_surfaces[DEFAULT] = load_surface("images/press.bmp");
    if (g_key_surfaces[DEFAULT] == NULL){
        cout << "Failed to load default image!\n";
        return false;
    }
    return true;
}

SDL_Surface* load_surface(const char* image_path) {
    SDL_Surface* surface = SDL_LoadBMP(image_path);
    if (surface == nullptr)
        cout << "Loading of: " << image_path << " failed!\n";
    return surface;
}

void update(SDL_Window* window) {
    SDL_UpdateWindowSurface(window);
}

void close(SDL_Window* window, SDL_Surface* screen_surface) {
    for(int i = 0; i < LENGTH; ++i)
		SDL_FreeSurface(g_key_surfaces[i]);

    SDL_FreeSurface(screen_surface);
    SDL_DestroyWindow(window);
    SDL_Quit();
}