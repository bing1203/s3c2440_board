/* 看门狗 */
#define WTCON (0x53000000)
#define WTDAT (0x53000004)
#define WTCNT (0x53000008)

/* 时钟 */
#define LOCKTIME (0x4C000000)
#define MPLLCON  (0x4C000004)
#define UPLLCON  (0x4C000008)
#define CLKCON   (0x4C00000C)
#define CLKDIVN  (0x4C000014)

#define FCLK_400MHz ((0x5C << 12) | (1 << 4) | (1 << 0))
#define HCLK_FCLK_4 (0x2 << 1)
#define PCLK_HCLK_2 (0x1 << 0)

.text
.global _start
_start:
	/* 关闭看门狗 */
	ldr r0, =WTCON
	mov r1, #0
	str r1, [r0]

	/* 设置MPLL，FCLK:HCLK:PCLK=400:100:50 */
	ldr r0, =LOCKTIME
	ldr r1, =0xFFFFFFFF
	str r1, [r0]

	/* CLKDIVN(0x4C000014) = 0x5, tFCLK:tHCLK:tPCLK=1:4:8 */
	ldr r0, =CLKDIVN
	ldr r1, =HCLK_FCLK_4 | PCLK_HCLK_2
	str r1, [r0]

	/* 设置CPU工作于异步模式 */
	mrc p15, 0, r0, c1, c0, 0
	orr r0, r0, #0xC0000000
	mcr p15, 0, r0, c1, c0, 0

	/* 设置MPLLCON(0x4C000004) = (92<<12)|(1<<4)|(1<<0) 
	 *  m = MDIV+8 = 92+8=100
	 *  p = PDIV+2 = 1+2 = 3
	 *  s = SDIV = 1
	 *  FCLK = 2*m*Fin/(p*2^s) = 2*100*12/(3*2^1)=400M
	 */

	/* 一旦设置PLL, 就会锁定lock time直到PLL输出稳定
	 * 然后CPU工作于新的频率FCLK
	 */

	ldr r0, =MPLLCON
	ldr r1, =FCLK_400MHz
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

	bl init

	bl main
halt:
	b halt
