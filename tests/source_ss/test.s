
.equ x, 5
byte_label_UND:
.byte 1
.section data_section: # comment
byte_label:
.byte 1
skip_label:     .skip 5
word_label:.word 2
.global word_label
.section section_name:
.skip 3
.global main
.global glb_f, glb_g
.extern ext_f
.extern ext_g, ext_h

main:
    xor %r1, %r1
# .end
    call ext_f
    call ext_h
    ret
