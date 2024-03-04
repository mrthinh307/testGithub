#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
using namespace std;

void logSDLError(ostream& os, const string& msg, bool fatal = false);

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const string WINDOW_TITLE = "ColorKeying";
//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

void initSDL();
void quitSDL();
void waitUntilKeyPressed();

class LTexture{
    public:
        //Initializes variables (Khoi tao)
        LTexture();

        //Deallocates memory (Phan bo bo nho - Ham huy)
        ~LTexture();

        //Load image at specified path
        bool loadFromFile(string path);

        //Deallocates texture (Phan bo ket cau - Ham huy)
        void free();

        //Render texture at give point
        void renderCopy(int x, int y);

        //Get image dimensions (Lay kich thuoc hinh anh)
        int getWidth();
        int getHeight();
    private:
        //The actual hardware texture (Ket cau phan cung thuc te)
        SDL_Texture* mTexture;

        //Image dimensions
        int mWidth;
        int mHeight;
};

//Texture wrapper class (Lớp bao bọc kết cấu)
LTexture::LTexture(){
    //Initialize
    mTexture = NULL;
    mWidth = 0;
    mHeight = 0;
}

LTexture::~LTexture()
{
    //Deallocate
    free();
}

bool LTexture::loadFromFile(string path){
    //Get rid of preexisting texture
    free();

    //The final texture
    SDL_Texture* newTexture = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if(loadedSurface == nullptr){
        cout << "Unable to load image " << path << " IMG Error: " << IMG_GetError() << endl;
    }
    else{
        //Color key image  SDL_SetColorKey: https://wiki.libsdl.org/SDL2/SDL_SetColorKey
        SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 255, 255));

        //Create new texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
        if(newTexture == nullptr){
            cout << "Unable create texture from " << path << "SDL Error: " << SDL_GetError() << endl;
        }
        else{
            //Get image dimensions
            mWidth = loadedSurface->w;
            mHeight = loadedSurface->h;

        }
        //Get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);
    }
    //Return success
    mTexture = newTexture;
    return mTexture != NULL;

}

void LTexture::free()
{
    //Free texture if it exists
    if( mTexture != NULL )
    {
        SDL_DestroyTexture( mTexture );
        mTexture = NULL;
        mWidth = 0;
        mHeight = 0;
    }
}

void LTexture::renderCopy( int x, int y )
{
    //Set rendering space and render to screen
    SDL_Rect renderQuad = { x, y, mWidth, mHeight };
    SDL_RenderCopy( gRenderer, mTexture, NULL, &renderQuad );
}

int LTexture::getWidth()
{
    return mWidth;
}

int LTexture::getHeight()
{
    return mHeight;
}

//Scene textures
LTexture gFooTexture;
LTexture gBackgroundTexture;

bool loadMedia(){
    bool success = true;
    //Load Foo' texture
    if(!gFooTexture.loadFromFile("foo.png")){
        cout << "Failed to load Foo' texture image " << endl;
        success = false;
    }

    //Load background texture
    if( !gBackgroundTexture.loadFromFile( "background.png" ) )
    {
        cout <<  "Failed to load background texture image!\n";
        success = false;
    }

    return success;

}

int main(int argc, char* args[]){
    initSDL();
    if(!loadMedia()){
        cout << "Unable to load image :))" << endl;
    }
    else{
        bool quit = false;
        SDL_Event e;

        while(!quit){
            while(SDL_PollEvent(&e) != 0){
                if(e.type == SDL_QUIT){
                    quit = true;
                }
            }
            //Clear screen
            SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0);
            SDL_RenderClear(gRenderer);

            //Render background texture
            gBackgroundTexture.renderCopy( 0, 0 );

            //Render Foo' texture
            gFooTexture.renderCopy( 240, 190 );

            //Update screen
            SDL_RenderPresent(gRenderer);
        }

        waitUntilKeyPressed();
        quitSDL();
    }
    return 0;
}

// BỔ SUNG HÀM QUIT
void quitSDL(){
    //Free loaded image
    gFooTexture.free();
    gBackgroundTexture.free();

    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    gRenderer = NULL;

    IMG_Quit();
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
