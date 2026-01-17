GCC_DIR := D:/GNU_Toolchain/GNU_News
CC = $(GCC_DIR)/bin/arm-none-eabi-gcc
AS = $(GCC_DIR)/bin/arm-none-eabi-as
HEX = $(GCC_DIR)/arm-none-eabi/bin/objcopy.exe
LD_FILE := Linker/stm_ls.ld
INC_DIRS += Driver/GPIO/inc \
			Driver/UART/inc
SRC_DIRS += Driver/GPIO/src

CHIP=cortex-m3
CCFLAGS= -c -mcpu=$(CHIP) -mthumb -std=gnu11 -O0 -I$(INC_DIR)
ASFLAGS = -mcpu=$(CHIP) -mthumb
LDFLAGS= -nostdlib -T $(LD_FILE) -Wl,-Map=Output/GPIO.map

clean:
	@rm ./Output/*
	@echo "Clean done!"
build: Output/GPIO.hex
	@echo "Build done!"

Output/main.o:User/src/main.c
	@$(CC) $(CCFLAGS) -o $@ $^

Output/GPIO.o: Driver/GPIO/src/GPIO.c
	@$(CC) $(CCFLAGS) -o $@ $^

Output/startup_stm32f10x_md.o: Startup/startup_stm32f10x_md.s
	@$(AS) $(ASFLAGS) $^ -o $@ 	

Output/GPIO.elf:Output/main.o Output/GPIO.o Output/startup_stm32f10x_md.o
	@echo "Linking ...."
	@$(CC) $^ -o $@ $(LDFLAGS)
	@echo "Linking done!"

Output/GPIO.hex: Output/GPIO.elf
	@$(HEX) -O ihex $^ $@ 
	@echo "Making file .hex..."

run:
	./Tools/ST-LINKUtility/ST-LINK_CLI.exe -ME
	./Tools/ST-LINKUtility/ST-LINK_CLI.exe -p Output/GPIO.hex 0x08000000
	./Tools/ST-LINKUtility/ST-LINK_CLI.exe -rst