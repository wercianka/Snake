#include "classes.h"
#include "functions.h"
#include <iostream>
#include <SDL2/SDL_ttf.h>
#include <string>



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
    pause_screen,
    game_over,
    options_screen
};

enum menu {
    start,
    quit,
    try_again,
    options,
    back,
    death,
    sound
};


int main( int argc, char *argv[] ) {
    
    SDL_Init( SDL_INIT_EVERYTHING );
    TTF_Init();
    Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 2048 );
    
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
    
    int total = 0;
    
    bool edge_death = false;
    bool play_sound = true;
    
    Uint32 white = SDL_MapRGB( screen->format, 255, 255, 255 );
    Uint32 black = SDL_MapRGB( screen->format, 0, 0, 0 );
    Uint32 red = SDL_MapRGB( screen->format, 255, 0, 0 );
    SDL_Color white_color = { 255, 255, 255 };
    SDL_Color menu_color = { 255, 0, 0 };
    
    TTF_Font *font = TTF_OpenFont( "/home/raiya/Documents/CPP/TEST/04B_30__.TTF", 100 );
    TTF_Font *menu_font = TTF_OpenFont( "/home/raiya/Documents/CPP/TEST/Perfect DOS VGA 437.ttf", 40 );
    TTF_Font *pause_font = TTF_OpenFont( "/home/raiya/Documents/CPP/TEST/Perfect DOS VGA 437.ttf", 120 );
    TTF_Font *game_over_font = TTF_OpenFont( "/home/raiya/Documents/CPP/TEST/Perfect DOS VGA 437.ttf", 80 );
    TTF_Font *score_font = TTF_OpenFont( "/home/raiya/Documents/CPP/TEST/Perfect DOS VGA 437.ttf", 40 );
    TTF_Font *controls_font = TTF_OpenFont( "/home/raiya/Documents/CPP/TEST/Perfect DOS VGA 437.ttf", 16 );
    
    SDL_Surface *font_surf_title = TTF_RenderText_Solid( font, "SNAKE", white_color );
    SDL_Surface *font_surf_pause = TTF_RenderText_Solid( pause_font, "PAUSE", white_color );
    SDL_Surface *font_surf_options = TTF_RenderText_Solid( pause_font, "OPTIONS", white_color );
    
    SDL_Surface *font_surf_menu_start = TTF_RenderText_Solid( menu_font, "START", white_color );
    SDL_Surface *font_surf_menu_start_selected = TTF_RenderText_Solid( menu_font, "START", menu_color );
    SDL_Surface *font_surf_menu_quit = TTF_RenderText_Solid( menu_font, "QUIT", white_color );
    SDL_Surface *font_surf_menu_quit_selected = TTF_RenderText_Solid( menu_font, "QUIT", menu_color );
    SDL_Surface *font_surf_menu_options = TTF_RenderText_Solid( menu_font, "OPTIONS", white_color );
    SDL_Surface *font_surf_menu_options_selected = TTF_RenderText_Solid( menu_font, "OPTIONS", menu_color );
    SDL_Surface *font_surf_menu_back = TTF_RenderText_Solid( menu_font, "BACK", white_color );
    SDL_Surface *font_surf_menu_back_selected = TTF_RenderText_Solid( menu_font, "BACK", menu_color );
    
    SDL_Surface *font_surf_menu_yes = TTF_RenderText_Solid( menu_font, "YES", white_color );
    SDL_Surface *font_surf_menu_yes_selected = TTF_RenderText_Solid( menu_font, "YES", menu_color );
    SDL_Surface *font_surf_menu_no = TTF_RenderText_Solid( menu_font, "NO", white_color );
    SDL_Surface *font_surf_menu_no_selected = TTF_RenderText_Solid( menu_font, "NO", menu_color );
    SDL_Surface *font_surf_death = TTF_RenderText_Solid( menu_font, "DEATH AT EDGES", white_color );
    SDL_Surface *font_surf_sound = TTF_RenderText_Solid( menu_font, "SOUNDS", white_color );
    
    SDL_Surface *font_surf_score = TTF_RenderText_Solid( menu_font, "SCORE", white_color );
    SDL_Surface *font_surf_game_over = TTF_RenderText_Solid( game_over_font, "GAME OVER", white_color );
    SDL_Surface *font_surf_try_again = TTF_RenderText_Solid( menu_font, "TRY AGAIN", white_color );
    SDL_Surface *font_surf_try_again_selected = TTF_RenderText_Solid( menu_font, "TRY AGAIN", menu_color );
    SDL_Surface *font_surf_controls = TTF_RenderText_Solid( controls_font, "move - awsd or arrow keys; confirm - enter; pause - spacebar", white_color );

    SDL_Surface *font_surf_number_1 = TTF_RenderText_Solid( score_font, "1", white_color );
    SDL_Surface *font_surf_number_2 = TTF_RenderText_Solid( score_font, "2", white_color );
    SDL_Surface *font_surf_number_3 = TTF_RenderText_Solid( score_font, "3", white_color );
    SDL_Surface *font_surf_number_4 = TTF_RenderText_Solid( score_font, "4", white_color );
    SDL_Surface *font_surf_number_5 = TTF_RenderText_Solid( score_font, "5", white_color );
    SDL_Surface *font_surf_number_6 = TTF_RenderText_Solid( score_font, "6", white_color );
    SDL_Surface *font_surf_number_7 = TTF_RenderText_Solid( score_font, "7", white_color );
    SDL_Surface *font_surf_number_8 = TTF_RenderText_Solid( score_font, "8", white_color );
    SDL_Surface *font_surf_number_9 = TTF_RenderText_Solid( score_font, "9", white_color );
    SDL_Surface *font_surf_number_0 = TTF_RenderText_Solid( score_font, "0", white_color );

    SDL_Surface *frame_w = SDL_CreateRGBSurface( 0, 470, 200, 32, 0, 0, 0, 0 );
    SDL_Surface *frame_b = SDL_CreateRGBSurface( 0, 460, 190, 32, 0, 0, 0, 0 );
    
    SDL_FillRect( frame_w, NULL, white );
    SDL_FillRect( frame_b, NULL, black );
    
    SDL_Surface *frame2_w = SDL_CreateRGBSurface( 0, 470, 200, 32, 0, 0, 0, 0 );
    SDL_Surface *frame2_b = SDL_CreateRGBSurface( 0, 460, 190, 32, 0, 0, 0, 0 );
    
    SDL_FillRect( frame2_w, NULL, white );
    SDL_FillRect( frame2_b, NULL, black );

    SDL_Rect frect;
    
    Mix_Chunk *sound_menu = Mix_LoadWAV( "/home/raiya/Documents/CPP/TEST/sfx_menu_move4.wav" );
    Mix_Chunk *sound_food = Mix_LoadWAV( "/home/raiya/Documents/CPP/TEST/sfx_sound_neutral8.wav" );
    Mix_Chunk *sound_dir = Mix_LoadWAV( "/home/raiya/Documents/CPP/TEST/sfx_movement_footsteps5.wav" );
    Mix_Chunk *sound_pause_in = Mix_LoadWAV( "/home/raiya/Documents/CPP/TEST/sfx_sounds_pause2_in.wav" );
    Mix_Chunk *sound_pause_out = Mix_LoadWAV( "/home/raiya/Documents/CPP/TEST/sfx_sounds_pause2_out.wav" );
    
    
    vector<int> snake_x;
    vector<int> snake_y;

    Food apple( red );
    apple.generate();
    
    snake_x.push_back( 320 );
    snake_y.push_back( 240 );
    
    
    int dir_x = 0;
    int dir_y = 0;
    int score_size = 0;
    string score;
    
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
                                    if ( play_sound ) {
                                        Mix_PlayChannel(-1, sound_menu, 0);
                                    }
                                    menu_number = back;
                                    mode_number = game;
                                }
                                else if ( menu_number == menu::options ) {
                                    if ( play_sound ) {
                                        Mix_PlayChannel(-1, sound_menu, 0);
                                    }
                                    menu_number = back;
                                    mode_number = options_screen;
                                }
                                else {
                                    if ( play_sound ) {
                                        Mix_PlayChannel(-1, sound_menu, 0);
                                    }
                                    running = false;
                                }
                                break;
                            case SDLK_w:
                                if ( menu_number == menu::start ) {
                                    if ( play_sound ) {
                                        Mix_PlayChannel(-1, sound_menu, 0);
                                    }
                                    menu_number = quit;
                                }
                                else if ( menu_number == menu::options ) {
                                    if ( play_sound ) {
                                        Mix_PlayChannel(-1, sound_menu, 0);
                                    }
                                    menu_number = start;
                                }
                                else {
                                    if ( play_sound ) {
                                        Mix_PlayChannel(-1, sound_menu, 0);
                                    }
                                    menu_number = options;
                                }
                                break;
                            case SDLK_s:
                                if ( menu_number == menu::start ) {
                                    if ( play_sound ) {
                                        Mix_PlayChannel(-1, sound_menu, 0);
                                    }
                                    menu_number = options;
                                }
                                else if ( menu_number == menu::options ) {
                                    if ( play_sound ) {
                                        Mix_PlayChannel(-1, sound_menu, 0);
                                    }
                                    menu_number = quit;
                                }
                                else {
                                    if ( play_sound ) {
                                        Mix_PlayChannel(-1, sound_menu, 0);
                                    }
                                    menu_number = start;
                                }
                                break;
                            case SDLK_UP:
                                if ( menu_number == menu::start ) {
                                    if ( play_sound ) {
                                        Mix_PlayChannel(-1, sound_menu, 0);
                                    }
                                    menu_number = quit;
                                }
                                else if ( menu_number == menu::options ) {
                                    if ( play_sound ) {
                                        Mix_PlayChannel(-1, sound_menu, 0);
                                    }
                                    menu_number = start;
                                }
                                else {
                                    if ( play_sound ) {
                                        Mix_PlayChannel(-1, sound_menu, 0);
                                    }
                                    menu_number = options;
                                }
                                break;
                            case SDLK_DOWN:
                                if ( menu_number == menu::start ) {
                                    if ( play_sound ) {
                                        Mix_PlayChannel(-1, sound_menu, 0);
                                    }
                                    menu_number = options;
                                }
                                else if ( menu_number == menu::options ) {
                                    if ( play_sound ) {
                                        Mix_PlayChannel(-1, sound_menu, 0);
                                    }
                                    menu_number = quit;
                                }
                                else {
                                    if ( play_sound ) {
                                        Mix_PlayChannel(-1, sound_menu, 0);
                                    }
                                    menu_number = start;
                                }
                                break;
                        }
                        break;
                    case mode::options_screen:
                        switch ( event.key.keysym.sym ) {
                            case SDLK_RETURN:
                                if ( menu_number == menu::back ) {
                                    if ( play_sound ) {
                                        Mix_PlayChannel(-1, sound_menu, 0);
                                    }
                                    menu_number = options;
                                    mode_number = starting_screen;
                                }
                                break;
                            case SDLK_w:
                                if ( menu_number == menu::back ) {
                                    if ( play_sound ) {
                                        Mix_PlayChannel(-1, sound_menu, 0);
                                    }
                                    menu_number = sound;
                                }
                                else if ( menu_number == menu::sound ) {
                                    if ( play_sound ) {
                                        Mix_PlayChannel(-1, sound_menu, 0);
                                    }
                                    menu_number = death;
                                }
                                else {
                                    if ( play_sound ) {
                                        Mix_PlayChannel(-1, sound_menu, 0);
                                    }
                                    menu_number = back;
                                }
                                break;
                            case SDLK_s:
                                if ( menu_number == menu::back ) {
                                    if ( play_sound ) {
                                        Mix_PlayChannel(-1, sound_menu, 0);
                                    }
                                    menu_number = death;
                                }
                                else if ( menu_number == death ) {
                                    if ( play_sound ) {
                                        Mix_PlayChannel(-1, sound_menu, 0);
                                    }
                                    menu_number = sound;
                                }
                                else {
                                    if ( play_sound ) {
                                        Mix_PlayChannel(-1, sound_menu, 0);
                                    }
                                    menu_number = back;
                                }
                                break;
                            case SDLK_UP:
                                if ( menu_number == menu::back ) {
                                    if ( play_sound ) {
                                        Mix_PlayChannel(-1, sound_menu, 0);
                                    }
                                    menu_number = sound;
                                }
                                else if ( menu_number == menu::sound ) {
                                    if ( play_sound ) {
                                        Mix_PlayChannel(-1, sound_menu, 0);
                                    }
                                    menu_number = death;
                                }
                                else {
                                    if ( play_sound ) {
                                        Mix_PlayChannel(-1, sound_menu, 0);
                                    }
                                    menu_number = back;
                                }
                                break;
                            case SDLK_DOWN:
                                if ( menu_number == menu::back ) {
                                    if ( play_sound ) {
                                        Mix_PlayChannel(-1, sound_menu, 0);
                                    }
                                    menu_number = death;
                                }
                                else if ( menu_number == death ) {
                                    if ( play_sound ) {
                                        Mix_PlayChannel(-1, sound_menu, 0);
                                    }
                                    menu_number = sound;
                                }
                                else {
                                    if ( play_sound ) {
                                        Mix_PlayChannel(-1, sound_menu, 0);
                                    }
                                    menu_number = back;
                                }
                                break;
                            case SDLK_d:
                                if ( menu_number == menu::death ) {
                                    if ( play_sound ) {
                                        Mix_PlayChannel(-1, sound_menu, 0);
                                    }
                                    if ( !edge_death ) {
                                        edge_death = true;
                                    }
                                    else {
                                        edge_death = false;
                                    }
                                }
                                else if ( menu_number == menu::sound ) {
                                    if ( play_sound ) {
                                        Mix_PlayChannel(-1, sound_menu, 0);
                                    }
                                    if ( play_sound ) {
                                        play_sound = false;
                                    }
                                    else {
                                        play_sound = true;
                                    }
                                }
                                break;
                            case SDLK_a:
                                if ( menu_number == menu::death ) {
                                    if ( play_sound ) {
                                        Mix_PlayChannel(-1, sound_menu, 0);
                                    }
                                    if ( !edge_death ) {
                                        edge_death = true;
                                    }
                                    else {
                                        edge_death = false;
                                    }
                                }
                                else if ( menu_number == menu::sound ) {
                                    if ( play_sound ) {
                                        Mix_PlayChannel(-1, sound_menu, 0);
                                    }
                                    if ( play_sound ) {
                                        play_sound = false;
                                    }
                                    else {
                                        play_sound = true;
                                    }
                                }
                                break;
                            case SDLK_RIGHT:
                                if ( menu_number == menu::death ) {
                                    if ( play_sound ) {
                                        Mix_PlayChannel(-1, sound_menu, 0);
                                    }
                                    if ( !edge_death ) {
                                        edge_death = true;
                                    }
                                    else {
                                        edge_death = false;
                                    }
                                }
                                else if ( menu_number == menu::sound ) {
                                    if ( play_sound ) {
                                        Mix_PlayChannel(-1, sound_menu, 0);
                                    }
                                    if ( play_sound ) {
                                        play_sound = false;
                                    }
                                    else {
                                        play_sound = true;
                                    }
                                }
                                break;
                            case SDLK_LEFT:
                                if ( menu_number == menu::death ) {
                                    if ( play_sound ) {
                                        Mix_PlayChannel(-1, sound_menu, 0);
                                    }
                                    if ( !edge_death ) {
                                        edge_death = true;
                                    }
                                    else {
                                        edge_death = false;
                                    }
                                }
                                else if ( menu_number == menu::sound ) {
                                    if ( play_sound ) {
                                        Mix_PlayChannel(-1, sound_menu, 0);
                                    }
                                    if ( play_sound ) {
                                        play_sound = false;
                                    }
                                    else {
                                        play_sound = true;
                                    }
                                }
                                break;
                            
                        }
                        break;
                    case mode::game:
                        switch ( event.key.keysym.sym ) {
                            case SDLK_d:
                                if ( total > 0 ) {
                                    if ( !check_reverse( snake_x, snake_y, 1, 0 ) ) {
                                        if ( play_sound ) {
                                            Mix_PlayChannel(-1, sound_dir, 0);
                                        }
                                        dir_x = 1;
                                        dir_y = 0;
                                    }
                                }
                                else {
                                    if ( play_sound ) {
                                            Mix_PlayChannel(-1, sound_dir, 0);
                                    }
                                    dir_x = 1;
                                    dir_y = 0;
                                }
                                
                                break;
                            case SDLK_w:
                                if ( total > 0 ) {
                                    if ( !check_reverse( snake_x, snake_y, 0, -1 ) ) {
                                        if ( play_sound ) {
                                            Mix_PlayChannel(-1, sound_dir, 0);
                                        }
                                        dir_x = 0;
                                        dir_y = -1;
                                    }
                                }
                                else {
                                    if ( play_sound ) {
                                        Mix_PlayChannel(-1, sound_dir, 0);
                                    }
                                    dir_x = 0;
                                    dir_y = -1;
                                }
                                
                                break;
                            case SDLK_a:
                                if ( total > 0 ) {
                                    if ( !check_reverse( snake_x, snake_y, -1, 0 ) ) {
                                        if ( play_sound ) {
                                            Mix_PlayChannel(-1, sound_dir, 0);
                                        }
                                        dir_x = -1;
                                        dir_y = 0;
                                    }
                                }
                                else {
                                    if ( play_sound ) {
                                            Mix_PlayChannel(-1, sound_dir, 0);
                                    }
                                    dir_x = -1;
                                    dir_y = 0;
                                }
                                
                                break;
                            case SDLK_s:
                                if ( total > 0 ) {
                                    if ( !check_reverse( snake_x, snake_y, 0, 1 ) ) {
                                        if ( play_sound ) {
                                            Mix_PlayChannel(-1, sound_dir, 0);
                                        }
                                        dir_x = 0;
                                        dir_y = 1;
                                    }
                                }
                                else {
                                    if ( play_sound ) {
                                        Mix_PlayChannel(-1, sound_dir, 0);
                                    }
                                    dir_x = 0;
                                    dir_y = 1;
                                }
                                
                                break;
                            case SDLK_RIGHT:
                                if ( total > 0 ) {
                                    if ( !check_reverse( snake_x, snake_y, 1, 0 ) ) {
                                        if ( play_sound ) {
                                            Mix_PlayChannel(-1, sound_dir, 0);
                                        }
                                        dir_x = 1;
                                        dir_y = 0;
                                    }
                                }
                                else {
                                    if ( play_sound ) {
                                            Mix_PlayChannel(-1, sound_dir, 0);
                                    }
                                    dir_x = 1;
                                    dir_y = 0;
                                }
                                
                                break;
                            case SDLK_UP:
                                if ( total > 0 ) {
                                    if ( !check_reverse( snake_x, snake_y, 0, -1 ) ) {
                                        if ( play_sound ) {
                                            Mix_PlayChannel(-1, sound_dir, 0);
                                        }
                                        dir_x = 0;
                                        dir_y = -1;
                                    }
                                }
                                else {
                                    if ( play_sound ) {
                                        Mix_PlayChannel(-1, sound_dir, 0);
                                    }
                                    dir_x = 0;
                                    dir_y = -1;
                                }
                                
                                break;
                            case SDLK_LEFT:
                                if ( total > 0 ) {
                                    if ( !check_reverse( snake_x, snake_y, -1, 0 ) ) {
                                        if ( play_sound ) {
                                            Mix_PlayChannel(-1, sound_dir, 0);
                                        }
                                        dir_x = -1;
                                        dir_y = 0;
                                    }
                                }
                                else {
                                    if ( play_sound ) {
                                        Mix_PlayChannel(-1, sound_dir, 0);
                                    }
                                    dir_x = -1;
                                    dir_y = 0;
                                }
                                
                                break;
                            case SDLK_DOWN:
                                if ( total > 0 ) {
                                    if ( !check_reverse( snake_x, snake_y, 0, 1 ) ) {
                                        if ( play_sound ) {
                                            Mix_PlayChannel(-1, sound_dir, 0);
                                        }
                                        dir_x = 0;
                                        dir_y = 1;
                                    }
                                }
                                else {
                                    if ( play_sound ) {
                                        Mix_PlayChannel(-1, sound_dir, 0);
                                    }
                                    dir_x = 0;
                                    dir_y = 1;
                                }
                                
                                break;
                            case SDLK_SPACE:
                                if ( play_sound ) {
                                    Mix_PlayChannel(-1, sound_pause_in, 0);
                                }
                                mode_number = pause_screen;
                                break;
                        }
                        break;
                    case mode::pause_screen:
                        if ( event.key.keysym.sym == SDLK_SPACE ) {
                            if ( play_sound ) {
                                    Mix_PlayChannel(-1, sound_pause_out, 0);
                            }
                            mode_number = game;
                        }
                        
                        break;
                    case mode::game_over:
                        switch ( event.key.keysym.sym ) {
                            case SDLK_RETURN:
                                if ( menu_number == menu::quit ) {
                                    if ( play_sound ) {
                                        Mix_PlayChannel(-1, sound_dir, 0);
                                    }
                                    running = false;
                                }
                                else {
                                    if ( play_sound ) {
                                        Mix_PlayChannel(-1, sound_dir, 0);
                                    }
                                    total = 0;
                                    dir_x = 0;
                                    dir_y = 0;
                                    
                                    apple.generate();
                                    
                                    snake_x.clear();
                                    snake_y.clear();
                                    
                                    snake_x.push_back( 320 );
                                    snake_y.push_back( 240 );
                                    
                                    snake_x.shrink_to_fit();
                                    snake_y.shrink_to_fit();
                                    
                                    mode_number = game;
                                }
                            case SDLK_w:
                                if ( menu_number == menu::try_again ) {
                                    if ( play_sound ) {
                                        Mix_PlayChannel(-1, sound_dir, 0);
                                    }
                                    menu_number = quit;
                                }
                                else {
                                    if ( play_sound ) {
                                        Mix_PlayChannel(-1, sound_dir, 0);
                                    }
                                    menu_number = try_again;
                                }
                                break;
                            case SDLK_s:
                                if ( menu_number == menu::try_again ) {
                                    if ( play_sound ) {
                                        Mix_PlayChannel(-1, sound_dir, 0);
                                    }
                                    menu_number = quit;
                                }
                                else {
                                    if ( play_sound ) {
                                        Mix_PlayChannel(-1, sound_dir, 0);
                                    }
                                    menu_number = try_again;
                                }
                                break;
                            case SDLK_UP:
                                if ( menu_number == menu::try_again ) {
                                    if ( play_sound ) {
                                        Mix_PlayChannel(-1, sound_dir, 0);
                                    }
                                    menu_number = quit;
                                }
                                else {
                                    if ( play_sound ) {
                                        Mix_PlayChannel(-1, sound_dir, 0);
                                    }
                                    menu_number = try_again;
                                }
                                break;
                            case SDLK_DOWN:
                                if ( menu_number == menu::try_again ) {
                                    if ( play_sound ) {
                                        Mix_PlayChannel(-1, sound_dir, 0);
                                    }
                                    menu_number = quit;
                                }
                                else {
                                    if ( play_sound ) {
                                        Mix_PlayChannel(-1, sound_dir, 0);
                                    }
                                    menu_number = try_again;
                                }
                                break;
                        }
                        break;
                
                }
                
            }
             
                
        }
        
        
        switch ( mode_number ) {
            case mode::starting_screen:  
                SDL_FillRect( screen, NULL, black );
                
                frect.x = 92;
                frect.y = 60;
                
                SDL_BlitSurface( font_surf_title, NULL, screen, &frect );
                
                frect.x = 100;
                frect.y = 220;
                
                if ( menu_number != menu::start ) {
                    SDL_BlitSurface( font_surf_menu_start, NULL, screen, &frect );
                }
                else {
                    SDL_BlitSurface( font_surf_menu_start_selected, NULL, screen, &frect );

                }
                
                frect.y = 280;
                
                if ( menu_number != menu::options ) {
                    SDL_BlitSurface( font_surf_menu_options, NULL, screen, &frect );
                }
                else {
                    SDL_BlitSurface( font_surf_menu_options_selected, NULL, screen, &frect );
                }
                
                frect.y = 340;
                
                if ( menu_number != menu::quit ) {
                    SDL_BlitSurface( font_surf_menu_quit, NULL, screen, &frect );
                }
                else {
                    SDL_BlitSurface( font_surf_menu_quit_selected, NULL, screen, &frect );
                }
                
                frect.x = 50;
                frect.y = 450;
                
                SDL_BlitSurface( font_surf_controls, NULL, screen, &frect );
                
                SDL_UpdateWindowSurface( window );

                
                break;
            case mode::game:
                
                SDL_Delay( 120 );
                
                    check_fruit( apple, total, snake_x, snake_y, sound_food, play_sound );
                    
                    frect.y = 5;
                    frect.x = 390;
                    
                    score = to_string(total);
                    score_size = score.length();
                    
                    SDL_FillRect( screen, NULL, black );
                    
                    SDL_BlitSurface( font_surf_score, NULL, screen, &frect );
                    
                    frect.x = 606 - 32*score_size;
                
                    for ( int i = 0; i < score_size; i++ ) {
                        frect.x = frect.x + 32;
                        switch ( score[i] ) {
                            case '1':
                                SDL_BlitSurface( font_surf_number_1, NULL, screen, &frect );
                                break;
                            case '2':
                                SDL_BlitSurface( font_surf_number_2, NULL, screen, &frect );
                                break;
                            case '3':
                                SDL_BlitSurface( font_surf_number_3, NULL, screen, &frect );
                                break;
                            case '4':
                                SDL_BlitSurface( font_surf_number_4, NULL, screen, &frect );
                                break;
                            case '5':
                                SDL_BlitSurface( font_surf_number_5, NULL, screen, &frect );
                                break;
                            case '6':
                                SDL_BlitSurface( font_surf_number_6, NULL, screen, &frect );
                                break;
                            case '7':
                                SDL_BlitSurface( font_surf_number_7, NULL, screen, &frect );
                                break;
                            case '8':
                                SDL_BlitSurface( font_surf_number_8, NULL, screen, &frect );
                                break;
                            case '9':
                                SDL_BlitSurface( font_surf_number_9, NULL, screen, &frect );
                                break;
                            case '0':
                                SDL_BlitSurface( font_surf_number_0, NULL, screen, &frect );
                                break;
                        }
                    }
                    
                    if ( !edge_death ) {
                        if ( !check_border( dir_x, dir_y, snake_x, snake_y ) ) {
                            move_snake( snake_x, snake_y, total, white, screen, dir_x, dir_y );
                        }
                    }
                    else {
                        move_snake( snake_x, snake_y, total, white, screen, dir_x, dir_y );
                    }
                    draw_snake( snake_x, snake_y, total, white, screen );
                
                    apple.draw( screen );
                    SDL_UpdateWindowSurface( window );
                    
                    if ( check_collision( snake_x, snake_y, total ) ) {
                        menu_number = try_again;
                        mode_number = game_over;
                    }
                    
                    if ( edge_death ) {
                        if ( check_border_death( dir_x, dir_y, snake_x, snake_y ) ) {
                            menu_number = try_again;
                            mode_number = game_over;
                        }
                    }
                
                break;
            case mode::pause_screen:
                SDL_FillRect( screen, NULL, black );
                
                frect.x = 155;
                frect.y = 60;
                
                SDL_BlitSurface( font_surf_pause, NULL, screen, &frect );
                
                SDL_UpdateWindowSurface( window );

                
                break;
            case mode::game_over:
                SDL_FillRect( screen, NULL, black );
                
                frect.x = 80;
                frect.y = 80;
                
                SDL_BlitSurface( frame_w, NULL, screen, &frect );
                
                frect.x = frect.x + 5;
                frect.y = frect.y + 5;
                
                SDL_BlitSurface( frame_b, NULL, screen, &frect );
                
                frect.x = 120;
                frect.y = 120;
                
                SDL_BlitSurface( font_surf_game_over, NULL, screen, &frect );
                
                frect.y = 200;
                
                SDL_BlitSurface( font_surf_score, NULL, screen, &frect );
                
                frect.x = 400;
                
                score_size = score.length();
                
                for ( int i = 0; i < score_size; i++ ) {
                    frect.x = frect.x + 32;
                    switch ( score[i] ) {
                        case '1':
                            SDL_BlitSurface( font_surf_number_1, NULL, screen, &frect );
                            break;
                        case '2':
                            SDL_BlitSurface( font_surf_number_2, NULL, screen, &frect );
                            break;
                        case '3':
                            SDL_BlitSurface( font_surf_number_3, NULL, screen, &frect );
                            break;
                        case '4':
                            SDL_BlitSurface( font_surf_number_4, NULL, screen, &frect );
                            break;
                        case '5':
                            SDL_BlitSurface( font_surf_number_5, NULL, screen, &frect );
                            break;
                        case '6':
                            SDL_BlitSurface( font_surf_number_6, NULL, screen, &frect );
                            break;
                        case '7':
                            SDL_BlitSurface( font_surf_number_7, NULL, screen, &frect );
                            break;
                        case '8':
                            SDL_BlitSurface( font_surf_number_8, NULL, screen, &frect );
                            break;
                        case '9':
                            SDL_BlitSurface( font_surf_number_9, NULL, screen, &frect );
                            break;
                        case '0':
                            SDL_BlitSurface( font_surf_number_0, NULL, screen, &frect );
                            break;
                    }
                }
                
                frect.x = 210;
                frect.y = 320;
                
                if ( menu_number == menu::try_again ) {
                    SDL_BlitSurface( font_surf_try_again_selected, NULL, screen, &frect );
                }
                else {
                    SDL_BlitSurface( font_surf_try_again, NULL, screen, &frect );
                }
                
                frect.x = 268;
                frect.y = 370;
                
                if ( menu_number != menu::quit ) {
                    SDL_BlitSurface( font_surf_menu_quit, NULL, screen, &frect );
                }
                else {
                    SDL_BlitSurface( font_surf_menu_quit_selected, NULL, screen, &frect );
                }
                
                SDL_UpdateWindowSurface( window );
                
                break;
            case mode::options_screen:
                SDL_FillRect( screen, NULL, black );

                frect.x = 88;
                frect.y = 30;
                
                SDL_BlitSurface( font_surf_options, NULL, screen, &frect );
                
                frect.x = 80;
                frect.y = 150;
                
                SDL_BlitSurface( frame_w, NULL, screen, &frect );
                
                frect.x = frect.x + 5;
                frect.y = frect.y + 5;
                
                SDL_BlitSurface( frame_b, NULL, screen, &frect );
                
                frect.x = 268;
                frect.y = 390;
                
                if ( menu_number != menu::back ) {
                    SDL_BlitSurface( font_surf_menu_back, NULL, screen, &frect );
                }
                else {
                    SDL_BlitSurface( font_surf_menu_back_selected, NULL, screen, &frect );
                }
                
                frect.x = 110;
                frect.y = 190;
                
                SDL_BlitSurface( font_surf_death, NULL, screen, &frect );
                
                frect.x = 460;
                
                if ( menu_number != menu::death ) {
                    if ( !edge_death ) {
                        SDL_BlitSurface( font_surf_menu_no, NULL, screen, &frect );
                    }
                    else {
                        SDL_BlitSurface( font_surf_menu_yes, NULL, screen, &frect );
                    }
                }
                else {
                     if ( !edge_death ) {
                        SDL_BlitSurface( font_surf_menu_no_selected, NULL, screen, &frect );
                    }
                    else {
                        SDL_BlitSurface( font_surf_menu_yes_selected, NULL, screen, &frect );
                    }
                }
                
                frect.x = 110;
                frect.y = 260;
                
                SDL_BlitSurface( font_surf_sound, NULL, screen, &frect );
                
                frect.x = 460;
                
                if ( menu_number != menu::sound ) {
                    if ( !play_sound ) {
                        SDL_BlitSurface( font_surf_menu_no, NULL, screen, &frect );
                    }
                    else {
                        SDL_BlitSurface( font_surf_menu_yes, NULL, screen, &frect );
                    }
                }
                else {
                     if ( !play_sound ) {
                        SDL_BlitSurface( font_surf_menu_no_selected, NULL, screen, &frect );
                    }
                    else {
                        SDL_BlitSurface( font_surf_menu_yes_selected, NULL, screen, &frect );
                    }
                }


                
                SDL_UpdateWindowSurface( window );
                break;
        }

        
        cap_framerate( starting_tick );
    }
    
    //////////////////////////////////////////////////////////////////////////////
    
    TTF_CloseFont( font );
    TTF_CloseFont( menu_font );
    TTF_CloseFont( pause_font );
    TTF_CloseFont( score_font );
    TTF_CloseFont( game_over_font );
    TTF_Quit();
    Mix_CloseAudio();
    SDL_DestroyWindow( window );
    SDL_Quit();
    return 0;
}
