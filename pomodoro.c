#include <gb/gb.h>
#include <stdint.h>
#include <stdio.h>

unsigned int frame_count = 0;
unsigned int seconds = 0;

void main(void)
{
    // Turn on display
    DISPLAY_ON;

    // Set up window
    SHOW_WIN;
    set_win_tiles(0, 0, 20, 1, "                    ");  // Initialize window area with blank spaces

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

        // Set the timer string in the window area (at position 0,0 in the window)
        set_win_tiles(0, 0, 6, 1, timer_str);

        // Synchronize with the screen refresh rate
        vsync();
    }
}
