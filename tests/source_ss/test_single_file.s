.section only_section:

.word _start                        # 0x0009
.word _illegal_instruction_handler  # 0x0008
.word _timer_handler                # 0x0008
.word _terminal_handler             # 0x0008

_illegal_instruction_handler:
_timer_handler:
_terminal_handler:
    iret

_start:
    # TODO: implement
    halt
