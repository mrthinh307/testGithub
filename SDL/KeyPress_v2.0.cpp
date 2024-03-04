#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
using namespace std;

void logSDLError(ostream& os, const string& msg, bool fatal = false);

enum KeyPressSurfaces
{
    KEY_PRESS_SURFACE_DEFAULT,
    KEY_PRESS_SURFACE_UP,
    KEY_PRESS_SURFACE_DOWN,
    KEY_PRESS_SURFACE_LEFT,
    KEY_PRESS_SURFACE_RIGHT,
    KEY_PRESS_SURFACE_TOTAL
};

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const string WINDOW_TITLE = "An implementation of Code.org Painter";

SDL_Texture* gKeyPressSurface[ KEY_PRESS_SURFACE_TOTAL ];
SDL_Texture* gCurrentTexture = NULL;

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer);
void quitSDL(SDL_Window* window, SDL_Renderer* renderer);

void waitUntilKeyPressed();




SDL_Texture* loadTexture(string path, SDL_Renderer* renderer){
    SDL_Texture* newTexture = nullptr;
    SDL_Surface* loadedSurface = IMG_Load(path.c_str()); // LOAD HINH ANH TU DIA LEN RAM
    if(loadedSurface == nullptr){
        cout << "Unable to load image " << path << " SDL image Error: " << SDL_GetError() << endl;
    }
    else{
        newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface); // CHUYEN SURFACE THANH TEXTURE DE VE
        if(newTexture == nullptr){
            cout << "Unable to create texture from " << path << " SDL Error: " << SDL_GetError() << endl;
        }
        SDL_FreeSurface(loadedSurface);
    }
    return newTexture;
}


bool loadImage(SDL_Renderer* renderer){
    bool success = true;

    //Load default surface
    gKeyPressSurface[ KEY_PRESS_SURFACE_DEFAULT ] = loadTexture("press.bmp", renderer);
    if(gKeyPressSurface[ KEY_PRESS_SURFACE_DEFAULT ] == nullptr){
        cout << "Unable to load default image " << endl;
        success = false;
    }

    gKeyPressSurface[ KEY_PRESS_SURFACE_UP] = loadTexture("up.bmp", renderer);
    if(gKeyPressSurface[ KEY_PRESS_SURFACE_UP] = nullptr){
        cout << "Unable to load up image " << endl;
        success = false;
    }

    gKeyPressSurface[ KEY_PRESS_SURFACE_DOWN] = loadTexture("down.bmp", renderer);
    if(gKeyPressSurface[ KEY_PRESS_SURFACE_DOWN] == nullptr){
        cout << "Unable to load down image" << endl;
        success = false;
    }

    gKeyPressSurface[KEY_PRESS_SURFACE_LEFT] = loadTexture("left.bmp", renderer);
    if(gKeyPressSurface[KEY_PRESS_SURFACE_LEFT] == nullptr){
        cout << "Unable to load left image " << endl;
        success = false;
    }

    gKeyPressSurface[KEY_PRESS_SURFACE_RIGHT] = loadTexture("right.bmp", renderer);
    if(gKeyPressSurface[KEY_PRESS_SURFACE_RIGHT] == nullptr){
        cout << "Unable to load right image " << endl;
        success = false;
    }

    return success;
}

void close(){
    for(int i = 0; i < KEY_PRESS_SURFACE_TOTAL; i++){
        gKeyPressSurface[i] = NULL;
    }
}
int main(int argc, char* args[]){
    SDL_Window* window;
    SDL_Renderer* renderer;
    initSDL(window, renderer);

    if(!loadImage(renderer)){
        cout << "Unable to load image\n";
    }
    else{

        SDL_Event e;
        gCurrentTexture = gKeyPressSurface[KEY_PRESS_SURFACE_DEFAULT];
        while(true){
            if(SDL_WaitEvent(&e) == 0){
                SDL_Delay(100);
            }
            else if(e.type == SDL_QUIT) break;
            else if(e.type == SDL_KEYDOWN){
                switch(e.key.keysym.sym){
                    case SDLK_w:
                    case SDLK_UP: gCurrentTexture = gKeyPressSurface[KEY_PRESS_SURFACE_UP]; break;
                    case SDLK_s:
                    case SDLK_DOWN: gCurrentTexture = gKeyPressSurface[KEY_PRESS_SURFACE_DOWN]; break;
                    case SDLK_a:
                    case SDLK_LEFT: gCurrentTexture = gKeyPressSurface[KEY_PRESS_SURFACE_LEFT]; break;
                    case SDLK_d:
                    case SDLK_RIGHT: gCurrentTexture = gKeyPressSurface[KEY_PRESS_SURFACE_RIGHT]; break;
                    default: gCurrentTexture = gKeyPressSurface[KEY_PRESS_SURFACE_DEFAULT]; break;
                }
            }
            SDL_RenderClear(renderer);
            SDL_RenderCopy(renderer, gCurrentTexture, NULL, NULL);
            SDL_RenderPresent(renderer);
        }
    }
    close();
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
