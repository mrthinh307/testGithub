/* XÓA MÀN HÌNH */
int SDL_RenderClear(SDL_Renderer* renderer)

/* ĐẶT MÀU VẼ */ 
int SDL_SetRenderDrawColor(SDL_Renderer* renderer, Uint8 r, Uint 8 g, Uint8 b, Uint8 a);

/* VẼ ĐIỂM */
int SDL_RenderDrawPoint(SDL_Renderer* renderer, int x, int y);

/* VẼ ĐOẠN THẲNG */
int SDL_RenderDrawLine(SDL_Renderer* renderer, int x1, int y1, int x2, int y2);

/* VẼ HÌNH CHỮ NHẬT RỖNG */
int SDL_RenderDrawRect(SDL_Renderer* renderer, const SDL_Rect* rect);

/* VẼ HÌNH CHỮ NHẬT ĐẶC */
int SDL_RenderFillRect(SDL_Renderer* renderer, const SDL_Rect* rect);


/* Sau khi vẽ xong, bạn cần gọi lệnh hiển thị ra màn hình để kết quả của các lệnh vẽ được 
đổ ra màn hình (render). Nếu quên mất bước này thì các hình vẽ chỉ nằm trong bộ nhớ. */

/* Khi thông thường chạy với môi trường bình thường ở nhà, với trước đó khởi tạo dùng */
 ->   renderer = SDL_CreateRenderer(...);
 ->   void SDL_RenderPresent(SDL_Renderer* renderer);
//Hoặc
/* Khi chạy ở máy thực hành WinXP ở trường (máy ảo), với trước đó khởi tạo dùng */
    renderer = SDL_CreateSoftwareRenderer(...);
    void SDL_UpdateWindowSurface(SDL_Window *window);



/* ex: */
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);   // white
    SDL_RenderDrawPoint(renderer, SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // red
    SDL_RenderDrawLine(renderer, 100, 100, 200, 200);
    SDL_Rect filled_rect;
    filled_rect.x = SCREEN_WIDTH - 400;
    filled_rect.y = SCREEN_HEIGHT - 150;
    filled_rect.w = 320;
    filled_rect.h = 100;
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // green
    SDL_RenderFillRect(renderer, &filled_rect);
    
    SDL_RenderPresent(renderer);