#include <gb/gb.h>
#include <stdint.h>
#include "typeset.h"
#include "background_data.c"
#include "background_map.c"

// Constants
#define TILE_BLANK 44
#define SCREEN_WIDTH 20
#define SCREEN_HEIGHT 18

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

    // Wait until start is pressed and released
    waitpad(J_START);
}

// Main game loop
void game_loop() {
    // Load the background tiles and map
    set_bkg_data(44, 227, background_data);  // Loading 227 background tiles
    set_bkg_tiles(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, background_map);  // Set background map

    while (1) {
        wait_vbl_done();
        // Game logic here...
    }
}

// Entry point
void main(void) {
    SHOW_BKG;
    DISPLAY_ON;

    clear_screen();  // Clear with blank tiles
    splash_screen();  // Show splash screen
    game_loop();      // Start the main game loop
}
