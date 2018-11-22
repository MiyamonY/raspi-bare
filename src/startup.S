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
  ;; ldr r0, =vector
  ;; mov r1, #0x0000

  ;; ldmia   r0!,{r2, r3, r4, r5, r6, r7, r8, r9}
  ;; stmia   r1!,{r2, r3, r4, r5, r6, r7, r8, r9}
  ;; ldmia   r0!,{r2, r3, r4, r5, r6, r7, r8, r9}
  ;; stmia   r1!,{r2, r3, r4, r5, r6, r7, r8, r9}

  ;; mov r0, #(CPSR_MODE_IRQ | CPSR_IRQ_INHIBIT | CPSR_FIQ_INHIBIT )
  ;; msr cpsr_c, r0
  ;; mov sp, #(63 * 1024 * 1024)

  ;; mov r0, #(CPSR_MODE_SVR | CPSR_IRQ_INHIBIT | CPSR_FIQ_INHIBIT )
  ;; msr cpsr_c, r0
  mov sp, #(64 * 1024 * 1024)

  bl main

  b .

exit_hypmode:
  ldr r0, =reset
  msr ELR_hyp, r0

  mov r0, #(CPSR_MODE_SVR | CPSR_IRQ_INHIBIT | CPSR_FIQ_INHIBIT)
  msr SPSR_hyp, r0
  eret

  .global _hangup
_hangup:
  stmfd r13!, {r0-r12, lr}
  bl err_handler
  ldmfd r13!, {r0-r12, lr}
  ldr r0, =0x000000d3
  msr cpsr, r0
  b .

_IRQ_interrupt:
  stmfd r13!, {r0-r12, lr}
  bl IRQ_handler
  ldmfd r13!, {r0-r12, lr}
  subs pc, lr, #4

  .global enable_IRQ
enable_IRQ:
  mrs r0, cpsr
  bic r0, r0, #0x80
  msr cpsr_c, r0
  bx lr

  .global disable_IRQ
disable_IRQ:
  mrs r0, cpsr
  ldr r1, =0x80
  orr r0, r0, r1
  msr cpsr_c, r0
  bx lr

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
_vec_Undef: .word _hangup
_vec_SWI: .word _hangup
_vec_PrefAbort: .word _hangup
_vec_DataAbort: .word _hangup
_vec_Reserved: .word _hangup
_vec_IRQ: .word _IRQ_interrupt
_vec_FIQ: .word _hangup
