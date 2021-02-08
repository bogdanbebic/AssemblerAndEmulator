.section only_section:
# .section startup:

.word _start
.word _illegal_instruction_handler
.word _timer_handler
.word _terminal_handler

# .section isr_handlers:

_illegal_instruction_handler:
_timer_handler:
    iret

_terminal_handler:
    mov (%r0), term_out
    mov 1(%r0), term_out
    mov 2(%r0), term_out
    mov 3(%r0), term_out

    mov $LF, term_out

    mov term_in, %r1
    mov %r1, term_out

    mov $LF, term_out

    # halt
    sub $1, cnt
    iret

# .section text:

_start:
    mov $msg, %r0

loop:
    cmp $0, cnt
    jne loop

    halt

# .section data:

cnt:
.word 5

msg:
.byte 'T', 'E', 'R', 'M'
msg_end:

.equ msg_len, msg_end - msg
.equ term_out, 0xff00
.equ term_in, 0xff02

.equ LF, 0xa
