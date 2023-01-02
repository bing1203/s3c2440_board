CROSS:=arm-linux

all:
	$(CROSS)-gcc -c -o led.o led.c
	$(CROSS)-gcc -c -o start.o start.S
	$(CROSS)-ld -Ttext 0 start.o led.o  -o led.elf
	$(CROSS)-objcopy -O binary -S led.elf led.bin
	$(CROSS)-objdump -D led.elf > led.dis

.PHONY:clean
clean:
	rm *.bin *.o *.elf *.dis 