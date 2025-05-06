#include <gb/gb.h>
#include <stdint.h>
#include <stdio.h>

unsigned int frame_count = 0;
unsigned int seconds = 0;

void main(void)
{
    // Turn on display
    DISPLAY_ON;

    // Start game loop
    while(1) {
        // Increment frame counter
        frame_count++;

        // Check if 60 frames have passed (roughly 1 second)
        if (frame_count >= 60) {
            frame_count = 0;  // Reset frame count after 1 second
            seconds++;        // Increment seconds
        }

        // Timer printing logic
        unsigned int min_temp = seconds / 60;
        unsigned int sec_temp = seconds % 60;
        char timer_str[6];  // Array to hold the formatted timer string

        if (min_temp < 10 && sec_temp < 10)
            sprintf(timer_str, "0%u:0%u", min_temp, sec_temp);
        else if (min_temp < 10)
            sprintf(timer_str, "0%u:%u", min_temp, sec_temp);
        else
            sprintf(timer_str, "%u:%u", min_temp, sec_temp);

        // Clear the background area (if needed)
        unsigned char blank_tile = 0;
        for (unsigned char y = 0; y < 18; y++) {
            for (unsigned char x = 0; x < 20; x++) {
                set_bkg_tiles(x, y, 1, 1, &blank_tile);
            }
        }

        // Set the timer string in the background area (at position 0,0)
        set_bkg_tiles(0, 0, 6, 1, timer_str);

        // Synchronize with the screen refresh rate
        vsync();
    }
}
