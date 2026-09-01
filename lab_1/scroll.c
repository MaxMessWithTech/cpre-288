#include "scroll.h"

#define LINE_LEN 20

/**
 * @brief Scrolls message accross the screen using lcd.h
 */
void scroll_message(char* message) {
    const int msg_len = strlen(message) + 1 + LINE_LEN;
    const char* adapted_message = (char*)malloc(sizeof(char) * msg_len);
    int i;

    // Add padding spaces
    for (i = 0; i < LINE_LEN; i++) {
        adapted_message[i] = ' ';
    }
    
    // Copy over message after spaces
    for (i = 0; i < strlen(message); i++) {
        adapted_message[i + LINE_LEN] = message[i];
    }

    // Add string end
    adapted_message[strlen(message) + LINE_LEN] = '\0';

    // Start Scroll Loop
    while (true) {
        // Clear LCD
	    lcd_clear();

        // write this itteration's chars
	    for (i = 0; i < LINE_LEN; i++) {
	        if (adapted_message[i + scroll_index] == '\0') {
	            break;
	        }
	        lcd_putc(adapted_message[i + scroll_index]);
	    }

        // Wait 0.3 seconds
	    timer_waitMicros(300000);

        // Add one to scroll_index, if it exceeds the length of the message, then loop it
	    if (++scroll_index >= msg_len) {
	        scroll_index = 0;
	    }
	}

}