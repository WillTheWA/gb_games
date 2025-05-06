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
	// Game main loop processing goes here
	cls();
	    
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
        if (min_temp < 10 && sec_temp < 10) 
            printf("0%u:0%u", min_temp, sec_temp);
        else if (min_temp < 10)
            printf("0%u:%u", min_temp, sec_temp);
        else
            printf("%u:%u", min_temp, sec_temp);

        // Sync screen and refresh rate
        vsync();
    }
}
