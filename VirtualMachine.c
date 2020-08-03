#include <stdio.h>
#include <stdbool.h>

//all instructions
typedef enum {
    PSH,
    POP,
    ADD,
    SET,
    HLT,
    OUT
} InstructionSet;

//registers
typedef enum {
    A, B, C, D, PC, SP,
    NUM_REGISTERS
} Registers;

//current program
const int program[] = {
    PSH, 5,
    SET, A, 7,
    ADD, 21,
    OUT, A,
    HLT
};

int stack[256];
int registers[NUM_REGISTERS];
bool running = true;

int fetch() {
    return program[registers[PC]];
}

void execute(int instruction) {
    switch(instruction) {
        case HLT: {
            //stops the machine
            running = false;
            break;
        }
        case PSH: {
            printf("Push\n");
            //pushes next value onto the stack
            stack[++registers[SP]] = program[registers[PC]++];
            break;
        }
        case POP: {
            printf("Pop\n");
            
            //gets value and decrements sp
            int popped_value = stack[registers[SP]--];
            
            //prints val
            printf("Popped: %d \n", popped_value);
            break;
        }
        case ADD: {
            printf("Add\n");
            
            //adds number to the A register
            int a = registers[A];
            int b = program[registers[PC]++];
            
            //puts result back into the A register
            registers[A] = a + b;
            break;
        }
        case SET: {
            printf("Set\n");
            
            //get the register to change from program
            int reg = program[registers[PC]++];

            //change the register with the next value in program
            registers[reg] = program[registers[PC]++];
            break;
        }
        case OUT: {
            printf("Out\n");
            //prints out value stored in register
            printf("Out: %d\n", registers[program[registers[PC]++]]);
            break;  
        }
    }
}

int main() {
    //init SP and PC
    registers[PC] = 0;
    registers[SP] = -1;
    
    while(running) {
        //fetch 
        int current_instruction = fetch();
        registers[PC]++;
        printf("PC: %d CI: %d \n", registers[PC], current_instruction);
        
        //decode and execute
        execute(current_instruction);
    }
    return 0;
}