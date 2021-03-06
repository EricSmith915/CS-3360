#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h> // malloc & free
#include <stdint.h> // use guaranteed 64-bit integers
#include "tokenizer.h" // Create header file and reference that
#include "memory.h" // built-in functions to read and write to a specific file
#include <string.h> //Used for strtok

int32_t* reg; // Array of 32 32-bit registers

void init_regs();
bool interpret(char* instr);
void write_read_demo();

/**
 * Initialize register array for usage.
 * Malloc space for each 32-bit register then initializes each register to 0.
 * Do not alter this function!
 */
void init_regs(){
	int reg_amount = 32;
	reg = malloc(reg_amount * sizeof(int32_t)); // 32 * 4 bytes
	for(int i = 0; i < 32; i++)
		reg[i] = i;
}

//turns a char pointer into a usable integer
int32_t read_num(char* input){
	int counter = 0;
	int tens = 1;
	bool first = true;
	bool is_negative = false;

	printf("%c\n", *input);
	if(*input == '-'){
		printf("THE STRING IS NEGATIVE\n");
		is_negative = true;
		input++;
	}

	char* temp = input;
	//Counts the length of the char pointer
	while(*temp >= 48 && *temp <= 57){
		if(counter != 0){
			tens = tens * 10;
		}
		temp++;
		counter++;
	}

	temp = input;
	int32_t total = 0;

	//Computes the integer which will be returned
	while(counter > 0){
		total += ((*temp) - '0') * tens;
		counter--;
		tens /= 10;
		temp++;
	}

	if(is_negative != true){
		return total;
	}
	return total * -1;
}

//Compares two strings to check instruction
bool check_instr(char* word_one, char* word_two){
	char* copy_one = word_one;
	char* copy_two = word_two;

	//Checks if the two dereferenced pointers are equal to each other
	while(*copy_one != '\0' || *copy_two != '\0'){
		if(*copy_one != *copy_two){
			return false;
		}
		copy_one++;
		copy_two++;
	}
	return true;
}

//converts register token to an int
int read_register(char* input){
	char* temp = input;
	int x = 0;
	int y = 0;
	int counter = 0;

	temp++;

	x = *temp - '0';

	temp++;

	if(temp != NULL && *temp != '\0' && *temp != '\n' && *temp != ')'){
		y = *temp - '0';
		x = x * 10;
		x = y + x;
	}

	return x;
}


/**
 * Fill out this function and use it to read interpret user input to execute RV64 instructions.
 * You may expect that a single, properly formatted RISC-V instruction string will be passed
 * as a parameter to this function.
 */
bool interpret(char* instr){
	
	char *parsed = strtok(instr, " ");
	int counter = 0;
	char* LW = "LW";
	char* SW = "SW";
	char* ADDI = "ADDI";
	char* ADD = "ADD";

	if(parsed == NULL){
		printf("Entered string reads as NULL. Try again\n");
		return false;
	}

	char* check = parsed;

	//Checks the selected instruction
	//Executes the load word instruction
	if(check_instr(check, LW)){
		printf("You selected to LOAD WORD\n");

		parsed = strtok(NULL, " ");
		int regi_one = read_register(parsed);

		parsed = strtok(NULL, " ");
		int num = read_num(parsed);

		parsed = strtok(parsed, "(");
		parsed = strtok(NULL, " ");

		int regi_two = read_register(parsed);

		int32_t read = read_address(num + regi_two, "mem.txt");

		if(read == 1){
			return false;
		}
		

		reg[regi_one] = read;

	}

	//Executes the store word instruction
	else if (check_instr(check, SW)) {
		printf("You selected to STORE WORD\n");

		parsed = strtok(NULL, " ");
		int regi_one = read_register(parsed);

		parsed = strtok(NULL, " ");
		int num = read_num(parsed);

		parsed = strtok(parsed, "(");
		parsed = strtok(NULL, " ");

		int regi_two = read_register(parsed);

		int check = write_address(reg[regi_one], num+regi_two, "mem.txt");

		if(check == -1){
			return false;
		}

		return true;
		
	}

	//Executes the Add instruction
	else if (check_instr(check, ADD)) {
		printf("You selected to ADD\n");
		
		parsed = strtok(NULL, " ");
		int regi_one = read_register(parsed);

		parsed = strtok(NULL, " ");
		int regi_two = read_register(parsed);

		parsed = strtok(NULL, " ");
		int regi_three = read_register(parsed);

		printf("%d\n", regi_one);
		printf("%d\n", regi_two);
		printf("%d\n", regi_three);

		reg[regi_one] = reg[regi_two] + reg[regi_three];
		
	}

	//Executes the add immediate instruction
	else if (check_instr(check, ADDI)){
		printf("You selected to ADD IMMEDIATE\n");

		parsed = strtok(NULL, " ");
		int regi_one = read_register(parsed);

		parsed = strtok(NULL, " ");
		int regi_two = read_register(parsed);

		parsed = strtok(NULL, " ");
		int32_t num = read_num(parsed);

		reg[regi_one] = reg[regi_two] + num;
		
	}

	//Executes if user did not select a valid instruction
	else {
		printf("You did not enter a valid instruction\n");
		return false;
	}
	
	return true;
}

/**
 * Simple demo program to show the usage of read_address() and write_address() found in memory.c
 * Before and after running this program, look at mem.txt to see how the values change.
 * Feel free to change "data_to_write" and "address" variables to see how these affect mem.txt
 * Use 0x before an int in C to hardcode it as text, but you may enter base 10 as you see fit.
 */
void write_read_demo(){
	int32_t data_to_write = 0xFFF; // equal to 4095
	int32_t address = 0x98; // equal to 152
	char* mem_file = "mem.txt";

	// Write 4095 (or "0000000 00000FFF") in the 20th address (address 152 == 0x98)
	int32_t write = write_address(data_to_write, address, mem_file);
	if(write == (int32_t) NULL)
		printf("ERROR: Unsucessful write to address %0X\n", 0x40);
	int32_t read = read_address(address, mem_file);

	printf("Read address %lu (0x%lX): %lu (0x%lX)\n", address, address, read, read); // %lu -> format as an long-unsigned
}

/**
 * Prints all 32 registers in column-format
 */
void print_regs(){
	int col_size = 10;
	for(int i = 0; i < 8; i++){
		printf("X%02i:%.*lld", i, col_size, (long long int) reg[i]);
		printf(" X%02i:%.*lld", i+8, col_size, (long long int) reg[i+8]);
		printf(" X%02i:%.*lld", i+16, col_size, (long long int) reg[i+16]);
		printf(" X%02i:%.*lld\n", i+24, col_size, (long long int) reg[i+24]);
	}
}

/**
 * Your code goes in the main
 *
 */
int main(){
	// Do not write any code between init_regs
	init_regs(); // DO NOT REMOVE THIS LINE

	print_regs();

	// Below is a sample program to a write-read. Overwrite this with your own code.
	//write_read_demo();
	write_read_demo();

	printf(" RV32 Interpreter.\nType RV32 instructions. Use upper-case letters and space as a delimiter.\nEnter 'EOF' character to end program\n");


	char* instruction = malloc(1000 * sizeof(char));
	bool is_null = false;
	// fgets() returns null if EOF is reached.
	is_null = fgets(instruction, 1000, stdin) == NULL;
	while(!is_null){
		interpret(instruction);
		printf("\n");
		print_regs();
		printf("\n");

		is_null = fgets(instruction, 1000, stdin) == NULL;
	}

	printf("Good bye!\n");

	return 0;
}
