    .globl __setflag
__setflag:
    push bc
    push af
    pop bc

    bit 2, c
    jr z, 0f
    ld a, c
    xor 0x80
    ld c, a
0:
    push bc
    pop af
    pop bc
    ret
