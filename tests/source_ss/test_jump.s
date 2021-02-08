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

    mov $0, %r0
    mov $1, %r1

    test %r0, $1
    jne error

    jmp label0

    mov $ascii_0, term_out # not executed

label0:
    mov $ascii_1, term_out

    cmp %r0, %r1
    jeq error
    cmp %r0, $0
    jne error
    cmp %r0, $0
    jgt error

    cmp $0, %r0
    jeq label1

    mov $ascii_0, term_out # not executed
label1:
    mov $ascii_2, term_out
    cmp %r0, %r1
    jne label2

    mov $ascii_0, term_out # not executed
label2:
    mov $ascii_3, term_out
    cmp %r1, %r0
    jgt label3

    mov $ascii_0, term_out # not executed
label3:
    mov $ascii_4, term_out
    test %r1, $1
    jne label4

    mov $ascii_0, term_out # not executed
label4:
    mov $ascii_5, term_out
    mov $LF, term_out
error:
    halt


# .section data:

.equ ascii_0, '0'
.equ ascii_1, '1'
.equ ascii_2, '2'
.equ ascii_3, '3'
.equ ascii_4, '4'
.equ ascii_5, '5'
.equ LF, 0xa
.equ term_out, 0xff00
