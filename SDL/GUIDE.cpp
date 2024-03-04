#include <iostream>
#include <SDL.h>

using namespace std;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const string WINDOW_TITLE = "SDL Learning";

void logSDLError(ostream& os, const string& msg, bool fatal = false);
void initSDL(SDL_Window* &window, SDL_Renderer* &renderer);
void quitSDL(SDL_Window* window, SDL_Renderer* renderer);
void waitUntilKeyPressed();

int main(int argc, char* argv[]){
    SDL_Window* window;
    SDL_Renderer* renderer;
    initSDL(window, renderer);

    // Your drawing code here
    // use SQL_RenderPresent(renderer) to show it

    waitUntilKeyPressed();
    quitSDL(window, renderer);
    return 0;
}
// FUNCTION TO NOTICE THAT THE PROGRAM ENCOUNTERED AN ERROR
void logSDLError(ostream& os,const string& msg, bool fatal ){
    cout << msg << "Error: " << SDL_GetError() << endl;
    if(fatal){
        SDL_Quit();
        exit(1);
    }
}
// FUNCTION TO CONSTRUCT SDL
void initSDL(SDL_Window* &window, SDL_Renderer* &renderer){
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0){
        logSDLError(cout, "SDL_Init", true);
    }
    // Hàm tạo cửa sổ
    window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    /* Trong ngôn ngữ lập trình, SDL_CreateWindow là một hàm để tạo ra một cửa sổ với các thông số như sau:

    - title: Tiêu đề của cửa sổ (được mã hóa bằng UTF-8).
    - x và y: Vị trí của cửa sổ trên màn hình. SDL_WINDOWPOS_CENTERED hoặc SDL_WINDOWPOS_UNDEFINED có thể được sử dụng để đặt vị trí ở giữa màn hình hoặc không xác định.
    - w và h: Kích thước của cửa sổ trong đơn vị pixel.
    - flags: Các cờ để chỉ định các thuộc tính của cửa sổ. Ví dụ: SDL_WINDOW_SHOWN để hiển thị cửa sổ. */
    if(window == nullptr){
        logSDLError(cout, "Create Window", true);
    }

    // Khi chạy trong môi trường bình thường không chạy máy ảo
    // Hàm tạo context vẽ 2D
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    /* Tham số: Hàm này nhận các tham số sau:
    - window: Cửa sổ mà renderer sẽ hiển thị trên.
    - index: Chỉ số của driver rendering để khởi tạo, hoặc -1 để khởi tạo driver đầu tiên hỗ trợ các flags yêu cầu.
    - flags: Các cờ để chỉ định các thuộc tính của renderer. Ví dụ: SDL_RENDERER_SOFTWARE để tạo renderer phần mềm.
    + Trả về: Hàm trả về một context vẽ hợp lệ hoặc NULL nếu có lỗi. Bạn có thể kiểm tra mã lỗi bằng cách gọi SDL_GetError(). */

    //Khi chạy ở máy ảo (ví dụ tại máy tính trong phòng thực hành ở trường)
    //renderer = SDL_CreateSoftwareRenderer(SDL_GetWindowSurface(window));

    if(renderer == nullptr){
        logSDLError(cout, "Create Renderer", true);
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear" /*best*/); // linear : vẽ tuyến tính, rõ ràng ko bị mờ
    /* Là một cách để thiết lập một gợi ý (hint) cho thư viện SDL (Simple DirectMedia Layer) về chất lượng tỷ lệ vẽ (render scale quality). */
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT); // hàm thiết lập độ phân giải logic
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

//FUNCTION TO QUIT SDL
void quitSDL(SDL_Window* window, SDL_Renderer* renderer){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
