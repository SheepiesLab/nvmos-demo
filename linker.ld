ENTRY(_start)

SECTIONS
{
	. = 0x40000000;
	.text BLOCK(4K): ALIGN(4K)
	{
		*(.text)
		*(.eh_frame)
	}
	.bss BLOCK(4K): ALIGN(4K)
	{
		*(.bss)
	}
}
