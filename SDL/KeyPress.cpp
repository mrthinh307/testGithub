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
const string WINDOW_TITLE = "KEY PRESS";

SDL_Texture* gKeyPressSurfaces[KEY_PRESS_SURFACE_TOTAL];
SDL_Texture* gCurrentTexture = NULL;

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer);
void quitSDL(SDL_Window* window, SDL_Renderer* renderer);

bool loadImage(SDL_Renderer* renderer);
void close();

int main(int argc, char* args[]) {
    SDL_Window* window;
    SDL_Renderer* renderer;
    initSDL(window, renderer);

    if (!loadImage(renderer)) {
        cout << "Unable to load image\n";
    }
    else{
        //Main loop flag
        bool quit = false;

        //Event handler
        SDL_Event e;

        //Set default current surface
        gCurrentTexture = gKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ];

        //While application is running
        while( !quit ){
            //Handle events on queue
            while( SDL_PollEvent( &e ) != 0 ){
                //User requests quit
                if( e.type == SDL_QUIT )
                {
                    quit = true;
                }
                //User presses a key
                else if( e.type == SDL_KEYDOWN )
                {
                    //Select surfaces based on key press
                    switch( e.key.keysym.sym )
                    {
                        case SDLK_UP:
                            gCurrentTexture = gKeyPressSurfaces[ KEY_PRESS_SURFACE_UP ];
                            break;

                        case SDLK_DOWN:
                            gCurrentTexture = gKeyPressSurfaces[ KEY_PRESS_SURFACE_DOWN ];
                            break;

                        case SDLK_LEFT:
							gCurrentTexture = gKeyPressSurfaces[ KEY_PRESS_SURFACE_LEFT ];
							break;

                        case SDLK_RIGHT:
							gCurrentTexture = gKeyPressSurfaces[ KEY_PRESS_SURFACE_RIGHT ];
							break;

                        default:
							gCurrentTexture = gKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ];
							break;
                    }
                }
            }
            SDL_RenderClear(renderer);
            SDL_RenderCopy(renderer, gCurrentTexture, NULL, NULL);
            SDL_RenderPresent(renderer);
        }

        close();

    }
    quitSDL(window, renderer);
    return 0;
}
void logSDLError(ostream& os, const string& msg, bool fatal) {
    cout << msg << " Error: " << SDL_GetError() << endl;
    if (fatal) {
        SDL_Quit();
        exit(1);
    }
}

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        logSDLError(cout, "SDL_Init", true);
    }

    window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if (window == nullptr) {
        logSDLError(cout, "Create Window", true);
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (renderer == nullptr) {
        logSDLError(cout, "Create Renderer", true);
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
}
// LOAD ALL IMAGE THAT WILL BE RENDERED
bool loadImage(SDL_Renderer* renderer) {
    bool success = true;

    // Load default surface
    gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] = IMG_LoadTexture(renderer, "press.bmp");
    if (gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] == NULL) {
        logSDLError(cout, "Unable to load default image", false);
        success = false;
    }

    gKeyPressSurfaces[KEY_PRESS_SURFACE_UP] = IMG_LoadTexture(renderer, "up.bmp");
    if (gKeyPressSurfaces[KEY_PRESS_SURFACE_UP] == NULL) {
        logSDLError(cout, "Unable to load up image", false);
        success = false;
    }

    gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] = IMG_LoadTexture(renderer, "down.bmp");
    if (gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] == NULL) {
        logSDLError(cout, "Unable to load down image", false);
        success = false;
    }

    gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] = IMG_LoadTexture(renderer, "left.bmp");
    if (gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] == NULL) {
        logSDLError(cout, "Unable to load left image", false);
        success = false;
    }

    gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] = IMG_LoadTexture(renderer, "right.bmp");
    if (gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] == NULL) {
        logSDLError(cout, "Unable to load right image", false);
        success = false;
    }

    return success;
}

void close() {
    for (int i = 0; i < KEY_PRESS_SURFACE_TOTAL; i++) {
        SDL_DestroyTexture(gKeyPressSurfaces[i]);
        gKeyPressSurfaces[i] = NULL;
    }
}

void quitSDL(SDL_Window* window, SDL_Renderer* renderer) {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
