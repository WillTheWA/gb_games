#include <gb/gb.h>
#include <stdint.h>
#include "typeset.h"

void main(void)
{
    // Load the tile set into VRAM
    set_bkg_data(0, 44, Typeset);

    // Create an array to fill the entire screen with the blank tile (index 44)
    unsigned char tile_map[20 * 18];    // Screen size is 20x18 tiles
    for (int i = 0; i < 20 * 18; i++) {
        tile_map[i] = 44;               // Set every tile to the blank character (index 44)
    }

    // Set the background with the blank character for the entire screen
    set_bkg_tiles(0, 0, 20, 18, tile_map);

    // Turn on the background and display
    SHOW_BKG;
    DISPLAY_ON;

    // Start game loop
    unsigned char hello_map[] = {7, 4, 11, 11, 14};
    unsigned char world_map[] = {22, 14, 17, 11, 3};
    
    while(1) {
        set_bkg_tiles(0, 0, 5, 1, hello_map);
        set_bkg_tiles(0, 1, 5, 1, world_map);
        wait_vbl_done();
    }
}
