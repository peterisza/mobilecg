#+---------------------------------------------------------------------------
#
#  Copyright (c) 2015 Anton Gusev aka AHTOXA (HTTP://AHTOXA.NET)
#
#  Modified by Robert Csordas for MobilECG II
#
#  File:       makefile
#
#  Contents:   makefile to build arm Cortex-M3/M4 software with gcc
#
#----------------------------------------------------------------------------

	TOOLCHAINDIR = 
	-include makefile.local
# program name
	TARGET	= mobilecg

# toolchain
	TOOL	= $(TOOLCHAINDIR)arm-none-eabi-

# program version
    VER_MAJOR   = 0
    VER_MINOR   = 1


# compile options

	OPTIMIZE        = -O0
	USE_LTO         = NO
	USE_CPP11       = YES
	USE_NANO_LIB    = YES

	CHIP		= STM32F411xE
	HSE_VALUE	= 12000000

# compiler defines
    DEFS        = -D$(CHIP)
    DEFS        += -DVER_MAJOR=$(VER_MAJOR)
    DEFS        += -DVER_MINOR=$(VER_MINOR)
    DEFS        += -DHSE_VALUE=$(HSE_VALUE)
	MCU			= cortex-m4
	FPU			= -mfpu=fpv4-sp-d16 -mfloat-abi=hard

	STM32_LIB_WARNING_SUPRESS = -Wno-unused-parameter -Wno-cast-align -Wno-pointer-sign -Wno-redundant-decls -Wno-sign-compare -Wno-cast-qual -Wno-missing-field-initializers -Wno-type-limits -Wno-empty-body
###########################################################
#  common part for all my cortex-m3/m4 projects
###########################################################

	BASE		= .
	CC			= $(TOOL)gcc
	CXX			= $(TOOL)g++
	LD			= $(TOOL)g++
	AS			= $(CC) -x assembler-with-cpp
	OBJCOPY		= $(TOOL)objcopy
	OBJDUMP		= $(TOOL)objdump
	SIZE		= $(TOOL)size -d
#	FLASHER		= openocd
#	FLASHER		= stm32flash
ifeq ($(OS),Windows_NT)
	FLASHER		= ST-LINK_CLI
else
	FLASHER		= openocd
#	FLASHER		= st-flash
endif
	DOXYGEN		= doxygen
	RM			= rm -rf
	CP			= cp
	MD			= mkdir -p


# dirs
	TARGETDIR   = output
	SRCDIR		= src
	OBJDIR		= $(TARGETDIR)/obj
	EXEDIR		= $(TARGETDIR)/exe
	LSTDIR		= $(TARGETDIR)/lst
	PRJDIR		= $(TARGETDIR)/prj
	LD_SCRIPTS	= $(SRCDIR)/linker

# files
	HEX		= $(EXEDIR)/$(TARGET).hex
	BIN		= $(EXEDIR)/$(TARGET).bin
	ELF		= $(EXEDIR)/$(TARGET).elf
	MAP		= $(LSTDIR)/$(TARGET).map
	LSS		= $(LSTDIR)/$(TARGET).lss
	OK		= $(EXEDIR)/$(TARGET).ok

# linker script (chip dependent)
	LD_SCRIPT	= $(CHIP).ld

# STM32 CubeMX generated directory
	CUBEDIR = $(SRCDIR)/STM32
	BLUETOOTH_DIR = $(SRCDIR)/Bluetopia
	BTLIBDIR = $(BLUETOOTH_DIR)/lib/gcc
	BTLIBFILE = Bluetopia_32_M4.fp_HW_FP

