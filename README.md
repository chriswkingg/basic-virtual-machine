# Basic Virtual Machine
Super simple virtual machine with a stack written in C

# Instructions:
    PSH: Pushes a value onto the stack ex: PSH, 12
    POP: Pops a value from the stack ex: POP, B
    ADD: Adds a value to the A register ex: ADD, 2
    SUB: Subtracts a value from the A register ex: SUB, 3
    SET: Sets value of any register ex: SET, B, 23
    MOV: Copies first register value into second register ex: MOV, A, PC
    HLT: Halts the machine ex: HLT
    OUT: Outputs contents of a register ex: OUT A
