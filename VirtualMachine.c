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

//current program
const int program[] = {
    PSH, 5,
    PSH, 6,
    ADD,
    POP,
    HLT
};

int program_counter = 0;
int stack_pointer = -1;
int stack[256];
bool running = true;

int main() {
    while(running) {
        //fetch 
        int current_instruction = fetch();
        program_counter++;
        
        //decode and execute
        execute(current_instruction);
    }
    return 0;
}

int fetch() {
    return program[program_counter];
}

void execute(int instruction) {
    switch(instruction) {
        case HLT:
            //stops the machine
            running = false;
            break;
        case PSH:
            //pushes next value onto the stack
            stack[++stack_pointer] = program[++program_counter];
            break;
        case POP:
            //gets value and decrements sp
            int popped_value = stack[stack_pointer--];
            
            //prints val
            printf("Popped: %d \n", popped_value);
            break;
        case ADD:
            //pops numbers to add
            int a = stack[stack_pointer--];
            int b = stack[stack_pointer--];
            
            //pushes result back onto the stack
            stack[++stack_pointer] = a + b; 
            break;
    }
}