#include <stdio.h>
#include <stdlib.h>

#define MEMORY_SIZE 12

int processList[MEMORY_SIZE] = {0};

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
 * Function to add new process 
 */
int addProcess() {
	//@TODO: implement agregation
	processList[0] = 1;
}

/*
 * Function to add new process 
 */
int showMemory() {
	int i;

	for(i = 0; i < MEMORY_SIZE; i++) {
		printf("position: %d, value: %d\n", i+1, processList[i]);
	}
}

/*
 * Function to show manual
 */
int showManual() {
	printf(
		"0) ➛ Exit\n"
		"1) ➛ Generate rambom process\n"
		"2) ➛ Finish process\n"
		"3) ➛ Compact processes\n"
		"4) ➛ Show process table\n"
		"5) ➛ Show memory\n"
	);
}

int main(void) {
	int option, extra;
	

	while(1) {
		showManual();
		printCyan("Please enter an option: ");

		option = getchar();

		if(option == '\n') continue;
		while((extra = getchar()) != '\n') { }

		if(option != '\n') {
			if(option == '0')
				exit(EXIT_SUCCESS);
			else if(option == '1')
				addProcess();
			else if(option == '5')
				showMemory(); 
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
