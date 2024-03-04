#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
using namespace std;

void logSDLError(ostream& os, const string& msg, bool fatal = false);

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const string WINDOW_TITLE = "An implementation of Code.org Painter";
//Loads individual image as texture
SDL_Texture* loadTexture( string path );

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//Current displayed texture
SDL_Texture* gTexture = NULL;


void initSDL();
void quitSDL();
void quitSDL_Texture();
void waitUntilKeyPressed();

int main(int argc, char* args[]){
    initSDL();

    bool quit = false;
    SDL_Event e;
    while(!quit){
        //Handle events on queue
        while(SDL_PollEvent( &e ) != 0){
            //User requests quit
            if(e.type == SDL_QUIT){
                quit = true;
            }
        }
        //Clear screen
        SDL_RenderClear(gRenderer);

        //Create a texture
        SDL_Texture* example = loadTexture("bubble.png");

        //Render texture to screen
        SDL_RenderCopy(gRenderer, example, NULL, NULL);

        //Update screen
        SDL_RenderPresent(gRenderer);
    }

    quitSDL_Texture();
    quitSDL();
    return 0;
}

SDL_Texture* loadTexture(string path){
    // The final texture
    SDL_Texture* newTexture = nullptr;
    // Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());

    if(loadedSurface == nullptr){
        cout << "Unable to load image " << path << " SDL_image Error: " << IMG_GetError() << endl;
    }
    else{
        // Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
        if(newTexture == nullptr){
            cout << "Unable to create texture from " << path << " SDL Error: " << SDL_GetError() << endl;

        }
        //Get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);
    }
    return newTexture;
}

void quitSDL_Texture()
{
    //Free loaded image
    SDL_DestroyTexture( gTexture );
    gTexture = NULL;

    //Quit SDL subsystems
    SDL_Quit();
}

void logSDLError(ostream& os,const string& msg, bool fatal ){
    cout << msg << "Error: " << SDL_GetError() << endl;
    if(fatal){
        SDL_Quit();
        exit(1);
    }
}

void initSDL(){
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0){
        logSDLError(cout, "SDL_Init", true);
    }

    gWindow = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if(gWindow == nullptr){
        logSDLError(cout, "Create Window", true);
    }


    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if(gRenderer == nullptr){
        logSDLError(cout, "Create Renderer", true);
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear" );
    SDL_RenderSetLogicalSize(gRenderer, SCREEN_WIDTH, SCREEN_HEIGHT);
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

void quitSDL(){
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    SDL_Quit();
}
