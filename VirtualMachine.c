#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define fetch program[registers[PC]]
#define MAX_PROGRAM_SIZE 512

//all instructions
typedef enum {
    PSH,    //Pushes a value onto the stack ex: PSH, 12
    POP,    //Pops a value from the stack ex: POP, B
    ADD,    //Adds a value to the A register ex: ADD, 2
    SUB,    //Subtracts a value from the A register ex: SUB, 3
    SET,    //Sets value of any register ex: SET, B, 23
    MOV,    //Copies first register value into second register ex: MOV, A, PC
    JSR,    //Jumps to a subroutine ex: JSR, 23
    RTS,    //Returns from a subroutine ex: RTS
    JZ,     //Branch to adress if 0 is in A register ex: BEQ, 12
    HLT,    //Halts the machine ex: HLT
    IOT,    //Outputs contents of a register ex: OUT, A
    COT     //Outputs contents of a register as char ex: OUT, B
} InstructionSet;

//registers
typedef enum {
    A, B, C, D, PC, SP,
    NUM_REGISTERS
} Registers;

//global variables
int* program;
int stack[256];
int registers[NUM_REGISTERS];
bool running = true;

void execute(int instruction) {
    switch(instruction) {
        case PSH: {
            //pushes next value onto the stack
            stack[++registers[SP]] = program[registers[PC]++];
            break;
        }
        case POP: {
            //check if stack has value
            if(registers[SP] < 0) printf("\nBVM Error: Tried to pop empty stack");
            
            //gets value and decrements sp
            int popped_value = stack[registers[SP]--];
            
            //stores value in register
            registers[program[registers[PC]++]] = popped_value;
            break;
        }
        case ADD: {
            //gets number to the A register
            int x = program[registers[PC]++];
            
            //puts result back into the A register
            registers[A] += x;
            break;
        }
        case SUB: {
            //gets number to subtract from A register
            int x = program[registers[PC]++];
            
            //puts result back into the A register
            registers[A] -= x;
            break;
        }
        case SET: {
            //get the register to change from program
            int reg = program[registers[PC]++];

            //change the register with the next value in program
            registers[reg] = program[registers[PC]++];
            break;
        }
        case MOV: {
            //get source and dest 
            int source = program[registers[PC]++];
            int dest = program[registers[PC]++];

            //copy
            registers[dest] = registers[source];
            break;
        }
        case JSR: {
            //get adress to jump to and push current onto stack
            int jump_adress = program[registers[PC]++];
            stack[++registers[SP]] = registers[PC];

            //jump
            registers[PC] = jump_adress;
            break;
        }
        case RTS: {
            //pull adress from stack and jump
            int jump_adress = stack[registers[SP]--];
            registers[PC] = jump_adress;
            break;
        }
        case JZ: {
            //gets adress
            int adress = program[registers[PC]++];
            
            //branch if zero
            if(registers[A] == 0) {
                registers[PC] = adress;
            }
            break;
        }
        case HLT: {
            //stops the machine
            running = false;
            break;
        }
        case IOT: {
            //prints int value stored in register
            printf("%d", registers[program[registers[PC]++]]);
            break;  
        }
        case COT: {
            //prints char value stored in the register 
            printf("%c", registers[program[registers[PC]++]]);
            break;
        }
    }
}

int* read_program(char file_name[]) {
    //create and open file
    FILE *file;
    int *program = malloc(sizeof(int) * MAX_PROGRAM_SIZE);
    file = fopen(file_name, "r");
    
    //check if file opened properly
    if(file == NULL) {
        printf("BVM Fatal Error: could not open file \n");
        running = false;
        return 0;
    }
    
    //read file
    for(int i = 0; i < MAX_PROGRAM_SIZE; i++) {
        fscanf(file, "%d", &program[i]);
    }
    
    //close file
    fclose(file);
    return program;
}

int main(int argc, char* argv[]) {
    //init SP and PC
    registers[PC] = 0;
    registers[SP] = -1;
    
    //read program from file
    if(argc == 2) {
        printf("BVM: Reading File \n");
        program = read_program(argv[1]);  
    } else {
        printf("BVM Fatal Error: no file specified \n");
        return 0;
    }
    

    //system clock
    while(running) {
        //fetch 
        int current_instruction = fetch;
        registers[PC]++;
        
        //decode and execute
        execute(current_instruction);
    }
    //free program from heap
    free(program);
    return 0;
}