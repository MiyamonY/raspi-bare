  @ startup

.equ    CPSR_MODE_USER,         0x10
.equ    CPSR_MODE_FIQ,          0x11
.equ    CPSR_MODE_IRQ,          0x12
.equ    CPSR_MODE_SVR,          0x13
.equ    CPSR_MODE_ABORT,        0x17
.equ    CPSR_MODE_UNDEFINED,    0x1B
.equ    CPSR_MODE_SYSTEM,       0x1F

.equ    CPSR_IRQ_INHIBIT,       0x80
.equ    CPSR_FIQ_INHIBIT,       0x40
.equ    CPSR_THUMB,             0x20

  .global _start
  .align
_start:
  ldr pc, _vec_Reset
  ldr pc, _vec_Undef
  ldr pc, _vec_SWI
  ldr pc, _vec_PrefAbort
  ldr pc, _vec_DataAbort
  ldr pc, _vec_Reserved
  ldr pc, _vec_IRQ
  ldr pc, _vec_FIQ

_vec_Reset:     .word _reset
_vec_Undef:     .word undefined_instruction_vector
_vec_SWI:       .word software_interrupt_vector
_vec_PrefAbort: .word prefetch_abort_vector
_vec_DataAbort: .word data_abort_vector
_vec_Reserved:  .word _reset
_vec_IRQ:       .word interrupt_vector
_vec_FIQ:       .word fast_interrupt_vector

_reset:
  mov     r0, #0x01000000
  mov     r1, #0x00000000

  ldmia   r0!,{r2, r3, r4, r5, r6, r7, r8, r9}
  stmia   r1!,{r2, r3, r4, r5, r6, r7, r8, r9}
  ldmia   r0!,{r2, r3, r4, r5, r6, r7, r8, r9}
  stmia   r1!,{r2, r3, r4, r5, r6, r7, r8, r9}

  mov r0, #(CPSR_MODE_IRQ | CPSR_IRQ_INHIBIT | CPSR_FIQ_INHIBIT)
  msr cpsr_c, r0
  mov sp, #(63 * 1024 * 1024)

  mov r0, #(CPSR_MODE_SVR | CPSR_IRQ_INHIBIT | CPSR_FIQ_INHIBIT)
  msr cpsr_c, r0
  mov sp, #(64*1024*1024)

  bl main

  b .

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

  .global getmode
getmode:
  mrs r0, cpsr
  bx lr
