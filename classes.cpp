#include "classes.h"
#include <cstdlib>
#include <ctime>

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
