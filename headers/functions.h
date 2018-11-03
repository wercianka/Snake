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
                SpriteGroup sprite_group, 
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

#endif