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

// Number lookup table
unsigned char number_tiles[10] = {
    237, // 0
    228, // 1
    229, // 2
    230, // 3
    231, // 4
    232, // 5
    233, // 6
    234, // 7
    235, // 8
    236  // 9
};

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

    set_bkg_tiles(6, 4, 8, 1, pomodoro_map);
    set_bkg_tiles(7, 5, 6, 1, timer_map);
    set_bkg_tiles(7, 10, 5, 1, start_map);

    // Wait until start button is pressed
    waitpad(J_START);
}

// Convert 2-digit number (like minutes or seconds) to 2 tiles
void convert_2digit_to_tiles(unsigned int num, unsigned char* out) {
    out[0] = number_tiles[(num / 10) % 10];
    out[1] = number_tiles[num % 10];
}

// Entry point
void main(void) {
    SHOW_BKG;
    DISPLAY_ON;

    clear_screen();  // Clear with blank tiles
    splash_screen();  // Show splash screen
    
    // Load 227 background tiles
    set_bkg_data(0, 227, background_data);
    
    // Draw background map
    set_bkg_tiles(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, background_map);
    
    // Load Numset after background map
    set_bkg_data(227, 12, Numset);

    // Timer default start time and cycle coutn
    unsigned int minutes = 25;
    unsigned int seconds = 0;
    unsigned int cycle = 0;

    // Set min and sec tiles
    unsigned char min_tiles[2];
    unsigned char sec_tiles[2];

    while (1) {
        // Convert minutes and seconds to tile data
        convert_2digit_to_tiles(minutes, min_tiles);
        convert_2digit_to_tiles(seconds, sec_tiles);

        // Set background tiles for MM:SS at the right positions
        set_bkg_tiles(TIMER_1X, TIMER_Y, 1, 1, &min_tiles[0]);
        set_bkg_tiles(TIMER_2X, TIMER_Y, 1, 1, &min_tiles[1]);

        // Colon in between MM and SS (tile 238)
        set_bkg_tiles(14, TIMER_Y, 1, 1, (unsigned char[]){238});

        set_bkg_tiles(TIMER_3X, TIMER_Y, 1, 1, &sec_tiles[0]);
        set_bkg_tiles(TIMER_4X, TIMER_Y, 1, 1, &sec_tiles[1]);

        // Delay ~1 second
        for (int i = 0; i < 60; i++) {
            wait_vbl_done();
        }

        // Countdown logic
        if (seconds == 0) {
            if (minutes == 0) {
                // Timer done
                // Increase cycle
                cycle++;
                
                // 25 minute study, 5 minute rest for 3 cycles
                //   then 25 minute study, 15 minute rest and 
                //   reset cycle
                if (cycle == 1 || cycle == 3 || cycle == 5) {
                    minutes = 5;
                } else if (cycle == 7) {
                    minutes = 15;
                    cycle = 0;
                } else 
                    minutes = 25;
                
                // Wait until A button is pressed
                waitpad(J_A);
            } else {
                minutes--;
                seconds = 59;
            }
        } else {
            seconds--;
        }
    }
}
