#include <stdlib.h>
#include <ncurses.h>
#include <locale.h>

#ifndef MAX_STR_SIZE // Of user input
#define MAX_STR_SIZE 128
#endif

int str_in_str(char* substr, char* str) {
	if(str[0] == '\0') return 0; // Never match empty strings.
	int i = 0, j = 0;
	do {
		if(str[i] == substr[j]) j++;
		else j = 0; 
		if(substr[j] == '\0') return 1;
		i++;
	} 
	while(str[i] != '\0');
	
	return 0;
}

int str_len(char* str) {
	//does not include '\0'
	int i = 0;
	while(str[i] != '\0') i++;
	return i;
}

int mmenu(char** options, int options_len, char* prompt) {
	setlocale(LC_ALL, "");
	initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	int rows, cols;
	getmaxyx(stdscr, rows, cols);
	char* str = malloc(MAX_STR_SIZE * sizeof(char));
	if(str == NULL) exit(1);
	int len = 0;
	int chr;
	int selection = 1;

	printw(prompt);
	int prompt_len = str_len(prompt);
		
	for(int i = 0; i < rows - 1 && i < options_len; i++) {
		move(i + 1, 0);
		if(i == 0) attron(A_STANDOUT);
		printw(options[i]);
		if(i == 0) attroff(A_STANDOUT);
	}
	
	move(0, prompt_len + len); // Move cursor back to text.
	refresh();
	
	while((chr = getch()) != 27) {
		if(chr == '\n') {
			int filtered = 0;
			for(int i = 0; i < options_len; i++){
				if(str_in_str(str, options[i])) {
					filtered++;
					if(filtered == selection) {
						endwin();
						free(str);
						return i;
					}
				}
			}
			break; //exit 0
		}
		switch(chr){
			case KEY_BACKSPACE: // Backspace
			case KEY_LEFT: // For when backspace breaks
				if(len > 0) {
					len--;
					str[len] = '\0';
				}
				break;
			case KEY_UP:
				if(selection > 1)
					selection--;
				break;
			case KEY_DOWN:
				if(selection < rows - 1)
					selection++;
				break;
			case '\n':
				break;
			case KEY_RIGHT: break;
			default:
				if(len != MAX_STR_SIZE - 1) {
					str[len] = chr;
					len++;
				}
				selection = 1;
				break;
		}
		move(0, prompt_len);
		clrtobot();
		printw(str);
		for(int i = 0, line = 0; i < options_len && line < rows; i++) {
			if(str_in_str(str, options[i])) {
				line++;
				move(line, 0);
				if(line == selection) attron(A_STANDOUT);
				printw(options[i]);
				if(line == selection) attroff(A_STANDOUT);
			}
		}
		move(0, prompt_len + len); // Move cursor back to text.
		refresh();
	}
	endwin();
	free(str);
	return -1;
}
