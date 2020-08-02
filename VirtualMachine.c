#include <stdio.h>
#include <stdbool.h>

//all instructions
typedef enum {
    PSH,
    POP,
    ADD,
    SET,
    HLT
} InstructionSet;

//registers
typedef enum {
    A, B, C, D, PC, SP,
    NUM_REGISTERS
} Registers;

//current program
const int program[] = {
    PSH, 5,
    PSH, 6,
    ADD,
    POP,
    HLT
};

int stack[256];
int registers[NUM_REGISTERS];
bool running = true;

int main() {
    //init SP and PC
    registers[PC] = 0;
    registers[SP] = -1;
    
    while(running) {
        //fetch 
        int current_instruction = fetch();
        registers[PC]++;
        
        //decode and execute
        execute(current_instruction);
    }
    return 0;
}

int fetch() {
    return program[registers[PC]];
}

void execute(int instruction) {
    switch(instruction) {
        case HLT:
            //stops the machine
            running = false;
            break;
        case PSH:
            //pushes next value onto the stack
            stack[++registers[SP]] = program[++registers[PC]];
            break;
        case POP:
            //gets value and decrements sp
            int popped_value = stack[registers[SP]--];
            
            //prints val
            printf("Popped: %d \n", popped_value);
            break;
        case ADD:
            //pops numbers to add
            int a = stack[registers[SP]--];
            int b = stack[registers[SP]--];
            
            //pushes result back onto the stack
            stack[++registers[SP]] = a + b; 
            break;
    }
}