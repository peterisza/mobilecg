#+---------------------------------------------------------------------------
#
#  Copyright (c) 2010 Anton Gusev aka AHTOXA (HTTP://AHTOXA.NET)
#
#  Modified by xdever
#
#  File:       makefile
#
#  Contents:   makefile to build ADuc7061 ARM software with gcc
#
#----------------------------------------------------------------------------

#############  program name
	TARGET	= CardECG

	TOOL	= arm-none-eabi-
#	TOOL	= arm-kgp-eabi-

	PORT    = /dev/tty.usbserial

# compile options 
	MCU			= arm7tdmi
	CHIP		= ADUC7061
	OPTIMIZE	= -O2
	USE_LTO		= NO

###########################################################
#  common part for all my ADUC7061 projects
###########################################################

	BASE		= .
	OUTBASE     = output
	CC			= $(TOOL)gcc
	CXX			= $(TOOL)g++
	LD			= $(TOOL)g++
	AS			= $(CC) -x assembler-with-cpp
	OBJCOPY		= $(TOOL)objcopy
	OBJDUMP		= $(TOOL)objdump
	SIZE		= $(TOOL)size -d
	RAR			= rar
	RM			= rm -f
	CP			= cp
	MD			= mkdir -p

#  dirs
	SRCDIR		= $(BASE)/src
	OBJDIR		= $(OUTBASE)/obj
	EXEDIR		= $(OUTBASE)/exe
	LSTDIR		= $(OUTBASE)/lst
	PRJDIR		= $(OUTBASE)/prj
	BAKDIR		= $(OUTBASE)/bak

#files
	HEX		= $(EXEDIR)/$(TARGET).hex
	ELF		= $(EXEDIR)/$(TARGET).elf
	BIN		= $(EXEDIR)/$(TARGET).bin
	MAP		= $(LSTDIR)/$(TARGET).map
	LSS		= $(LSTDIR)/$(TARGET).lss
	OK		= $(EXEDIR)/$(TARGET).ok

# scmRTOS dir
	SCMDIR		= scmRTOS
	COMMON		= common

# linker script
	LD_SCRIPT	= $(COMMON)/ADUC7061-ROM.ld

