// pcdefs.h - PC Parallel Port Registers and Pinout definitions
//
// Copyright (C) 1997, Ian Harries & Imperial College, London, UK
//
// compiled with Microsoft Visual C++ v4.2 under Windows95

// IBM-PC Parallel Printer Port Registers
// ======================================
//           7   6   5   4   3   2   1   0   I/O Port
//         +---+---+---+---+---+---+---+---+
// DATA    |DB7|DB6|DB5|DB4|DB3|DB2|DB1|DB0| Base = 278/378/3BC Hex
//         +---+---+---+---+---+---+---+---+
// STATUS  | x | x | x | x | x | - | - | - | Base + 1
//         +---+---+---+---+---+---+---+---+
// CONTROL | - | - | - | - |RS | E | x | x | Base + 2
//         +---+---+---+---+---+---+---+---+
//
//         N.B. C0, C1 & C3 are inverted
//         i.e. C0 = 1 will cause Parallel Port pin 1 to go LOW.
//
//         If timing is non-critical (no need to check Busy Flag DB7)
//         then the R/W line - LCD Pin 5 - can be tied to Ground (LOW).

#define Data    0x378    // or 0x278 or 0x3BC
#define Status  Data + 1 // unused
#define Control Data + 2

//      PC Parallel Port Control Register Outputs
//      =========================================
//      Register Select       7   6   5   4   3   2   1   0 
//      ===============      === === === === === === === ===
#define Data_Register 0x00 // .   .   .   .   0   .   .   .
#define Ins_Register  0x08 // .   .   .   .   1   .   .   .

//      Enable                7   6   5   4   3   2   1   0 
//      ======               === === === === === === === ===
#define Enable_Low    0x00 // .   .   .   .   .   0   .   .
#define Enable_High   0x04 // .   .   .   .   .   1   .   .