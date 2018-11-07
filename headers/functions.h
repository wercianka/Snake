#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "classes.h"


void check_fruit( Food &food_object, 
                  Sprite sprite_object, 
                  int &total, 
                  vector<int>& tail_x,
                  vector<int>& tail_y,
                  Sprite object);

void draw_game( SDL_Surface *surface, 
                Uint32 color, 
                SDL_Window *window_draw, 
                Sprite head, 
                Food food_sprite );

void draw_tail(const vector<int>& tail_x, 
               const vector<int>& tail_y, 
               int total, 
               Uint32 color, 
               SDL_Surface *destination );

void move_tail( vector<int>& tail_x, 
                vector<int>& tail_y, 
                int total, 
                Uint32 color, 
                SDL_Surface *destination, 
                Sprite object );
                
bool check_collision( const vector<int>& tail_x, 
                      const vector<int>& tail_y, 
                      Sprite object, 
                      int total );

bool check_reverse( const vector<int>& tail_x, 
                    const vector<int>& tail_y, 
                    Sprite object,
                    int dir_x,
                    int dir_y);


#endif