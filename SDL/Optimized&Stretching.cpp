/* Khi sử dụng SDL_ConvertSurface:
Bằng cách sử dụng hàm này, bạn tạo ra một surface mới (optimizedSurface) với định dạng pixel tối ưu hóa.
Surface mới này chứa dữ liệu từ hình ảnh gốc (loadedSurface) đã được chuyển đổi.
Khi bạn vẽ trực tiếp lên renderer bằng optimizedSurface, 
SDL sẽ sao chép pixel từ surface đã được tối ưu hóa, giúp tăng tốc độ vẽ.
Khi vẽ bằng renderer, 
việc sử dụng SDL_ConvertSurface có thể giúp tối ưu hóa việc sao chép dữ liệu và cải thiện hiệu suất vẽ.*/
SDL_Surface* gScreenSurface = NULL;
SDL_Texture* loadImage(SDL_Renderer* renderer, string path){
    SDL_Texture* newTexture = NULL;
    
    SDL_Surface* optimizedSurface = NULL; // the final optimized image

    SDL_Surface* loadedSurface = IMG_Load(path.c_str());

    if(loadedSurface == nullptr){
        cout << "Unable to load image " << path << " SDL Error: " << SDL_GetError() << endl;
    }
    else{
        optimizedSurface = SDL_ConvertSurface(loadedSurface, gScreenSurface -> format, 0);

        if(optimizedSurface == NULL){
            cout << "Unable to optimized surface! SDL Error: " << SDL_GetError() << endl;
        }

        SDL_FreeSurface(loadedSurface);
        newTexture = SDL_CreateTextureFromSurface(renderer, optimizedSurface);

        if(newTexture == nullptr){
            cout << "Unable to create texture from " << path << " SDL Error: " << SDL_GetError() << endl;
        }
        SDL_FreeSurface(optimizedSurface);
    }
    return newTexture;
}

// BỔ SUNG gScreenSurface ở hàm Init
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

    gScreenSurface = SDL_GetWindowSurface(window);     // HERE

    if(renderer == nullptr){
        logSDLError(cout, "Create Renderer", true);
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear" );
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
}