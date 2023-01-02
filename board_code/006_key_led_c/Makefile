CROSS:=arm-linux

all:
	$(CROSS)-gcc -c -o key_led.o key_led.c
	$(CROSS)-gcc -c -o start.o start.S
	$(CROSS)-ld -Ttext 0 start.o key_led.o  -o key_led.elf
	$(CROSS)-objcopy -O binary -S key_led.elf key_led.bin
	$(CROSS)-objdump -D key_led.elf > key_led.dis

.PHONY:clean
clean:
	rm *.bin *.o *.elf *.dis 