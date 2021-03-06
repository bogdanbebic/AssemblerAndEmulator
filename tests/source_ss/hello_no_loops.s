.section only_section:
# .section startup:

.word _start                        # 0x0009
.word _illegal_instruction_handler  # 0x0008
.word _timer_handler                # 0x0008
.word _terminal_handler             # 0x0008

# .section isr_handlers:

_illegal_instruction_handler:
_timer_handler:
_terminal_handler:
    iret

# .section text:

_start:
    # mov $0xe000, %psw
    mov $msg, %r0

    mov (%r0), term_out
    add $1, %r0
    mov (%r0), term_out
    add $1, %r0
    mov (%r0), term_out
    add $1, %r0
    mov (%r0), term_out
    add $1, %r0
    mov (%r0), term_out
    add $1, %r0
    mov (%r0), term_out
    add $1, %r0
    mov (%r0), term_out
    add $1, %r0
    mov (%r0), term_out
    add $1, %r0
    mov (%r0), term_out
    add $1, %r0
    mov (%r0), term_out
    add $1, %r0
    mov (%r0), term_out
    add $1, %r0
    mov (%r0), term_out
    add $1, %r0
    mov (%r0), term_out
    add $1, %r0
    mov (%r0), term_out
    add $1, %r0

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
