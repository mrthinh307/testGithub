#include <iostream>
#include <SDL.h>

using namespace std;

void logSDLError(ostream& os, const string& msg, bool fatal = false);

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const string WINDOW_TITLE = "An implementation of Code.org Painter";
const int RECT_SIZE = 3;
void initSDL(SDL_Window* &window, SDL_Renderer* &renderer);
void quitSDL(SDL_Window* window, SDL_Renderer* renderer);
void waitUntilKeyPressed();
void draw(SDL_Renderer* renderer,int x,int y){
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = RECT_SIZE;
    rect.h = RECT_SIZE;

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
    SDL_RenderDrawRect(renderer, &rect);
    SDL_RenderPresent(renderer);
}
int main(int argc, char* args[]){
    SDL_Window* window;
    SDL_Renderer* renderer;
    initSDL(window, renderer);

    int x = SCREEN_WIDTH / 2;
    int y = SCREEN_HEIGHT / 2;
    int step = 5;
    SDL_Event e;
    while(true){
        if(SDL_WaitEvent(&e) == 0) SDL_Delay(100); // Chờ tiếp cho đến khi event xảy ra
        else if(e.type == SDL_QUIT) break;
        else if(e.type == SDL_KEYDOWN){
            cout << "_" << SDL_GetKeyName(e.key.keysym.sym) << "_" << endl;
            switch(e.key.keysym.sym){
                case SDLK_w:
                case SDLK_UP: y -= step; break;
                case SDLK_s:
                case SDLK_DOWN: y+= step; break;
                case SDLK_a:
                case SDLK_LEFT: x -= step; break;
                case SDLK_d:
                case SDLK_RIGHT: x += step; break;

            }
            draw(renderer, x, y);
        }

    }


    quitSDL(window, renderer);
    return 0;
}

void logSDLError(ostream& os,const string& msg, bool fatal ){
    cout << msg << "Error: " << SDL_GetError() << endl;
    if(fatal){
        SDL_Quit();
        exit(1);
    }
}

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer){
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0){
        logSDLError(cout, "SDL_Init", true);
    }

    window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if(window == nullptr){
        logSDLError(cout, "Create Window", true);
    }


    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if(renderer == nullptr){
        logSDLError(cout, "Create Renderer", true);
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear" );
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void waitUntilKeyPressed(){
    SDL_Event e;
    while(true){
        if(SDL_WaitEvent(&e) && (e.type == SDL_KEYDOWN || e.type == SDL_QUIT)){
            return;

        }
        SDL_Delay(100);
    }
}


void quitSDL(SDL_Window* window, SDL_Renderer* renderer){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
