#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

using std::cout;

enum KEY_PRESS_SURFACES {
    LEFT,
    UP,
    RIGHT,
    DOWN,
    DEFAULT,
    LENGTH
};

const int SCREEN_WIDTH =  980;
const int SCREEN_HEIGHT = 540;

SDL_Texture* g_key_surfaces[LENGTH];
SDL_Texture* g_texture = nullptr;

void main_loop(SDL_Window* window, SDL_Renderer* renderer);
bool init(SDL_Window** window, SDL_Surface** screen_surface, SDL_Renderer** renderer);
bool load_media(SDL_Renderer* renderer);
SDL_Texture* load_texture(SDL_Renderer* renderer, const char* image_path);
void close(SDL_Window* window, SDL_Surface* screen_surface, SDL_Renderer* renderer); 

int main(int argc, char* args[]) {
    SDL_Window* window = nullptr;
    SDL_Surface* screen_surface = nullptr;
    SDL_Renderer* renderer = nullptr;

    if (!init(&window, &screen_surface, &renderer))
        cout << "Initialization failed!\n";

    if (!load_media(renderer))
        cout << "Loading media failed!\n";

    main_loop(window, renderer);
    close(window, screen_surface, renderer);
    return 0;
}

void main_loop(SDL_Window* window, SDL_Renderer* renderer) {
    SDL_Texture* curr_texture = g_key_surfaces[DEFAULT];
    SDL_RenderCopy(renderer, curr_texture, NULL, NULL);
    SDL_RenderPresent(renderer);
    SDL_Event e;
    while (true) {
        while(SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT)
                return;
            else if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    case SDLK_LEFT:
                    curr_texture = g_key_surfaces[LEFT];
                    break;

                    case SDLK_UP:
                    curr_texture = g_key_surfaces[UP];
                    break;

                    case SDLK_RIGHT:
                    curr_texture = g_key_surfaces[RIGHT];
                    break;

                    case SDLK_DOWN:
                    curr_texture = g_key_surfaces[DOWN];
                    break;

                    default:
                    curr_texture = g_key_surfaces[DEFAULT];
                    break;
                }
                SDL_RenderClear(renderer);
                SDL_RenderCopy(renderer, curr_texture, NULL, NULL);
                SDL_RenderPresent(renderer);
            }
        }
    }
}

bool init(SDL_Window** window, SDL_Surface** screen_surface, SDL_Renderer** renderer) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cout << "SDL could not initialize!\n" << SDL_GetError();
        return false;
    }

    *window = SDL_CreateWindow("Pacman", SDL_WINDOWPOS_UNDEFINED, 
    SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (*window == nullptr) {
        cout << "Window could not be created!\n" << SDL_GetError();
        return false;
    }

    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
    if (*renderer == nullptr) {
        cout << "Renderer could not be created!\n" << SDL_GetError();
    }
    SDL_SetRenderDrawColor(*renderer, 0xFF, 0xFF, 0xFF, 0xFF);

    int img_flags = IMG_INIT_PNG;
    // Chekcs if the returned flags contains the flags we sent in
    if (!(IMG_Init(img_flags) & img_flags)) {
        cout << "SDL_image could not initialize!\n" << IMG_GetError();
        return false;
    }

    *screen_surface = SDL_GetWindowSurface(*window);
    return true;
}

bool load_media(SDL_Renderer* renderer) {
    g_key_surfaces[LEFT] = load_texture(renderer, "images/left.bmp");
    if (g_key_surfaces[LEFT] == NULL){
        cout << "Failed to load left image!\n";
        return false;
    }

    g_key_surfaces[UP] = load_texture(renderer, "images/up.bmp");
    if (g_key_surfaces[UP] == NULL){
        cout << "Failed to load up image!\n";
        return false;
    }

    g_key_surfaces[RIGHT] = load_texture(renderer, "images/right.bmp");
    if (g_key_surfaces[RIGHT] == NULL){
        cout << "Failed to load right image!\n";
        return false;
    }

    g_key_surfaces[DOWN] = load_texture(renderer, "images/down.bmp");
    if (g_key_surfaces[DOWN] == NULL){
        cout << "Failed to load down image!\n";
        return false;
    }

    g_key_surfaces[DEFAULT] = load_texture(renderer, "images/press.bmp");
    if (g_key_surfaces[DEFAULT] == NULL){
        cout << "Failed to load default image!\n";
        return false;
    }
    return true;
}

SDL_Texture* load_texture(SDL_Renderer* renderer, const char* image_path) {
    SDL_Texture* texture = nullptr;
    SDL_Surface* surface = IMG_Load(image_path);
    if (surface == nullptr)
        cout << "Unable to load image in texture!\n" << IMG_GetError();
    
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (texture == nullptr)
        cout << "Couldn't create texture from surface!\n" << SDL_GetError();

    SDL_FreeSurface(surface);
    return texture;
}

void close(SDL_Window* window, SDL_Surface* screen_surface, SDL_Renderer* renderer) {
    for(int i = 0; i < LENGTH; ++i)
		SDL_DestroyTexture(g_key_surfaces[i]);
    SDL_FreeSurface(screen_surface);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}