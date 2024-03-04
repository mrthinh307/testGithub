/* Texture là một cấu trúc dữ liệu để chứa thông tin về hình ảnh hoặc texture. 
Dưới đây là một số điểm quan trọng về Texture:

- Định nghĩa: Texture là một cấu trúc dữ liệu hiệu quả, 
  được tối ưu hóa cho việc lưu trữ dữ liệu pixel của hình ảnh.
- Vị trí lưu trữ: Texture tồn tại trên VRAM (Video RAM), 
  nơi GPU (Graphics Processing Unit) có thể truy cập nhanh chóng để vẽ lên màn hình.
- Sử dụng: Khi bạn muốn hiển thị hình ảnh hoặc texture lên màn hình, 
  bạn sẽ tạo một Texture từ dữ liệu hình ảnh (thường là từ Surface)
  và sau đó vẽ Texture lên màn hình bằng Renderer.
- Khác biệt với Surface: Surface là một cấu trúc dữ liệu tương tự, 
  nhưng tồn tại trên RAM (Random Access Memory).
  Surface thường được sử dụng để load hình ảnh từ đĩa lên RAM, 
  sau đó chuyển thành Texture để vẽ lên màn hình.*/


#include <SDL_image.h>


void quitTexture(SDL_Texture* texture){
    SDL_Destroy(texture);
    texture = NULL;
    IMG_Quit();
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

SDL_Texture* loadTexture(string path, SDL_Renderer* renderer){
    // The final texture
    SDL_Texture* newTexture = nullptr;
    // Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());

    if(loadedSurface == nullptr){
        cout << "Unable to load image " << path << " SDL_image Error: " << IMG_GetError() << endl;
    }
    else{
        // Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        if(newTexture == nullptr){
            cout << "Unable to create texture from " << path << " SDL Error: " << SDL_GetError() << endl;

        }
        //Get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);
    }
    return newTexture;
}
void quitSDL(SDL_Window* window, SDL_Renderer* renderer){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

int main(int argc, char* args[]){
    SDL_Window* window;
    SDL_Renderer* renderer;
    initSDL(window, renderer);

    SDL_Texture* background = loadTexture("background.jpg", renderer);
    SDL_RenderCopy(renderer, background, NULL, NULL); // ĐẦY ĐỦ KÍCH THƯỚC, ĐẦY ĐỦ MÀN HÌNH

    SDL_Texture* bubble = loadTexture("bubble.png", renderer);
    // VẼ HÌNH VÀO VÀO PHẦN NÀY CỦA MÀN HÌNH
    SDL_Rect bubbleRect;
    SDL_QueryTexture(bubble, NULL, NULL, &bubbleRect.w, &bubbleRect.h);
    bubbleRect.x = 0;
    bubbleRect.y = 0;
    bubbleRect.w /= 3.0;
    bubbleRect.h /= 3.0;
    //SDL_RenderCopy(renderer, bubble, NULL, &bubbleRect);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
    SDL_RenderDrawPoint(renderer, 400,300);
    // CẮT HÌNH TỪ (X, Y) 
    SDL_Rect bubbleSrc;
    bubbleSrc.x = 0;
    bubbleSrc.y = 0;
    bubbleSrc.w /= 5.0;
    bubbleSrc.h /= 5.0;
    SDL_RenderCopy(renderer, bubble, &bubbleSrc/*vẽ từng này của hình*/, &bubbleRect /* vẽ vào khoảng này của màn hình*/);

    SDL_RenderPresent(renderer);

    waitUntilKeyPressed();
    
    quitTexture(bubble);
    quitTexture(background);
    quitSDL(window, renderer);
    return 0;
}
