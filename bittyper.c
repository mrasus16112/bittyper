#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <stdbool.h>

#define newline putchar('\n')
#define REGISTERS_MAX_SIZE 64
typedef unsigned char byte_t;

void help() {
    system("clear");
    puts("7 6 5 4  3 2 1 0\n"
         "a s d f  j k l ;\n\n"
         "How it works\n"
         "You start with an empty byte. "
         "When you type a key as shown on the chart above, it will flip the bit of the byte at the corresponding position. "
         "For example, as the chart above shows, hitting L will flip bit 1, and hitting D will flip bit 5. "
         "Once you have finished flipping bits, hit space to write the byte to the specified file.\n\n"
         "Register system\n" 
         "By default, you have 8 'registers' that can store one byte each. "
         "When you write a register's value, it will not get reset after the operation. "
         "This allows you to use registers as shortcuts for a specific byte."
         "You can also set the amount of registers you want (64).\n\n"
         "Commands\n"
         "g: open the guide\n"
         "h: toggle hex representation\n"
         "r: set current byte to register value\n"
         "u: update a register's value to the current byte\n"
         "n: set number of registers\n"
		 "b: break up the binary representation to align with keyboard\n"
		 "c: toggle clearing after writing byte to file\n\n"
         "Press any key to exit the guide\n"
         "Press Ctrl-C at any time to exit the program");
    (void) getchar();
}

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
    help();

    byte_t *registers = calloc(8, sizeof(byte_t)), byte = 0, key;
    bool hex = false, brk = false, clr = true;

    do {
		if (input(key, &byte)) switch (key) {
			case ' ':
				putc(byte, file);
				if (clr) byte = 0;
				break;
            case 'g':
                help();
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