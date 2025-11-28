.syntax unified
.cpu cortex-m3
.thumb

.global _start
.global Reset_Handler

.section .vectors, "a", %progbits
.word _estack
.word Reset_Handler
.word Default_Handler

.word Default_Handler

.section .text
.thumb_func

Reset_Handler:
  ldr r0, =_sidata
  ldr r1, =_sdata
  ldr r2, =_edata

copy_data:
  cmp r1, r2
  bge zero_bss
  ldr r3, [r0], #4
  str r3, [r1], #4
  b copy_data 

zero_bss:
  ldr r1, =_sbss
  ldr r2, =_ebss
  

zero_loop:
  cmp r1, r2
  bge call_main
  movs r3, #0
  str r3, [r1], #4
  b zero_loop 

call_main:
  ;LDR R0, =var
  ;LDR R1, [R0]
  ;ADD R1, R1, #1
  ;STR R1, [R0]
  ;BX LR
  bl main 

hang: 
  b hang

  .thumb_func
Default_Handler:
  b .


;.section .data
;var:
;  .word 41

