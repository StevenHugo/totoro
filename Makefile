VERSION := 0
SUBVERSION := 13
PATCHVERSION := .7
TOTORO_VERSION := $(VERSION).$(SUBVERSION)$(PATCHVERSION)
IMAGE = TOTORO-$(TOTORO_VERSION)

TOOLS_PREFIX = arm-none-eabi-
CC      := $(TOOLS_PREFIX)gcc
AS      := $(TOOLS_PREFIX)as
LD      := $(TOOLS_PREFIX)ld
CPP     := $(TOOLS_PREFIX)cpp
OBJCOPY := $(TOOLS_PREFIX)objcopy

KERNEL_SOURCE = arch drivers include kernel scripts test ports/README.md
KERNEL_HEADER = arch include test ports
KERNEL_OBJS = arch/sys.o \
	kernel/kernel.o kernel/taskq.o kernel/sem.o kernel/timer.o \
	drivers/clock/clock.o drivers/gpio/gpio.o

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $< $(INCLUDES)
%.o: %.S
	$(CC) -c -o $@ $<

.PHONY: all clean backup help info tags cscope

all: $(OBJS)
	$(CC) -o ${IMAGE} $(OBJS) $(LDFALGS)

backup:
	tar -zcvf totoro-$(TOTORO_VERSION).tar.gz $(KERNEL_SOURCE)

help:
	@echo 'totoro making decision'
	@echo 'make [option]'
	@echo 'options:'
	@echo '  help            display this'
	@echo '  backup          back up this project'
	@echo '                  generate totoro-x.x.x.tar.gz at parent directory'
	@echo '  info            display the infos of:'
	@echo '                    arch to be build for'
	@echo '                    cross toolchain to build with'
	@echo '                    totoro kernel version to be build'
	@echo '  md5             calculate md5 checksum'
	@echo '  clean           clean working space'

info:
	@echo Building architecture: $(ARCH)
	@echo Building toochain: $(TOOLS_PREFIX)
	@echo Totoro version: $(TOTORO_VERSION)

md5:
	@make backup
	md5sum totoro-$(TOTORO_VERSION).tar.gz

tags:
	touch cscope.files cscope.files.sorted tags; > cscope.files; > tags
	for n in $(KERNEL_SOURCE); do find $$n | grep "\.c$$\|\.h$$" >> cscope.files; done
	sort cscope.files > cscope.files.sorted; mv cscope.files.sorted cscope.files
	ctags -f tags -L cscope.files

cscope:
	cscope -b

clean:
	rm -rf $(OBJS) ${IMAGE}

distclean:
	@make clean
	rm -rf cscope.files cscope.out tags
