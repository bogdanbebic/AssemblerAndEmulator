.global msg, msg_len
.global term_out

.section data:

msg:
.byte 'H', 'e', 'l', 'l', 'o',
.byte 44 # comma
.byte 32 # space
.byte 'W', 'o', 'r', 'l', 'd', '!'
.byte 10 # LF
msg_end:

.equ msg_len, msg_end - msg
.equ term_out, 0xff00
