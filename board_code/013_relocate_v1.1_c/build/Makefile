CROSS:=arm-linux

CCFLAG:=-fdata-sections -ffunction-sections
LDFLAG:=--gc-sections

# 头文件路径
INCLUDE += -I../include/
INCLUDE += -I../include/driver/
INCLUDE += -I../include/lib/
INCLUDE += -I../include/s3c2440/

# 源文件路径
SRCPATH += ../src/driver
SRCPATH += ../src/lib
SRCPATH += ../src/start
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

LDOBJ1+=$(OUTPUT_obj)/start.o
LDOBJ1+=$(OUTPUT_obj)/lib1funcs.o
LDOBJ2+=$(foreach var, $(OBJC), $(addprefix $(OUTPUT_obj)/, $(var)))
LDOBJ2:=$(sort $(LDOBJ2))

all:$(OBJCPATH) $(OBJAPATH)
	$(CROSS)-ld -T uboot.lds $(LDOBJ1) $(LDOBJ2) $(LDFLAG) -o $(OUTPUT)/$(NAME).elf
	$(CROSS)-objcopy -O binary -S $(OUTPUT)/$(NAME).elf $(OUTPUT)/$(NAME).bin
	$(CROSS)-objdump -D $(OUTPUT)/$(NAME).elf > $(OUTPUT)/$(NAME).dis

%.o:%.c
	$(CROSS)-gcc -c -o $(OUTPUT_obj)/$(notdir $@) $^ $(INCLUDE) $(CCFLAG)

$(OBJAPATH):
	$(CROSS)-gcc -c -o $(OUTPUT_obj)/$(notdir $@) $(@:.o=.S) $(CCFLAG)

.PHONY:clean
clean:
	-rm $(OUTPUT)/obj/* -r
	-rm $(OUTPUT)/*.elf -r
	-rm $(OUTPUT)/*.bin -r
	-rm $(OUTPUT)/*.dis -r