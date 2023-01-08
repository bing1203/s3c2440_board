OUTPUT_FORMAT("elf32-littlearm", "elf32-littlearm", "elf32-littlearm")
OUTPUT_ARCH(arm)
ENTRY(_start)
SECTIONS{
	. = 0x33C00000;
	__text_start = .;
	. = ALIGN(4);

	.text :
	{
		../bin/obj/start.o (.text)
		../bin/obj/lib1funcs.o (.text)
		../bin/obj/init.o (.text)
		../bin/obj/s3c2440.o (.text)
		../bin/obj/sdram.o (.text)
		../bin/obj/nand.o (.text)
		*(.text)
	}

	. = ALIGN(4);
	.rodata :
	{
		*(.rodata)
	}

	. = ALIGN(4);
	.data :
	{
		*(.data)
	}

	. = ALIGN(4);
	.got :
	{
		*(.got)
	}

	. = ALIGN(4);
	__bss_start = .;
	.bss :
	{
		*(.bss)
	}
	__bss_end = .;
}