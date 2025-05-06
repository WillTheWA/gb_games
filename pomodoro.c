#include <gb/gb.h>
#include <stdint.h>
#include "typeset.h"

void main(void)
{
    // Load letter set tiles
    set_bkg_data(0, 44, Typeset);
    set_bkg_tiles(0, 0, 20, 18, 44); // x=2, y=10, 3 tiles wide

    // Turn on background layer and display
    // Start background
    SHOW_BKG;
    DISPLAY_ON;

    // Start game loop
    while(1) {
        wait_vbl_done();
    }
}
