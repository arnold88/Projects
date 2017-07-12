// hd44780.h - HD44780 Instructions and Parameter definitions
//
// Copyright (C) 1997, Ian Harries & Imperial College, London, UK
//
// compiled with Microsoft Visual C++ v4.2 under Windows95

#include <string.h>  // just for strlen
#include <conio.h>   // required for _outp, _inp

#include "pcdefs.h"  // PC Parallel Port Registers and Pinout definitions

//      HD44780 Instruction Set             DB7 DB6 DB5 DB4 DB3 DB2 DB1 DB0
//      =======================             === === === === === === === ===
#define Clear_Display                0x01 // 0   0   0   0   0   0   0   1

#define Return_Home                  0x02 // 0   0   0   0   0   0   1   *

#define Set_Entry_Mode               0x04 // 0   0   0   0   0   1  I/D  S

#define Set_Display                  0x08 // 0   0   0   0   1   D   C   B

#define Set_Cursor_and_Display_Shift 0x10 // 0   0   0   1  S/C R/L  *   *

#define Set_Function                 0x20 // 0   0   1   DL  N   F   *   *

#define Set_CGRAM_Address            0x40 // 0   1   A   A   A   A   A   A

#define Set_DDRAM_Address            0x80 // 1   A   A   A   A   A   A   A

//      HD44780 Parameters 
//      ==================
//      N.B. explicit values for EVERY corresponding parameter
//      ==== MUST be passed each time any instruction is used

//      Set_Entry_Mode
//      ==============
#define Decrement_Address            0x00 // .   .   .   .   .   .   0   .
#define Increment_Address            0x02 // .   .   .   .   .   .   1   .

#define Shift_Display_Off            0x00 // .   .   .   .   .   .   .   0
#define Shift_Display_On             0x01 // .   .   .   .   .   .   .   1

//      Set_Display
//      ===========
#define Display_Off                  0x00 // .   .   .   .   .   0   .   .
#define Display_On                   0x04 // .   .   .   .   .   1   .   .

#define Cursor_Off                   0x00 // .   .   .   .   .   .   0   .
#define Cursor_On                    0x02 // .   .   .   .   .   .   1   .

#define Blink_Off                    0x00 // .   .   .   .   .   .   .   0
#define Blink_On                     0x01 // .   .   .   .   .   .   .   1

//      Set_Cursor_and_Display_Shift
//      ============================
#define Cursor                       0x00 // .   .   .   .   0   .   .   .
#define Display_and_Cursor           0x08 // .   .   .   .   1   .   .   .

#define Left                         0x00 // .   .   .   .   .   0   .   .
#define Right                        0x04 // .   .   .   .   .   1   .   .

//      Set_Function
//      ============
#define Data_Length_4                0x00 // .   .   .   0   .   .   .   .
#define Data_Length_8                0x10 // .   .   .   1   .   .   .   .

#define One_Display_Line             0x00 // .   .   .   .   0   .   .   .
#define Two_Display_Lines            0x08 // .   .   .   .   1   .   .   .

#define Font_5x7                     0x00 // .   .   .   .   .   0   .   .
#define Font_5x10                    0x04 // .   .   .   .   .   1   .   .

#define Line2_Offset 0x40

#define Put_Char Put_Data // same thing

void Pause(void) { // dilute to taste
    int i;
    for (i = 1; i <= 100000; i++); // do nothing
}

void Put_Ins(int Ins) {
    _outp(Control,Ins_Register + Enable_High);
    _outp(Data,Ins);
    Pause();
    _outp(Control,Ins_Register + Enable_Low);
}

void Put_Data(unsigned char Ch) {
    _outp(Control,Data_Register + Enable_High);
    _outp(Data,Ch);
    Pause();
    _outp(Control,Data_Register + Enable_Low);
}

void Put_Str(char Str[]) {
    unsigned int i;
    for (i = 0; i < strlen(Str); i++)
        Put_Char(Str[i]);
}

void Init_Display(void) {
    Put_Ins(Set_Function + Data_Length_8);
    Put_Ins(Set_Function + Data_Length_8);
    Put_Ins(Set_Function + Data_Length_8);
    Put_Ins(Set_Function + Data_Length_8 + Two_Display_Lines + Font_5x7);
    Put_Ins(Set_Display + Display_Off + Cursor_Off + Blink_Off);
    Put_Ins(Clear_Display);
    Put_Ins(Set_Entry_Mode + Increment_Address + Shift_Display_Off);
}