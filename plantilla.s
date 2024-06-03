// prj.s
// 23 de Mayo de 2022
// Arqui I UCC

.text

.global main
main:
      LDR R3, =array // load base address of a into R3
      ... more code here
done: NOP            // dummy instruction for breakpoint
      MOV PC,L       // return from main

.data
array:
      .byte 0x08
      .byte 0x10
      .byte 0xFF
      ... more data here
.end
