.text
.global _start
_start:
	/* 将GPF5设置为输出引脚 */
	ldr r1, =0x56000050
	ldr r0, =0x400
	str r0, [r1]

	/* 将GPF5设置为高电平 */
	ldr r1, =0x56000054
	ldr r0, =0
	str r0, [r1]
halt:
	b halt