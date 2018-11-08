#include "functions.h"


void check_fruit( Food &food_object, 
                  int &total, 
                  vector<int>& snake_x,
                  vector<int>& snake_y) {
    if ( ( food_object.value_x() == snake_x[0] ) && ( food_object.value_y() == snake_y[0] ) ) {
        food_object.generate();
        total = total + 1;
        snake_x.push_back( 0 );
        snake_y.push_back( 0 );
    }
}

void draw_snake(const vector<int>& snake_x, 
               const vector<int>& snake_y, 
               int total, 
               Uint32 color, 
               SDL_Surface *destination ) {
                   
    SDL_Surface *image;
    SDL_Rect rect;
                   
    image = SDL_CreateRGBSurface( 0, 16, 16, 32, 0, 0, 0, 0 );
    
    SDL_FillRect( image, NULL, color );
                   
    for ( int i = total; i >= 0; i-- ) {
        rect.x = snake_x[i];
        rect.y = snake_y[i];
        SDL_BlitSurface( image, NULL, destination, &rect );

    }
}

void move_snake( vector<int>& snake_x, 
                vector<int>& snake_y, 
                int total, 
                Uint32 color, 
                SDL_Surface *destination, 
                int dir_x,
                int dir_y) {
                    
    for ( int i = total; i >= 0; i-- ) {
        if ( i != 0 ) {
            snake_x[i] = snake_x[i-1];
            snake_y[i] = snake_y[i-1];
        }
        else {
            snake_x[0] = snake_x[0] + dir_x*16;
            snake_y[0] = snake_y[0] + dir_y*16;
        }

    }
}

bool check_collision( const vector<int>& snake_x, const vector<int>& snake_y, int total ) {
    for ( int i = 1; i <= total; i++ ) {
        if ( ( snake_x[i] == snake_x[0] ) && ( snake_y[i] == snake_y[0] ) ) {
            return true;
        }
    }
    return false;
}

bool check_reverse( const vector<int>& snake_x, const vector<int>& snake_y, int dir_x, int dir_y)  {
    if ( ( (snake_x[0] + 16*dir_x) == (snake_x[1]) ) && ( (snake_y[0] + 16*dir_y) == snake_y[1] ) ) {
        return true;
    }
    else {
        return false;
    }
}

bool check_border( int dir_x, int dir_y, const vector<int>& snake_x, const vector<int>& snake_y ) {
    if ( ( snake_x[0] <= 0 ) && ( dir_x == -1 )  ) {
        return true;
    }
    
    
    if ( ( snake_x[0] >= ( 640 - 16 ) ) && ( dir_x == 1 )  ) {
        return true;
    }
    
    
    if ( ( snake_y[0] <= 0 ) && ( dir_y == -1 )  ) {
        return true;
    }
    
    
    if ( ( snake_y[0] >= ( 480 - 16 ) ) && ( dir_y == 1 )  ) {
        return true;
    }
    
    return false;
}

bool check_border_death( int dir_x, int dir_y, const vector<int>& snake_x, const vector<int>& snake_y ) {
    if ( ( snake_x[0] < 0 ) && ( dir_x == -1 )  ) {
        return true;
    }
    
    
    if ( ( snake_x[0] > ( 640 - 16 ) ) && ( dir_x == 1 )  ) {
        return true;
    }
    
    
    if ( ( snake_y[0] < 0 ) && ( dir_y == -1 )  ) {
        return true;
    }
    
    
    if ( ( snake_y[0] > ( 480 - 16 ) ) && ( dir_y == 1 )  ) {
        return true;
    }
    
    return false;
}

