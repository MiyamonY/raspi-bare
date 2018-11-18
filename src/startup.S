  @ startup
  .global _start
  .align

  .equ CPSR_MODE_USER, 0x10
  .equ CPSR_MODE_FIQ,  0x11
  .equ CPSR_MODE_IRQ,  0x12
  .equ CPSR_MODE_SVR,  0x13
  .equ CPSR_MODE_MON, 0x16
  .equ CPSR_MODE_ABORT, 0x17
	.equ CPSR_MODE_HYP, 0x1B
  .equ CPSR_MODE_UNDEFINED, 0x1B
  .equ CPSR_MODE_SYSTEM, 0x1F

  .equ CPSR_IRQ_INHIBIT, 0x80
  .equ CPSR_FIQ_INHIBIT, 0x40
  .equ CPSR_THUMB, 0x20

_start:
  bl exit_hypmode

reset:
  ldr sp, =0x06400000

  bl main

  b .

exit_hypmode:
  ldr r0, =reset
  msr ELR_hyp, r0

  mov r0, #(CPSR_MODE_SVR | CPSR_IRQ_INHIBIT | CPSR_FIQ_INHIBIT)
  msr SPSR_hyp, r0
  eret
