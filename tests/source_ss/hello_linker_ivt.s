.extern _start
.global _illegal_instruction_handler
.global _timer_handler
.global _terminal_handler

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

