#include <gb/gb.h>
#include <stdint.h>
#include "typeset.h"
#include "numset.h"
#include "background_data.c"
#include "background_map.c"

// Constants
#define TILE_BLANK 44
#define SCREEN_WIDTH 20
#define SCREEN_HEIGHT 18
#define TIMER_1X 12
#define TIMER_2X 13
#define TIMER_3X 15
#define TIMER_4X 16
#define TIMER_Y 9
#define NUM_OFFSET 227

// Clear screen by filling it with blank tiles
void clear_screen() {
    set_bkg_data(0, 44, Typeset);
    static unsigned char tile_map[SCREEN_WIDTH * SCREEN_HEIGHT];
    for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++) {
        tile_map[i] = TILE_BLANK;
    }
    set_bkg_tiles(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, tile_map);
}

// Display splash screen
void splash_screen() {
    set_bkg_data(0, 44, Typeset);
    unsigned char pomodoro_map[] = {15, 14, 12, 14, 3, 14, 17, 14};
    unsigned char timer_map[] = {19, 8, 12, 4, 17, 42};
    unsigned char start_map[] = {18, 19, 0, 17, 19};

    set_bkg_tiles(6, 4, 8, 1, pomodoro_map);  // Correct tile count here
    set_bkg_tiles(7, 5, 6, 1, timer_map);
    set_bkg_tiles(7, 10, 5, 1, start_map);

    // Wait until start is pressed
    waitpad(J_START);
}

unsigned char* convert_num(int num) {
	unsigned char temp[] = {num + NUM_OFFSET};
	return temp;
}

// Entry point
void main(void) {
    SHOW_BKG;
    DISPLAY_ON;

    clear_screen();  // Clear with blank tiles
    splash_screen();  // Show splash screen
    
    // Load tiles
    set_bkg_data(0, 227, background_data);  // Loading 227 background tiles
    
    // Draw background map
    set_bkg_tiles(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, background_map);
    
    // Load Numset after background map
    set_bkg_data(227, 12, Numset);

    // Draw timer
    unsigned char game_timer_map[] = {237, 237, 238, 237, 237};
    set_bkg_tiles(TIMER_1X, TIMER_Y, 5, 1, game_timer_map);

    // Main game loop
    while (1) {
        set_bkg_tiles(TIMER_1X, TIMER_Y, 1, 1, convert_num(1));
	set_bkg_tiles(TIMER_2X, TIMER_Y, 1, 1, convert_num(2));
	set_bkg_tiles(TIMER_3X, TIMER_Y, 1, 1, convert_num(3));
	set_bkg_tiles(TIMER_4X, TIMER_Y, 1, 1, convert_num(4));
        wait_vbl_done();
    }
}
