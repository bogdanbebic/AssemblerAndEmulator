.section only_section:
# .section startup:

.word _start
.word _illegal_instruction_handler
.word _timer_handler
.word _terminal_handler

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
    sub $1, cnt
    iret

# .section text:

_start:
    mov $msg, %r0

loop0:
    cmp $0, cnt
    jne loop0

    mov $1, timer_cfg
    mov $5, cnt

loop1:
    cmp $0, cnt
    jne loop1

    halt

# .section data:

cnt:
.word 5

msg:
.byte 'T', 'I', 'M', 'E', 'R'
.byte 10 # LF
msg_end:

.equ msg_len, msg_end - msg
.equ term_out, 0xff00

.equ timer_cfg, 0xff10
