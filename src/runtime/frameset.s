    .globl __frameset0
__frameset0:
    pop hl

    push ix
    ld ix, 0
    add ix, sp

    jp (hl)
    
    .globl __frameset
__frameset:
    pop de
    
    push ix
    ld ix, 0
    add ix, sp
    add hl, sp
    ld sp, hl

    ex de, hl
    jp (hl)
