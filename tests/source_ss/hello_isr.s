.section only_section:
# .section startup:

.word _start
.word _illegal_instruction_handler
.word _timer_handler
.word _terminal_handler
.word interrupt_handler

# .section isr_handlers:

_illegal_instruction_handler:
_timer_handler:
_terminal_handler:
    iret

interrupt_handler:
    mov (%r0), term_out
    mov 1(%r0), term_out
    mov 2(%r0), term_out
    mov $LF, term_out
    iret

# .section text:

_start:
    mov $msg, %r0

    int 4

    halt

# .section data:

msg:
.byte 'I', 'N', 'T'
msg_end:

.equ msg_len, msg_end - msg
.equ term_out, 0xff00
.equ LF, 0xa
