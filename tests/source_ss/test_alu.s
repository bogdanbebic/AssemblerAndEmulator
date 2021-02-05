.section only_section:
# .section startup:

.word _start
.word _illegal_instruction_handler
.word _timer_handler
.word _terminal_handler

# .section isr_handlers:

_illegal_instruction_handler:
_timer_handler:
_terminal_handler:
    iret

# .section text:

_start:

    # arithmetic operations
    mov $5, %r0
    mov $6, %r1
    mov $3, %r2
    mov $8, %r3

    add $1, %r0
    sub $2, %r1
    mul $3, %r2
    div $4, %r3

    add $ascii_zero, %r0
    add $ascii_zero, %r1
    add $ascii_zero, %r2
    add $ascii_zero, %r3

    mov %r0, term_out # 6
    mov $LF, term_out # \n
    mov %r1, term_out # 4
    mov $LF, term_out # \n
    mov %r2, term_out # 9
    mov $LF, term_out # \n
    mov %r3, term_out # 2
    mov $LF, term_out # \n

    mov $LF, term_out # \n

    # logical operations (bit operations)
    not $0xffbe, %r0

    mov $0xff73, %r1
    and $0x00c6, %r1

    mov $0x3, %r2
    or $0x40, %r2

    mov $0x40, %r3
    xor $0x04, %r3

    mov %r0, term_out # A
    mov $LF, term_out # \n
    mov %r1, term_out # B
    mov $LF, term_out # \n
    mov %r2, term_out # C
    mov $LF, term_out # \n
    mov %r3, term_out # D
    mov $LF, term_out # \n

    mov $LF, term_out # \n

    # shift operations
    mov $2, %r0
    mov $2, %r1

    shl $1, %r0
    shr %r1, $1

    add $ascii_zero, %r0
    add $ascii_zero, %r1

    mov %r0, term_out # 4
    mov $LF, term_out # \n
    mov %r1, term_out # 1
    mov $LF, term_out # \n

    halt

# .section data:

.equ ascii_zero, '0'
.equ LF, 0xa
.equ term_out, 0xff00
