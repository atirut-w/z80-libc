MEMORY {
    TPA (rwx) : ORIGIN = 0x0100, LENGTH = 48k
}

SECTIONS {
    .text : {
        *(.header)
        *(.text)
    } > TPA
    .data : {
        *(.data)
    } > TPA
    .bss : {
        ___bss_start = .;
        *(.bss)
        ___bss_end = .;
    } > TPA
}
