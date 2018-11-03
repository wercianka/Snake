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


SpriteGroup SpriteGroup::copy() {
    SpriteGroup new_group;
        
        for ( int i = 0; i < sprites_size; i++ ) {
            new_group.add( sprites[i] );
        }
        
    return new_group;
}
        
void SpriteGroup::add( Sprite *sprite ) {
        sprites.push_back( sprite );
        
        sprites_size = sprites.size();
    }
    
        
void SpriteGroup::remove( Sprite sprite_object ) {
    for ( int i = 0; i < sprites_size; i++ ) {
        if ( *sprites[i] == sprite_object ) {
            sprites.erase( sprites.begin() + i );
        }
    }
            
    sprites_size = sprites.size();
            
}
        
bool SpriteGroup::has( Sprite sprite_object ) {
    for ( int i = 0; i < sprites_size; i++ ) {
        if ( *sprites[i] == sprite_object ) {
            return true;
        }
    }
    return false;
}
        
void SpriteGroup::update() {
    if ( !sprites.empty() ) {
        for ( int i = 0; i < sprites_size; i++ ) {
            sprites[i]->update();
        }
    }
            
}
        
void SpriteGroup::draw( SDL_Surface *destination ) {
    if ( !sprites.empty() ) {
        
        for ( int i = 0; i < sprites_size; i++ ) {
            sprites[i]->draw( destination );
        }
    }
            
}
        
void SpriteGroup::empty() {
    sprites.clear();
    
    sprites_size = sprites.size();
}

int SpriteGroup::size() {
    return sprites_size;
}
        
vector <Sprite*> SpriteGroup::get_sprites() {
    return sprites;
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
