#include <gb/gb.h>
#include <stdint.h>
#include "typeset.h"

void clear_screen() {
	// Create an array to fill the entire screen with the blank tile (index 44)
    unsigned char tile_map[20 * 18];    // Screen size is 20x18 tiles
    for (int i = 0; i < 20 * 18; i++) {
        tile_map[i] = 44;               // Set every tile to the blank character (index 44)
    }

    // Set the background with the blank character for the entire screen
    set_bkg_tiles(0, 0, 20, 18, tile_map);
}

void main(void) {
    // Load the tile set into VRAM
    set_bkg_data(0, 44, Typeset);
    clear_screen();

    // Turn on the background and display
    SHOW_BKG;
    DISPLAY_ON;

    // Start game loop
    unsigned char pomodoro_map[] = {15, 14, 12, 14, 3, 14, 17, 14};
    unsigned char timer_map[] = {19, 8, 12, 4, 17, 42};
    
    while(1) {
	// Write pomodoro timer
        set_bkg_tiles(6, 11, 8, 1, pomodoro_map);
        set_bkg_tiles(7, 12, 6, 1, timer_map);
        wait_vbl_done();
    }
}
