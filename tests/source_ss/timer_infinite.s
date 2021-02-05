.section only_section:
# .section startup:

.word _start                        # 0x0009
.word _illegal_instruction_handler  # 0x0008
.word _timer_handler                # 0x0008
.word _terminal_handler             # 0x0008

# .section isr_handlers:

_illegal_instruction_handler:
_terminal_handler:
    iret

_timer_handler:
    mov (%r0), term_out
    mov 1(%r0), term_out
    mov 2(%r0), term_out
    mov 3(%r0), term_out
    mov 4(%r0), term_out
    mov 5(%r0), term_out
    iret

# .section text:

_start:
    mov $msg, %r0

loop:
    jmp loop

    halt

# .section data:

msg:
.byte 'T', 'i', 'm', 'e', 'r', '!'
.byte 10 # LF
msg_end:

.equ msg_len, msg_end - msg
.equ term_out, 0xff00
