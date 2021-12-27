* :asmsyntax=nasm

                ORG     $8000
                CLD
clock_address   EQU     $bf07       ; points to address of clock driver code
clock_address   EQU     $bf08       ; points to address of clock driver code
date1_address   EQU     $bf90       ; prodos Y6-Y0 and M3 address bits
date2_address   EQU     $bf91       ; prodos M2-M0 and D4-D0 address bits
bday1           EQU                 ; Hardcode my birthday for testing
bday2           EQU                 ; Hardcode my birthday for testing
machid          EQU     $bf98       ; bit 0 -> 1=clock found, 0=no clock

