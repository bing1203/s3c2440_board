.text
.global _start
_start:
	/* 设置栈 */
	ldr sp, =4096 /* nand启动 */

	/* 调用main */
	bl main
halt:
	b halt