# source directories (all *.c, *.cpp and *.S files included)
	DIRS	:= $(SRCDIR)
	DIRS	+= $(CUBEDIR)/Drivers/CMSIS/Device/ST/STM32F4xx/Include $(CUBEDIR)/Drivers/CMSIS/Include
	DIRS	+= $(CUBEDIR)/Drivers/STM32F4xx_HAL_Driver/Src $(CUBEDIR)/Drivers/STM32F4xx_HAL_Driver/Inc 
	DIRS	+= $(CUBEDIR)/Src $(CUBEDIR)/Inc
	DIRS    += $(CUBEDIR)/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc $(CUBEDIR)/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Src
	DIRS	+= $(CUBEDIR)/Middlewares/ST/STM32_USB_Device_Library/Core/Inc $(CUBEDIR)/Middlewares/ST/STM32_USB_Device_Library/Core/Src
	DIRS    += $(CUBEDIR)/Middlewares/Third_Party/FreeRTOS/Source/ $(CUBEDIR)/Middlewares/Third_Party/FreeRTOS/Source/Include
	DIRS    += $(CUBEDIR)/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F $(CUBEDIR)/Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang
	DIRS    += $(CUBEDIR)/Third_Party/FreeRTOS/Source/CMSIS_RTOS $(CUBEDIR)/Middlewares/Third_Party/FreeRTOS/Source/include/
	DIRS    += $(CUBEDIR)/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS/
	DIRS    += $(CUBEDIR)/Drivers/CMSIS/Device/ST/STM32F4xx/Source/Templates/
	DIRS    += $(SRCDIR)/libeeprom
	DIRS	+= $(SRCDIR)/startup
	DIRS    += $(SRCDIR)/wrappers
	DIRS    += $(BLUETOOTH_DIR)/btpskrnl $(BLUETOOTH_DIR)/btpsvend $(BLUETOOTH_DIR)/btvs $(BLUETOOTH_DIR)/hcitrans.dma  $(BLUETOOTH_DIR)/include
	DIRS    += $(SRCDIR)/common
#	DIRS    += $(CUBEDIR)/Drivers/CMSIS/Device/ST/STM32F4xx/Source/Templates/

# includes
	INCS	:= $(patsubst %, -I "%", $(DIRS))

# individual source files
	SRCS	:= 

