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

hello:
    mov $msg, %r0

    mov (%r0), term_out
    mov 1(%r0), term_out
    mov 2(%r0), term_out
    mov 3(%r0), term_out
    mov 4(%r0), term_out
    mov 5(%r0), term_out
    mov 6(%r0), term_out
    mov 7(%r0), term_out
    mov 8(%r0), term_out
    mov 9(%r0), term_out
    mov 10(%r0), term_out
    mov 11(%r0), term_out
    mov 12(%r0), term_out
    mov 13(%r0), term_out

    ret

_start:
    call hello
    halt

# .section data:

msg:
.byte 'H', 'e', 'l', 'l', 'o',
.byte 44 # comma
.byte 32 # space
.byte 'W', 'o', 'r', 'l', 'd', '!'
.byte 10 # LF
msg_end:

.equ msg_len, msg_end - msg
.equ term_out, 0xff00
