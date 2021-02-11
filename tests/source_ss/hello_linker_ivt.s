.extern _start
.extern _illegal_instruction_handler
.extern _timer_handler
.extern _terminal_handler

.section startup:

.word _start
.word _illegal_instruction_handler
.word _timer_handler
.word _terminal_handler

.section text:

_illegal_instruction_handler:
_timer_handler:
_terminal_handler:
    iret

