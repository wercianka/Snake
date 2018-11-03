#include "classes.h"
#include "functions.h"
#include <iostream>
#include <SDL2/SDL_ttf.h>



#define window_width 640
#define window_height 480

#define fps 60


void cap_framerate( Uint32 starting_tick ) {
    if ( ( 1000 / fps ) > SDL_GetTicks() - starting_tick ) {
            SDL_Delay( 1000 / fps - (SDL_GetTicks() - starting_tick ) );
        }
}


int main( int argc, char *argv[] ) {
    
    SDL_Init( SDL_INIT_EVERYTHING );
    TTF_Init();
    
    SDL_Window *window = NULL;
    window = SDL_CreateWindow( "Snake", 
                                SDL_WINDOWPOS_UNDEFINED, 
                                SDL_WINDOWPOS_UNDEFINED, 
                                window_width, //window_width
                                window_height, //window_height
                                0 );
    
    if ( window == NULL ) {
        cout << "There was an error initialising the window!" << endl << SDL_GetError() << endl;
    }
    
    SDL_Surface *screen = SDL_GetWindowSurface( window );
    
    Uint32 white = SDL_MapRGB( screen->format, 255, 255, 255 );
    Uint32 black = SDL_MapRGB( screen->format, 0, 0, 0 );
    Uint32 red = SDL_MapRGB( screen->format, 255, 0, 0 );
    
    vector<int> tail_x;
    vector<int> tail_y;

    Food apple( red );
    apple.generate();
    
    Sprite object( white, 320, 240);

    SpriteGroup active_sprites;
    active_sprites.add( &object );

    
    active_sprites.draw( screen );
    apple.draw( screen );
    
    SDL_UpdateWindowSurface( window );
    
    int dir_x = 0;
    int dir_y = 0;
    int total = 0;
    
    bool pause = false;
    
    
    Uint32 starting_tick;
    
    SDL_Event event;
    bool running = true;
    
    while ( running ) {
        starting_tick = SDL_GetTicks();
        
        while ( SDL_PollEvent( &event )) {
            if ( event.type == SDL_QUIT ) {
                running = false;
                break;
            }
            
            
            if ( event.type == SDL_KEYDOWN ) {
                switch ( event.key.keysym.sym ) {
                    case SDLK_d:
                        if ( !pause ) {
                            dir_x = 1;
                            dir_y = 0;
                        }
                        break;
                    case SDLK_w:
                        if ( !pause ) {
                            dir_x = 0;
                            dir_y = -1;
                        }
                        break;
                    case SDLK_a:
                        if ( !pause ) {
                            dir_x = -1;
                            dir_y = 0;
                        }
                        break;
                    case SDLK_s:
                        if ( !pause ) {
                            dir_x = 0;
                            dir_y = 1;
                        }
                        break;
                    case SDLK_SPACE:
                        if ( pause == false ) {
                            pause = true;
                        }
                        else {
                            pause = false;
                        }
                }
                
            }
             
                
        }
        
        if ( !pause ) {
            SDL_Delay( 120 );


            if ( !object.check_border( dir_x, dir_y ) ) {
                
                check_fruit( apple, object, total, tail_x, tail_y, object );
                
                object.set_values( dir_x, dir_y );

                SDL_FillRect( screen, NULL, black );

                if ( total != 0 ) {
                    draw_tail( tail_x, tail_y, total, white, screen );
                    move_tail( tail_x, tail_y, total, white, screen, object );
                }
                
                
                draw_game( screen, black, window, active_sprites, apple );
                
            }
            cout << "dir_x = " << dir_x << endl;
            cout << "dir_y = " << dir_y << endl;
            cout << "x = " << object.value_x() << endl;
            cout << "y = " << object.value_y() << endl;
            cout << "foods x = " << apple.value_x() << endl;
            cout << "foods y = " << apple.value_y() << endl;
            cout << "score = " << total << endl;
        }
        
        cap_framerate( starting_tick );
    }
    
    TTF_Quit();
    SDL_DestroyWindow( window );
    SDL_Quit();
    return 0;
}