#calc obj files list
	OBJS	:= $(SRCS)
	OBJS	+= $(wildcard $(addsuffix /*.cpp, $(DIRS)))
	OBJS	+= $(wildcard $(addsuffix /*.c, $(DIRS)))
	OBJS	+= $(wildcard $(addsuffix /*.S, $(DIRS)))
	OBJS	:= $(notdir $(OBJS))
	OBJS	:= $(OBJS:.cpp=.o)
	OBJS	:= $(OBJS:.c=.o)
	OBJS	:= $(OBJS:.S=.o)
	OBJS	:= $(patsubst %, $(OBJDIR)/%, $(OBJS))


# flags
	FLAGS	= -mcpu=$(MCU) -mthumb
	FLAGS	+= $(FPU)
	FLAGS	+= $(INCS)
	FLAGS	+= $(DEFS)
	FLAGS	+= -Wa,-adhlns=$(addprefix $(LSTDIR)/, $(notdir $(addsuffix .lst, $(basename $<))))

	AFLAGS	= $(FLAGS)

	CFLAGS	= $(FLAGS)
	CFLAGS	+= $(OPTIMIZE)
	ifneq (,$(filter-out discovery defines,$(MAKECMDGOALS)))
	CFLAGS	+= -MD 
    endif
	CFLAGS	+= -std=gnu99
	CFLAGS	+= -g
	CFLAGS	+= -pipe
	CFLAGS	+= -ffunction-sections -fdata-sections
	CFLAGS	+= -Wall -Wextra
	CFLAGS	+= -Wimplicit -Wcast-align -Wpointer-arith -Wredundant-decls
	CFLAGS	+= -Wshadow -Wcast-qual -Wnested-externs -pedantic
	CFLAGS  += $(STM32_LIB_WARNING_SUPRESS)

	CXXFLAGS	= $(FLAGS)
	CXXFLAGS	+= $(OPTIMIZE)
ifneq (,$(filter-out discovery defines,$(MAKECMDGOALS)))
	CXXFLAGS	+= -MD 
endif
ifeq ($(USE_CPP11),YES)
	CXXFLAGS	+= -std=c++11
    endif
	CXXFLAGS	+= -g
	CXXFLAGS	+= -pipe
	CXXFLAGS	+= -fno-exceptions -fno-rtti
	CXXFLAGS	+= -ffunction-sections -fdata-sections
	CXXFLAGS	+= -funsigned-bitfields -fshort-enums
	CXXFLAGS	+= -Wall -Wextra
	CXXFLAGS	+= -Winline
	CXXFLAGS	+= -Wpointer-arith -Wredundant-decls
	CXXFLAGS	+= -Wshadow -Wcast-qual -Wcast-align -pedantic -Wno-variadic-macros

	LD_FLAGS	= -mcpu=$(MCU)
	LD_FLAGS	+= -mthumb
	LD_FLAGS	+= $(FPU)
	LD_FLAGS	+= -nostartfiles 
ifeq ($(USE_NANO_LIB),YES)
	LD_FLAGS	+= --specs=nano.specs
#	LD_FLAGS	+= -u _printf_float  
endif
	LD_FLAGS	+= -Wl,-Map="$(MAP)",--cref
	LD_FLAGS	+= -Wl,--gc-sections
	LD_FLAGS	+= -L$(LD_SCRIPTS)
	LD_FLAGS	+= -T$(LD_SCRIPT)
	LD_FLAGS    += -L$(BTLIBDIR) -l$(BTLIBFILE)

ifeq ($(USE_LTO),YES)
	CFLAGS		+= -flto
	CXXFLAGS	+= -flto
	LD_FLAGS	+= -flto $(OPTIMIZE)
endif

#openocd command-line

# debug level (d0..d3)
	OPENOCD_PARAMS		= -d0

# interface and board/target settings (using the OOCD target-library here)
#	OPENOCD_PARAMS		+= -f interface/arm-usb-ocd.cfg 
#	OPENOCD_PARAMS		+= -f $(PRJDIR)/STM32F10X.cfg
	OPENOCD_PARAMS		+= -f board/stm32f4discovery.cfg
	OPENOCD_PARAMS		+= -c init
	OPENOCD_PARAMS		+= -c "sleep 200"

# commands to flash-write
	OPENOCD_PARAMS_LOAD	= $(OPENOCD_PARAMS)
	OPENOCD_PARAMS_LOAD	+= -c "reset halt"
	OPENOCD_PARAMS_LOAD	+= -c "wait_halt"
	OPENOCD_PARAMS_LOAD	+= -c "sleep 200"
	OPENOCD_PARAMS_LOAD	+= -c "flash write_image erase $(ELF)"
	OPENOCD_PARAMS_LOAD	+= -c "verify_image $(ELF)"
	OPENOCD_PARAMS_LOAD	+= -c "reset run"
	OPENOCD_PARAMS_LOAD	+= -c shutdown

# commands to just reset target
	OPENOCD_PARAMS_RESET	= $(OPENOCD_PARAMS)
	OPENOCD_PARAMS_RESET	+= -c "reset run"
	OPENOCD_PARAMS_RESET	+= -c shutdown


.SILENT :

.PHONY: all dirs build clean program protect reset archive docs discovery defines

############# targets

all : 
	@echo --- building $(TARGET). defines: $(DEFS)
	$(MAKE) dirs
	$(MAKE) $(ELF)
	$(MAKE) $(HEX)
	$(MAKE) $(BIN)
	$(MAKE) $(LSS)
	$(SIZE) $(ELF)
	@echo "Errors: none"

patch: clean
	patch -p0 < patches/main.patch
	#for this file patch works in reverse direction (tries to patch the original file) on OSX 10.11. I was unable to figure out the problem.
	#the patch file has the correct format, with --- on original file and +++ on the file needed to be modified. So hardcode the patch
	#into the patch command.
	patch  src/STM32/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS/cmsis_os.h < patches/cmsis_os.patch
	#patch -p0 < patches/cdcCaseFix.patch
	patch src/STM32/Middlewares/Third_Party/FreeRTOS/Source/tasks.c < patches/freertos_tasks.patch
	mv src/STM32/Src/main.c src/STM32/Src/inithw.c
	rm src/STM32/Src/freertos.c

bluetoothPatch: clean
	patch -p0 < patches/btCaseFix1.patch

build:
	$(MAKE) clean
	$(MAKE) all

$(LSS): $(ELF) makefile
	@echo --- making asm-lst...
#	@$(OBJDUMP) -dStC $(ELF) > $(LSS)
	$(OBJDUMP) -dC $(ELF) > $(LSS)

$(ELF):	$(OBJS) $(LIBS) makefile
	@echo --- linking... 
	$(LD) $(OBJS) $(LD_FLAGS) -o "$(ELF)"

$(HEX): $(ELF) makefile
	@echo --- make hex...
	$(OBJCOPY) -O ihex $(ELF) $(HEX)

$(BIN): $(ELF) makefile
	@echo --- make bin...
	$(OBJCOPY) -O binary $(ELF) $(BIN)

program: $(HEX) $(BIN)
	@echo "Programming with $(FLASHER)"
ifeq ($(FLASHER),openocd)
	$(FLASHER) $(OPENOCD_PARAMS_LOAD)
endif
ifeq ($(FLASHER),st-flash)
	$(FLASHER) write $(BIN) 0x08000000
endif
ifeq ($(FLASHER),stm32flash)
	$(FLASHER) -b 115200 -w $(HEX) -v -g 0x0 /dev/ttyS0
#	$(FLASHER) -b 115200 -w $(HEX) -v -g 0x0 COM1
endif
ifeq ($(FLASHER),ST-LINK_CLI)
#	$(FLASHER) -Q -P $(HEX) -V $(HEX) -Run
	$(FLASHER)  -c SWD UR -Q -P $(HEX) -V "while_programming" -Run
endif

protect:
ifeq ($(FLASHER),ST-LINK_CLI)
	$(FLASHER)  -c SWD UR -Q -P $(HEX) -V $(HEX) -OB RDP=1
endif

reset:
	@echo Resetting device
ifeq ($(FLASHER),ST-LINK_CLI)
	$(FLASHER) -Q -Rst
endif
ifeq ($(FLASHER),openocd)
	$(FLASHER) $(OPENOCD_PARAMS_RESET)
endif

docs:
	@echo Creating doxygen docs...
	$(DOXYGEN) $(PRJDIR)/Doxyfile

VPATH := $(DIRS)

$(OBJDIR)/%.o: %.cpp makefile
	@echo --- compiling $<...
	$(CXX) -c $(CXXFLAGS) -o $@ $<

$(OBJDIR)/%.o: %.c makefile
	@echo --- compiling $<...
	$(CC) -c $(CFLAGS) -o $@ $<

$(OBJDIR)/%.o: %.S makefile
	@echo --- assembling $<...
	$(AS) -c $(AFLAGS) -o $@ $<

dirs: $(OBJDIR) $(EXEDIR) $(LSTDIR)

$(OBJDIR):
	-@$(MD) $(OBJDIR)

$(EXEDIR):
	-@$(MD) $(EXEDIR)

$(LSTDIR):
	-@$(MD) $(LSTDIR)


clean:
	-@$(RM) $(TARGETDIR) 2>/dev/null


#discovery target for Eclipse parser
discovery:
ifeq ($(extension),c)
	@echo -- discovery for $(CC)
	$(CC) $(INCS) $(CFLAGS) -E -P -v -dD '$(specs_file)'
else
	@echo -- discovery for $(CCX)
	$(CXX) $(INCS) $(CXXFLAGS) -E -P -v -dD '$(specs_file)'
endif
	$(RM) spec.d
	
defines:
	$(CC) $(CFLAGS) -dM -E - < /dev/null | sort

#do not include dependency info on some targets:
ifneq (,$(filter-out docs build clean dirs discovery,$(MAKECMDGOALS)))
   -include $(wildcard $(OBJDIR)/*.d) 
endif
