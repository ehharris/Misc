;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Start of reserved section - DO NOT CHANGE ANYTHING HERE!!!
; The only exception is that you can modify the .FILL value of Needle to make
; it easy to test.

                .ORIG x3000
                BR Main

; Stack base
Stack           .FILL x4000

; Parameter and result
Needle          .FILL #4
Result          .FILL xFFFF

; Entry point
Main            LD    R6, Stack           ; Stack initialization
                LD    R5, Stack           ;
                
                LD    R0, Count           ; Load the number of elements
                LEA   R1, Haystack        ; Load loAddress
                LD    R2, Needle          ; Load the element to search for
                
                AND   R3, R3, #0          ; Calculate hiAddress
                ADD   R3, R3, #-1         ;
                ADD   R3, R0, R3          ;
                ADD   R3, R1, R3          ;
                PUSH  R3                  ; Push parameters in reverse order
                PUSH  R1                  ;
                PUSH  R2                  ;
                JSR   BinarySearch        ; Call BinarySearch
                POP   R0                  ; Retrieve the return value
                ADD   R6, R6, #3          ; Clean up
                
                ST    R0, Result          ; Store the result in global variable
Finish          HALT
                
; End of reserved section
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; DO NOT ADD ANYTHING IN BETWEEN THESE SECTIONS
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Start of the array definition - DO NOT CHANGE THE LABEL NAMES OR POSITIONS!!!
; In this section, you're only allowed to change the .FILL value for Count
; (number of elements in the array) and the .FILL values of the array but DO NOT
; delete or add any lines in this section (otherwise, you risk getting no
; credit). If you want fewer elements in the array, simply change Count. Note 
; that the maximum number of elements in the array is 20.

Count           .FILL #7

Haystack        .FILL #14
                .FILL #12
                .FILL #10
                .FILL #8
                .FILL #6
                .FILL #4
                .FILL #2
                .FILL #0
                .FILL #0
                .FILL #0
                .FILL #0
                .FILL #0
                .FILL #0
                .FILL #0
                .FILL #0
                .FILL #0
                .FILL #0
                .FILL #0
                .FILL #0
                .FILL #0

; End of the array definition
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Start of the function definition
; This is where you will implement your BinarySearch function. DO NOT implement
; any other functions (not even helper functions).

; int *BinarySearch(int x, int *loAddress, int *hiAddress);
Mid             .BLKW 1         ;for mid value
negT            .FILL #-2       ;literally just -2 cause lc3 is dumb

BinarySearch                    ;Initialize
                ADD R6, R6, #-1 ;Ret addy
                PUSH R7
                PUSH R5
                ADD R5, R6, #-1 ;New FP
                ADD R6, R6, #-2 ;Local Vari
                LDR R1, R5, #5  ;BaseCase Check
                LDR R2, R5, #6  ;R1 = lo, R2 = hi
                NOT R1, R1      
                ADD R1, R1, #1  ;Neg R1
                ADD R3, R1, R2  ;R3 = hi - lo
                BRn BaseCase    ;if hi < lo ret 0
                .ZERO R4        ;Offset Count
                LD R0, negT     

CalcOffset          
                ADD R1, R0, R3  
                BRn Next        ;< divisor so break
                ADD R3, R3, R0
                ADD R4, R4, #1  ;Incr offset
                BR CalcOffset

Next     
                STR R4, R5, #0  ;locvari1
                LDR R1, R5, #5  ;R1 = lo again
                ADD R3, R1, R4  ;R3 = lo + offset
                STR R3, R5, #-1 ;locvari2
                STR R3, R5, #3  ;result
                ST R3, Mid      ;Store here for fun (thanks lc3)
                LDI R0, Mid     ;Now R0 = potential result
                LDR R4, R5, #4  ;R4 = needle
                NOT R4, R4
                ADD R4, R4, #1  ;negNeedle
                ADD R2, R0, R4  ;(lo + offset) - needle
                BRz TheGreatReturno ;found it
                BRp TryLower    ;go to lower else look higher
                ADD R3, R3, #1  ;mid+1
                LDR R4, R5, #4  
                LDR R2, R5, #6  ;R2 = high again
                PUSH R2         ;hi
                PUSH R3         ;lo
                PUSH R4         ;needle
                JSR BinarySearch ;recurse
                POP R0          ;result
                ADD R6, R6, #3  ;stack stuff
                STR R0, R5, #3  ;new ans
                BR TheGreatReturno
                
TryLower        
                ADD R3, R3, #-1 ;mid-1
                LDR R4, R5, #4  ;repeat from 118
                PUSH R3         ;hi
                PUSH R1         ;lo
                PUSH R4         ;needle
                JSR BinarySearch
                POP R0
                ADD R6, R6, #3
                STR R0, R5, #3
                BR TheGreatReturno
                
BaseCase        
                .ZERO R0        ;make R0 = 0
                STR R0, R5, #3  ;ans = 0

TheGreatReturno 
                ADD R6, R6, #2  ;Remove locvaris
                POP R5          
                POP R7
                ; Start here
                ; My solution was 75 lines (including empty lines and comments)
                RET

; End of the function definition
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

                .END
