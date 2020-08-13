SET, B, 1,
SET, C, 0,
SET, D, ' ',

MOV, C, A,
ADD, B
MOV, B, C,
MOV, A, B,

IOT, B,
COT, D,

SUB, 233,
JZ, 31,
SET, PC, 9
HLT 