# files
	DIRS	:= $(SRCDIR)
	DIRS	+= $(COMMON)
	DIRS	+= $(SCMDIR)/Common $(SCMDIR)/ARM7

	INCS	:= $(patsubst %, -I "%", $(DIRS))
	SRCS	:= $(wildcard $(addsuffix /*.cpp, $(DIRS))) $(wildcard $(addsuffix /*.c, $(DIRS))) $(wildcard $(addsuffix /*.S, $(DIRS)))
	OBJS	:= $(notdir $(SRCS) )
	OBJS	:= $(OBJS:.cpp=.o)
	OBJS	:= $(OBJS:.c=.o)
	OBJS	:= $(OBJS:.S=.o)
	OBJS	:= $(OBJS:.s=.o)
	OBJS	:= $(patsubst %, $(OBJDIR)/%, $(OBJS))

#files to archive
	ARCFILES	= \
		$(SRCDIR) \
		$(PRJDIR) \
		$(SCMDIR) \
		$(LIBDIR) \
		$(BASE)/makefile \
		$(BASE)/.cproject \
		$(BASE)/.project

# flags
	FLAGS	= -mcpu=$(MCU)
#	FLAGS	+= -mthumb-interwork
	FLAGS	+= -g -gdwarf-2
	FLAGS	+= $(INCS)
	FLAGS	+= -MD
	FLAGS	+= -D$(CHIP)
	FLAGS	+= -Wa,-adhlns=$(addprefix $(LSTDIR)/, $(notdir $(addsuffix .lst, $(basename $<))))

	AFLAGS	= $(FLAGS)

	CFLAGS	= $(FLAGS)
	CFLAGS	+= $(OPTIMIZE)
	CFLAGS	+= -std=gnu99
	CFLAGS	+= -ffunction-sections -fdata-sections
	CFLAGS	+= -Wall -Wextra
	CFLAGS	+= -Wimplicit -Wcast-align -Wpointer-arith -Wredundant-decls
	CFLAGS	+= -Wshadow -Wcast-qual -Wcast-align -Wnested-externs -pedantic
	
	CXXFLAGS	= $(FLAGS)
	CXXFLAGS	+= $(OPTIMIZE)
	CXXFLAGS	+= -fno-exceptions -fno-rtti
	CXXFLAGS	+= -ffunction-sections -fdata-sections
	CXXFLAGS	+= -funsigned-bitfields -fshort-enums
	CXXFLAGS	+= -Wall -Wextra
	CXXFLAGS	+= -Winline
	CXXFLAGS	+= -Wcast-align -Wpointer-arith
	CXXFLAGS	+= -Wshadow -Wcast-qual -Wcast-align -pedantic
	CXXFLAGS    += -fno-use-cxa-atexit
	
	LD_FLAGS	= -mcpu=$(MCU)
	LD_FLAGS	+= -nostartfiles 
	LD_FLAGS	+= -Wl,-Map="$(MAP)",--cref
	LD_FLAGS	+= -fno-exceptions -fno-rtti	
	LD_FLAGS	+= -Wl,--gc-sections
	LD_FLAGS	+= -T$(LD_SCRIPT)
	


ifeq ($(USE_LTO),YES)
	CFLAGS		+= -flto
	CXXFLAGS	+= -flto
	LD_FLAGS	+= -flto $(OPTIMIZE)
endif

.SILENT :

.PHONY: all dirs build clean program reset archive info

############# targets

all : dirs $(ELF) $(HEX) $(LSS) $(OK)

build: clean all


$(LSS): $(ELF) makefile
	@echo --- making asm-lst...
	$(OBJDUMP) -dC $(ELF) > $(LSS)

info:
	$(CC) -E -P -v -dD $(CFLAGS) ./src/sys.c

$(OK): $(ELF)
	$(SIZE) $(ELF)
	@echo "Errors: none"

$(ELF):	$(OBJS) makefile
	@echo --- linking...
	$(LD) $(OBJS) $(LD_FLAGS) -o $(ELF)

$(HEX): $(ELF)
	@echo --- make hex...
	$(OBJCOPY) -O ihex $(ELF) $(HEX)
#	$(OBJCOPY) -O binary $(ELF) $(BIN)

$(EXEDIR)/aducloader : loader/aducloader.c
	gcc -Wall -O2 -g -DADUCLOADER_VERSION='"0.1-xdever"' -o $@ $<
	rm -rf $(EXEDIR)/aducloader.*

program: all $(EXEDIR)/aducloader
	@echo "Programming..."
	$(WINE) $(FLASHER) $(F_FLAGS)
	
	$(EXEDIR)/aducloader --ttyfile=$(PORT) --ihexfile $(HEX) --baudrate=38400 --reset
	
	
killwine:
	-@$(kill -9 `ps aux|grep -i armwsd|awk '{print $2}'`)

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

dirs: $(OBJDIR) $(EXEDIR) $(LSTDIR) $(BAKDIR)

$(OBJDIR):
	-@$(MD) $(OBJDIR)

$(EXEDIR):
	-@$(MD) $(EXEDIR)

$(LSTDIR):
	-@$(MD) $(LSTDIR)

$(BAKDIR):
	-@$(MD) $(BAKDIR)

clean:
	-@$(RM) -rf $(OUTBASE)

archive:
	@echo --- archiving...
	7z a $(BAKDIR)/$(TARGET)_`date +%Y-%m-%d,%H-%M-%S` $(ARCFILES)
	@echo --- done!

ifeq (,$(findstring build,$(MAKECMDGOALS)))
 ifeq (,$(findstring clean,$(MAKECMDGOALS)))
  ifeq (,$(findstring dirs,$(MAKECMDGOALS)))
  -include $(wildcard $(OBJDIR)/*.d) 
  endif
 endif
endif
