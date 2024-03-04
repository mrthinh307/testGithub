        //Render at the top left        
        topLeftViewport.x = 0;
        topLeftViewport.y = 0;
        topLeftViewport.w = SCREEN_WIDTH / 2;
        topLeftViewport.h = SCREEN_HEIGHT / 2;
        
        //Any rendering done after that call will render inside the region defined by the given viewport.
        SDL_RenderSetViewport( gRenderer, &topLeftViewport );

        SDL_RenderCopy( gRenderer, ex, NULL, NULL );
        SDL_RenderCopy( gRenderer, ex2, NULL, NULL );