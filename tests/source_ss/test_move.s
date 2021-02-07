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

    # mov

    mov $data, %r0
    mov data, %r1

    mov %r1, term_out # 0
    mov (%r0), term_out # 0
    mov 2(%r0), term_out # 1

    mov $LF, term_out # \n

    # xchg

    mov $ascii_A, %r0
    mov $ascii_B, %r1

    mov %r0, term_out # A
    mov %r1, term_out # B

    xchg %r0, %r1

    mov %r0, term_out # B
    mov %r1, term_out # A

    mov $LF, term_out # \n

    # stack

    mov %r0, term_out # B
    mov %r1, term_out # A

    push %r0
    pop %r1

    mov %r0, term_out # B
    mov %r1, term_out # B

    mov $LF, term_out # \n

    halt

# .section data:

data:
.word '0'
.word '1'

.equ ascii_A, 'A'
.equ ascii_B, 'B'
.equ LF, 0xa
.equ term_out, 0xff00
