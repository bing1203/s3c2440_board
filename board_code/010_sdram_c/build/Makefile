CROSS:=arm-linux

# 头文件路径
INCLUDE += -I../include/
INCLUDE += -I../include/driver/
INCLUDE += -I../include/lib/
INCLUDE += -I../include/s3c2440/

# 源文件路径
SRCPATH += ../src/driver
SRCPATH += ../src/lib
SRCPATH += ../test

# 源文件
SRC:=$(foreach var, $(SRCPATH), $(wildcard $(var)/*.c))
ASM:=$(foreach var, $(SRCPATH), $(wildcard $(var)/*.S))

# 目标文件
OBJCPATH:=$(foreach var, $(SRC), $(var:.c=.o))
OBJC:=$(foreach var, $(OBJCPATH), $(notdir $(var)))

OBJAPATH:=$(foreach var, $(ASM), $(var:.S=.o))
OBJA:=$(foreach var, $(OBJAPATH), $(notdir $(var)))

# 汇编文件

# 产物目录
OUTPUT:=../bin
OUTPUT_obj:=$(OUTPUT)/obj

# 输出产物名称
NAME ?= test

LDOBJ+=$(OUTPUT_obj)/start.o
LDOBJ+=$(OUTPUT_obj)/lib1funcs.o
LDOBJ+=$(foreach var, $(OBJC), $(addprefix $(OUTPUT_obj)/, $(var)))

all:$(OBJCPATH) $(OBJAPATH)
	$(CROSS)-ld -Ttext 0 $(LDOBJ) -o $(OUTPUT)/$(NAME).elf
	$(CROSS)-objcopy -O binary -S $(OUTPUT)/$(NAME).elf $(OUTPUT)/$(NAME).bin
	$(CROSS)-objdump -D $(OUTPUT)/$(NAME).elf > $(OUTPUT)/$(NAME).dis

%.o:%.c
	$(CROSS)-gcc -c -o $(OUTPUT_obj)/$(notdir $@) $^ $(INCLUDE)

$(OBJAPATH):
	$(CROSS)-gcc -c -o $(OUTPUT_obj)/$(notdir $@) $(@:.o=.S)

.PHONY:clean
clean:
	-rm $(OUTPUT)/obj/* -r
	-rm $(OUTPUT)/*.elf -r
	-rm $(OUTPUT)/*.bin -r
	-rm $(OUTPUT)/*.dis -r