.text
.global _start
_start:
	/* 关闭看门狗 */
	ldr r0, =0x53000000
	mov r1, #0
	str r1, [r0]

	/* 设置栈 */
	/* 判断从nand或nor启动，设置不同的栈顶指针 */
	/* 无法像写内存一样写nor，若同一地址写入数据和读出数据不同，则是nor启动 */
	mov r1, #0
	ldr r0, [r1] /* 读取地址0的值备份 */
	str r1, [r1] /* 向地址0写0 */
	ldr r2, [r1] /* 再读出地址0的值 */
	cmp r1, r2   /* 比较写入和读出的值 */
	ldr sp, =0x40000000+4096 /* 假设是nor启动 */
	moveq sp, #4096 /* nand启动 */
	streq r0, [r1]  /* 恢复地址0的值 */

	bl main
halt:
	b halt
