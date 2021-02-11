.extern msg, msg_len
.extern term_out

.global _start

.section text:

_start:
    # mov $0xe000, %psw
    mov $msg, %r0
    mov $0, %r1
    mov $msg_len, %r2
loop:
    mov (%r0), term_out

    add $1, %r0
    add $1, %r1
    cmp %r1, %r2
    jne loop

    halt
