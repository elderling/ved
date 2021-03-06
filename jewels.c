#include <vic20.h>
#include <conio.h>
//#include <stdlib.h>
#include <joystick.h>

#define PLAYFIELD_X 8
#define PLAYFIELD_Y 8

void init_playfield();
void draw_playfield( unsigned char [PLAYFIELD_X][PLAYFIELD_Y] );
void init_playfield( unsigned char [PLAYFIELD_X][PLAYFIELD_Y] );
void clear_groups_of_3_or_more();
unsigned char must_clear_jewel( char, char, unsigned char);
unsigned char up_down_match( char x, char y, unsigned char color);
unsigned char left_right_match( char x, char y, unsigned char color);

unsigned char playfield[PLAYFIELD_X][PLAYFIELD_Y] ={ 
{'a','b','c','d','e', 'f', 'g', 'h'},
{'b','c','d','e','f', 'g', 'h', 'i'},
{'c','d','e','f','g', 'h', 'i', 'j'},
{'d','e','f','g','h', 'i', 'j', 'k'},
{'e','f','g','h','i', 'j', 'k', 'l'},
{'f','g','h','i','j', 'k', 'l', 'm'},
{'g','h','i','j','k', 'l', 'm', 'n'},
{'h','i','j','k','l', 'm', 'n', 'o'},
};

unsigned char clear_jewel_tracker[PLAYFIELD_X][PLAYFIELD_Y];

int main(void) {
  unsigned char screen_x;
  unsigned char screen_y;

  screensize( &screen_x, &screen_y);

  clrscr();
  init_playfield(clear_jewel_tracker);
  draw_playfield( playfield );
  gotoxy(0,19);
  
  cprintf("%d, %d", screen_x, screen_y);
  return 0;
}

void init_playfield( unsigned char playfield[PLAYFIELD_X][PLAYFIELD_Y] ) {
  unsigned char x,y;
  for (x = 0; x < PLAYFIELD_X; x++) {
    for (y = 0; y < PLAYFIELD_Y; y++) {
      playfield[x][y] = 1;
    }
  }
}

void draw_playfield( unsigned char playfield[PLAYFIELD_X][PLAYFIELD_Y] ) {

  unsigned char x,y;
    for (x = 0; x < PLAYFIELD_X; x++) {
      for (y = 0; y < PLAYFIELD_Y; y++) {
        cputcxy(x,y, playfield[x][y]);
      }
  }
}

void clear_groups_of_3_or_more() {
  signed char x,y;
  unsigned char current_jewel_color;
    for (x = 0; x < PLAYFIELD_X; x++) {
      for (y = 0; y < PLAYFIELD_Y; y++) {
        current_jewel_color = playfield[x][y];
        if ( must_clear_jewel(x,y,current_jewel_color) ) {
          clear_jewel_tracker[x][y] = 1;
        }
      }
  }
}

unsigned char must_clear_jewel( char x, char y, unsigned char color) {
  if ( up_down_match( x, y, color) ) {
    return 1;
  }
  if ( left_right_match( x, y, color) ) {
    return 1;
  }
  return 0;
}

unsigned char up_down_match( char x, char y, unsigned char color) {
  if ( y == 0 || y == PLAYFIELD_Y - 1 ) {
    return 0;
  }
  if ( playfield[x][y-1] == color && playfield[x][y+1] == color ) {
    return 1;
  }
  return 0;
}

unsigned char left_right_match( char x, char y, unsigned char color) {
  if ( x == 0 || x == PLAYFIELD_X - 1 ) {
    return 0;
  }
  if ( playfield[x-1][y] == color && playfield[x+1][y] == color ) {
    return 1;
  }
  return 0;
}
