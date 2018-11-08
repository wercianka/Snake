#ifndef CLASSES_H
#define CLASSES_H

#include <vector>
#include <SDL2/SDL.h>


using namespace std;

class Food{
    private:
        SDL_Surface *image;
        SDL_Rect rect;
        
    public:
        Food( Uint32 color );
        
        void generate();
        
        int value_x();
        
        int value_y();
        
        void draw( SDL_Surface *destination );
};

#endif