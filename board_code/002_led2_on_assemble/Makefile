CROSS:=arm-linux

all:
	$(CROSS)-gcc -c -o start.o start.S
	$(CROSS)-ld -Ttext 0 start.o -o start.elf
	$(CROSS)-objcopy -O binary -S start.elf start.bin
	$(CROSS)-objdump -D start.elf > start.dis

.PHONY:clean
clean:
	rm *.bin *.o *.elf *.dis 