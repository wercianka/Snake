#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "classes.h"


void check_fruit( Food &food_object, 
                  int &total, 
                  vector<int>& snake_x,
                  vector<int>& snake_y);

void draw_snake(const vector<int>& snake_x, 
               const vector<int>& snake_y, 
               int total, 
               Uint32 color, 
               SDL_Surface *destination );

void move_snake( vector<int>& snake_x, 
                vector<int>& snake_y, 
                int total, 
                Uint32 color, 
                SDL_Surface *destination, 
                int dir_x,
                int dir_y);
                
bool check_collision( const vector<int>& snake_x, 
                      const vector<int>& snake_y, 
                      int total );

bool check_reverse( const vector<int>& snake_x, 
                    const vector<int>& snake_y, 
                    int dir_x, 
                    int dir_y);
                    
bool check_border( int dir_x, 
                   int dir_y, 
                   const vector<int>& snake_x, 
                   const vector<int>& snake_y );
                   
bool check_border_death( int dir_x, 
                         int dir_y, 
                         const vector<int>& snake_x, 
                         const vector<int>& snake_y );


#endif