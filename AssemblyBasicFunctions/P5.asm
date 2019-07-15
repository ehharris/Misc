; P5 Assignment
; Author: Elijah Harris
; Date:   10/1/17
; Email:  ehharris@rams.colostate.edu
; Class:  CS270
;
; Description: Implements the arithmetic, bitwise, and shift operations

;------------------------------------------------------------------------------
; Begin reserved section: do not change ANYTHING in reserved section!

                .ORIG x3000
                BR Main

Functions       .FILL IntAdd         ; Address of IntAdd routine     (option 0)
                .FILL IntSub         ; Address of IntSub routine     (option 1)
                .FILL IntMul         ; Address of IntMul routine     (option 2)
                .FILL BinaryOr       ; Address of BinaryOr routine   (option 3)
                .FILL LeftShift      ; Address of LeftShift routine  (option 4)
                .FILL RightShift     ; Address of RightShift routine (option 5)

Main            LEA R0,Functions     ; The main routine calls one of the 
                LD  R1,Option        ; subroutines below based on the value of
                ADD R0,R0,R1         ; the Option parameter.
                LDR R0,R0,0          ;
                JSRR R0              ;
EndProg         HALT                 ;

; Parameters and return values for all functions
Option          .FILL #0             ; Which function to call
Param1          .BLKW 1              ; Space to specify first parameter
Param2          .BLKW 1              ; Space to specify second parameter
Result          .BLKW 1              ; Space to store result

; End reserved section: do not change ANYTHING in reserved section!
;------------------------------------------------------------------------------

; You may add variables and functions after here as you see fit.

;------------------------------------------------------------------------------
IntAdd          LD R1, Param1
                LD R2, Param2 
                ADD R3, R2, R1
                ST R3, Result
                                     ; Result is Param1 + Param2
                                     ; Your code goes here (~4 lines)
                RET
;------------------------------------------------------------------------------
IntSub          LD R1, Param1
                LD R2, Param2
                NOT R2, R2
                ADD R2, R2, 1
                ADD R3, R1, R2
                ST R3, Result

                                     ; Result is Param1 - Param2
                                     ; Your code goes here (~6 lines)
                RET
;------------------------------------------------------------------------------
IntMul         
               AND R0, R0, 0
               LD R1, Param1
               BRz EXIT
               LD R2, Param2
               BRz EXIT
TEST           
               ADD R0, R0, R1
               ADD R2, R2, -1
               BRz EXIT
               BR TEST
EXIT            
               ST R0, Result
                                     ; Result is Param1 * Param2
                                     ; Your code goes here (~9 lines)
                RET
;------------------------------------------------------------------------------
BinaryOr        
                LD R1, Param1
                LD R2, Param2
                NOT R1, R1
                NOT R2, R2
                ADD R0, R1, R2
                NOT R0, R0
                ST R0, Result
                                     ; Result is Param1 | Param2
                                     ; Your code goes here (~7 lines)
                RET
;------------------------------------------------------------------------------
LeftShift      
                LD R1, Param1
                LD R2, Param2
LOOP            
                ADD R1, R1, R1
                ADD R2, R2, -1
                BRp LOOP
                ST R1, Result
                                     ; Result is Param1 << Param2
                                     ; (Fill vacant positions with 0's)
                                     ; Your code goes here (~7 lines)
                RET
;------------------------------------------------------------------------------
RightShift      

                                     ; Result is Param1 >> Param2
                                     ; (Fill vacant positions with 0's)
                                     ; Your code goes here (~16 lines)
                RET
;------------------------------------------------------------------------------
                .END
