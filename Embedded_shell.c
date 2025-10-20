#include <stdio.h>
#include <string.h>

void help(void) {
    printf("Available commands:\n");
    printf("  help    - Show this help message\n");
    printf("  led_on  - Turn LED on\n");
    printf("  led_off - Turn LED off\n");
    printf("  exit    - Exit CLI\n");
}

int main(void) {
    char cmd[64];
    printf("Welcome to My STM32 CLI\n");
    printf("Type 'help' to see available commands\n");

    while (1) {
        printf("> ");
        fflush(stdout);

        if (fgets(cmd, sizeof(cmd), stdin) == NULL)
            break; // EOF or error

        // remove newline
        cmd[strcspn(cmd, "\r\n")] = 0;

        if (strcmp(cmd, "help") == 0) {
            help();
        } else if (strcmp(cmd, "led_on") == 0) {
            printf("Turning LED on...\n");
            // TODO: add GPIO control here
        } else if (strcmp(cmd, "led_off") == 0) {
            printf("Turning LED off...\n");
            // TODO: add GPIO control here
        } else if (strcmp(cmd, "exit") == 0) {
            printf("Goodbye!\n");
            break;
        } else if (strlen(cmd) > 0) {
            printf("Unknown command: %s\n", cmd);
        }
    }

    return 0;
}

