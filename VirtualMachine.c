#include <stdio.h>
#include <stdbool.h>

//all instructions
typedef enum {
    PSH,    //Pushes a value onto the stack ex: PSH, 12
    POP,    //Pops a value from the stack ex: POP, B
    ADD,    //Adds a value to the A register ex: ADD, 2
    SUB,    //Subtracts a value from the A register ex: SUB, 3
    SET,    //Sets value of any register ex: SET, B, 23
    MOV,    //Copies first register value into second register ex: MOV, A, PC
    HLT,    //Halts the machine ex: HLT
    OUT     //Outputs contents of a register ex: OUT A
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
            
            //stores value in register
            registers[program[registers[PC]++]] = popped_value;
            break;
        }
        case ADD: {
            printf("Add\n");
            
            //gets number to the A register
            int x = program[registers[PC]++];
            
            //puts result back into the A register
            registers[A] += x;
            break;
        }
        case SUB: {
            printf("Sub\n");
            
            //gets number to subtract from A register
            int x = program[registers[PC]++];
            
            //puts result back into the A register
            registers[A] -= x;
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
        case MOV: {
            printf("Mov");
            
            //get source and dest 
            int source = program[registers[PC]++];
            int dest = program[registers[PC]++];

            //copy
            registers[dest] = registers[source];
            break;
        }
        case HLT: {
            printf("Halt");
            
            //stops the machine
            running = false;
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
    
    //system clock
    while(running) {
        //fetch 
        int current_instruction = fetch();
        registers[PC]++;
        printf("PC: %d \n", registers[PC]);
        
        //decode and execute
        execute(current_instruction);
    }
    return 0;
}