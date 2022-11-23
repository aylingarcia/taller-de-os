#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

#define MEMORY_SIZE 20

int memory[MEMORY_SIZE] = {0};

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

int getFreeSpace() {
	int i, free = 0;

	for(i = MEMORY_SIZE - 1; i >= 0; i--) {
		if(memory[i] == 0) free++;
		else break;
	}


	return free;
}

/*
 * Function to add new process 
 */
int addProcess() {
	int processSize = rand() % 10;  
	if(processSize == 0) processSize = 1;

	int freeSize = getFreeSpace();

	//printf("free: %d \n", freeSize);

	if(freeSize >= processSize) {
		int i, start = MEMORY_SIZE - freeSize, end = start + processSize;

		for(i = start; i < end; i++) {
			memory[i] = processSize;
		}
	} else {
		printCyan("\n\n\nNo have memory space\n\n\n");
	}
}

/*
 * Function to add  
 */
int showMemory() {
	int i;

	for(i = 0; i < MEMORY_SIZE; i++) {
		printf("position: %d, value: %d\n", i+1, memory[i]);
	}
}

/*
 * Function to add  
 */
int compactMemory() {
	int i;

	for(i = 0; i < MEMORY_SIZE; i++) {
		printf("position: %d, value: %d\n", i+1, memory[i]);
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

/*
 * Function to show manual
 */
void terminateProcess() {
	int option, extra;

	printCyan("Enter the pid: ");

	option = getchar();

	if(option == '\n') return;
	while((extra = getchar()) != '\n') { }

	for(i = 0; i < MEMORY_SIZE; i++) {
		printf("position: %d, value: %d\n", i+1, memory[i]);
	}
}

int main(void) {
	int option, extra;

	srand(time(NULL));

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
			else if(option == '2')
				terminateProcess();
			else if(option == '3')
				compactMemory(); 
			else if(option == '4')
				showMemory(); 
			else
				printRed(
					"** Invalid option *** \n\n"
					"Enter 6 to cheack available options"
				);
		}
	}

	return(0);
}
