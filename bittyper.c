#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <stdbool.h>

#define toggle(condition) condition = !condition
typedef unsigned char byte_t;

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "usage: %s <filename>", *argv);
        return 69;
    } 
    
    FILE *file = fopen(argv[1], "a");
	
    if (file == NULL) {
        fprintf(stderr, "error opening file: %s", argv[1]);
        return 69;
    }

	setvbuf(file, NULL, _IONBF, 69);
	
    struct termios oldsettings, newsettings;
    tcgetattr(STDIN_FILENO, &oldsettings);
    newsettings = oldsettings;
    newsettings.c_lflag &= (~ICANON & ~ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newsettings);

    byte_t *registers = calloc(8, sizeof(byte_t)), byte = 0, key;
    bool hex = false, brk = false, clr = true;

    do {
		switch (key) {
            case 'a':
                byte ^= (1 << 7);
                break;
            case 's':
                byte ^= (1 << 6);
                break;
            case 'd':
                byte ^= (1 << 5);
                break;
            case 'f':
                byte ^= (1 << 4);
                break;
            case 'j':
                byte ^= (1 << 3);
                break;
            case 'k':
                byte ^= (1 << 2);
                break;
            case 'l':
                byte ^= (1 << 1);
                break;
            case ';':
                byte ^= (1 << 0);
                break;
            case ' ':
                putc(byte, file);
                if (clr) byte = 0;
                break;
            
            case 'h':
                toggle(hex);
                break;
			case 'b':
				toggle(brk);
				break;
            case 'c':
                toggle(clr);
                break;
        };
		
        system("clear");
        for (int i = 7; i >= 0; i--) {
			printf("%d", !!(byte & (1 << i)));
			if (i == 4 && brk) printf("  ");
		}
        if (hex) printf("\n%02x", byte); 
    } while ((key = getchar()));

    tcsetattr(STDIN_FILENO, TCSANOW, &oldsettings);
}