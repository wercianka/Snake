#include "functions.h"


void check_fruit( Food &food_object, 
                  Sprite sprite_object, 
                  int &total, 
                  vector<int>& tail_x,
                  vector<int>& tail_y,
                  Sprite object) {
    if ( ( food_object.value_x() == sprite_object.value_x() ) && ( food_object.value_y() == sprite_object.value_y() ) ) {
        food_object.generate();
        total = total + 1;
        tail_x.push_back( object.value_x() );
        tail_y.push_back( object.value_y() );
        
        /*
        for ( int i = total-1; i >= 0; i-- ) {
        if ( i != 0 ) {
            tail_x[i] = tail_x[i-1];
            tail_y[i] = tail_y[i-1];
        }
        
        tail_x[0] = object.value_x();
        tail_y[0] = object.value_y();
        }
        */
    }
}

void draw_game( SDL_Surface *surface, 
                Uint32 color, 
                SDL_Window *window_draw, 
                SpriteGroup sprite_group, 
                Food food_sprite ) {
                    
    sprite_group.draw( surface );
    food_sprite.draw( surface );
    SDL_UpdateWindowSurface( window_draw );
}

void draw_tail(const vector<int>& tail_x, 
               const vector<int>& tail_y, 
               int total, 
               Uint32 color, 
               SDL_Surface *destination ) {
                   
    SDL_Surface *image;
    SDL_Rect rect;
                   
    image = SDL_CreateRGBSurface( 0, 16, 16, 32, 0, 0, 0, 0 );
    
    SDL_FillRect( image, NULL, color );
                   
    for ( int i = total-1; i >= 0; i-- ) {
        rect.x = tail_x[i];
        rect.y = tail_y[i];
        SDL_BlitSurface( image, NULL, destination, &rect );

    }
}

void move_tail( vector<int>& tail_x, 
                vector<int>& tail_y, 
                int total, 
                Uint32 color, 
                SDL_Surface *destination, 
                Sprite object ) {
                    
    for ( int i = total-1; i >= 0; i-- ) {
        if ( i != 0 ) {
            tail_x[i] = tail_x[i-1];
            tail_y[i] = tail_y[i-1];
        }
        else {
            tail_x[0] = object.value_x();
            tail_y[0] = object.value_y();
        }

    }
}
