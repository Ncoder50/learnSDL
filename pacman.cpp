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

const int SCREEN_WIDTH = 3440;
const int SCREEN_HEIGHT = 1440;

SDL_Surface* g_key_surfaces[LENGTH];

void main_loop(SDL_Window* window, SDL_Surface* screen_surface, SDL_Rect* rect);
bool init(SDL_Window** window, SDL_Surface** screen_surface);
bool load_media(SDL_Surface* screen_surface);
SDL_Surface* load_surface(SDL_Surface* screen_surface, const char* image_path);
SDL_Rect* load_rect();
void update(SDL_Window* window);
void close(SDL_Window* window, SDL_Surface* screen_surface); 

int main(int argc, char* args[]) {
    SDL_Window* window = nullptr;
    SDL_Surface* screen_surface = nullptr;

    if (!init(&window, &screen_surface))
        cout << "Initialization failed!\n";

    if (!load_media(screen_surface))
        cout << "Loading media failed!\n";

    SDL_Rect* rect = load_rect();

    main_loop(window, screen_surface, rect);
    close(window, screen_surface);
    return 0;
}

void main_loop(SDL_Window* window, SDL_Surface* screen_surface, SDL_Rect* rect) {
    SDL_Surface* curr_surface = g_key_surfaces[DEFAULT];
    SDL_BlitScaled(curr_surface, NULL, screen_surface, rect);
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
                SDL_BlitScaled(curr_surface, NULL, screen_surface, rect);
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

bool load_media(SDL_Surface* screen_surface) {
    g_key_surfaces[LEFT] = load_surface(screen_surface, "images/left.bmp");
    if (g_key_surfaces[LEFT] == NULL){
        cout << "Failed to load left image!\n";
        return false;
    }

    g_key_surfaces[UP] = load_surface(screen_surface, "images/up.bmp");
    if (g_key_surfaces[UP] == NULL){
        cout << "Failed to load up image!\n";
        return false;
    }

    g_key_surfaces[RIGHT] = load_surface(screen_surface, "images/right.bmp");
    if (g_key_surfaces[RIGHT] == NULL){
        cout << "Failed to load right image!\n";
        return false;
    }

    g_key_surfaces[DOWN] = load_surface(screen_surface, "images/down.bmp");
    if (g_key_surfaces[DOWN] == NULL){
        cout << "Failed to load down image!\n";
        return false;
    }

    g_key_surfaces[DEFAULT] = load_surface(screen_surface, "images/press.bmp");
    if (g_key_surfaces[DEFAULT] == NULL){
        cout << "Failed to load default image!\n";
        return false;
    }
    return true;
}

SDL_Surface* load_surface(SDL_Surface* screen_surface, const char* image_path) {
    SDL_Surface* surface = SDL_LoadBMP(image_path);
    if (surface == nullptr)
        cout << "Loading of: " << image_path << " failed!\n";
    SDL_Surface* stretched_surface = SDL_ConvertSurface(surface, screen_surface->format, 0);
    if (stretched_surface == nullptr)
        cout << "Converting surface of: " << image_path << " failed!\n";
    SDL_FreeSurface(surface);
    return stretched_surface;
}

SDL_Rect* load_rect() {
    SDL_Rect rect;
    rect.x = 0;
    rect.y = 0;
    rect.w = SCREEN_WIDTH;
    rect.h = SCREEN_HEIGHT;
    return &rect;
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