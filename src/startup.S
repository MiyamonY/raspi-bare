  @ startup
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

  .global vector
vector:
  ldr pc, _vec_Reset
  ldr pc, _vec_Undef
  ldr pc, _vec_SWI
  ldr pc, _vec_PrefAbort
  ldr pc, _vec_DataAbort
  ldr pc, _vec_Reserved
  ldr pc, _vec_IRQ
  ldr pc, _vec_FIQ

_vec_Reset: .word reset
_vec_Undef: .word interrupt_undef
_vec_SWI: .word interrupt_swi
_vec_PrefAbort: .word interrupt_pref_abort
_vec_DataAbort: .word interrupt_data_abort
_vec_Reserved: .word reset
_vec_IRQ: .word interrupt_irq
_vec_FIQ: .word interrupt_fiq

reset:
  bl exit_hypmode

start:
  mov r0, #0x8000
  mov r1, #0x0000

  ldmia   r0!, {r2, r3, r4, r5, r6, r7, r8, r9}
  stmia   r1!, {r2, r3, r4, r5, r6, r7, r8, r9}
  ldmia   r0!, {r2, r3, r4, r5, r6, r7, r8, r9}
  stmia   r1!, {r2, r3, r4, r5, r6, r7, r8, r9}

  mov r0, #(CPSR_MODE_IRQ | CPSR_IRQ_INHIBIT | CPSR_FIQ_INHIBIT)
  msr cpsr_c, r0
  mov sp, #0x4000

  mov r0, #(CPSR_MODE_SVR | CPSR_IRQ_INHIBIT | CPSR_FIQ_INHIBIT)
  msr cpsr_c, r0
  mov sp, #0x8000

  bl main

  b .

exit_hypmode:
  ldr r0, =start
  msr ELR_hyp, r0

  mov r0, #(CPSR_MODE_SVR | CPSR_IRQ_INHIBIT | CPSR_FIQ_INHIBIT)
  msr SPSR_hyp, r0
  eret
