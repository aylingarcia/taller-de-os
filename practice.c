#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define MEMORY_SIZE 15

typedef enum {false, true} bool;
typedef struct {
  int id;
  char name[20];
  bool state;
  int size;
  int located;
  char date[20];
} Process;
typedef struct {
  Process *array;
  size_t used;
  size_t size;
} Array;


/*
 * Global variables
 */
int memory[MEMORY_SIZE] = {0};
Array processTable;
int serial = 0;

/** Colors to print on console **/
void reset () {
  printf("\033[0m");
}
void printRed (const char *format) {
	printf("\033[1;31m");
	printf("\n%s\n", format);
	reset();
}
void printCyan (const char *format) {
	printf("\033[0;36m");
	printf("%s", format);
	reset();
}
void yellow() {
	printf("\033[0;33m");
}
void green() {
	printf("\033[0;32m");
}
void printBlue(const char *format) {
	printf("\033[0;34m");
	printf("%s", format);
	reset();
}
void printGreen(const char *format) {
	printf("\033[0;32m");
	printf("%s", format);
	reset();
}

/*
 * Manage dymanic lists
 */
void initArray(Array *a, size_t initialSize) {
  a->array = malloc(initialSize * sizeof(Process));
  a->used = 0;
  a->size = initialSize;
}
void insertArray(Array *a, Process element) {
  if (a->used == a->size) {
    a->size *= 2;
    a->array = realloc(a->array, a->size * sizeof(Process));
  }

  a->array[a->used++] = element;
}

/*
 * Print on console Memory Used
 */
void showMemory() {
  printf(" "); 
  for(int i = 0; i < MEMORY_SIZE; i++) {
    if(i != MEMORY_SIZE-1) printf("─────");
    else printf("────\n");
  }

  printf("│");
  for(int i = 0; i < MEMORY_SIZE; i++) {

		if(memory[i] == -1) printf(" OS │");
		else printf(" %-2d │", memory[i]);
  }
  printf("\n");

  for(int i = 0; i < MEMORY_SIZE; i++) {
    if(i == 0) printf(" "); 

    if(i != MEMORY_SIZE-1) printf("─────");
    else printf("────\n");
  }
}

/*
 * Print on console Process Talbe
 */
void showProcessTable() {
  printf(" ─────────────────────────────────────────────────────────────\n"); 
  printf("│ id │  Name      │ State    │ Space │ Located │ Start On     │\n"); 
  printf("│─────────────────────────────────────────────────────────────│\n"); 

  for(int i = 0; i < processTable.used; i++) {
    printf(
      "│ %-2d │ %-10s │ %-8s │ %-5d | %-7d | %-12s │\n",
      processTable.array[i].id,
      processTable.array[i].name,
      processTable.array[i].state == true ? "active" : "finished",
      processTable.array[i].size,
      processTable.array[i].located,
      processTable.array[i].date
    ); 
  }

  printf(" ─────────────────────────────────────────────────────────────\n"); 
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
void addProcessToTable(int pid, int psize, int located) {
	Process process;
	struct tm* date;
	time_t timeRef;
	char name[20];
	char dateStr[20];

	timeRef = time(NULL);
	date = localtime(&timeRef);

	sprintf(
		dateStr,
		"%d:%d:%d",
		date->tm_hour,
		date->tm_min,
		date->tm_sec
	);
	sprintf(name, "process %d", pid);

	process.id = pid; 
	process.size = psize; 
	process.state = true; 
	process.located = located; 
	strcpy(process.name, name); 
	strcpy(process.date, dateStr); 

	insertArray(&processTable, process);
}

int addProcess() {
	int limit = (int)(MEMORY_SIZE /2);
	int processSize = rand() % limit;  
	if(processSize == 0) processSize = 1;

	int freeSize = getFreeSpace();

	if(freeSize >= processSize) {
		int start = MEMORY_SIZE - freeSize;
		int end = start + processSize;
		int pid = ++serial;

		for(int i = start; i < end; i++) {
			memory[i] = pid;
		}

		addProcessToTable(pid, processSize, start);

		green();
		printf("\nProcess(%d) added with %d space(s)\n\n", pid, processSize);
		reset();
	} else {
		yellow();
		printf("\nWe no have enough memory space: %d(u)\n\n", processSize);
		reset();
	}
}

/*
 *  Compact Memory 
 */
int compactMemory() {
	for(int i = 2; i < MEMORY_SIZE; i++) {
		memory[i] = 0;
	}

	for(int i = 0; i < processTable.used; i++) {
		Process curr = processTable.array[i]; 

		if(curr.state == true) {
			int freeSize = getFreeSpace();
			int start = MEMORY_SIZE - freeSize;
			int end = start + curr.size;

			int pid = curr.id;

			for(int i = start; i < end; i++) {
				memory[i] = pid;
			}

			processTable.array[i].located = start;
		}
	}
		printGreen("\nSuccessful compacted memory\n\n");
}

/*
 * Function to show manual
 */
int showManual() {
	printf(
		"0) ➛ Show options\n"
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
	int pid = 0, extra;

	showMemory(); 

	printBlue("Enter the pid [ENTER to cancel]: ");
	while((extra = getchar()) != '\n') {
		int digit = extra - 0x30;
		pid =  (pid * 10) + digit;
	}

	if (pid != 0) {   
		for(int i = 0; i < MEMORY_SIZE; i++) {
			if(memory[i] == pid) memory[i] = 0;
		}

		for(int i = 0; i < processTable.used; i++) {
			if(processTable.array[i].id == pid) {
				processTable.array[i].state = false;
				processTable.array[i].located = -1;
			}
		}

		printf("\nProcess %d finished.\n\n", pid);
	}
}

int main(void) {
	int option, extra;

  initArray(&processTable, 10);
	srand(time(NULL));

	showManual();
	while(1) {
		printCyan("Please enter an option: ");

		option = getchar();
		
		memory[0] = -1;
		memory[1] = -1;

		if(option == '\n') continue;
		while((extra = getchar()) != '\n') { }

		if(option == '0')
			showManual();
		else if(option == '1')
			addProcess();
		else if(option == '2')
			terminateProcess();
		else if(option == '3')
			compactMemory(); 
		else if(option == '4')
			showProcessTable(); 
		else if(option == '5')
			showMemory(); 
		else showManual();
	}

	return(0);
}
