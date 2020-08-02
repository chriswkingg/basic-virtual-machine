#include <stdio.h>
#include <stdbool.h>

typedef enum {
    PSH,
    POP,
    ADD,
    SET,
    HLT
} InstructionSet;

const int program[] = {
    PSH, 5,
    PSH, 6,
    ADD,
    POP,
    HLT
};

int program_counter = 0;
bool running = true;

int main() {
    while(running) {
        int current_instruction = fetch();
        program_counter++;
    }
    return 0;
}

int fetch() {
    return program[program_counter];
}