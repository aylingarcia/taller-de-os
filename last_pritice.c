#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>

#define MEMORY_SIZE 12

/** Colors to print on console **/
void reset () {
  printf("\033[0m");
}

void printRed (const char *format) {
	printf("\033[1;31m");
	printf("\n");
	printf("%s", format);
	printf("\n");
	reset();
}
void printCyan (const char *format) {
	printf("\033[0;36m");
	printf("%s", format);
	reset();
}

/*
 * Function to clear console 
 */
int clearConsole() {
	printf("\e[1;1H\e[2J");
}

/*
 * Function to show manual
 */
int showManual() {
	printf(
		"1) ➛ Generate rambom process\n"
		"2) ➛ Finish process\n"
		"3) ➛ Compact processes\n"
		"4) ➛ Show process table\n"
		"0) ➛ Exit\n"
	);
}

int main(void) {
	char inputLine[50];
	int option, extra;

	while(1) {
		char name[25];

		showManual();
		printCyan("Please enter an option: ");

		// scanf("%d", &option);
		option = getchar();
		// sprintf(name, "Process Nro. %d", option);
		if(option == '\n') continue;
		while((extra = getchar()) != '\n') { }

		if(option != '\n') {
			if(option == '0')
				exit(EXIT_SUCCESS);
			else if(option == '2')
				clearConsole();
			else if(option == '3')
				clearConsole(); 
			else if(option == '4')
				clearConsole(); 
			else if(option == '5')
				showManual();
			else
				printRed(
					"** Invalid option *** \n\n"
					"Enter 6 to cheack available options"
				);
		}
	}

	return(0);
}
