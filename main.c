#include <gb/gb.h>
#include <stdint.h>
#include "typeset.h"

void main(void)
{
    // Load letter set tiles
    set_bkg_data(0, 44, Typeset);

    unsigned char msg[] = {0, 1, 2}; // tile indices
    set_bkg_tiles(2, 10, 3, 1, msg); // x=2, y=10, 3 tiles wide

    // Turn on background layer and display
    SHOW_BKG;
    DISPLAY_ON;

    // Start game loop
    while(1) {
        wait_vbl_done();
        //vsync();
    }
}
