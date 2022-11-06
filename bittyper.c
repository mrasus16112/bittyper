#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <stdbool.h>

#define newline putchar('\n')
#define REGISTERS_MAX_SIZE 64
typedef unsigned char byte_t;

int input(byte_t key, byte_t *byte) {
	switch (key) {
		case 'a':
			*byte ^= (1 << 7);
			return 0;
		case 's':
			*byte ^= (1 << 6);
			return 0;
		case 'd':
			*byte ^= (1 << 5);
			return 0;
		case 'f':
			*byte ^= (1 << 4);
			return 0;
		case 'j':
			*byte ^= (1 << 3);
			return 0;
		case 'k':
			*byte ^= (1 << 2);
			return 0;
		case 'l':
			*byte ^= (1 << 1);
			return 0;
		case ';':
			*byte ^= (1 << 0);
			return 0;
	}
	return 1;
}

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "usage: %s <filename>", *argv);
        return 69;
    } 
    
    FILE *file = fopen(argv[1], "ab");
	
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
		if (input(key, &byte)) switch (key) {
			case ' ':
				putc(byte, file);
				if (clr) byte = 0;
				break;
            case 'h':
                hex = !hex;
                break;
			case 'b':
				brk = !brk;
				break; // moment
        };
		
        system("clear");
        for (int i = 7; i >= 0; i--) {
			printf("%d", !!(byte & (1 << i)));
			if (i == 4 && brk) printf("  ");
		}
		
        if (hex) printf("\n%02x", byte); 
    } while ((key = getchar()));

    tcsetattr(STDIN_FILENO, TCSANOW, &oldsettings);
    return 0;
}