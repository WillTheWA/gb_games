#include <gb/gb.h>
#include <stdint.h>
#include <stdio.h>

void main(void)
{
    DISPLAY_ON;
    // Loop forever
    while(1) {
		// Game main loop processing goes here
        printf("Hello World");
        vsync();
    }
}
