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
    static unsigned char tile_map[SCREEN_WIDTH * SCREEN_HEIGHT];
    for (uint8_t i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++) {
        tile_map[i] = TILE_BLANK;
    }
    set_bkg_tiles(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, tile_map);
}

// Display splash screen
void splash_screen() {
    // "POMODORO", "TIMER!", "START"
    unsigned char pomodoro_map[] = {15, 14, 12, 14, 3, 14, 17, 14};
    unsigned char timer_map[] = {19, 8, 12, 4, 17, 42};
    unsigned char start_map[] = {18, 19, 0, 17, 19};

    set_bkg_tiles(6, 4, sizeof(pomodoro_map), 1, pomodoro_map);
    set_bkg_tiles(7, 5, sizeof(timer_map), 1, timer_map);
    set_bkg_tiles(7, 10, sizeof(start_map), 1, start_map);

    // Wait until start is pressed and released
    waitpad(J_START);
    waitpadup();
}

// Main game loop
void game_loop() {
    // Draw background
    set_bkg_tiles(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, background_map);

    while (1) {
        wait_vbl_done();
        // Game logic here...
    }
}

// Entry point
void main(void) {
    // Load tile data into VRAM
    set_bkg_data(0, TILE_BLANK, Typeset);
    set_bkg_data(TILE_BLANK, 114, background_data);  // Load after blank tiles

    SHOW_BKG;
    DISPLAY_ON;

    clear_screen();
    splash_screen();
    game_loop();
}

