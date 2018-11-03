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

enum mode {
    starting_screen,
    game,
    pause_screen
};

enum menu {
    start,
    quit,
    pause_return
};


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
    SDL_Color white_color = { 255, 255, 255 };
    SDL_Color menu_color = { 255, 0, 0 };
    
    TTF_Font *font = TTF_OpenFont( "/home/raiya/Documents/CPP/TEST/04B_30__.TTF", 100 );
    TTF_Font *menu_font = TTF_OpenFont( "/home/raiya/Documents/CPP/TEST/Perfect DOS VGA 437.ttf", 40 );
    
    SDL_Surface *font_surf_title = TTF_RenderText_Solid( font, "SNAKE", white_color );
    SDL_Surface *font_surf_pause = TTF_RenderText_Solid( font, "PAUSE", white_color );
    SDL_Surface *font_surf_menu_start = TTF_RenderText_Solid( menu_font, "START", white_color );
    SDL_Surface *font_surf_menu_start_selected = TTF_RenderText_Solid( menu_font, "START", menu_color );
    SDL_Surface *font_surf_menu_quit = TTF_RenderText_Solid( menu_font, "QUIT", white_color );
    SDL_Surface *font_surf_menu_quit_selected = TTF_RenderText_Solid( menu_font, "QUIT", menu_color );


    SDL_Rect frect;
    
    
    vector<int> tail_x;
    vector<int> tail_y;

    Food apple( red );
    apple.generate();
    
    Sprite object( white, 320, 240);

    SpriteGroup active_sprites;
    active_sprites.add( &object );
    
    
    int dir_x = 0;
    int dir_y = 0;
    int total = 0;
    
    //bool pause = false;
    mode mode_number = starting_screen;
    menu menu_number = start;
    
    
    Uint32 starting_tick;
    
    SDL_Event event;
    bool running = true;
    
    //////////////////////////////////////////////////////////////////////////////
    while ( running ) {
        starting_tick = SDL_GetTicks();
        
        while ( SDL_PollEvent( &event )) {
            if ( event.type == SDL_QUIT ) {
                running = false;
                break;
            }
            
            
            if ( event.type == SDL_KEYDOWN ) {
                switch ( mode_number ) {
                    case mode::starting_screen:
                        switch ( event.key.keysym.sym ) {
                            case SDLK_RETURN:
                                if ( menu_number == menu::start ) {
                                    mode_number = game;
                                }
                                else {
                                    running = false;
                                }
                                break;
                            case SDLK_w:
                                if ( menu_number == menu::start ) {
                                    menu_number = quit;
                                }
                                else {
                                    menu_number = start;
                                }
                                break;
                            case SDLK_s:
                                if ( menu_number == menu::start ) {
                                    menu_number = quit;
                                }
                                else {
                                    menu_number = start;
                                }
                                break;
                        }
                        break;
                    case mode::game:
                        switch ( event.key.keysym.sym ) {
                            case SDLK_d:
                                dir_x = 1;
                                dir_y = 0;
                                
                                break;
                            case SDLK_w:
                                dir_x = 0;
                                dir_y = -1;
                                
                                break;
                            case SDLK_a:
                                dir_x = -1;
                                dir_y = 0;
                                
                                break;
                            case SDLK_s:
                                dir_x = 0;
                                dir_y = 1;
                                
                                break;
                            case SDLK_SPACE:
                                mode_number = pause_screen;
                                break;
                        }
                        break;
                    case mode::pause_screen:
                        if ( event.key.keysym.sym == SDLK_SPACE ) {
                            mode_number = game;
                        }
                        
                        break;
                
                }
                
            }
             
                
        }
        
        
        switch ( mode_number ) {
            case mode::starting_screen:  
                frect.x = 92;
                frect.y = 60;
                
                SDL_BlitSurface( font_surf_title, NULL, screen, &frect );
                
                frect.x = 250;
                frect.y = 200;
                
                if ( menu_number != menu::start ) {
                    SDL_BlitSurface( font_surf_menu_start, NULL, screen, &frect );
                }
                else {
                    SDL_BlitSurface( font_surf_menu_start_selected, NULL, screen, &frect );

                }
                
                frect.y = 280;
                
                if ( menu_number != menu::quit ) {
                    SDL_BlitSurface( font_surf_menu_quit, NULL, screen, &frect );
                }
                else {
                    SDL_BlitSurface( font_surf_menu_quit_selected, NULL, screen, &frect );
                }
                
                SDL_UpdateWindowSurface( window );

                
                break;
            case mode::game:
                
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
                
                break;
            case mode::pause_screen:
                SDL_FillRect( screen, NULL, black );
                
                frect.x = 92;
                frect.y = 60;
                
                SDL_BlitSurface( font_surf_pause, NULL, screen, &frect );
                
                SDL_UpdateWindowSurface( window );

                
                break;
        }

        
        cap_framerate( starting_tick );
    }
    
    //////////////////////////////////////////////////////////////////////////////
    
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_DestroyWindow( window );
    SDL_Quit();
    return 0;
}