MEMORY {
    TPA (rwx) : ORIGIN = 0x0100, LENGTH = 48k
}

SECTIONS {
    .text : {
        *(.header)
        *(.text)
    } > TPA
    .data : {
        ___data_start = .;
        *(.data)
        ___data_end = .;
        ___data_load = LOADADDR(.data);
    } > TPA
    .bss : {
        ___bss_start = .;
        *(.bss)
        ___bss_end = .;
    } > TPA
    .heap : {
        ___heap_start = .;
        . += 512;
        ___heap_end = .;
    } > TPA
}
