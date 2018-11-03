#include "classes.h"
#include <cstdlib>
#include <ctime>


Sprite::Sprite( Uint32 color, int x, int y, int w , int h ) {
    image = SDL_CreateRGBSurface( 0, w, h, 32, 0, 0, 0, 0 );
    
    SDL_FillRect( image, NULL, color );
    
    rect = image->clip_rect;
    
    rect.x = x;
    rect.y = y;
}
        
void Sprite::update() {
        //can be overriden
    }
        
void Sprite::draw( SDL_Surface *destination ) {
    SDL_BlitSurface( image, NULL, destination, &rect );
}
        
void Sprite::set_values ( int new_x, int new_y ) {
    rect.x = rect.x + new_x*16;
    rect.y = rect.y + new_y*16;
}

bool Sprite::check_border( int dir_x, int dir_y ) {
    if ( ( rect.x <= 0 ) && ( dir_x == -1 )  ) {
        return true;
    }
    
    
    if ( ( rect.x >= ( 640 - 16 ) ) && ( dir_x == 1 )  ) {
        return true;
    }
    
    
    if ( ( rect.y <= 0 ) && ( dir_y == -1 )  ) {
        return true;
    }
    
    
    if ( ( rect.y >= ( 480 - 16 ) ) && ( dir_y == 1 )  ) {
        return true;
    }
    
    return false;
}


int Sprite::value_x() {
     return rect.x;
}

int Sprite::value_y() {
     return rect.y;
}
       
SDL_Surface* Sprite::get_image() const {
    return image;
    }
       
bool Sprite::operator==( const Sprite &other ) const {
        return ( image == other.get_image() );
    }



Food::Food( Uint32 color ) {
    image = SDL_CreateRGBSurface( 0, 16, 16, 32, 0, 0, 0, 0 );
    
    SDL_FillRect( image, NULL, color );
    
    rect = image->clip_rect;
    
}

void Food::generate() {
    srand((int)time(0));

    
    rect.x = (rand() % 20)*16;
    rect.y = (rand() % 15)*16;
    
}

int Food::value_x() {
    return rect.x;
}

int Food::value_y() {
    return rect.y;
}

void Food::draw( SDL_Surface *destination ) {
    SDL_BlitSurface( image, NULL, destination, &rect );
}
