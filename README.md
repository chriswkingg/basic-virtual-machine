# Basic Virtual Machine
Super simple virtual machine with a stack written in C. The machine has very few instructions but it is still possible to create working programs including hello world!

# Instructions:
    PSH: Pushes a value onto the stack ex: PSH, 12
    POP: Pops a value from the stack ex: POP, B
    ADD: Adds a value to the A register ex: ADD, 2
    SUB: Subtracts a value from the A register ex: SUB, 3
    SET: Sets value of any register ex: SET, B, 23
    MOV: Copies first register value into second register ex: MOV, A, PC
    JSR: Jumps to a subroutine ex: JSR, 23
    RTS: Returns from a subroutine ex: RTS
    BEQ: Branch to adress if 0 is in A register ex: BEQ, 12
    HLT: Halts the machine ex: HLT
    IOT: Outputs contents of a register ex: OUT, A
    COT: Outputs contents of a register as char ex: OUT, B
# Getting Started:
To use the machine, you must compile it and include the program filename when running the machine
    ex: .\VirtualMachine.exe helloworld.bvm
