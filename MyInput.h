//13 == ASCII code for "ENTER"
//32 == ASCII code for "SPACE"
//8 == ASCII code for "BACKSPACE"

#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

#define MOVE_UP 72
#define MOVE_DOWN 80
#define MOVE_RIGHT 77
#define ESC 27
#define ENTER 13



// Needs the argument MaxSize, which is the maximum size of the password
// Returns the string password

void cursor(COORD coord,char c) {
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	printf("%c", c);
}

char *GetPassword (int MaxSize) {
	
	char *password, character;
	int j = 0;
		
	while (character != 13) {
		if (j <= MaxSize)
			character = getch();
			
		if (j < MaxSize) {
			if (isalnum(character)) {
					password[j] = character;
					j++;
					printf ("*");
			}
		}
		if (!isalnum(character) && character == 8) {
			if (j > 0) {
				password[j] = '\0';
				printf ("\b \b");
				j--;
			}
		}
	}
	password[j] = '\0';
	
	return password;
}

// Needs the argument MaxSize, which is the maximum size of the string
// Returns the string
char *GetString (int MaxSize) {
	
	char *string, character;
	int j = 0;
		
	while (character != 13) {
		if (j <= MaxSize)
			character = getch();
			
		if (j < MaxSize) {
			if (isalnum(character) || character == 32) {
					string[j] = character;
					j++;
					printf ("%c", character);
			}
		}
		if (!isalnum(character) && character == 8) {
			if (j > 0) {
				string[j] = '\0';
				printf ("\b \b");
				j--;
			}
		}
	}
	string[j] = '\0';
	
	printf ("\n");
	
	return string;
}

void menu(int id){
	COORD cr;
	
	
}
