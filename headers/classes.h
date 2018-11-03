#ifndef CLASSES_H
#define CLASSES_H

#include <vector>
#include <SDL2/SDL.h>


using namespace std;

class Sprite{
  
    private:
        SDL_Surface *image;
        SDL_Rect rect;
        
        int origin_x, origin_y;
        
    public:
        Sprite( Uint32 color, int x, int y, int w = 16, int h = 16 );
        
        void update();
        
        void draw( SDL_Surface *destination );
        
        void set_values( int new_x, int new_y );
        
        bool check_border( int dir_x, int dir_y );
        
        int value_x();
        
        int value_y();
       
        SDL_Surface* get_image() const;
       
        bool operator==( const Sprite &other ) const;
  
};


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